#include"../src/recom.h"

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

int main(void){
  std::vector<std::string> dirs = Mkdir({"FIREFLY", "GROUPLENS"});
  //Recomクラスの生成
  Recom recom(user_number, item_number, 0, 0, KESSON);
  //時間計測
  auto start=std::chrono::system_clock::now();
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
    recom.revise_missing_values_new();
    //FIREFLY Methodで予測
    recom.reset2();
    recom.pearsonsim();
    recom.pearsonpred1();
    recom.mae(dirs[0], 0);
    recom.fmeasure(dirs[0], 0);
    recom.roc(dirs[0]);
    recom.reset2();
    recom.pearsonpred2();
    recom.mae(dirs[1], 1);
    recom.fmeasure(dirs[1], 1);
    recom.roc(dirs[1]);
    recom.choice_mae_f(dirs, 0);
  }
  //AUC，MAE，F-measureの平均を計算，出力
  recom.precision_summury(dirs);
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
  for(int i=0;i<(int)dirs.size();i++)
    rename(dirs[i].c_str(), (dirs[i]+time).c_str());
  return 0;
}
