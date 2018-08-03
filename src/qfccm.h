#include"hccm.h"
#include"qfcm.h"

#ifndef __QFCCM__
#define __QFCCM__

class QFCCM: public HCCM, public QFCM {
public:
  QFCCM(int dimension,
	int data_number,
	int centers_number,
	double fuzzifierEm,
	double fuzzifierLambda);
  virtual void revise_centers(void);
};

#endif
