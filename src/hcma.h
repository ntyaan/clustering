#include"hcm.h"

#ifndef __HCMA__
#define __HCMA__

class HCMA: virtual public HCM{
protected:
  //クラスタサイズ調整変数
  Vector Clusters_size, Tmp_Clusters_size;
public:
  HCMA(int dimension,
       int data_number,
       int centers_number);
  //クラスタサイズ調整変数の計算
  virtual void revise_clusters_size(void)=0;
  //初期クラスタサイズ調整変数の決定
  void initialize_clustersize();
  //各変数の初期化
  void reset(void);
  //クラスタサイズ調整変数をベクトルで返す
  Vector clusters_size(void) const;
  //前ループのクラスタサイズ調整変数をベクトルで返す
  Vector tmp_clusters_size(void) const;
  //クラスタサイズ調整変数の要素を返したり書き換えたり
  double &clusters_size(int index1);
};

#endif
