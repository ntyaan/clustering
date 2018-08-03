#include"ocs_bfcs.h"

OCS_BFCS::OCS_BFCS(int dimension,
		   int data_number,
		   int centers_number,
		   double fuzzifierEm,
		   int number_of_missing_values): 
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  BFCS(dimension, data_number, centers_number, fuzzifierEm),
  OCS(dimension, data_number, centers_number, number_of_missing_values){
}

void OCS_BFCS::revise_data(void){
  for(int k=0;k<data_number();k++){
    Vector Numerator(dimension());
    for(int ell=0;ell<dimension();ell++)
      Numerator[ell]=0.0;
    double num=0.0;
    double denominator=0.0;
    for(int ell=0;ell<Data[k].essencialSize();ell++)
      //欠損してなかったら
      if(IncompleteIndex[k][Data[k].indexIndex(ell)]!=1.0)
	num+=pow(Data[k].elementIndex(ell), 2.0);
    for(int ell=0;ell<dimension();ell++){
      for(int i=0;i<centers_number();i++){
	Numerator[ell]
	  +=pow(Clusters_size[i], 1.0-FuzzifierEm)
	  *pow(Membership[i][k], FuzzifierEm)
	  *Centers[i][ell];
      }
      //欠損してなかったら
      //if(IncompleteIndex[k][ell]!=1.0)
      denominator+=pow(Numerator[ell], 2.0);
    }
    for(int ell=0;ell<Data[k].essencialSize();ell++){
      //欠損していたら
      if(IncompleteIndex[k][Data[k].indexIndex(ell)]==1.0){
	Data[k].elementIndex(ell)
	  =(Numerator[Data[k].indexIndex(ell)]
	    *sqrt(1.0-num))/sqrt(denominator);
	if(std::isnan(Data[k].elementIndex(ell))){
	  std::cout<<k<<" "<<Data[k].elementIndex(ell)<<" "
		   <<Numerator[Data[k].indexIndex(ell)]<<" "
		   <<denominator<<std::endl;
	  std::cout<<Data[k]<<std::endl;
	  exit(1);
	}
      }
    }
  }
  return;
}
