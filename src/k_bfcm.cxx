#include"k_bfcm.h"

K_BFCM::K_BFCM(int dimension,
	       int data_number,
	       int centers_number,
	       double fuzzifierEm,
	       double sigma): 
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  BFCM(dimension, data_number, centers_number, fuzzifierEm),
  K_(dimension, data_number, centers_number, sigma){
}

void K_BFCM::revise_kernelcenters(void){
#ifdef CHECK_CLASS
  std::cout<<"K_bfcm::revise_kernlcenters"<<std::endl;
#endif
  Tmp_KernelCenters=KernelCenters;
  for(int i=0;i<centers_number();i++){
    double denominator=0.0;
    Vector numerator(data_number(), 0.0, "all");
    for(int k=0;k<data_number();k++){
      denominator+=pow(Membership[i][k],FuzzifierEm);
      numerator+=pow(Membership[i][k],FuzzifierEm)*UnitData[k];
    }
    KernelCenters[i]=numerator/denominator;
  }
  return;
}
