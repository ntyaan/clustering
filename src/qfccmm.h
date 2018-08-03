#include"hccmm.h"
#include"qfcm.h"

#ifndef __QFCCMM__
#define __QFCCMM__

class QFCCMM: public HCCMM, public QFCM{
public:
  QFCCMM(int dimension,
	 int data_number,
	 int centers_number,
	 double fuzzifierEm,
	 double fuzzifierLambda,
	 double fuzzifierEt);
  virtual void revise_centers(void);
};

#endif
