#include"hcm.h"
#include<boost/math/special_functions/digamma.hpp>
#include<boost/math/special_functions/trigamma.hpp>

#ifndef __HCCMP__
#define __HCCMP__

class HCCMP: virtual public HCM{
protected:
  Vector Data_k, Alpha_i;
public:
  HCCMP(int dimension,
	int data_number,
	int centers_number);
  void data_k(void);
  void alpha_i(void);
  virtual void revise_dissimilarities(void);
};

#endif
