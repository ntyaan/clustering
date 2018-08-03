#include"bfcs.h"
#include"kernel.h"

#ifndef __KBFCS__
#define __KBFCS__

class K_BFCS: public BFCS, public K_{
public:
  K_BFCS(int dimension,
	 int data_number,
	 int centers_number,
	 double fuzzifierEm,
	 double sigma);
  virtual void revise_kernelcenters(void);
  virtual void revise_dissimilarities(void);
};

#endif
