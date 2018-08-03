#include"hcm.h"

#ifndef __HCCM__
#define __HCCM__

class HCCM: virtual public HCM{
public:
  HCCM(int dimension,
       int data_number,
       int centers_number);
  //非類似度の計算
  virtual void revise_dissimilarities(void);
  virtual void initialize_centers_dissimilarities(int index);
  //データの正規化(MMMtype)
  void ForMMMData(void);
};

#endif
