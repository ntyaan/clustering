#include"rfcm.h"
#include"qfcm.h"

#ifndef __QRFCM__
#define __QRFCM__

class QRFCM: public RFCM, public QFCM{
public:
  QRFCM(int dimension,
	int data_number,
	int centers_number,
	double fuzzifierEm,
	double fuzzifierLambda);
  virtual void revise_centers(void);
  virtual void set_objective(void);
};

#endif
