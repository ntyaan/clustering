#include"klfcm.h"

#ifndef __FCCM__
#define __FCCM__

class FCCM: public KLFCM{
protected:
  double FuzzifierLambda2;
public:
  FCCM(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierLambda,
       double fuzzifierLambda2);
  double &fuzzifierLambda2(void);
  virtual void revise_dissimilarities(void);
  virtual void revise_centers(void);
  virtual void initialize_centers_dissimilarities(int index);
  virtual void set_objective(void);
};

#endif
