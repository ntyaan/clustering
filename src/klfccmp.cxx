#include"klfccmp.h"

KLFCCMP::KLFCCMP(int dimension,
		 int data_number,
		 int centers_number,
		 double fuzzifierLambda): 
  HCM(dimension, data_number, centers_number),
  HCMA(dimension, data_number, centers_number),
  HCCMP(dimension, data_number, centers_number),
  KLFCCM(dimension, data_number, centers_number, fuzzifierLambda){
}
void KLFCCMP::revise_dissimilarities(void){
  HCCMP::revise_dissimilarities();
}

void KLFCCMP::revise_centers(void){
#ifdef CHECK_CLASS
  std::cout<<"KLFCCMP::revise_centers"<<std::endl;
#endif
  Tmp_Centers=Centers;
  Vector Numerator(dimension());
  Vector Alpha(centers_number());
  Vector NAlpha(dimension());
  for(int i=0;i<centers_number();i++){
    int count=0;
    while(1){
      Alpha[i]=0.0;
      for(int ell=0;ell<dimension();ell++){
	Alpha[i]+=Centers[i][ell];   
	Numerator[ell]=0.0;
      }
      double denominator=0.0;
      for(int k=0;k<data_number();k++){
	for(int ell=0;ell<Data[k].essencialSize();ell++){
	  if(Centers[i][Data[k].indexIndex(ell)]>0.0)
	    Numerator[Data[k].indexIndex(ell)]
	      +=Membership[i][k]
	      *((Data[k].elementIndex(ell))
		/(Data[k].elementIndex(ell)
		  -1.0+Centers[i][Data[k].indexIndex(ell)]));
	}	
	denominator+=Membership[i][k]
	  *Data_k[k]/(Data_k[k]-1.0+Alpha[i]);
      }
      for(int ell=0;ell<Numerator.size();ell++){
	//if(Numerator[ell]<=0.0)
	//std::cout<<ell<<" "<<Numerator[ell]<<std::endl;
	//return;
	//else
	NAlpha[ell]=Centers[i][ell]*Numerator[ell]/denominator;
	if(std::isnan(NAlpha[ell])){
	  std::cout<<"centers nan:"<<i<<" "<<ell<<std::endl;
	  std::cout<<"denominator:"<<denominator<<std::endl;
	  exit(1);
	}
      }
      double diff=squared_norm(Centers[i]-NAlpha)/squared_norm(Centers[i]);
      if(count>0 && diff<1.0E-2) break;
      Centers[i]=NAlpha;
      count++;
    }
  }
  return;
}

double logsumexp(double x, double y, int init){
  double vmin = std::min(x, y);
  double vmax = std::max(x, y);
  if(init){
    return y;
  }
  if(x==y){
    return x+log(2.0);
  }
  if(vmax>vmin+50){
    return vmax;
  }
  else{
    return vmax+log(1.0+exp(vmin-vmax));
  }
}

double KLFCCMP::pseudoLogLikelihood(void){
  double likelihood=0.0, z=0.0;
  for(int k=0;k<data_number();k++){ 
    for(int i =0;i<centers_number();i++){
      double s1=0.0,s2=0.0;
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	if(Centers[i][Data[k].indexIndex(ell)]>0.0){
	  s1+=(Centers[i][Data[k].indexIndex(ell)]+Data[k].elementIndex(ell));
	  s2+=Centers[i][Data[k].indexIndex(ell)];
	}
      }
      double s =log(Clusters_size[i])
	+boost::math::lgamma(s2)
	-boost::math::lgamma(s1);
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	if(Centers[i][Data[k].indexIndex(ell)]>0.0){
	  s+=boost::math::lgamma(Centers[i][Data[k].indexIndex(ell)]
				 +Data[k].elementIndex(ell))
	    -boost::math::lgamma(Centers[i][Data[k].indexIndex(ell)]);
	}
      }//ell
      z =logsumexp(z,s,(i==0));
    }//i
    likelihood+=z;
  }//k
  return likelihood;
}

void KLFCCMP::initialize_alpha(void){
  KLFCCM::revise_centers();
  return;
}

