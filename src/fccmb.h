#include"bfcm.h"

#ifndef __FCCMB__
#define __FCCMB__

class FCCMB: public BFCM{
protected:
  double FuzzifierEm2;
public:
  FCCMB(int dimension,
	int data_number,
	int centers_number,
	double fuzzifierEm,
	double fuzzifierEm2);
  double &fuzzifierEm2(void);
  virtual void revise_dissimilarities(void);
  virtual void revise_centers(void);
  virtual void initialize_centers_dissimilarities(int index);
};

#endif
