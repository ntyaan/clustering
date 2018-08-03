#include"matrix.h"

#ifndef __VECTOR3D__
#define __VECTOR3D__

class Vector3d{
private:
  //行数
  int Height;
  Matrix *Element;
public:
  //3dArray(int rows=0);
  //コンストラクタ
  Vector3d(int, int, int);
  //全ての要素をargで初期化
  Vector3d(int, int, int, double);
  //第三引数を"I"とすることでdim*dimの単位行列生成
  explicit Vector3d(int dim, int height, const char *s);
  //第三引数をdiagとすることでargの要素を対角成分とする
  explicit Vector3d(const Vector &arg, int height, const char *s);
  //コピーコンストラクタ
  Vector3d(const Vector3d &arg);
  //ムーブコンストラクタ
  Vector3d(Vector3d &&arg);
  //デストラクタ
  ~Vector3d(void);
  //コピー代入
  Vector3d &operator=(const Vector3d &arg);
  //ムーブ代入
  Vector3d &operator=(Vector3d &&arg);
  //高さを返す
  int height(void) const;
  //行数を返す
  int rows(void) const;
  //列数を返す
  int cols(void) const;
  //演算子
  Matrix operator[](int index) const;
  Matrix &operator[](int index);
  Vector3d operator+(void) const;
  Vector3d operator-(void) const;
  Vector3d &operator+=(const Vector3d &rhs);
  Vector3d &operator-=(const Vector3d &rhs);
  Vector3d &operator*=(double rhs);
  Vector3d &operator/=(double rhs);
};

Vector3d operator+(const Vector3d &lhs, const Vector3d &rhs);
Vector3d operator-(const Vector3d &lhs, const Vector3d &rhs);
Vector3d operator*(const double lhs, const Vector3d &rhs);
Vector3d operator*(const Vector3d &lhs, double rhs);
Vector3d operator/(const Vector3d &lhs, double rhs);
std::ostream &operator<<(std::ostream &os, const Vector3d &rhs);
bool operator==(const Vector3d &lhs, const Vector3d &rhs);
//行列の各abbsumの最大
double frobenius_norm(const Vector3d &arg);

#endif
