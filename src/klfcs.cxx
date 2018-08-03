#include"klfcs.h"

KLFCS::KLFCS(int dimension,
	     int data_number,
	     int centers_number,
	     double fuzzifierLambda): 
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  HCS(dimension, data_number, centers_number),
  KLFCM(dimension, data_number, centers_number, fuzzifierLambda){
}

void KLFCS::revise_centers(void){
#ifdef CHECK_CLASS
  std::cout<<"KLFCS::revise_centers"<<std::endl;;
#endif
  Tmp_Centers=Centers;
  for(int i=0;i<centers_number();i++){
    Vector numerator(dimension(), 0.0, "all");
    for(int k=0;k<data_number();k++){
      for(int ell=0;ell<Data[k].essencialSize();ell++){
        numerator[Data[k].indexIndex(ell)]
          +=Membership[i][k]*Data[k].elementIndex(ell);
      }
    }
    Centers[i]=numerator/squared_norm(numerator);
  }
  return;
}
