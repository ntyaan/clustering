#include"hccmp.h"

HCCMP::HCCMP(int dimension,
	     int data_number,
	     int centers_number):
  HCM(dimension, data_number, centers_number),
  Data_k(data_number),
  Alpha_i(centers_number){
}

void HCCMP::data_k(void){
  for(int k=0;k<data_number();k++){
    Data_k[k]=0.0;
    for(int ell=0;ell<Data[k].essencialSize();ell++)
      Data_k[k]+=Data[k].elementIndex(ell);
  }
  return;
}

void HCCMP::alpha_i(void){
  for(int i=0;i<centers_number();i++){
    Alpha_i[i]=0.0;
    for(int ell=0;ell<dimension();ell++)
      Alpha_i[i]+=Centers[i][ell];
  }
  return;
}

void HCCMP::revise_dissimilarities(void){
#ifdef CHECK_CLASS
  std::cout<<"HCCMP::revise_dissimilarities"<<std::endl;;
#endif
  alpha_i();
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      double sum=0.0;
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	if(Centers[i][Data[k].indexIndex(ell)]>0.0){
	  sum+=boost::math::lgamma(Data[k].elementIndex(ell)
				   +Centers[i][Data[k].indexIndex(ell)])
	    -boost::math::lgamma(Centers[i][Data[k].indexIndex(ell)]);
	}
      }
      Dissimilarities[i][k]=-boost::math::lgamma(Alpha_i[i])
	+boost::math::lgamma(Alpha_i[i]+Data_k[k])-sum;
    }
  }
  return;
}
