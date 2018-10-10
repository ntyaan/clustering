#include"brfcm.h"

BRFCM::BRFCM(int dimension,
	   int data_number,
	   int centers_number,
	   double fuzzifierEm): 
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  RFCM(dimension, data_number, centers_number),
  BFCM(dimension, data_number, centers_number, fuzzifierEm){
}

void BRFCM::revise_centers(void){
#ifdef CHECK_CLASS
  std::cout<<"BRFCM::revise_centers"<<std::endl;
#endif
  Tmp_Centers=Centers;
  for(int i=0;i<centers_number();i++){
    double denominator=0.0;
    Vector numerator(Centers[i].size(), 0.0, "all");
    for(int k=0;k<data_number();k++){
      denominator+=pow(Membership[i][k],FuzzifierEm);
      numerator+=pow(Membership[i][k],FuzzifierEm)*UnitMatrixData[k];
    }                                                                      
    Centers[i]=numerator/denominator;
  }
  return;
}

void BRFCM::set_objective(void){
  Objective=0.0;
  for(int i=0;i<centers_number();i++){
    double numerator=0.0,denominator=0.0;
    for(int k1=0;k1<data_number();k1++){
      denominator+=pow(Membership[i][k1],FuzzifierEm);
      for(int k2=0;k2<data_number();k2++)
	numerator+=pow(Membership[i][k1],FuzzifierEm)
	  *pow(Membership[i][k2],FuzzifierEm)
	  *Kernel[k1][k2];
    }
    Objective+=pow(Clusters_size[i],1.0-FuzzifierEm)
      *numerator/(2.0*denominator);
  }
  return;
}
