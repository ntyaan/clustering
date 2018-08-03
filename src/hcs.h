#include"hcm.h"

#ifndef __HCS__
#define __HCS__

class HCS: virtual public HCM{
public:
  HCS(int dimension,
      int data_number,
      int centers_number);
  virtual void revise_dissimilarities(void);
  virtual void initialize_centers_dissimilarities(int index);
  void ForSphericalData(void);
};

#endif
