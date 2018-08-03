#include"../src/recom.h"
#include"../src/epcs.h"

//収束条件
#define MAX_ITE 1000
#define DIFF_FOR_STOP 1.0E-10
//ユーザ数
const int user_number=return_user_number();
//アイテム数
const int item_number=return_item_number();
//最大評価値
const double max_value=return_max_value();
//データの名前
const std::string data_name=return_data_name();
//入力するデータの場所
const std::string InputDataName="data/2018/sparse_"+data_name
  +"_"+std::to_string(user_number)
  +"_"+std::to_string(item_number)+".txt";
//クラスタリング手法名
const std::string METHOD_NAME="EPCS";
constexpr int clusters_number=1;

int main(void){
  std::string c_p = current_path();
  c_p = c_p + "/../../RESULT";
  //RESULTフォルダを作る
  mkdir(c_p.c_str(),0755);
  //RESULT下に手法名＋データ名＋最大欠損数という名のフォルダを作る
  const std::string d=
    c_p+"/"+METHOD_NAME
    +"_"+data_name+std::to_string(END);
  mkdir(d.c_str(),0755);
  //Recomクラスの生成
  Recom recom(user_number, item_number,
	      clusters_number, clusters_number, END);
  //SparseAfccmdクラスの生成
  for(double l=60;l<=100;l+=10){
    for(double alpha=0.0001;alpha<=0.1;alpha*=10){
      //時間計測
      auto start=std::chrono::system_clock::now();
      EPCS test(item_number, user_number,
		clusters_number, l, alpha);
      //有効数字5桁で表示
      std::ostringstream oss2, oss3;
      oss2<<std::setprecision(15)<<l;
      oss3<<std::setprecision(15)<<alpha;
      std::string fuzzifier2(oss2.str());
      std::string fuzzifier3(oss3.str());
      const std::string dir=d+"/"+METHOD_NAME+"_"
	+std::string(fuzzifier2)+"_"
	+std::string(fuzzifier3);
      //データ名，パラメータ，クラスタ数ごとにフォルダ作成
      mkdir(dir.c_str(),0755);
      //ROCフォルダ作成
      const std::string roc=dir+"/ROC";
      mkdir(roc.c_str(),0755);
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
      for(int miss=BEGIN;miss<=END;miss+=BEGIN){
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
	  //spherical用にデータを正規化する
	  test.ForSphericalData();
	  //ユーザ数分クラスタリングし，N*Nの帰属度を得る
	  for(int k=0;k<user_number;k++){
	    //変数初期化
	    test.reset();
	    //可能性クラスクラスタリング初期クラスタ中心
	    test.initialize_centers_one_cluster(k);
	    //クラスタリングループ数
	    test.iterates()=0;
	    while(1){
	      test.revise_dissimilarities();
	      test.revise_membership();
	      test.revise_centers();
	      double diff_v
		=max_norm(test.tmp_centers()-test.centers());
	      double diff_u
		=max_norm(test.tmp_membership()-test.membership());
	      double diff=diff_u+diff_v;
	      //std::cout<<diff_v<<" "<<diff_u<<std::endl;
	      if(std::isnan(diff)){
		std::cout<<"diff is nan \t"
			 <<l<<" "<<alpha<<std::endl;
		test.reset();
		exit(1);
	      }
	      if(diff<DIFF_FOR_STOP)break;
	      if(test.iterates()>=MAX_ITE)break;
	      test.iterates()++;
	    }
	    //目的関数値の計算
	    test.set_objective();
	    //帰属度保存
	    test.save_membebrship(k);
	  }
	  //PCM＋ピアソン相関係数の計算
	  recom.pearsonsim_for_pcm(test.membership_pcm(),
				   test.membership_threshold());
	  //grouplens計算
	  recom.pearsonpred2(miss);
	  //MAEの計算，保存
	  mae+=recom.MAE(miss,dir+"/"+METHOD_NAME+"MAE.txt");
	  //F-measureの計算，閾値ごとに行う
	  for(int siki=1;siki<=max_value*10;siki++)
	    fmeasure+=recom.F_measure(miss,siki,dir+"/"
				      +METHOD_NAME+"Fmeasure.txt");
	  std::string ROC_STR=roc+"/"+METHOD_NAME
	    +"ROC"+std::to_string(miss)+"_"
	    +std::to_string(recom.current())+"sort.txt";
	  //ROCのプロット点の出力
	  recom.ROC(ROC_STR);
	}
	//AUC，MAE，F-measureの平均を計算，出力
	recom.roc_area(roc+"/"+METHOD_NAME+"ROC",
		       dir+"/"+METHOD_NAME+"averageMaeFmeasureAuc.txt",
		       mae, fmeasure, miss);
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
    }//alpha
  }//lambda
  return 0;
}
