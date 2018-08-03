#include"plsa.h"

PLSA::PLSA(int dimension,
	   int data_number,
	   int centers_number):
  Hcm(dimension, data_number, centers_number),
  Phi(centers_number, data_number, dimension),
  Tmp_Phi(centers_number,data_number, dimension){
  for(int i=0;i<centers_number;i++)
    for(int k=0;k<data_number;k++)
      for(int ell=0;ell<dimension;ell++)
	Phi[i][k][ell]=1.0/dimension;
}

Array3 PLSA::phi(void){
  return Phi;
}

Array3 PLSA::tmp_phi(void){
  return Tmp_Phi;
}

void PLSA::initialize_phi(double arg){
  for(int i=0;i<centers_number();i++)
    for(int k=0;k<data_number();k++)
      for(int ell=0;ell<dimension();ell++)
	Phi[i][k][ell]=arg;
  return;
}

void PLSA::revise_membership(void){
#ifdef CHECK_CLASS
  std::cout<<"PLSA::revise_membeship"<<std::endl;;
#endif
  Tmp_Membership=Membership;
  Matrix Numerator(centers_number, dimension);
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Numerator[i][k]=0.0;
      for(int ell=0;ell<Data[k].essencialSize();ell++)
	Numerator[i][k]+=
	  Data[k].elementIndex(ell)*Phi[i][k][Data.indexIndex(ell)];
    }
  }
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      double denominator=0.0;
      for(int j=0;j<centers_number();j++)
	denominator+=Numerator[j][k];
      Membership[i][k]=Numerator[i][k]/denominator;
    }
  }
  return;
}

void PLSA::revise_centers(void){
#ifdef CHECK_CLASS
  std::cout<<"PLSA::revise_centers"<<std::endl;;
#endif
  Tmp_Centers=Centers;
  for(int i=0;i<centers_number();i++){
    double denominator=0.0;
    Vector numerator(dimension());
    for(int ell=0;ell<dimension();ell++)
      numerator[ell]=0.0;
    for(int k=0;k<data_number();k++){
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	numerator[Data[k].indexIndex(ell)]
          +=Data[k].elementIndex(ell)*Phi[i][k][Data[k].indexIndex(ell)];
	denominator
	  +=Data[k].elementIndex(ell)*Phi[i][k][Data[k].indexIndex(ell)];
      }
    }
    Centers[i]=numerator/denominator;
  }
  return;
}

void PLSA::revise_phi(void){
#ifdef CHECK_CLASS
  std::cout<<"PLSA::revise_phi"<<std::endl;;
#endif
  Tmp_Phi=Phi;
  Array3 Tmp(centers_number(),data_number(),dimension());
  for(int k=0;k<data_number();k++){
    for(int ell=0;ell<dimension();ell++){
      for(int i=0;i<centers_number();i++)
	Tmp[i][k][ell]=Membership[i][k]*Centers[i][ell];
      for(int i=0;i<centers_number();i++){
	double denominator=0.0;
	for(int j=0;j<centers_number();j++){
	  denominator
	    +=Tmp[j][k][ell]/Tmp[i][k][ell];
	}
	Phi[i][k][ell]=1.0/denominator;
      }
    }
  }
  return;
}

void PLSA::set_objective(void){
  Objective=0.0;
  return;
}
