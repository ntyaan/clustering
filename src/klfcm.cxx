#include"klfcm.h"

KLFCM::KLFCM(int dimension,
	     int data_number,
	     int centers_number,
	     double fuzzifierLambda): 
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  FuzzifierLambda(fuzzifierLambda){
  }

double &KLFCM::fuzzifierLambda(void){
  return FuzzifierLambda;
}

void KLFCM::revise_membership(void){
#ifdef CHECK_CLASS
  std::cout<<"KLFCM::revise_membershipが呼び出されました"<<std::endl;
#endif
  Tmp_Membership=Membership;
  for(int k=0;k<data_number();k++){
    for(int i=0;i<centers_number();i++){
      double denominator=0.0;
      for(int j=0;j<centers_number();j++){
	denominator+=Clusters_size[j]/Clusters_size[i]
	  *exp(-FuzzifierLambda*(Dissimilarities[j][k]
				 -Dissimilarities[i][k]));
      }
      Membership[i][k]=1.0/denominator;
    }
  }
  return;
}

void KLFCM::revise_clusters_size(void){
#ifdef CHECK_CLASS
  std::cout<<"KLFCM::revise_clusters_sizeが呼び出されました"<<std::endl;
#endif
  Tmp_Clusters_size=Clusters_size;
  for(int i=0;i<centers_number();i++){
    double numerator=0.0;
    for(int k=0;k<data_number();k++){
      numerator+=Membership[i][k];
    }
    Clusters_size[i]=numerator/data_number();
  }
  return;
}

void KLFCM::set_objective(void){
  Objective=0.0;
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Objective+=Membership[i][k]*Dissimilarities[i][k]
	+(1.0/FuzzifierLambda)*Membership[i][k]
	*(log(Membership[i][k])-log(Clusters_size[i]));
    }
  }
  return;
}
