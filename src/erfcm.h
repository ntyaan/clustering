#include"rfcm.h"
#include"klfcm.h"

#ifndef __ERFCM__
#define __ERFCM__

class ERFCM: public RFCM, public KLFCM{
public:
  ERFCM(int dimension,
	int data_number,
	int centers_number,
	double fuzzifierLambda);
  virtual void revise_centers(void);
  virtual void set_objective(void);
};

#endif
