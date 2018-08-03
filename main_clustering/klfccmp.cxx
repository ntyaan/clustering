#include"../src/klfccmp.h"
#include"data_doc.h"

//収束条件
#define MAX_ITERATES 100000
#define DIFF_FOR_STOP 1.0E-6

#define INDEX 4
const int centers_number=centers[INDEX];
const std::string file=files[INDEX];

int main(void){
  //読み込むデータファイル
  std::string filenameData 
    ="data/clustering/"+files[INDEX]+"/sparse_"+files[INDEX]+".txt";
  //読み込むデータファイルの正解の帰属度ファイル
  std::string filenameCorrectCrispMembership
    ="data/clustering/"+files[INDEX]+"/"+files[INDEX]+"_correct.txt";
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
  //SparseKLFCSクラスの生成
  KLFCCMP test(data_dimension, data_number, centers_number, 1.1);
  //読み込んだデータを格納
  for(int cnt=0;cnt<data_number;cnt++){
    int essencialSize;
    ifs >> essencialSize;
    SparseVector dummy(data_dimension, essencialSize);
    //double tmp=0.0;
    for(int ell=0;ell<essencialSize;ell++){
      ifs >> dummy.indexIndex(ell) >> dummy.elementIndex(ell);
      //dummy.elementIndex(ell)*=2.0;
    }
    test.data(cnt)=dummy;
  }
  //正解の帰属度の読み込み
  std::ifstream ifs_correctCrispMembership
    (filenameCorrectCrispMembership);
  if(!ifs_correctCrispMembership){
    std::cerr << "File:" << filenameCorrectCrispMembership
	      << "could not open." << std::endl;
    exit(1);
  }
  //正解clustersize
  Vector C(centers_number);
  //読み込んだ正解の帰属度を格納
  for(int i=0;i<test.centers_number();i++){
    C[i]=0;
    for(int k=0;k<test.data_number();k++){
      ifs_correctCrispMembership >> test.correctCrispMembership(i,k);
      //正解の帰属度を与える
      if(test.correctCrispMembership(i, k)==0)
	test.membership(i,k)
	  =((centers_number-1.0)/100.0)/(centers_number-1.0);
      else{
        test.membership(i,k)=1.0-(centers_number-1.0)/100.0;
	C[i]++;
      }
    }
  }
  //時間計測
  auto start=std::chrono::system_clock::now();
  //test.ForMMMData();
  //初期クラスタサイズ調整変数
  for(int i=0;i<test.centers_number();i++)
    test.clusters_size(i)=(double)C[i]/(double)data_number;
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
