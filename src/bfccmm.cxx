#include"bfccmm.h"

BFCCMM::BFCCMM(int dimension,
	       int data_number,
	       int centers_number,
	       double fuzzifierEm,
	       double fuzzifierEt):
  HCM(dimension, data_number, centers_number),
  HCCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  HCCMM(dimension, data_number, centers_number, fuzzifierEt),
  BFCM(dimension, data_number, centers_number,fuzzifierEm){
}

void BFCCMM::revise_centers(void){
#ifdef CHECK_CLASS
  std::cout<<"BFCCMM::revise_centers"<<std::endl;;
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
    for(int ell=0;ell<dimension();ell++)
      Centers[i][ell]=pow(numerator[ell]/denominator,
			  1.0/(1.0-FuzzifierEt));
  }
  return;
}
