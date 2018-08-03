#include"k_bfcs.h"

K_BFCS::K_BFCS(int dimension,
	       int data_number,
	       int centers_number,
	       double fuzzifierEm,
	       double sigma):
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  BFCS(dimension, data_number, centers_number, fuzzifierEm),
  K_(dimension, data_number, centers_number, sigma){
}

void K_BFCS::revise_kernelcenters(void){
#ifdef CHECK_CLASS
  std::cout<<"k_bfcs::revise_kernlcenters"<<std::endl;
#endif
  Tmp_KernelCenters=KernelCenters;
  for(int i=0;i<centers_number();i++){
    Vector numerator(data_number(), 0.0, "all");
    for(int k=0;k<data_number();k++)
      numerator+=pow(Membership[i][k],FuzzifierEm)*UnitData[k];
    KernelCenters[i]=numerator/squared_norm(numerator);
  }
  return;
}

void K_BFCS::revise_dissimilarities(void){
  Tmp_Dissimilarities=Dissimilarities;
  for(int i=0;i<centers_number();i++){
    Vector numerator(data_number(), 0.0, "all");
    double denominator=0.0;
    for(int k=0;k<data_number();k++){
      numerator[k]=0.0;
      for(int ell=0;ell<data_number();ell++)
	numerator[k]+=pow(Membership[i][ell], FuzzifierEm)*Kernel[k][ell];
    }
    for(int r=0;r<data_number();r++)
      denominator+=numerator[r]*pow(Membership[i][r], FuzzifierEm);
    for(int k=0;k<data_number();k++)
      Dissimilarities[i][k]=-numerator[k]/sqrt(denominator);
  }
  return;
}
