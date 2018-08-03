#include "hcm.h"
#include "array3.h"

#ifndef __PLSA__
#define __PLSA__

class PLSA: public HCM{
protected:
  Array3 Phi, Tmp_Phi;
public:
  PLSA(int dimension,
       int data_number,
       int centers_number);
  Array3 phi(void);
  Array3 tmp_phi(void);
  void initialize_phi(double arg);
  virtual void revise_membership(void);
  virtual void revise_centers(void);
  virtual void revise_phi(void);
  virtual void set_objective(void);
};

#endif
