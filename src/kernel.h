#include"hcma.h"

#ifndef __KERNEL__
#define __KERNEL__

class K_: virtual public HCMA{
protected:
  double Sigma;
  Matrix Kernel;
  Matrix KernelCenters;
  Matrix Tmp_KernelCenters;
  Matrix Tmp_Dissimilarities;
  Matrix UnitData;
public:
  K_(int dimension,
     int data_number,
     int centers_number,
     double sigma);
  double &sigma(void);
  Matrix kernelcenters(void) const;
  Matrix tmp_kernelcenters(void) const;
  Matrix tmp_dissimilarities(void) const;
  virtual void calcurate_kernel(void);
  virtual void revise_dissimilarities(void);
  virtual void revise_kernelcenters(void);
};

#endif
