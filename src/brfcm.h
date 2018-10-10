#include"rfcm.h"
#include"bfcm.h"

#ifndef __BRFCM__
#define __BRFCM__

class BRFCM: public RFCM, public BFCM{
public:
  BRFCM(int dimension,
	int data_number,
	int centers_number,
	double fuzzifierEm);
  virtual void revise_centers(void);
  virtual void set_objective(void);
};

#endif
