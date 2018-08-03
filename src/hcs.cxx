#include"hcs.h"

HCS::HCS(int dimension,
	 int data_number,
	 int centers_number):
  HCM(dimension, data_number, centers_number){
}

void HCS::revise_dissimilarities(void){
#ifdef CHECK_CLASS
  std::cout<<"HCS::revise_dissimilarities"<<std::endl;;
#endif
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Dissimilarities[i][k]=0.0;
      for(int ell=0;ell<Data[k].essencialSize();ell++){
        Dissimilarities[i][k]
          +=Data[k].elementIndex(ell)*Centers[i][Data[k].indexIndex(ell)];
      }
      Dissimilarities[i][k]=1.0-Dissimilarities[i][k];
    }
  }
  return;
}

void HCS::initialize_centers_dissimilarities(int index){
  for(int i=0;i<index+1;i++){
    for(int k=0;k<data_number();k++){
      Dissimilarities[i][k]=0.0;
      for(int ell=0;ell<Data[k].essencialSize();ell++){
        Dissimilarities[i][k]
          +=Data[k].elementIndex(ell)*Centers[i][Data[k].indexIndex(ell)];
      }
      Dissimilarities[i][k]=1.0-Dissimilarities[i][k];
    }
  }
  return;
}

void HCS::ForSphericalData(void){
  for(int k=0;k<data_number();k++){
    double sum=0.0;
    for(int ell=0;ell<Data[k].essencialSize();ell++)
      sum+=pow(Data[k].elementIndex(ell),2.0);
    for(int ell=0;ell<Data[k].essencialSize();ell++)
      Data[k].elementIndex(ell)/=sqrt(sum);
  }
  return;
}
