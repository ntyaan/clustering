#include"hcs.h"
#include"klfcm.h"

#ifndef __KLFCS__
#define __KLFCS__

class KLFCS: public HCS, public KLFCM{
public:
  KLFCS(int dimension,
	int data_number,
	int centers_number,
	double fuzzifierLambda);
  virtual void revise_centers(void);

};

#endif
