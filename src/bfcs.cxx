#include"bfcs.h"

BFCS::BFCS(int dimension,
	   int data_number,
	   int centers_number,
	   double fuzzifierEm): 
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  HCS(dimension, data_number, centers_number),
  BFCM(dimension, data_number, centers_number, fuzzifierEm){
}

void BFCS::revise_centers(void){
#ifdef CHECK_CLASS
  std::cout<<"BFCS::revise_centers"<<std::endl;
#endif
  Tmp_Centers=Centers;
  for(int i=0;i<centers_number();i++){
    Vector numerator(dimension(), 0.0, "all");
    for(int k=0;k<data_number();k++){
      for(int ell=0;ell<Data[k].essencialSize();ell++){
        numerator[Data[k].indexIndex(ell)]
          +=pow(Membership[i][k],FuzzifierEm)*Data[k].elementIndex(ell);
      }
    }
    Centers[i]=numerator/squared_norm(numerator);
  }
  return;
}
