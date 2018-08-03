#include"hccm.h"

HCCM::HCCM(int dimension,
	   int data_number,
	   int centers_number):
  HCM(dimension, data_number, centers_number){
}

void HCCM::revise_dissimilarities(void){
#ifdef CHECK_CLASS
  std::cout<<"HCCM::revise_dissimilarities"<<std::endl;;
#endif
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Dissimilarities[i][k]=0.0;
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	if(Centers[i][Data[k].indexIndex(ell)]>0.0){
	  Dissimilarities[i][k]
	    -=log(Centers[i][Data[k].indexIndex(ell)])
	    *Data[k].elementIndex(ell);
	}
      }
    }
  }   
  return;
}

void HCCM::initialize_centers_dissimilarities(int index){
  for(int i=0;i<index+1;i++){
    for(int k=0;k<data_number();k++){
      Dissimilarities[i][k]=0.0;
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	if(Centers[i][Data[k].indexIndex(ell)]>0)
	  Dissimilarities[i][k]
	    -=log(Centers[i][Data[k].indexIndex(ell)])
	    *Data[k].elementIndex(ell);
      }
    }
  }   
  return;
}

void HCCM::ForMMMData(void){
  for(int k=0;k<data_number();k++){
    double sum=0.0;
    for(int ell=0;ell<Data[k].essencialSize();ell++)
      sum+=Data[k].elementIndex(ell);
    for(int ell=0;ell<Data[k].essencialSize();ell++)
      Data[k].elementIndex(ell)=Data[k].elementIndex(ell)/sum;
  }
  return;
}
