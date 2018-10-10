#include"erfcm.h"

ERFCM::ERFCM(int dimension,
	     int data_number,
	     int centers_number,
	     double fuzzifierLambda): 
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  RFCM(dimension, data_number, centers_number),
  KLFCM(dimension, data_number, centers_number, fuzzifierLambda){
}

void ERFCM::revise_centers(void){
#ifdef CHECK_CLASS
  std::cout<<"ERFCM::revise_centers"<<std::endl;
#endif
  Tmp_Centers=Centers;
  for(int i=0;i<centers_number();i++){
    double denominator=0.0;
    Vector numerator(Centers[i].size(), 0.0, "all");
    for(int k=0;k<data_number();k++){
      denominator+=Membership[i][k];
      numerator+=Membership[i][k]*UnitMatrixData[k];
    }                                                                      
    Centers[i]=numerator/denominator;
  }
  return;
}

void ERFCM::set_objective(void){
  Objective=0.0;
  double tmp=0.0;
  for(int i=0;i<centers_number();i++){
    double numerator=0.0,denominator=0.0;
    for(int k1=0;k1<data_number();k1++){
      denominator+=Membership[i][k1];
      tmp+=Membership[i][k1]
	*log(Membership[i][k1]/Clusters_size[i]);
      for(int k2=0;k2<data_number();k2++)
	numerator+=Membership[i][k1]
	  *Membership[i][k2]
	  *Kernel[k1][k2];
    }
    Objective+=numerator/(2.0*denominator);
  }
  Objective+=(tmp/FuzzifierLambda);
  return;
}

