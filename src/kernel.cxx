#include"kernel.h"

K_::K_(int dimension,
       int data_number,
       int centers_number,
       double sigma):
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  Sigma(sigma),
  Kernel(data_number, data_number),
  KernelCenters(centers_number, data_number),
  Tmp_KernelCenters(centers_number, data_number),
  Tmp_Dissimilarities(centers_number, data_number),
  UnitData(data_number, "I"){
  for(int i=0;i<centers_number;i++)
    for(int k=0;k<data_number;k++){
      KernelCenters[i][k]=DBL_MAX;
      Dissimilarities[i][k]=DBL_MAX;
    }
}

double &K_::sigma(void){
  return Sigma;
}

Matrix K_::kernelcenters(void) const{
  return KernelCenters;
}

Matrix K_::tmp_kernelcenters(void) const{
  return Tmp_KernelCenters;
}

Matrix K_::tmp_dissimilarities(void) const{
  return Tmp_Dissimilarities;
}

void K_::calcurate_kernel(void){
  for(int k1=0;k1<data_number();k1++){
    int Sz1=Data[k1].essencialSize();
    for(int k2=0;k2<data_number();k2++){
      int L1=0, L2=0, Sz2=Data[k2].essencialSize();
      int index1_end=0,index2_end=0;
      double V=0.0;
      while(1){
	if(index1_end*index2_end==1.0)
	  break;
	else if(index1_end+index2_end==0){
	  if(Data[k1].indexIndex(L1)==Data[k2].indexIndex(L2)){
	    V+=pow(Data[k1].elementIndex(L1)
		   -Data[k2].elementIndex(L2), 2.0);
	    L1++;
	    L2++;
	  }
	  else if(Data[k1].indexIndex(L1)<Data[k2].indexIndex(L2)){
	    V+=pow(0.0-Data[k1].elementIndex(L1), 2.0);
	    L1++;
	  }
	  else if(Data[k2].indexIndex(L2)<Data[k1].indexIndex(L1)){
	    V+=pow(0.0-Data[k2].elementIndex(L2), 2.0);
	    L2++;
	  }
	}
	else if(index1_end){
	  V+=pow(0.0-Data[k2].elementIndex(L2), 2.0);
	  L2++;
	}
	else if(index2_end){
	  V+=pow(0.0-Data[k1].elementIndex(L1), 2.0);
	  L1++;
	}
	if(L1==Sz1)index1_end=1;
	if(L2==Sz2)index2_end=1;
      }
      Kernel[k1][k2]=exp(-Sigma*V);
    }
  }
  return;
}

void K_::revise_dissimilarities(void){
  Tmp_Dissimilarities=Dissimilarities;
  for(int i=0;i<centers_number();i++)
    for(int k=0;k<data_number();k++)
      Dissimilarities[i][k]
	=(UnitData[k]-KernelCenters[i])
	*(Kernel*(UnitData[k]-KernelCenters[i]));
  return;
}

void K_::revise_kernelcenters(void){
  return;
}
