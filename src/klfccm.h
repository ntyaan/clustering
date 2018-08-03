#include"hccm.h"
#include"klfcm.h"

#ifndef __KLFCCM__
#define __KLFCCM__

class KLFCCM: public HCCM, public KLFCM{
public:
  KLFCCM(int dimension,
	 int data_number,
	 int centers_number,
	 double fuzzifierLambda);
  virtual void revise_centers(void);
};

#endif
