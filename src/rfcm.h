#include"hcm.h"

#ifndef __RFCM__
#define __RFCM__

class RFCM: virtual public HCM{
protected:
  Matrix Kernel;
  Matrix UnitMatrixData;
public:
  RFCM(int dimension,
       int data_number,
       int centers_number);
  void copy_similarities(const Matrix &arg);
  virtual void revise_dissimilarities(void);
  void centersInitializePlusPlus(int random_index);
};
#endif
