#include"hcma.h"

HCMA::HCMA(int dimension,
	   int data_number,
	   int centers_number):
  HCM(dimension, data_number, centers_number),
  Clusters_size(centers_number),
  Tmp_Clusters_size(centers_number){
  for(int i=0;i<centers_number;i++)
    Clusters_size[i]=DBL_MAX;
  }

void HCMA::revise_clusters_size(void){
  return;
}

void HCMA::initialize_clustersize(void){
  //ここではクラスタ数分の1を初期値に与えている
  //データが各クラスタへどれくらい属しているか分かっている場合
  //その比率を初期値に与えたほうがベスト
  for(int i=0;i<centers_number();i++){
    Clusters_size[i]=1.0/centers_number();
  }
  return;
}

void HCMA::reset(void){
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Tmp_Membership[i][k]=0.0;
      Membership[i][k]=DBL_MAX;
    }
    for(int ell=0;ell<dimension();ell++){
      Tmp_Centers[i][ell]=0.0;
      Centers[i][ell]=DBL_MAX;
    }
    Tmp_Clusters_size[i]=0.0;
    Clusters_size[i]=DBL_MAX;
  }
  return;
}

Vector HCMA::clusters_size(void) const{
  return Clusters_size;
}

Vector HCMA::tmp_clusters_size(void) const{
  return Tmp_Clusters_size;
}

double &HCMA::clusters_size(int index1){
  return Clusters_size[index1];
}
