#include"epcs.h"

EPCS::EPCS(int dimension,
	   int data_number,
	   int centers_number,
	   double fuzzifierLambda,
	   double alpha): 
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  KLFCS(dimension, data_number, centers_number, fuzzifierLambda),
  PCM(dimension, data_number, centers_number, alpha){
}

void EPCS::revise_membership(void){
#ifdef CHECK_CLASS
  std::cout<<"EPCS::revise_membership"<<std::endl;
#endif
  Tmp_Membership=Membership;
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Membership[i][k]=
	exp(FuzzifierLambda*(Alpha-Dissimilarities[i][k])-1.0);
    }
  }
  return;
}

void EPCS::revise_centers(void){
  KLFCS::revise_centers();
  return;
}


void EPCS::set_objective(void){
  Objective=0.0;
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Objective+=Membership[i][k]*Dissimilarities[i][k]
	+(1.0/FuzzifierLambda)*Membership[i][k]
	*log(Membership[i][k])
	-Alpha*Membership[i][k];
    }
  }
  return;
}
