#include"hcm.h"

#ifndef __PCM__
#define __PCM__

class PCM: virtual public HCM{
protected:
  double Alpha;
  Vector Membership_Threshold;
  Matrix Membership_PCM;
public:
  PCM(int dimension,
      int data_number,
      int centers_number,
      double alpha);
  double &alpha(void);
  void initialize_centers_one_cluster(int);
  void ofs_membership(void);
  Matrix membership_pcm(void);
  Vector membership_threshold(void);
  void save_membebrship(int index);
};

#endif
