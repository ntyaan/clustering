#include"rfcm.h"

RFCM::RFCM(int dimension,
	   int data_number,
	   int centers_number):
  HCM(dimension, data_number, centers_number),
  Kernel(data_number,data_number),
  UnitMatrixData(data_number,"I"){
}

void RFCM::copy_similarities(const Matrix &arg){
  Kernel=arg;
  return;
}

void RFCM::revise_dissimilarities(void){
  bool negativeFlag=false;
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Dissimilarities[i][k]=
	(UnitMatrixData[k]-Centers[i])
	*(Kernel*(UnitMatrixData[k]-Centers[i]));
      /***ここから神澤追加***/
      if(Dissimilarities[i][k]<0.0){
	negativeFlag=true;
      }
      /***ここまで神澤追加*下にもあり****/
    }}
  /***ここから神澤改訂***/
  if(negativeFlag){
    double tmp_beta=0.0,beta=0.0;
    Matrix CentersT=transpose(Centers);
    for(int i=0;i<centers_number();i++){
      double CentersInnerproduct=Centers[i]*Centers[i];
      for(int k=0;k<data_number();k++){
	//std::cout<<"i="<<i<<" k="<<k<<std::endl;
	tmp_beta=-2.0*Dissimilarities[i][k]/
	  (1.0-2.0*Centers[i][k]+CentersInnerproduct);
	if(tmp_beta<0.0)
	  tmp_beta=0.0;
	if(beta<tmp_beta)
	  beta=tmp_beta;
	//std::cout<<"beta="<<beta<<" original_Dissimilarities[i][k]="
	//<<Dissimilarities[i][k]<<std::endl;
      }
    }
    for(int i=0;i<centers_number();i++){
      double CentersInnerproduct=Centers[i]*Centers[i];
      for(int k=0;k<data_number();k++){
	double tmp1=beta*(1.0-2.0*Centers[i][k]+CentersInnerproduct);
	//std::cout<<"Centers[i][k]="<<Centers[i][k]<<std::endl;
	//std::cout<<"tmp1="<<tmp1<<std::endl;
	Dissimilarities[i][k]+=tmp1;
	//std::cout<<"Dissimilarities[i][k]="
	//<<Dissimilarities[i][k]<<std::endl;
	//std::cout<<std::endl;
      }
    }
  }//if(negativeFlag)
  /***ここまで神澤改訂******************************************/
  return;
}

void RFCM::centersInitializePlusPlus(int random_index){
  //  static std::mt19937 mt2(0);
  static std::mt19937_64 mt;
  static std::uniform_int_distribution<>
    randDataNumber(0,data_number()-1);
  mt.seed(random_index);
  InitializeC[0]=randDataNumber(mt);
  for(int ell=0;ell<dimension();ell++){
    Centers[0][ell]=UnitMatrixData[InitializeC[0]][ell];
  }
  for(int tentativeCentersNumber=1;
      tentativeCentersNumber<centers_number();tentativeCentersNumber++){
    Vector rangeStarts(data_number()+1, 0.0, "all");
    for(int k=1;k<data_number()+1;k++){
      double min=DBL_MAX;
      for(int i=0;i<tentativeCentersNumber;i++){
	double tentativeDissimilarity=
	  (UnitMatrixData[k-1]-Centers[i])
	  *(Kernel*(UnitMatrixData[k-1]-Centers[i]));
	if(tentativeDissimilarity<min){
	  min=tentativeDissimilarity;
	}
      }
      rangeStarts[k]=min;
    }
    double sum=rangeStarts*Vector(data_number()+1, 1.0, "all");
    for(int k=1;k<data_number()+1;k++){
      rangeStarts[k]/=sum;
    }
    rangeStarts[0]=0.0;
    for(int k=1;k<rangeStarts.size();k++){
      rangeStarts[k]=rangeStarts[k-1]+rangeStarts[k];
    }
    std::uniform_real_distribution<double> targetFunc(0.0, 1.0);
    double target=targetFunc(mt);
    int start=0, end=data_number()+1;
    while(1){
      int mid=(start+end)/2;
      if(target<rangeStarts[mid]){
	end=mid-1;
      }
      else if(target>rangeStarts[mid+1]){
	start=mid+1;
      }
      else{
	for(int ell=0;ell<dimension();ell++){
	  Centers[tentativeCentersNumber][ell]
	    =UnitMatrixData[mid][ell];
	}
	InitializeC[tentativeCentersNumber]=mid;
	break;
      }
    }
  }//tentativeCentersNumber
  return;
}
