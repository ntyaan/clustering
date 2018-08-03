#include"../src/recom.h"

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
//手法名
const std::string METHOD_NAME="GROPELENS";

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
  Recom recom(user_number, item_number, 0, 0, END);
  //時間計測
  auto start=std::chrono::system_clock::now();
  const std::string dir=d+"/"+METHOD_NAME;
  //データ名ごとにフォルダ作成
  mkdir(dir.c_str(),0755);
  //ROCフォルダ作成
  const std::string roc=dir+"/ROC";
  mkdir(roc.c_str(),0755);
  //選ばれるROCファイルをまとめるフォルダ作成
  const std::string choice=roc+"/choice";
  mkdir(choice.c_str(),0755);
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
      //データ初期化
      recom.reset();
      //データを欠損
      recom.revise_missing_values(miss);
      //ピアソン相関係数の計算
      recom.pearsonsim();
      //GroupLens Methodで予測
      recom.pearsonpred2(miss);
      //MAEの計算，保存
      mae+=recom.MAE(miss,dir+"/"+METHOD_NAME+"MAE.txt");
      //F-measureの計算，閾値ごとに行う
      for(int siki=1;siki<=max_value*10;siki++)
        fmeasure
	  +=recom.F_measure(miss,siki,dir+"/"+METHOD_NAME+"Fmeasure.txt");
      //ROCのプロット点の出力
      std::string ROC_STR
	=roc+"/"+METHOD_NAME+"ROC"+std::to_string(miss)+"_"
	+std::to_string(recom.current())+"sort.txt";
      recom.ROC(ROC_STR);
      //シード値とかクラスタ中心として選ばれたデータとか保存
      recom.ofs_seed(miss, dir+"/object.txt");
      FILE_ENDL(dir+"/object.txt");
      //選ばれたROCをchoiceフォルダに移す
      std::string oldname
	=roc+"/"+METHOD_NAME+"ROC"
	+std::to_string(miss)+"_"
	+std::to_string(recom.current())+"sort.txt";
      std::string newname
	=choice+"/"+METHOD_NAME+"ROC"
	+std::to_string(miss)+"_"
	+std::to_string(recom.current())+"sort.txt";
      Rename(oldname,newname);
    }
    //AUC，MAE，F-measureの平均を計算，出力
    recom.roc_area(choice+"/"+METHOD_NAME+"ROC"
		   ,dir+"/"+METHOD_NAME+"averageMaeFmeasureAuc.txt"
		   ,mae,fmeasure,miss);
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
  return 0;
}
