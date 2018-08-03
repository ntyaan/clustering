#include"hccmm.h"
#include"klfcm.h"

#ifndef __KLFCCMM__
#define __KLFCCMM__

class KLFCCMM: public HCCMM, public KLFCM{
public:
  KLFCCMM(int dimension,
	  int data_number,
	  int centers_number,
	  double fuzzifierLambda,
	  double fuzzifierEt);
  virtual void revise_centers(void);
};

#endif
