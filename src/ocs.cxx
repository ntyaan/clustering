#include"ocs.h"

OCS::OCS(int dimension,
	 int data_number,
	 int centers_number,
	 int number_of_missing_values):
  HCM(dimension, data_number, centers_number),
  CorrectData(data_number, dimension),
  IncompleteIndex(data_number, dimension),
  NumberOfMissingValues(number_of_missing_values){
}

double OCS::incompleteindex(int index1, int index2){
  return IncompleteIndex[index1][index2];
}

SparseMatrix OCS::correctdata(void){
  return CorrectData;
}

SparseVector OCS::correctdata(int index){
  return CorrectData[index];
}

void OCS::IncompleIndexForRecom(const Matrix &Index){
  for(int index=0;index<NumberOfMissingValues;index++)
    IncompleteIndex[Index[index][0]][Index[index][1]]=1.0;
  return;
}

Vector OCS::PredictionForRecom(const Matrix &IndexRow,
			       const Vector &IndexCol){
  Vector Prediction(IndexRow.rows());
  for(int index=0;index<NumberOfMissingValues;index++)
    Prediction[index]
      = Data[IndexRow[index][0]].elementIndex(IndexCol[index]);
  return Prediction;
}

Vector OCS::PredictionForRecomForSpherical(const Matrix &IndexRow,
					   const Vector &IndexCol,
					   const SparseMatrix &SD){
  Vector Prediction(IndexRow.rows());
  for(int index=0;index<NumberOfMissingValues;index++){
    double sum=0.0;
    for(int ell=0;ell<SD[IndexRow[index][0]].essencialSize();ell++)
      sum+=pow(SD[IndexRow[index][0]].elementIndex(ell), 2.0);
    Prediction[index]
      = Data[IndexRow[index][0]].elementIndex(IndexCol[index])*sum;
  }
  return Prediction;
}

void OCS::revise_data(void){
  return;
}

void OCS::set_missing_values(int seed_of_random_number,
			     int missing_at_a_time){
  CorrectData=Data;
  if(missing_at_a_time*NumberOfMissingValues==0)
    return;
  int tmprow, tmpcol, ell, count;
  int current_missing_number=0;
  std::mt19937_64 mt; 
  mt.seed(seed_of_random_number);
  while(1){
    //欠損させる要素の行番号を決定
    while(1){
      count = 0;
      std::uniform_int_distribution<>
	randRow(0,data_number()-1);
      tmprow=randRow(mt);
      for(int ell=0; ell<Data[tmprow].essencialSize();ell++)
	if(IncompleteIndex[tmprow][Data[tmprow].indexIndex(ell)]==1.0)
          count++;
      //その行に対して欠損させた要素数が元々の要素数-2より小さかったら
      if(count<Data[tmprow].essencialSize()-2)
        break;
    }
    //欠損させる列番号を決定
    for(ell=0; ell<missing_at_a_time;){
      std::uniform_int_distribution<>
	randCol(0,Data[tmprow].essencialSize()-1);
      tmpcol=randCol(mt);
      if(IncompleteIndex[tmprow][Data[tmprow].indexIndex(tmpcol)]!=1.0){
	Data[tmprow].elementIndex(tmpcol)=0.0;
        IncompleteIndex[tmprow][Data[tmprow].indexIndex(tmpcol)]
	  =1.0;
	current_missing_number++;
	if(current_missing_number==NumberOfMissingValues)
	  return;
	ell++;
      }
    }
  }
}
