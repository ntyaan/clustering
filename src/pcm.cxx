#include"pcm.h"

PCM::PCM(int dimension,
	 int data_number,
	 int centers_number,
	 double alpha): 
  HCM(dimension, data_number, centers_number),
  Alpha(alpha),
  Membership_Threshold(data_number),
  Membership_PCM(data_number, data_number){
}

double &PCM::alpha(void){
  return Alpha;
}

void PCM::initialize_centers_one_cluster(int index){
  for(int ell=0;ell<dimension();ell++)
    Centers[0][ell]=0.0;
  for(int ell=0;ell<Data[index].essencialSize();ell++)
    Centers[0][Data[index].indexIndex(ell)]=Data[index].elementIndex(ell);
  return;
}

void PCM::ofs_membership(void){
  std::ofstream ofs("membership.txt");
  for(int k=0;k<data_number();k++)
    ofs<<Membership[0][k]<<" ";
  return;
}

Matrix PCM::membership_pcm(void){
  return Membership_PCM;
}

Vector PCM::membership_threshold(void){
  return Membership_Threshold;
}

double mid(Vector x){
  for (int i = 0; i < x.size() - 1; i++){
    int j = i;    
    for (int k = i; k < x.size(); k++){
      if (x[k] < x[j]) j = k;
    }
    if (i < j){
      double v = x[i];
      x[i] = x[j]; x[j] = v;
    }
  }
  return (x.size() % 2 == 0) ?
    (x[x.size()/2-1]+x[x.size()/2])/2.0 :
    x[x.size()/2];
}

 
void PCM::save_membebrship(int index){ 
  for(int k=0;k<data_number();k++)
    Membership_PCM[index][k]=Membership[0][k];
  //帰属度中央値を保存
  Membership_Threshold[index]=mid(Membership_PCM[index]);
  return;
}
