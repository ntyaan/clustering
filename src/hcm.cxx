#include"hcm.h"

HCM::HCM(int dimension,
	 int data_number,
	 int centers_number):
  Data(data_number, dimension),
  Centers(centers_number, dimension),
  Tmp_Centers(centers_number, dimension),
  Membership(centers_number, data_number),
  Tmp_Membership(centers_number, data_number),
  Dissimilarities(centers_number, data_number),
  CrispMembership(centers_number, data_number),
  CorrectCrispMembership(centers_number, data_number),
  ContingencyTable(centers_number+1, centers_number+1),
  InitializeC(centers_number),
  Iterates(0), Objective(0){
  /***↓収束判定のためにDBL_MAXに設定***/
  for(int i=0;i<centers_number;i++){
    Centers[i]=Vector(dimension);
    for(int ell=0;ell<dimension;ell++){
      Centers[i][ell]=DBL_MAX;
    }
  }
  for(int i=0;i<centers_number;i++){
    for(int k=0;k<data_number;k++){
      Membership[i][k]=DBL_MAX;
    }
  }
  for(int i=0;i<centers_number;i++)
    InitializeC[i]=-1;
}

void HCM::revise_dissimilarities(void){
#ifdef CHECK_CLASS
  std::cout<<"HCM::revise_dissimilarities"<<std::endl;;
#endif
  for(int i=0;i<centers_number();i++){
    double centersNormSquare=norm_square(Centers[i]);
    for(int k=0;k<data_number();k++){
      Dissimilarities[i][k]=norm_square(Data[k])
	-2.0*(Data[k]*Centers[i])+centersNormSquare;
    }
  }
  return;
}

void HCM::revise_membership(void){
#ifdef CHECK_CLASS
  std::cout<<"HCM::revise_membership"<<std::endl;;
#endif
  Tmp_Membership=Membership;
  for(int k=0;k<data_number();k++){
    int min_index=0; double min_dissimilarity=Dissimilarities[0][k];
    for(int i=1;i<centers_number();i++){
      if(min_dissimilarity>Dissimilarities[i][k]){
	min_index=i;
	min_dissimilarity=Dissimilarities[i][k];
      }
    }
    for(int i=0;i<centers_number();i++){
      Membership[i][k]=0.0;
    }
    Membership[min_index][k]=1.0;
  }
  return;
}

void HCM::revise_centers(void){
#ifdef CHECK_CLASS
  std::cout<<"HCM::revise_centers"<<std::endl;;
#endif
  Tmp_Centers=Centers;
  for(int i=0;i<centers_number();i++){
    double denominator=0.0;
    Vector numerator(Centers[i].size());
    for(int ell=0;ell<numerator.size();ell++){
      numerator[ell]=0.0;
    }
    for(int k=0;k<data_number();k++){
      denominator+=Membership[i][k];
      for(int ell=0;ell<Data[k].essencialSize();ell++){
	numerator[Data[k].indexIndex(ell)]
	  +=Membership[i][k]*Data[k].elementIndex(ell);
      }
    }
    Centers[i]=numerator/denominator;
  }
  return;
}

void HCM::set_objective(void){
  Objective=0.0;
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Objective+=Membership[i][k]*Dissimilarities[i][k];
    }
  }
  return;
}
  
int HCM::dimension(void) const{
  return Data.cols();
}

int HCM::data_number(void) const{
  return Data.rows();
}

int HCM::centers_number(void) const{
  return Membership.rows();
}

SparseMatrix HCM::data(void) const{
  return Data;
}

Matrix HCM::centers(void) const{
  return Centers;
}

Matrix HCM::tmp_centers(void) const{
  return Tmp_Centers;
}

Matrix HCM::membership(void) const{
  return Membership;
}

Matrix HCM::tmp_membership(void) const{
  return Tmp_Membership;
}

Matrix HCM::dissimilarities(void) const{
  return Dissimilarities;
}

Matrix HCM::crispMembership(void) const{
  return CrispMembership;
}

Matrix HCM::correctCrispMembership(void) const{
  return CorrectCrispMembership;
}

Matrix HCM::contingencyTable(void) const{
  return ContingencyTable;
}

SparseVector &HCM::data(int index1){
  return Data[index1];
}

Vector &HCM::centers(int index1){
  return Centers[index1];
}

int &HCM::iterates(void){
  return Iterates;
}

double HCM::objective(void) const{
  return Objective;
}

double &HCM::centers(int index1, int index2){
  return Centers[index1][index2];
}

double &HCM::membership(int row, int col){
  return Membership[row][col];
}

double &HCM::dissimilarities(int index1, int index2){
  return Dissimilarities[index1][index2];
}

double &HCM::crispMembership(int index1, int index2){
  return CrispMembership[index1][index2];
}


double &HCM::correctCrispMembership(int index1, int index2){
  return CorrectCrispMembership[index1][index2];
}

void HCM::set_crispMembership(void){
  for(int k=0;k<data_number();k++){
    for(int i=0;i<centers_number();i++){
      CrispMembership[i][k]=0.0;
    }
    double max=-DBL_MAX;
    int max_index=-1;
    for(int i=0;i<centers_number();i++){
      if(Membership[i][k]>max){
	max=Membership[i][k];
	max_index=i;
      }
    }
    CrispMembership[max_index][k]=1.0;
  }
  return;
}

void HCM::set_contingencyTable(void){
  ContingencyTable.set_sub
    (0,centers_number()-1, 0, centers_number()-1
     ,CrispMembership*transpose(CorrectCrispMembership));
  for(int i=0;i<ContingencyTable.rows()-1;i++){
    ContingencyTable[i][ContingencyTable.cols()-1]=0.0;
    for(int j=0;j<ContingencyTable.cols()-1;j++){
      ContingencyTable[i][ContingencyTable.cols()-1]
	+=ContingencyTable[i][j];
    }
  }
  for(int j=0;j<ContingencyTable.cols()-1;j++){
    ContingencyTable[ContingencyTable.rows()-1][j]=0.0;
    for(int i=0;i<ContingencyTable.rows()-1;i++){
      ContingencyTable[ContingencyTable.rows()-1][j]
	+=ContingencyTable[i][j];
    }
  }
  ContingencyTable[ContingencyTable.rows()-1][ContingencyTable.cols()-1]
    =data_number();
  return;
}

double combination(int n, int k){
  if(n<k) return 0.0;
  return boost::math::binomial_coefficient<double>(n, k); 
}

double HCM::ARI(void) const{
  double Index=0.0;
  for(int i=0;i<ContingencyTable.rows()-1;i++){
    for(int j=0;j<ContingencyTable.cols()-1;j++){
      Index+=ContingencyTable[i][j]*ContingencyTable[i][j];
    }
  }
  Index=0.5*(Index-ContingencyTable[ContingencyTable.rows()-1]
	     [ContingencyTable.cols()-1]);
  //  std::cout << "Index:" << Index << std::endl;
  double ExpectedIndexI=0.0;
  for(int i=0;i<ContingencyTable.rows()-1;i++){
    ExpectedIndexI+=combination
      (ContingencyTable[i][ContingencyTable.cols()-1], 2);
  }
  //  std::cout << "ExpectedIndexI:" << ExpectedIndexI << std::endl;
  double ExpectedIndexJ=0.0;
  for(int j=0;j<ContingencyTable.cols()-1;j++){
    ExpectedIndexJ+=combination
      (ContingencyTable[ContingencyTable.rows()-1][j], 2);
  }
  //  std::cout << "ExpectedIndexJ:" << ExpectedIndexJ << std::endl;
  double ExpectedIndex=ExpectedIndexI*ExpectedIndexJ
    /combination(ContingencyTable[ContingencyTable.rows()-1]
		 [ContingencyTable.cols()-1], 2);
  double MaxIndex=0.5*(ExpectedIndexI+ExpectedIndexJ);
  return (Index-ExpectedIndex)/(MaxIndex-ExpectedIndex);
}

void HCM::reset(void){
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      Tmp_Membership[i][k]=0.0;
      Membership[i][k]=DBL_MAX;
      Dissimilarities[i][k]=0.0;
    }
    for(int ell=0;ell<dimension();ell++){
      Tmp_Centers[i][ell]=0.0;
      Centers[i][ell]=DBL_MAX;
    }
  }
  return;
}

void HCM::initialize_centers_dissimilarities(int index){
  for(int i=0;i<index+1;i++){
    double centersNormSquare=norm_square(Centers[i]);
    for(int k=0;k<data_number();k++){
      Dissimilarities[i][k]
	=norm_square(Data[k])-2.0*(Data[k]*Centers[i])
	+centersNormSquare;
    }
  }
  return;
}

void HCM::initialize_centers(int random_index){
  std::mt19937_64 mt;
  //データ番号をランダムに発生
  std::uniform_int_distribution<> randNum(0,data_number()-1);
  //0~1の実数を発生
  std::uniform_real_distribution<> rand01(0.0,1.0);
  //クラスタ中心の初期化
  for(int x=0;x<centers_number();x++){
    for(int ell=0;ell<dimension();ell++){
      Centers[x][ell]=0.0;
    }
    InitializeC[x]=-1;
  }
  //選ばれたデータ番号格納用
  mt.seed(random_index);
  //step1:ランダムに一つデータを選ぶ
  InitializeC[0]=randNum(mt);
  //step1で選ばれたデータを第一クラスタ中心とする
  for(int ell=0;ell<Data[InitializeC[0]].essencialSize();ell++)
    Centers[0][Data[InitializeC[0]].indexIndex(ell)]	  	  	  
      =Data[InitializeC[0]].elementIndex(ell);
  for(int i=1;i<centers_number();i++){
    //step:2
    //データ間非類似度d_{i,k}を計算
    //bFCCMならd_{i,k}はsum_{l=1}^{M} (w_{i,l})^{1/m_2}x_{k,l}
    initialize_centers_dissimilarities(i-1);
    //クラスタ中心とデータ点の距離を格納
    double Tmp_Vector[data_number()];
    //第二クラスタ決定以降は各クラスタ中心の中で
    //データ点との距離が一番近いクラスタ中心を選択
    for(int k=0;k<data_number();k++){
      Tmp_Vector[k]=0.0;
      double min=DBL_MAX;
      for(int j=0;j<i;j++)
	if(min>Dissimilarities[j][k])
	  min=Dissimilarities[j][k];	      
      Tmp_Vector[k]=min;
    }
    //各非類似度を0~1の線で表す用
    double Tmp_Similarities[data_number()+1];
    for(int k=0;k<data_number()+1;k++)
      Tmp_Similarities[k]=0.0;
    double Sum=0.0,tmp=0.0;
    //合計を計算
    for(int k=0;k<data_number();k++)
      Sum+=Tmp_Vector[k];
    //std::cout<<std::endl<<std::endl;
    //非類似度を0~1で表現
    for(int k=1;k<data_number()+1;k++){
      tmp+=Tmp_Vector[k-1]/Sum;
      Tmp_Similarities[k]=tmp;
    }
    //0~1をランダムで選び，選ばれたデータをクラスタ中心へ
    double rnd01=rand01(mt);
    for(int k=0;k<data_number();k++)
      if(Tmp_Similarities[k]<rnd01&&Tmp_Similarities[k+1]>=rnd01)
	InitializeC[i]=k;
    for(int ell=0;ell<Data[InitializeC[i]].essencialSize();ell++)
      Centers[i][Data[InitializeC[i]].indexIndex(ell)]
	=Data[InitializeC[i]].elementIndex(ell);
  }
  return;
}

//推薦用人工データ
void HCM::initialize_membership(std::string file){
  std::ifstream ifs(file);
  if(!ifs){
    std::cerr<<"correct membership error"<<std::endl;
    exit(1);
  }
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      ifs>>CorrectCrispMembership[i][k];
      if(CorrectCrispMembership[i][k])
	Membership[i][k]=1.0-(centers_number()-1.0)/100;
      else
	Membership[i][k]=((centers_number()-1.0)/100.0)
	  /(centers_number()-1.0);
    }
  }
  if(centers_number()==4)
    for(int i=0;i<centers_number();i++)
      for(int k=80;k<data_number();k++)
	Membership[i][k]=1.0/centers_number();
  return;
}

void HCM::ofs_selected_data(std::string text){
  std::ofstream ofs(text+"/object.txt",std::ios::app);
  if(!ofs){
    std::cerr<<"ファイルオープン失敗\n";
    exit(1);
  }
  double partitioncofficient=0.0;
  for(int i=0;i<centers_number();i++){
    for(int k=0;k<data_number();k++){
      partitioncofficient+=pow(Membership[i][k],2.0);
    }
  }
  partitioncofficient/=data_number();
  for(int i=0;i<centers_number();i++)
    ofs<<InitializeC[i]<<"\t";
  ofs<<std::fixed<<std::setprecision(10)<<Objective
     <<"\t"<<partitioncofficient
     <<std::endl;
  ofs.close();
  return;
}

void HCM::copydata(const SparseMatrix &arg1){
  Data=arg1;
  return;
}

void HCM::print_frobenius_norm(void){
  std::cout<<"membership_frobenius_norm:"
	   <<std::setprecision(50)
	   <<"loop:"<<iterates()
	   <<":"<<frobenius_norm(membership())
	   <<std::endl;
  std::cout<<"centers_frobenius_norm:"
	   <<std::setprecision(50)
	   <<"loop:"<<iterates()
	   <<":"<<frobenius_norm(centers())
	   <<std::endl;
  return;
}

void tfidf1(SparseMatrix &Data){
  SparseMatrix TF(Data);
  Vector IDF(Data.cols());
  for(int k=0;k<Data.rows();k++){
    double denominator=0.0;
    for(int ell=0;ell<Data[k].essencialSize();ell++)
      denominator+=Data[k].elementIndex(ell);
    for(int ell=0;ell<Data[k].essencialSize();ell++)
      TF[k].elementIndex(ell)=Data[k].elementIndex(ell)/denominator;
  }
  for(int ell=0;ell<Data.cols();ell++){
    IDF[ell]=0.0;
    double df=0.0;
    for(int k=0;k<Data.rows();k++){
      for(int r=0;r<Data[k].essencialSize();r++)
	if(ell==Data[k].indexIndex(r)){
	  df++;
	  break;
	}
    }
    IDF[ell]=log((double)Data.rows()/df);
  }
  for(int k=0;k<Data.rows();k++)
    for(int ell=0;ell<Data[k].essencialSize();ell++)
      Data[k].elementIndex(ell)
	=TF[k].elementIndex(ell)*IDF[Data[k].indexIndex(ell)];
  return;
}

void tfidf2(SparseMatrix &Data){
  SparseMatrix TF(Data);
  Vector IDF(Data.cols());
  for(int k=0;k<Data.rows();k++)
    for(int ell=0;ell<Data[k].essencialSize();ell++)
      TF[k].elementIndex(ell)=1.0+log(Data[k].elementIndex(ell));
  for(int ell=0;ell<Data.cols();ell++){
    IDF[ell]=0.0;
    double df=0.0;
    for(int k=0;k<Data.rows();k++){
      for(int r=0;r<Data[k].essencialSize();r++)
	if(ell==Data[k].indexIndex(r)){
	  df++;
	  break;
	}
    }
    IDF[ell]=log(1.0+(double)Data.rows()/df);
  }
  for(int k=0;k<Data.rows();k++)
    for(int ell=0;ell<Data[k].essencialSize();ell++)
      Data[k].elementIndex(ell)
	=TF[k].elementIndex(ell)*IDF[Data[k].indexIndex(ell)];
  return;
}
