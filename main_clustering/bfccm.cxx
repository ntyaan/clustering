#include"../src/bfccm.h"
#include"data_doc.h"

//収束条件
#define MAX_ITERATES 10000
#define DIFF_FOR_STOP 1.0E-6
std::string method=
  "FreqData";
  // "SimplexData";
  //"tfidf1-SimplexData";
  //"tfidf2-SimplexData";
constexpr int PARAMETER = 5;

int main(void){
  std::string c_p = current_path();
  for(int INDEX=0;INDEX<(int)centers.size();INDEX++){
    const int centers_number=centers[INDEX];
    const std::string file=files[INDEX];
    //読み込むデータファイル
    std::string filenameData 
      =c_p+"/../../data/"+files[INDEX]+"/sparse_"+files[INDEX]+".txt";
    //読み込むデータファイルの正解の帰属度ファイル
    std::string filenameCorrectCrispMembership
      =c_p+"/../../data/"+files[INDEX]+"/"+files[INDEX]+"_correct.txt";
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
    SparseMatrix Data(data_number, data_dimension);
    //読み込んだデータを格納
    for(int cnt=0;cnt<data_number;cnt++){
      int essencialSize;
      ifs >> essencialSize;
      SparseVector dummy(data_dimension, essencialSize);
      for(int ell=0;ell<essencialSize;ell++){
	ifs >> dummy.indexIndex(ell) >> dummy.elementIndex(ell);
      }
      Data[cnt]=dummy;
    }
    ifs.close();
    //tfidf2(Data);
    Matrix CorrectMembership(centers_number, data_number);
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
    for(int i=0;i<centers_number;i++){
      C[i]=0;
      for(int k=0;k<data_number;k++){
	ifs_correctCrispMembership >> CorrectMembership[i][k];
	//正解の帰属度を与える
	if(CorrectMembership[i][k]==1)
	  C[i]++;
      }
    }
    ifs_correctCrispMembership.close();
    //ARIテキスト書き込み
    std::ofstream ofs("ARI-BFCCM-"+method+"-"+file+".txt", std::ios::app);
    double Parameter[PARAMETER]={1.00001, 1.0001, 1.001, 1.01, 1.1};
    BFCCM test(data_dimension, data_number, centers_number, 0);
    //データを与える
    test.copydata(Data);
    test.ForMMMData();
    for(int index=0;index<PARAMETER;index++){
      test.fuzzifierEm()=Parameter[index];
      //ファジィな正解帰属度を与える
      for(int i=0;i<centers_number;i++){
	//初期クラスタサイズ調整変数
	test.clusters_size(i)=(double)C[i]/(double)data_number;
	for(int k=0;k<data_number;k++){
	  test.correctCrispMembership(i,k)=CorrectMembership[i][k];
	  if(test.correctCrispMembership(i, k)==0)
	    test.membership(i,k)
	      =((centers_number-1.0)/100.0)/(centers_number-1.0);
	  else
	    test.membership(i,k)=1.0-(centers_number-1.0)/100.0;
	}
      }
      //時間計測
      auto start=std::chrono::system_clock::now();
      //更新式ループ回数
      test.iterates()=0;
      int p=1;
      double savediff=0.0;
      while(1){
	test.revise_centers();
	test.revise_dissimilarities();
	test.revise_membership();
	test.revise_clusters_size();
	//帰属度の収束具合
	double diff_u=max_norm(test.tmp_membership()-test.membership());
	//クラスタ中心の収束具合
	double diff_v=max_norm(test.tmp_centers()-test.centers());
	//クラスタ混合比の収束具合
	double diff_p=max_norm(test.tmp_clusters_size()-test.clusters_size());
	//全体の収束具合
	double diff=diff_u+diff_v+diff_p;
	savediff=diff;
	//std::cout<<diff_u<<" "<<diff_v<<" "<<diff_p<<std::endl;
	//収束したらクラスタリング終了
	if(diff<DIFF_FOR_STOP)break;
	if(test.iterates()>=MAX_ITERATES)break;
	test.iterates()++;
	if(std::isnan(diff)){
	  p=-1;
	  break;
	}
      }
      if(p==1){
	std::cout<<"loop:"<<test.iterates()<<"\n";
	test.set_crispMembership();
	test.set_contingencyTable();
	std::cout << "Contingency Table:\n"
		  << test.contingencyTable()
		  << std::endl;
	std::cout << "ARI:" << test.ARI()
		  << std::endl;
	//計測終了
	auto end=std::chrono::system_clock::now();
	auto endstart=end-start;
	ofs<<test.fuzzifierEm()<<"\t"
	   <<test.ARI()<<"\t"
	   <<savediff<<"\t"
	   <<test.iterates()<<"\t"
	   <<std::chrono::duration_cast
	  <std::chrono::hours>(endstart).count()<<":"
	   <<std::chrono::duration_cast
	  <std::chrono::minutes>(endstart).count()%60<<":"
	   <<std::chrono::duration_cast
	  <std::chrono::seconds>(endstart).count()%60<<std::endl;
      }
      else
	ofs<<test.fuzzifierEm()<<"\t"
	   <<"nan\t"
	   <<savediff<<"\t"
	   <<test.iterates()<<std::endl;
      test.reset();
    }
    ofs.close();
  }
  return 0;
}
