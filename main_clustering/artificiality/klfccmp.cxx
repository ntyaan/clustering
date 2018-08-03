#include"../../src/klfccmp.h"

//収束条件
#define MAX_ITERATES 100000
#define DIFF_FOR_STOP 1.0E-10

//クラスタ数
const int centers_number=4;

int main(void){
  //読み込むデータファイル
  std::string filenameData 
    ("data/clustering/test/sparse_multinomial.txt");
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
  KLFCCMP test(data_dimension, data_number, centers_number, 1.0);
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
  //test.ForMMMData();
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
  //時間計測
  auto start=std::chrono::system_clock::now();
  //初期クラスタサイズ調整変数
  test.initialize_clustersize();
  test.initialize_alpha();
  test.data_k();
  //更新式ループ回数
  test.iterates()=0;
  double plik=0.0;
  while(1){
    //初期値に何を与えるかで計算順序を変える必要あり
    test.revise_centers();
    test.revise_dissimilarities();
    test.revise_membership();
    test.revise_clusters_size();
    double likelihood=test.pseudoLogLikelihood();
    std::cout << "likelihood: " << likelihood << std::endl;
    test.set_crispMembership();
    test.set_contingencyTable();
    std::cout << "Contingency Table:\n" << test.contingencyTable() << std::endl;  
    std::cout << "l:" << test.fuzzifierLambda() << std::endl;
    std::cout << "ARI:" << test.ARI() << std::endl;
    if((test.iterates()>1)&&(fabs((likelihood-plik)/likelihood)<1.0E-4))
      break;
    plik=likelihood;
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

  std::string filenameResultCenters
    ="centers.txt";
  std::ofstream ofs_centers(filenameResultCenters);
  if(!ofs_centers){
    std::cerr << "File:" << filenameResultCenters
	      << "could not open." << std::endl;
    exit(1);
  }
  for(int i=0;i<test.centers_number();i++){
    for(int ell=0;ell<test.dimension();ell++){
      ofs_centers <<test.centers()[i][ell]/100.0 << "\t";
    }
    ofs_centers << std::endl;
  }
  ofs_centers.close();

  std::string FuzzyClassFunc1
    ="fucntion.txt";
  std::ofstream ofs_FuzzyClassFunc1(FuzzyClassFunc1);
  if(!ofs_FuzzyClassFunc1){
    std::cerr << "File:" << FuzzyClassFunc1
	      << "could not open." << std::endl;
    exit(1);
  }
  
  KLFCCMP classify1(data_dimension,1,centers_number,test.fuzzifierLambda());
  for(int ell=0;ell<test.dimension();ell++){
    for(int i=0;i<test.centers_number();i++){
      classify1.centers(i,ell)=test.centers(i,ell);
      classify1.clusters_size(i)=test.clusters_size(i);
    }
  }
  for(double a=0.0;a<100;a+=1.0){
    for(double b=0;b<100-a;b+=1.0){
      SparseVector d(data_dimension, 3);
      d.indexIndex(0)=0;
      d.elementIndex(0)=a;
      d.indexIndex(1)=1;
      d.elementIndex(1)=b;
      d.indexIndex(2)=2;
      d.elementIndex(2)=100-a-b;
      classify1.data(0)=d;
      classify1.data_k();
      classify1.revise_dissimilarities();
      classify1.revise_membership();
      ofs_FuzzyClassFunc1<<classify1.data(0).elementIndex(0)/100<<" ";
      ofs_FuzzyClassFunc1<<classify1.data(0).elementIndex(1)/100<<" ";
      ofs_FuzzyClassFunc1<<classify1.data(0).elementIndex(2)/100<<" ";
      double tmp=-DBL_MAX;
      for(int c=0;c<test.centers_number();c++){
	ofs_FuzzyClassFunc1<<classify1.membership(c,0)<<" ";
	if(tmp <=classify1.membership(c,0)){
	  tmp=classify1.membership(c,0);
	}
	if(c==3)
	  ofs_FuzzyClassFunc1<<tmp;       
      }
      ofs_FuzzyClassFunc1<<std::endl;
    }
    ofs_FuzzyClassFunc1<<std::endl;
  }
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
  return 0;
}
