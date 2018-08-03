#include"qfcm.h"

QFCM::QFCM(int dimension,
	   int data_number,
	   int centers_number,
	   double fuzzifierEm,
	   double fuzzifierLambda):
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  BFCM(dimension, data_number, centers_number, fuzzifierEm),
  KLFCM(dimension, data_number, centers_number, fuzzifierLambda){
}

void QFCM::revise_membership(void){
#ifdef CHECK_CLASS
  std::cout<<"QFCM::revise_membership"<<std::endl;;
#endif
  Tmp_Membership=Membership;
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      double denominator=0.0;
      for(int j=0;j<centers_number();j++){
        denominator+=(Clusters_size[j]/Clusters_size[i])
	  *pow((1.0-FuzzifierLambda*(1.0-FuzzifierEm)*Dissimilarities[j][k])
               /(1.0-FuzzifierLambda*(1.0-FuzzifierEm)*Dissimilarities[i][k])
               ,1.0/(1.0-FuzzifierEm));
      }
      Membership[i][k]=1.0/denominator;
    }
  }
  return;
}

void QFCM::revise_centers(void){
#ifdef CHECK_CLASS
  std::cout<<"QFCM-";
#endif
  BFCM::revise_centers();
}

void QFCM::revise_clusters_size(void){
#ifdef CHECK_CLASS
  std::cout<<"QFCM::revise_clusters_size"<<std::endl;;
#endif
  Tmp_Clusters_size=Clusters_size;
  Vector Tmp(centers_number());
  for(int i=0;i<centers_number();i++){
    Tmp[i]=0.0;
    for(int k=0;k<data_number();k++){
      Tmp[i]+=pow(Membership[i][k],FuzzifierEm)
	*(1.0-FuzzifierLambda*(1.0-FuzzifierEm))*Dissimilarities[i][k];
    }
  }
  for(int i=0;i<centers_number();i++){
    double denominator=0.0;
    for(int j=0;j<centers_number();j++){
      denominator+=pow(Tmp[j]/Tmp[i], 1.0/FuzzifierEm);
    }
    Clusters_size[i]=1.0/denominator;
  }
  return;
}
  
void QFCM::set_objective(void){
  Objective=0.0;
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Objective+=pow(Clusters_size[i],1.0-FuzzifierEm)*
        pow(Membership[i][k],FuzzifierEm)*Dissimilarities[i][k]
	+1.0/(FuzzifierLambda*(FuzzifierEm-1.0))
	*pow(Clusters_size[i],1.0-FuzzifierEm)
	*pow(Membership[i][k],FuzzifierEm);
    }
  }
  return;
}
