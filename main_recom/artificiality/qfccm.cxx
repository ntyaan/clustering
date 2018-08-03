#include"../../src/recom.h"
#include"../../src/qfccm.h"

//収束条件
#define MAX_ITE 1000
#define DIFF_FOR_STOP 1.0E-10
//ユーザ数
const int user_number=return_user_number();
//アイテム数
const int item_number=return_item_number();
//データの名前
const std::string data_name=return_data_name();
//正解のクリスプ帰属度ファイル名
const std::string correctcrisp
="data/2018/artificiality_100_100_correctCrispMembership.txt";
//入力するデータの場所
const std::string InputDataName="data/2018/sparse_"+data_name
  +"_"+std::to_string(user_number)
  +"_"+std::to_string(item_number)+".txt";
//クラスタリング手法名
const std::string METHOD_NAME="QFCCM";

int main(void){
  std::string c_p = current_path();
  c_p = c_p + "/../../RESULT";
  //RESULTフォルダを作る
  mkdir(c_p.c_str(),0755);
  //RESULT下に手法名＋データ名＋最大欠損数という名のフォルダを作る
  const std::string d=
    c_p+"/"+METHOD_NAME
    +"_"+data_name+std::to_string(MAX_KESSON);
  mkdir(d.c_str(),0755);
  //クラスタ数でループ
  for(int clusters_number=4;clusters_number<=6;clusters_number++){
    //Recomクラスの生成
    Recom recom(user_number, item_number,
		clusters_number, clusters_number, MAX_KESSON);
    //パラメータmでループ
    for(double m=1.0001;m<=1.001;m+=0.0003){
      //パラメータlambdaでループ
      for(double l=10;l<=40;l+=10){
	double summae=0.0;
	//時間計測
	auto start=std::chrono::system_clock::now();
	//SparseAfccmdクラスの生成
	QFCCM test(item_number, user_number,
		   clusters_number, m, l);
	//有効数字5桁で表示
	std::ostringstream oss1,oss2;
	oss1<<std::setprecision(15)<<m;
	oss2<<std::setprecision(15)<<l;
	std::string fuzzifier1(oss1.str());
	std::string fuzzifier2(oss2.str());
	const std::string dir=d+"/"+METHOD_NAME+"_"
	  +std::string(fuzzifier1)+"-"
	  +std::string(fuzzifier2)
	  +"_C"+std::to_string(clusters_number);
	//データ名，パラメータ，クラスタ数ごとにフォルダ作成
	mkdir(dir.c_str(),0755);
	//データ入力
	std::ifstream ifs(InputDataName);
	if(!ifs){
	  std::cerr << "DirectoryName: could not open." << std::endl;
	  exit(1);
	}
	for(int cnt=0;cnt<user_number;cnt++){
	  int essencialSize;
	  ifs >> essencialSize;
	  SparseVector dummy(item_number, essencialSize);
	  for(int ell=0;ell<essencialSize;ell++){
	    ifs >> dummy.indexIndex(ell) >> dummy.elementIndex(ell);
	  }
	  recom.sparsecorrectdata(cnt)=dummy;
	}
	ifs.close();
	//欠損数ループ
	for(int miss=100;miss<=MAX_KESSON;miss+=100){
	  //シード値の初期化
	  recom.Seed();
	  double mae=0.0,fmeasure=0.0;
	  //欠損のさせ方ループ
	  for(recom.current()=0;recom.current()
		<MISSINGTRIALS;recom.current()++){
	    std::cout<<"cause missing values:"
		     <<recom.current()<<std::endl;
	    //シード値の保存
	    recom.Seed2(recom.current());
	    //シード値の初期化
	    recom.Seed();
	    recom.reset();
	    //データを欠損
	    recom.revise_missing_values(miss);
	    //データをtestに渡す
	    test.copydata(recom.sparseincompletedata());
	    //MMM用にデータを正規化する
	    test.ForMMMData();
	    //初期クラスタサイズ調整変数の設定
	    test.initialize_clustersize();
	    //初期帰属度の設定
	    test.initialize_membership(correctcrisp);
	    //クラスタリングループ数
	    test.iterates()=0;
	    while(1){
	      test.revise_centers();
	      test.revise_dissimilarities();
	      test.revise_membership();
	      test.revise_clusters_size();
	      double diff_v
		=max_norm(test.tmp_centers()-test.centers());
	      double diff_u
		=max_norm(test.tmp_membership()-test.membership());
	      double diff_p
		=max_norm(test.tmp_clusters_size()-test.clusters_size());
	      double diff=diff_u+diff_v+diff_p;
	      if(std::isnan(diff)){
		std::cout<<"diff is nan \t"
			 <<l<<"\tC:"<<clusters_number<<std::endl;
		test.reset();
		exit(1);
	      }
	      if(diff<DIFF_FOR_STOP)break;
	      if(test.iterates()>=MAX_ITE)break;
	      test.iterates()++;
	    }
	    //目的関数値の計算
	    test.set_objective();
	    //recomに目的関数値を渡す
	    recom.obje(recom.Ccurrent())=test.objective();
	    //recomに帰属度を渡してクリスプ化
	    recom.crisp(test.membership(),test.centers());
	    //クラスタリング＋ピアソン相関係数の計算
	    recom.pearsonsim_clustering();
	    //GroupLen Methodで予測
	    recom.pearsonpred2(miss);
	    //MAEの計算，保存
	    mae+=recom.MAE(miss,dir+"/"+METHOD_NAME+"MAE.txt");
	    //F-measureの計算
	    fmeasure+=recom.F_measure(miss,35,dir+"/"
				      +METHOD_NAME+"Fmeasure.txt");
	    //シード値とかクラスタ中心として選ばれたデータとか保存
	    recom.ofs_seed(miss, dir+"/object.txt");
	    //partitioncofficientとか目的関数値とか保存
	    test.ofs_selected_data(dir+"/object.txt");
	  }
	  //AUC，MAE，F-measureの平均を計算，出力
	  recom.mae_f_out(dir+"/"+METHOD_NAME+"averageMaeFmeasureAuc"
			  +std::to_string(clusters_number)+".txt",
			  mae, fmeasure, miss);
	  summae+=mae;
	}//number of missing values
	//計測終了
	auto end=std::chrono::system_clock::now();
	auto endstart=end-start;
	std::string dirname=dir
	  +"_"+std::to_string
	  (std::chrono::duration_cast<std::chrono::hours>(endstart).count())
	  +"h"+std::to_string
	  (std::chrono::duration_cast<std::chrono::minutes>(endstart).count()%60)
	  +"m"+std::to_string
	  (std::chrono::duration_cast<std::chrono::seconds>(endstart).count()%60)
	  +"s";
	//計測時間でリネーム
	if(rename(dir.c_str(),dirname.c_str())==0)
	  std::cout<<"rename\n";
	else
	  std::cout<<"rename 失敗\n";
      }//lambda
    }//m
  }//number of clusters
  return 0;
}
