#include"vector.h"

#ifndef __SPARSEVECTOR__
#define __SPARSEVECTOR__

class Vector;

class SparseVector{
 private:
  //本当のサイズ
  int Size;
  //非ゼロ成分のみサイズ
  int EssencialSize;
  //非ゼロ成分本当のデータ番号
  int *Index;
  //非ゼロ成分要素
  double *Element;
 public:
  //コンストラクタ
  SparseVector(int Size=0, int essencialSize=0);
  //コピーコンストラクタ
  SparseVector(const SparseVector &arg);
  //ムーブコンストラクタ
  SparseVector(SparseVector &&arg);
  //デストラクタ
  ~SparseVector(void);
  //コピー代入
  SparseVector &operator=(const SparseVector &arg);
  //ムーブ代入
  SparseVector &operator=(SparseVector &&arg);
  //Sizeを返す
  int size(void) const;
  //EssencialSizeを返す
  int essencialSize(void) const;
  //Index[index]を返す
  int indexIndex(int index) const;
  //Index[index]を変更する
  int &indexIndex(int index);
  //ElementIndex[index]を返す
  double elementIndex(int index) const;
  //ElementIndex[index]を変える
  double &elementIndex(int index);
  SparseVector operator+(void) const;
  SparseVector operator-(void) const;
  bool operator==(const SparseVector &rhs) const;
  bool operator!=(const SparseVector &rhs) const;
};

std::ostream &operator<<(std::ostream &os, const SparseVector &rhs);
//絶対値をとった要素の最大
double max_norm(const SparseVector &arg);
//2ノルム
double squared_norm(const SparseVector &arg);
//2ノルムの二乗
double norm_square(const SparseVector &arg);
//SparseVectorとVectorの内積
double operator*(const SparseVector &lhs, const Vector &rhs);
double operator*(const Vector &lhs, const SparseVector &rhs);

#endif
