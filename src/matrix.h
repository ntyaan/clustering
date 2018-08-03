#include"vector.h"

#ifndef __MATRIX__
#define __MATRIX__

typedef std::initializer_list
<std::initializer_list<double>> i_list;

class Matrix{
private:
  //行数
  int Rows;
  Vector *Element;
public:
  //Matrix(int rows=0);
  //コンストラクタ
  Matrix(int rows=0, int cols=0);
  //全ての要素をargで初期化
  Matrix(int rows, int cols, double arg);
  //初期化子並びコンストラクタ
  Matrix(const i_list& args);
  //第二引数を"I"とすることでdim*dimの単位行列生成
  //'I'にするとバグる
  explicit Matrix(int dim, const char *s);
  //第二引数をdiagとすることでargの要素を対角成分とする対角行列生成
  explicit Matrix(const Vector &arg, const char *s);
  Matrix(const Matrix &arg);
  Matrix(Matrix &&arg);
  //デストラクタ
  ~Matrix(void);
  //コピー代入
  Matrix &operator=(const Matrix &arg);
  //ムーブ代入
  Matrix &operator=(Matrix &&arg);
  //行数を返す
  int rows(void) const;
  //列数を返す
  int cols(void) const;
  //演算子
  Vector operator[](int index) const;
  Vector &operator[](int index);
  Matrix operator+(void) const;
  Matrix operator-(void) const;
  Matrix &operator+=(const Matrix &rhs);
  Matrix &operator-=(const Matrix &rhs);
  Matrix &operator*=(double rhs);
  Matrix &operator/=(double rhs);
  //row_beginからrow_end，col_beginからcol_endまで要素を取り出し
  //新たな行列生成
  Matrix sub(int row_begin,
	     int row_end,
	     int col_begin,
	     int col_end) const;
  //argのrow_beginからrow_end，col_beginからcol_endまで要素をコピー
  void set_sub(int row_begin,
	       int row_end,
	       int col_begin,
	       int col_end,
	       const Matrix &arg);
};

Matrix operator+(const Matrix &lhs, const Matrix &rhs);
Matrix operator-(const Matrix &lhs, const Matrix &rhs);
Matrix operator*(const double lhs, const Matrix &rhs);
Matrix operator*(const Matrix &lhs, double rhs);
Vector operator*(const Matrix &lhs, const Vector &rhs);
Matrix operator*(const Vector &lhs, const Matrix &rhs);
Matrix operator*(const Matrix &lhs, const Matrix &rhs);
Matrix operator/(const Matrix &lhs, double rhs);
//Matrix operator/(double lhs, const Matrix &rhs);
std::ostream &operator<<(std::ostream &os, const Matrix &rhs);
bool operator==(const Matrix &lhs, const Matrix &rhs);
//argの要素の絶対値合計
double abssum(const Vector &arg);
//行列の各abbsumの最大
double max_norm(const Matrix &arg);
//各要素を2乗し足し合わせたものを平方根
double frobenius_norm(const Matrix &arg);
//転置行列
Matrix transpose(const Matrix &arg);
//正方行列の対角成分をベクトルへ
Vector diag(const Matrix &arg);
//argの各要素をpower乗
Matrix pow(const Matrix &arg, double power);
//縦ベクトルを横ベクトルへ
Matrix transpose(const Vector &arg);
//逆数
Matrix fraction(const Matrix &);
//行列の要素最大値で各要素を割る
Matrix max_fraction(const Matrix &);
//行列の各ベクトルの要素の和で各ベクトルの要素を割る
Matrix sum_fraction(const Matrix &);

#endif
