#include"hccmm.h"

HCCMM::HCCMM(int dimension,
	     int data_number,
	     int centers_number,
	     double fuzzifierEt):
  HCM(dimension, data_number, centers_number),
  HCCM(dimension, data_number, centers_number),
  FuzzifierEt(fuzzifierEt){
}

double &HCCMM::fuzzifierEt(void){
  return FuzzifierEt;
}

void HCCMM::revise_dissimilarities(void){
#ifdef CHECK_CLASS
  std::cout<<"HCCMM::revise_dissimilarities"<<std::endl;;
#endif
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Dissimilarities[i][k]=0.0;
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	Dissimilarities[i][k]-=(1.0/FuzzifierEt)
	  *(pow(Centers[i][Data[k].indexIndex(ell)],FuzzifierEt)-1.0)
	  *Data[k].elementIndex(ell);
      }
    }
  }
  return;
}

void HCCMM::initialize_centers_dissimilarities(int index){
  for(int i=0;i<index+1;i++){
    for(int k=0;k<data_number();k++){
      Dissimilarities[i][k]=0.0;
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	Dissimilarities[i][k]
	  -=(1.0/FuzzifierEt)
	  *(pow(Centers[i][Data[k].indexIndex(ell)],FuzzifierEt)-1.0)
	  *Data[k].elementIndex(ell);
      }
    }
  }   
  return;
}
