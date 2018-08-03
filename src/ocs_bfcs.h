#include"ocs.h"
#include"bfcs.h"

#ifndef __OCSBFCS__
#define __OCSBFCS__

class OCS_BFCS: public BFCS, public OCS{
public:
  OCS_BFCS(int dimension,
	   int data_number,
	   int centers_number,
	   double fuzzifierEm,
	   int number_of_missing_values);
  virtual void revise_data(void);
};

#endif
