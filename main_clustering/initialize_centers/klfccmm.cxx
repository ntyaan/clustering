#include"../../src/klfccmm.h"
#include"../data_doc.h"

//収束条件
#define MAX_ITERATES 10000
#define DIFF_FOR_STOP 1.0E-6
std::string method=
  "SimplexData";
//"tfidf1-SimplexData";
//"tfidf2-SimplexData";
constexpr int PARAMETER = 5;
constexpr int INIT_CENTERS = 10;

int main(void){
  std::string c_p = current_path();
  std::ofstream ofs_ari("ARI-KLFCCMM-"+method+"_init_centers.txt", std::ios::app);
  for(int INDEX=0;INDEX<(int)centers.size();INDEX++){
    const int centers_number=centers[INDEX];
    const std::string file=files[INDEX];
    std::cout<<files[INDEX]<<std::endl;
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
    //tfidf1(Data);
    //ARIテキスト書き込み
    std::ofstream ofs("ARI-KLFCCMM-"+method+"-"+file+".txt", std::ios::app);
    double Parameter[PARAMETER]={0.5, 1.0, 10, 100, 1000};
    double Parameter3[PARAMETER]={1.0E-6, 1.0E-4, 0.01, 0.1, 0.5};
    KLFCCMM test(data_dimension, data_number, centers_number, 0, 0);
    //正解の帰属度の読み込み
    std::ifstream ifs_correctCrispMembership
      (filenameCorrectCrispMembership);
    if(!ifs_correctCrispMembership){
      std::cerr << "File:" << filenameCorrectCrispMembership
		<< "could not open." << std::endl;
      exit(1);
    }
    //読み込んだ正解の帰属度を格納
    for(int i=0;i<centers_number;i++)
      for(int k=0;k<data_number;k++)
	ifs_correctCrispMembership >> test.correctCrispMembership(i,k);
    ifs_correctCrispMembership.close();
    //データを与える
    test.copydata(Data);
    test.ForMMMData();
    double average_ari=-1.0, sd=0.0, params0=0.0, params1=0.0, min_obje_ari=0.0;
    for(int index=0;index<PARAMETER;index++){
      for(int index3=0;index3<PARAMETER;index3++){
	test.fuzzifierLambda()=Parameter[index];
	test.fuzzifierEt()=Parameter3[index3];
	std::vector<double> ARIs(INIT_CENTERS);
	int FALSE=0, Index=0; double sumARI=0.0, min_objective=DBL_MAX;
	for(int ite=0;ite<INIT_CENTERS;ite++){
	  test.reset();
	  //初期クラスタサイズ調整変数
	  test.initialize_clustersize();
	  //初期クラスタ中心
	  test.initialize_centers(ite+FALSE);
	  //時間計測
	  auto start=std::chrono::system_clock::now();
	  //更新式ループ回数
	  test.iterates()=0;
	  int p=1;
	  double savediff=0.0;
	  while(1){
	    test.revise_dissimilarities();
	    test.revise_membership();
	    test.revise_centers();
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
	    //収束したらクラスタリング終了
	    if(diff<DIFF_FOR_STOP)break;
	    if(test.iterates()>=MAX_ITERATES)break;
	    test.iterates()++;
	    if(std::isnan(diff)){
	      FALSE++;
	      ite--;
	      p=-1;
	      break;
	    }
	  }
	  if(p==1){
	    //std::cout<<"loop:"<<test.iterates()<<"\n";
	    test.set_crispMembership();
	    test.set_contingencyTable();
	    test.set_objective();
	    ARIs[ite]=test.ARI();
	    //計測終了
	    auto end=std::chrono::system_clock::now();
	    auto endstart=end-start;
	    ofs<<test.fuzzifierLambda()<<"\t"
	       <<test.fuzzifierEt()<<"\t"
	       <<ARIs[ite]<<"\t"
	       <<savediff<<"\t"
	       <<test.iterates()<<"\t"
	       <<std::chrono::duration_cast
	      <std::chrono::hours>(endstart).count()<<":"
	       <<std::chrono::duration_cast
	      <std::chrono::minutes>(endstart).count()%60<<":"
	       <<std::chrono::duration_cast
	      <std::chrono::seconds>(endstart).count()%60<<"\t";
	    for(int j=0;j<test.initialize_c().size();j++)
	      ofs<<test.initialize_c()[j]<<" ";
	    ofs<<std::endl;
	    if(min_objective<test.objective()){
	      Index=ite;
	      min_objective=test.objective();
	    }
	    sumARI+=ARIs[ite];
	  }
	  else
	    ofs<<test.fuzzifierLambda()<<"\t"
	       <<"nan\t"
	       <<savediff<<"\t"
	       <<test.iterates()<<std::endl;
	}
	sumARI/=(double)INIT_CENTERS;
	double s=0.0;
	for(int j=0;j<INIT_CENTERS;j++)
	  s+=pow(ARIs[j]-sumARI,2.0);
	if(sumARI>average_ari){
	  average_ari=sumARI;
	  sd=sqrt(s/(double)INIT_CENTERS);
	  params0=test.fuzzifierLambda();
	  params1=test.fuzzifierEt();
	  min_obje_ari=ARIs[Index];
	}
      }
    }
    ofs.close();
    ofs_ari<<files[INDEX]<<std::endl
	   <<"KLFCCMM    & "<< average_ari
	   << " & " << sd
	   << " & " << min_obje_ari
	   << " & $\\lambda=" << params0
	   << "$ & $t="<< params1
	   << "$ \\\\\\hline" <<std::endl;
  }
  ofs_ari.close();
  return 0;
}
