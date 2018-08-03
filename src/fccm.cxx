#include"../src/fccm.h"

FCCM::FCCM(int dimension,
	   int data_number,
	   int centers_number,
	   double fuzzifierLambda,
	   double fuzzifierLambda2):
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  KLFCM(dimension, data_number
	, centers_number,fuzzifierLambda),
  FuzzifierLambda2(fuzzifierLambda2){
}

double &FCCM::fuzzifierLambda2(void){
  return FuzzifierLambda2;
}

void FCCM::revise_dissimilarities(void){
#ifdef CHECK_CLASS
  std::cout<<"FCCM::revise_dissimilarities"<<std::endl;;
#endif
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Dissimilarities[i][k]=0.0;
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	Dissimilarities[i][k]
	  -=Centers[i][Data[k].indexIndex(ell)]
	  *Data[k].elementIndex(ell);
      }
    }
  }   
  return;
}

void FCCM::revise_centers(void){
#ifdef CHECK_CLASS
  std::cout<<"FCCM::revise_centers"<<std::endl;;
#endif
  Tmp_Centers=Centers;
  for(int i=0;i<centers_number();i++){
    Vector numerator(dimension());
    for(int ell=0;ell<dimension();ell++)
      numerator[ell]=0.0;
    for(int k=0;k<data_number();k++){
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	numerator[Data[k].indexIndex(ell)]
	  +=Membership[i][k]
	  *Data[k].elementIndex(ell);
      }
    }
    for(int ell=0;ell<dimension();ell++){
      double denominator=0.0;
      for(int r=0;r<dimension();r++)
	denominator+=
	  exp(FuzzifierLambda2
	      *(numerator[r]-numerator[ell]));
      Centers[i][ell]=1.0/denominator;
    }
  }
  return;
}


void FCCM::initialize_centers_dissimilarities(int index){
  for(int k=0;k<data_number();k++){
    for(int i=0;i<index+1;i++){
      Dissimilarities[i][k]=0.0;
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	Dissimilarities[i][k]
	  -=Centers[i][Data[k].indexIndex(ell)]
	  *Data[k].elementIndex(ell);
      }
    }
  }
  return;
}

void FCCM::set_objective(void){
  Objective=0.0;
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Objective+=Membership[i][k]*Dissimilarities[i][k];
      Objective+=(1.0/FuzzifierLambda)*Membership[i][k]
        *log(Membership[i][k]/Clusters_size[i]);
    }
    for(int ell=0;ell<dimension();ell++){
      Objective+=(1.0/FuzzifierLambda2)*Centers[i][ell]
	*log(Centers[i][ell]);
    }
  }
  return;
}
