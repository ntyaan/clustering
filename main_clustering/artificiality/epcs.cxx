#include"../../src/epcs.h"

//収束条件
#define MAX_ITERATES 1000000
#define DIFF_FOR_STOP 1.0E-10

//クラスタ数
const int centers_number=4;

int main(void){
  // for(double l=1.0;l<=5.0;l+=0.1){
  //for(double a=0.1;a<=5.0;a+=0.1){
  //std::cout<<l<<" "<<a<<std::endl;
  //読み込むデータファイル
  std::string filenameData 
    ("data/clustering/test/sparse_spherical.txt");
  //読み込むデータファイルの正解の帰属度ファイル
  std::string filenameCorrectCrispMembership
    ("data/clustering/test/correct_test.txt");
  //データの読み込み
  std::ifstream ifs(filenameData);
  if(!ifs){
    std::cerr << "File:" << filenameData
	      << " could not open." << std::endl;
    exit(1);
  }
  //読み込んだデータ行数，データ列数を格納
  int data_number, data_dimension;
  ifs >> data_number;
  ifs >> data_dimension;
  EPCS test(data_dimension, data_number, centers_number, 100, 0.01);
  //読み込んだデータを格納
  for(int cnt=0;cnt<data_number;cnt++){
    int essencialSize;
    ifs >> essencialSize;
    SparseVector dummy(data_dimension, essencialSize);
    //double tmp=0.0;
    for(int ell=0;ell<essencialSize;ell++)
      ifs >> dummy.indexIndex(ell) >> dummy.elementIndex(ell);
    test.data(cnt)=dummy;
  }
  ifs.close();
  //正解の帰属度の読み込み
  std::ifstream ifs_correctCrispMembership
    (filenameCorrectCrispMembership);
  if(!ifs_correctCrispMembership){
    std::cerr << "File:" << filenameCorrectCrispMembership
	      << "could not open." << std::endl;
    exit(1);
  }
  //読み込んだ正解の帰属度を格納
  for(int i=0;i<test.centers_number();i++){
    for(int k=0;k<test.data_number();k++){
      ifs_correctCrispMembership >> test.correctCrispMembership(i,k);
      //正解の帰属度を与える
      test.membership(i,k) = test.correctCrispMembership(i,k);
    }
  }
  ifs_correctCrispMembership.close();
  //時間計測
  auto start=std::chrono::system_clock::now();
  //更新式ループ回数
  test.iterates()=0;
  while(1){
    //初期値に何を与えるかで計算順序を変える必要あり
    test.revise_centers();
    test.revise_dissimilarities();
    test.revise_membership();
    //帰属度の収束具合
    double diff_u=max_norm(test.tmp_membership()-test.membership());
    //クラスタ中心の収束具合
    double diff_v=max_norm(test.tmp_centers()-test.centers());
    //全体の収束具合
    double diff=diff_u+diff_v;
    //diffの出力

    std::cout<<"diff_u:"<<diff_u
	     <<"\tdiff_v:"<<diff_v
	     <<"\tdiff:"<<diff<<std::endl;
    //収束したらクラスタリング終了
    if(diff<DIFF_FOR_STOP)break;
    if(test.iterates()>=MAX_ITERATES)break;
    test.iterates()++;
  }
  std::cout<<"loop:"<<test.iterates()<<"\n";
  test.set_crispMembership();
  test.set_contingencyTable();
  std::cout << "Contingency Table:\n"
	    << test.contingencyTable()
	    << std::endl;
  std::cout << "ARI:" << test.ARI()
	    << std::endl;
  //}
  //確認
  //test.print_frobenius_norm();
  //計測終了
  auto end=std::chrono::system_clock::now();
  auto endstart=end-start;
  std::cout<<std::chrono::duration_cast
    <std::chrono::hours>(endstart).count()<<":"
	   <<std::chrono::duration_cast
    <std::chrono::minutes>(endstart).count()%60<<":"
	   <<std::chrono::duration_cast
    <std::chrono::seconds>(endstart).count()%60<<std::endl;
  //}
  // }
  std::cout<<test.membership()<<std::endl;
  std::cout<<test.centers()<<std::endl;
  return 0;
}
