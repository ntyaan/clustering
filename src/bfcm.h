#include"hcma.h"

#ifndef __BFCM__
#define __BFCM__

class BFCM: virtual public HCMA{
protected:
  //Bzdek-typeファジィ化パラメータ
  double FuzzifierEm;
public:
  BFCM(int dimension,
       int data_number,
       int centers_number,
       double fuzzifierEm);
  double &fuzzifierEm(void);
  virtual void revise_membership(void);
  virtual void revise_centers(void);
  virtual void revise_clusters_size(void);
  virtual void set_objective(void);
};

#endif
