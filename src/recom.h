#include"sparseMatrix.h"
#include"matrix.h"
//欠損のさせ方を何通りにするか
#define MISSINGTRIALS 5
//クラスタリングの初期値を何通りにするか
#define CLUSTERINGTRIALS 10
//pearson, eicf, co-clustering
#define METHOD_NUMBER 2
//BookCrossingは10240欠損させる
//他は20480欠損させる
//BEGINは最初の欠損数，ENDは最大の欠損数
#ifdef BOOK
#define KESSON 10000
#elif defined SUSHI
#define KESSON 10000
#elif defined ARTIFICIALITY
#define KESSON 7500
#else
#define KESSON 20000
#endif

//人工データ欠損数
#define KIZAMI 500

#ifndef __RECOM__
#define __RECOM__

class Recom{
protected:
  std::string METHOD_NAME;
  //欠損のさせ方を決めるシード値
  int SEED;
  //欠損のさせ方ループ数，クラスタリング初期値ループ数，現在の欠損数
  int Current, CCurrent, Missing;
  //欠損後データ
  SparseMatrix SparseIncompleteData;
  //欠損前データ
  SparseMatrix SparseCorrectData;
  //球面正規データ
  SparseMatrix NormalizedData;
  //欠損させた箇所，類似度
  Matrix KessonIndex, Similarity;
  //行帰属度，列帰属度
  Matrix Mem, ItemMem;
  //MAE, F-measure, AUC
  Matrix resultMAE, resultFmeasure;
  Matrix choiceMAE, choiceFmeasure;
  //予測評価値
  Vector Prediction;
  //欠損させた箇所のスパースデータの列番号
  Vector SparseIndex;
  //Recall，Fallout
  Vector TP_FN, FP_TN;
  //目的関数値
  Vector Obje;
  //w of EICF
  Vector W;
 public:
  //ユーザ数，アイテム数，行クラスタ数，列クラスタ数，最大欠損数
  Recom(int user,
        int item,
	int user_cen,
	int item_cen,
	int miss);
  std::string &method_name(void);
  Vector obje(void) const;
  Matrix kessonindex(void) const;
  double similarity(int, int);
  double &obje(int index);
  int &current(void);//欠損のさせ方番号
  int &Ccurrent(void);//クラスタリングの初期値番号
  int &missing(void); //現在の欠損数
  void input(std::string);
  //欠損のさせ方の初期化
  void Seed(void);
  //初期化
  void reset(void);
  void reset2(void);
  //データを欠損
  void revise_missing_values(void);
  //MAEの計算，textに保存
  void mae(std::string, int);
  //F-measureの計算，textに保存，indexはROC用ループ添字
  void fmeasure(std::string, int);
  //ROCで必要な値をtextに保存
  void roc(std::string);
  //ROCの横軸の値で小さい順にソート
  void Sort(Vector &fal, Vector &tru, int index);
  //Seedとか保存
  void ofs_objective(std::string);
  //選ばれたクラスタリング初期値によるMAE,Fmeasureの欠損させ方数平均
  int min_objective_index(void);
  void choice_mae_f(std::vector<std::string>, int p=1);
  //maeとfmeasure出力:人工データ用
  void save_mae_f(std::vector<std::string>);
  void out_mae_f(std::vector<std::string>);
  //AUCの計算，text1に読み込むROCファイル，text2に平均AUCを保存
  void precision_summury(std::vector<std::string>);
  //クラスタリングのみで予測値計算
  void revise_prediction(void);
  //Efficient Incremental Collaborative Filtering system
  void computation_w(void);
  void revise_prediction2(const Matrix &V);
  //ピアソン相関係数計算
  void pearsonsim(void);
  //行クラスタでフィルタにかけた状態で相関係数計算
  void pearsonsim_clustering(void);
  //PCM用類似度計算
  void pearsonsim_for_pcm(const Matrix &Membership, const Vector &Threshold);
  //予測値計算:FireFly
  void pearsonpred1(void);
  //予測値計算:GroupLens
  void pearsonpred2(void);
  //indexのユーザの既評価値平均を計算
  double user_average(int index);
  SparseMatrix sparsecorrectdata(void) const;
  SparseVector &sparsecorrectdata(int index);
  SparseMatrix sparseincompletedata(void) const;
  SparseVector &sparseincompletedata(const int &index);
  //収束した帰属度をクリスプ化
  void crisp(const Matrix &Membership, const Matrix &ItemMembership);
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
std::vector<std::string> MkdirFCCM(std::string);
std::vector<std::string> MkdirFCS(std::string);
std::vector<std::string>
Mkdir(std::vector<double> para, int c, std::vector<std::string> dirs);
std::vector<std::string> Mkdir(std::vector<std::string> methods);
const std::vector<std::string> FCCM = {"PEAR", "CO"};
const std::vector<std::string> FCS = {"PEAR"};

#endif
