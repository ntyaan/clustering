#include"matrix.h"
#include"sparseMatrix.h"

#ifndef __HCM__
#define __HCM__

class HCM{
protected:
  //非ゼロ行列としたデータ
  SparseMatrix Data;
  //クラスタ中心，前ループのクラスタ中心
  Matrix Centers, Tmp_Centers;
  //帰属度，前ループの帰属度，非類似度
  Matrix Membership, Tmp_Membership, Dissimilarities;
  //クリスプ化した帰属度，正解の帰属度，分割表
  Matrix CrispMembership, CorrectCrispMembership, ContingencyTable;
  //初期クラスタ中心に選ばれたデータ番号を保存
  Vector InitializeC;
  //更新式計算のループ回数
  int Iterates;
  //目的関数値
  double Objective;
public:
  //HCMクラスの生成
  HCM(int dimension,
      int data_number,
      int centers_number);
  //非類似度の計算
  virtual void revise_dissimilarities(void);
  //帰属度の計算
  virtual void revise_membership(void);
  //クラスタ中心の計算
  virtual void revise_centers(void);
  //目的関数の計算
  virtual void set_objective(void);
  //次元数または列数
  int dimension(void) const;
  //データ点の数または行数
  int data_number(void) const;
  //クラスタ数
  int centers_number(void) const;
  //データを非ゼロ行列で返す
  SparseMatrix data(void) const;
  //クラスタ中心を行列で返す
  Matrix centers(void) const;
  //前ループのクラスタ中心を行列で返す
  Matrix tmp_centers(void) const;
  //帰属度を行列で返す
  Matrix membership(void) const;
  //前ループの帰属度を行列で返す
  Matrix tmp_membership(void) const;
  //非類似度を行列で返す
  Matrix dissimilarities(void) const;
  //クリスプ化した帰属度を行列で返す
  Matrix crispMembership(void) const;
  //正解の帰属度を行列で返す
  Matrix correctCrispMembership(void) const;
  //分割表を行列で返す
  Matrix contingencyTable(void) const;
  //非ゼロ行列のデータを非ゼロベクトルで返したり書き換えたり
  SparseVector &data(int index1);
  //行列のクラスタ中心をベクトルで返したり書き換えたり
  Vector &centers(int index1);
  //現在のループ回数を返したり書き換えたり
  int &iterates(void);
  //目的関数値を返す
  double objective(void) const;
  //クラスタ中心の要素を返したり書き換えたり
  double &centers(int index1, int index2);
  //帰属度の要素を返したり書き換えたり
  double &membership(int index1, int index2);
  //非類似度の要素を返したり書き換えたり
  double &dissimilarities(int index1, int index2);
  //クリスプ化した帰属度の要素を返したり書き換えたり
  double &crispMembership(int index1, int index2);
  //正解の帰属度の要素を返したり書き換えたり
  double &correctCrispMembership(int index1, int index2);
  //帰属度をクリスプ化
  void set_crispMembership(void);
  //分割表を計算
  void set_contingencyTable(void);
  //Adjusted Rand Indexの計算
  double ARI(void) const;
  //各変数の初期化
  void reset(void);
  //k-means++っぽく初期クラスタ中心を決定
  virtual void initialize_centers_dissimilarities(int index);
  void initialize_centers(int random_index);
  //初期帰属度に正解の帰属度を
  void initialize_membership(std::string);
  void initialize_membership2(void);
  void initialize_centers2(int method);
  //HCMとSparseHCMで同じ結果か確認用
  void print_frobenius_norm(void);
  //初期値として選ばれたデータやその他出力
  void ofs_selected_data(std::string text);
  //データをもらう
  void copydata(const SparseMatrix &arg1);
  Vector initialize_c(void) const;
};
//ARIの計算で使う組合せの関数
double combination(int n, int k);
//TFIDF
void tfidf1(SparseMatrix &Data);
void tfidf2(SparseMatrix &Data);

#endif
