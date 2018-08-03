#include"hccm.h"
#include"bfcm.h"

#ifndef __BFCCM__
#define __BFCCM__

class BFCCM: public HCCM, public BFCM{
public:
  BFCCM(int dimension,
	int data_number,
	int centers_number,
	double fuzzifierEm);
  virtual void revise_centers(void);
};

#endif
