#include"sparseMatrix.h"
#include"matrix.h"
//欠損のさせ方を何通りにするか
#define MISSINGTRIALS 5
//クラスタリングの初期値を何通りにするか
#define CLUSTERINGTRIALS 10
//BookCrossingは10240欠損させる
//他は20480欠損させる
//BEGINは最初の欠損数，ENDは最大の欠損数
#ifdef BOOK
#define BEGIN 10000
#define END 10000
#elif defined SUSHI
#define BEGIN 10000
#define END 10000
#else
#define BEGIN 20000
#define END 20000
#endif

//人工データ欠損数
#define MAX_KESSON 7500
#define KIZAMI 500

#ifndef __RECOM__
#define __RECOM__

class Recom{
protected:
  //欠損数，欠損のさせ方を決めるシード値
  int Miss, SEED, SEED2;
  //クラスタリング初期値ループ数，欠損のさせ方ループ数
  int Current, CCurrent;
  //欠損後データ
  SparseMatrix SparseIncompleteData;
  //欠損前データ
  SparseMatrix SparseCorrectData;
  //欠損させた箇所，類似度
  Matrix KessonIndex, Similarity;
  //行帰属度，列帰属度
  Matrix Mem, ItemMem;
  //予測評価値
  Vector Prediction;
  //欠損させた箇所のスパースデータの列番号
  Vector SparseIndex;
  //Recall，Fallout
  Vector TP_FN, FP_TN;
  //目的関数値
  Vector Obje;
 public:
  //ユーザ数，アイテム数，行クラスタ数，列クラスタ数，欠損数
  Recom(int user,
        int item,
	int user_cen,
	int item_cen,
	int miss);
  Vector obje(void) const;
  Matrix kessonindex(void) const;
  double similarity(int, int);
  double &obje(int index);
  int &current(void);
  int &Ccurrent(void);
  int &miss(void);
  int seed2(void);
  //欠損のさせ方の初期化
  void Seed(void);
  //欠損のさせ方の最大シード値を保存
  void Seed2(int i);
  //初期化
  void reset(void);
  //データを欠損
  void revise_missing_values(int missing);
  //欠損させた箇所，正解値，予測値の保存
  void defect_pred_ofile(int missing, std::string dat);
  //MAEの計算，textに保存
  double MAE(int missing, std::string text);
  //F-measureの計算，textに保存，indexはROC用ループ添字
  double F_measure(int missing, int index,
		   std::string text);
  //ROCで必要な値をtextに保存
  void ROC(std::string text);
  //ROCの横軸の値で小さい順にソート
  void Sort(Vector &fal, Vector &tru, int index);
  //クラスタリングのみで予測値計算
  void revise_prediction(int missing);
  //ピアソン相関家数計算
  void pearsonsim(void);
  //行クラスタでフィルタにかけた状態で相関係数計算
  void pearsonsim_clustering(void);
  //PCM用類似度計算
  void pearsonsim_for_pcm(const Matrix Membership, const Vector Threshold);
  //予測値計算:FireFly
  void pearsonpred1(int missing);
  //予測値計算:GroupLens
  void pearsonpred2(int missing);
  //indexのユーザの既評価値平均を計算
  double user_average(int index);
  SparseMatrix sparsecorrectdata(void) const;
  SparseVector &sparsecorrectdata(int index);
  SparseMatrix sparseincompletedata(void) const;
  SparseVector &sparseincompletedata(const int &index);
  //収束した帰属度をクリスプ化
  void crisp(const Matrix &Membership, const Matrix &ItemMembership);
  //AUCの計算，text1に読み込むROCファイル，text2に平均AUCを保存
  //ついでにMAEとF-measureの平均値も出力
  void roc_area(std::string text1, std::string text2,
		  double mae, double f, int miss);
  //maeとfmeasure出力
  void mae_f_out(std::string, double, double, int);
  //Seedとか保存
  void ofs_seed(int missing, std::string text);
};
//ユーザ数を返す
int return_user_number(void);
//アイテム数を返す
int return_item_number(void);
//設定した閾値を返す
double return_threshold(void);
//最大評価値を返す
double return_max_value(void);
//データの名前を返す
std::string return_data_name(void);
//textを改行する
void FILE_ENDL(std::string text);
//何通りかの初期値を与えた場合，目的関数最大時のROCのを選ぶ
void Rename(std::string filename, std::string newname);

#endif
