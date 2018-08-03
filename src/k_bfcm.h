#include"bfcm.h"
#include"kernel.h"

#ifndef __KBFCM__
#define __KBFCM__

class K_BFCM: public BFCM, public K_{
public:
  K_BFCM(int dimension,
	 int data_number,
	 int centers_number,
	 double fuzzifierEm,
	 double sigma);
  virtual void revise_kernelcenters(void);
};

#endif
