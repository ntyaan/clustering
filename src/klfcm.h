#include"hcma.h"

#ifndef __KLFCM__
#define __KLFCM__

class KLFCM: virtual public HCMA{
protected:
  //KLダイバージェンス正則化項に付与したパラメータ
  double FuzzifierLambda;
public:
  KLFCM(int dimension,
	int data_number,
	int centers_number,
	double fuzzifierLambda);
  double &fuzzifierLambda(void);
  virtual void revise_membership(void);
  virtual void revise_clusters_size(void);
  virtual void set_objective(void);
};

#endif
