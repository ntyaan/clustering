#include"hccm.h"

#ifndef __HCCMM__
#define __HCCMM__

class HCCMM: virtual public HCCM{
protected:
  double FuzzifierEt;
public:
  HCCMM(int dimension,
	int data_number,
	int centers_number,
	double fuzzifierEt);
  double &fuzzifierEt(void);
  virtual void revise_dissimilarities(void);
  virtual void initialize_centers_dissimilarities(int index);
};

#endif
