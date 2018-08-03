#include"qfccm.h"

QFCCM::QFCCM(int dimension,
	     int data_number,
	     int centers_number,
	     double fuzzifierEm,
	     double fuzzifierLambda):
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  HCCM(dimension, data_number, centers_number),
  QFCM(dimension, data_number ,centers_number, fuzzifierEm, fuzzifierLambda){
}

void QFCCM::revise_centers(void){
#ifdef CHECK_CLASS
  std::cout<<"QFCCM::revise_centers"<<std::endl;
#endif
  Tmp_Centers=Centers;
  for(int i=0;i<centers_number();i++){
    double denominator=0.0;
    Vector numerator(Centers[i].size());
    for(int ell=0;ell<numerator.size();ell++)
      numerator[ell]=0.0;
    for(int k=0;k<data_number();k++){
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	numerator[Data[k].indexIndex(ell)]
	  +=pow(Membership[i][k],FuzzifierEm)
	  *Data[k].elementIndex(ell);
	denominator+=pow(Membership[i][k],FuzzifierEm)
	  *Data[k].elementIndex(ell);
      }
    }
    Centers[i]=numerator/denominator;
  }
  return;
}
