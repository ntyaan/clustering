#include"hcs.h"
#include"bfcm.h"

#ifndef __BFCS__
#define __BFCS__

class BFCS: public HCS, public BFCM{
public:
  BFCS(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierEm);
  virtual void revise_centers(void);
};

#endif
