#include"../src/fccmb.h"

FCCMB::FCCMB(int dimension,
	     int data_number,
	     int centers_number,
	     double fuzzifierEm,
	     double fuzzifierEm2):
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  BFCM(dimension, data_number, centers_number,fuzzifierEm),
  FuzzifierEm2(fuzzifierEm2){
}

double &FCCMB::fuzzifierEm2(void){
  return FuzzifierEm2;
}

void FCCMB::revise_dissimilarities(void){
#ifdef CHECK_CLASS
  std::cout<<"FCCMB::revise_dissimilarities"<<std::endl;;
#endif
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Dissimilarities[i][k]=0.0;
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	Dissimilarities[i][k]
	  -=pow(Centers[i][Data[k].indexIndex(ell)], FuzzifierEm2)
	  *Data[k].elementIndex(ell);
      }
    }
  }
  return;
}

void FCCMB::revise_centers(void){
#ifdef CHECK_CLASS
  std::cout<<"FCCMB::revise_centers"<<std::endl;;
#endif
  Tmp_Centers=Centers;
  for(int i=0;i<centers_number();i++){
    Vector numerator(dimension());
    for(int ell=0;ell<dimension();ell++)
      numerator[ell]=0.0;
    for(int k=0;k<data_number();k++){
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	numerator[Data[k].indexIndex(ell)]
	  +=pow(Membership[i][k], FuzzifierEm)
	  *Data[k].elementIndex(ell);
      }
    }
    for(int ell=0;ell<dimension();ell++){
      double denominator=0.0;
      for(int r=0;r<dimension();r++)
	denominator+=
	  pow(numerator[r]/numerator[ell], 1.0/(1.0-FuzzifierEm2));
      Centers[i][ell]=1.0/denominator;
    }
  }
  return;
}

void FCCMB::initialize_centers_dissimilarities(int index){
  for(int k=0;k<data_number();k++){
    for(int i=0;i<index+1;i++){
      Dissimilarities[i][k]=0.0;
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	Dissimilarities[i][k]
	  -=pow(Centers[i][Data[k].indexIndex(ell)], FuzzifierEm2)
	  *Data[k].elementIndex(ell);
      }
    }
  }   
  return;
}
