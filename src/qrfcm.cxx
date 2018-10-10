#include"qrfcm.h"

QRFCM::QRFCM(int dimension,
	     int data_number,
	     int centers_number,
	     double fuzzifierEm,
	     double fuzzifierLambda): 
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  RFCM(dimension, data_number, centers_number),
  QFCM(dimension, data_number, centers_number,
       fuzzifierEm, fuzzifierLambda){
}

void QRFCM::revise_centers(void){
#ifdef CHECK_CLASS
  std::cout<<"QRFCM::revise_centers"<<std::endl;
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

void QRFCM::set_objective(void){
  Objective=0.0;
  double tmp=0.0;
  for(int i=0;i<centers_number();i++){
    double numerator=0.0,denominator=0.0;
    for(int k1=0;k1<data_number();k1++){
      denominator+=pow(Membership[i][k1],FuzzifierEm);
      tmp+=pow(Clusters_size[i],1.0-FuzzifierEm)
	*pow(Membership[i][k1],FuzzifierEm);
      for(int k2=0;k2<data_number();k2++)
	numerator+=pow(Membership[i][k1],FuzzifierEm)
	  *pow(Membership[i][k2],FuzzifierEm)
	  *Kernel[k1][k2];
    }
    Objective+=pow(Clusters_size[i],1.0-FuzzifierEm)
      *numerator/(2.0*denominator);
  }
  Objective+=1.0/(FuzzifierLambda*(FuzzifierEm-1.0))*(tmp-1.0);
  return;
}
