#include"hccmp.h"
#include"klfccm.h"

#ifndef __KLFCCMP__
#define __KLFCCMP__

class KLFCCMP: public HCCMP, public KLFCCM{
public:
  KLFCCMP(int dimension,
	  int data_number,
	  int centers_number,
	  double fuzzifierLambda);
  virtual void revise_dissimilarities(void);
  virtual void revise_centers(void);
  double pseudoLogLikelihood(void);
  void initialize_alpha(void);
};

#endif
