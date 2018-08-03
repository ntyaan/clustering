#include"bfcm.h"
#include"klfcm.h"

#ifndef __QFCM__
#define __QFCM__

class QFCM: public BFCM, public KLFCM{
 public:
  QFCM(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierEm,
       double fuzzifierLambda);
  virtual void revise_membership(void);
  virtual void revise_centers(void);
  virtual void revise_clusters_size(void);
  virtual void set_objective(void);
};

#endif
