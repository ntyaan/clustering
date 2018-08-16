#include"../../src/recom.h"
#include"../../src/epcs.h"

//収束条件
#define MAX_ITE 1000
#define DIFF_FOR_STOP 1.0E-10

//ユーザ数
const int user_number=return_user_number();
//アイテム数
const int item_number=return_item_number();
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
  std::vector<std::string> dirs = MkdirFCS(METHOD_NAME);
  //Recomクラスの生成
  Recom recom(user_number, item_number,
	      clusters_number, clusters_number, KESSON);
  recom.method_name()=METHOD_NAME;
  for(double lambda=60;lambda<=100;lambda+=10){
    for(double alpha=0.0001;alpha<=0.1;alpha*=10){
      //時間計測
      auto start=std::chrono::system_clock::now();
      EPCS test(item_number, user_number,
		clusters_number, lambda, alpha);
      std::vector<double> parameter= {lambda};
      std::vector<std::string> dir
	= Mkdir(parameter, clusters_number, dirs);
      //データ入力
      recom.input(InputDataName);
      //欠損数
      recom.missing()=KESSON;
      //シード値の初期化
      recom.Seed();
      //欠損のさせ方ループ
      for(recom.current()=0;recom.current()
	    <MISSINGTRIALS;recom.current()++){
	//初期化
	recom.reset();
	//データを欠損
	recom.revise_missing_values();
	//データをtestに渡す
	test.copydata(recom.sparseincompletedata());
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
	    if(std::isnan(diff)){
	      std::cout<<"diff is nan \t"
		       <<lambda<<" "<<alpha<<std::endl;
	      test.reset();
	      exit(1);
	    }
	    if(diff<DIFF_FOR_STOP)break;
	    if(test.iterates()>=MAX_ITE)break;
	    test.iterates()++;
	  }
	  //帰属度保存
	  test.save_membebrship(k);
	}
	//PCM＋ピアソン相関係数の計算
	recom.pearsonsim_for_pcm(test.membership_pcm(),
				 test.membership_threshold());
	//grouplens計算
	recom.pearsonpred2();
	recom.mae(dir[0], 0);
	recom.fmeasure(dir[0], 0);
	recom.roc(dir[0]);
	recom.obje(recom.Ccurrent())=-1;
	recom.ofs_objective(dir[0]);
	test.ofs_selected_data(dir[0]);
	recom.choice_mae_f(dir);
      }//number of missing values
      //AUC，MAE，F-measureの平均を計算，出力
      recom.precision_summury(dir);
      //計測終了
      auto end=std::chrono::system_clock::now();
      auto endstart=end-start;
      std::string time="_"
	+std::to_string
	(std::chrono::duration_cast<std::chrono::hours>(endstart).count())
	+"h"+std::to_string
	(std::chrono::duration_cast<std::chrono::minutes>(endstart).count()%60)
	+"m"+std::to_string
	(std::chrono::duration_cast<std::chrono::seconds>(endstart).count()%60)
	+"s";
      //計測時間でリネーム
      for(int i=0;i<(int)dir.size();i++)
	rename(dir[i].c_str(), (dir[i]+time).c_str());
    }//alpha
  }//lambda
  return 0;
}
