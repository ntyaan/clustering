#include"hcs.h"
#include"qfcm.h"

#ifndef __QFCS__
#define __QFCS__

class QFCS: public HCS, public QFCM{
 public:
  QFCS(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierEm,
       double fuzzifierLambda);
  virtual void revise_centers(void);
};

#endif
