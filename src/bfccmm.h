#include"hccmm.h"
#include"bfcm.h"

#ifndef __BFCCMM__
#define __BFCCMM__

class BFCCMM: public HCCMM, public BFCM{
public:
  BFCCMM(int dimension,
	 int data_number,
	 int centers_number,
	 double fuzzifierEm,
	 double fuzzifeirEt);
  virtual void revise_centers(void);
};

#endif
