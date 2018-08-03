#include"vector.h"
#include"matrix.h"
#include"vector3d.h"

//コンストラクタ
Vector3d::Vector3d(int height, int rows, int cols) try :
  Height(height), Element(new Matrix[Height]){
    for(int i=0;i<Height;i++)
      Element[i]=Matrix(rows, cols);
  }
catch(std::bad_alloc){
  std::cerr << "Out of Memory" << std::endl;
  throw;
 }

//全ての要素をargで初期化
Vector3d::Vector3d(int height, int rows, int cols, double arg) try :
  Height(height), Element(new Matrix[Height]){
    for(int i=0;i<Height;i++)
      Element[i]=Matrix(rows, cols);
    for(int h=0;h<height;h++)
      for(int i=0;i<rows;i++)
	for(int j=0;j<cols;j++)
	  Element[h][i][j]=arg;
  }
catch(std::bad_alloc){
  std::cerr << "Out of Memory" << std::endl;
  throw;
 }

Vector3d::Vector3d(int dim, int height, const char *s) try :
  Height(height), Element(new Matrix[Height]){
    if(strcmp(s, "I")!=0){
      std::cerr << "Invalid string parameter" << std::endl;
      exit(1);	
    }
    //dim*dimの行列生成
    for(int i=0;i<Height;i++)
      Element[i]=Matrix(dim, dim);
    //単位行列生成
    for(int h=0;h<height;h++){
      for(int i=0;i<dim;i++){
	for(int j=0;j<dim;j++)
	  Element[h][i][j]=0.0;
	Element[h][i][i]=1.0;
      }
    }
  }
catch(std::bad_alloc){
  std::cerr << "Out of Memory" << std::endl;
  throw;
 }

Vector3d::Vector3d(const Vector &arg, int height, const char *s) try : 
  Height(height), Element(new Matrix[Height]){
    if(strcmp(s, "diag")!=0){
      std::cerr << "Invalid string parameter" << std::endl;
      exit(1);
    }
    for(int i=0;i<Height;i++)
      Element[i]=Matrix(arg.size(), arg.size());
    //Vectorの要素を対角成分とする対角行列生成
    for(int h=0;h<Height;h++){
      for(int i=0;i<arg.size();i++){
	for(int j=0;j<arg.size();j++)
	  Element[h][i][j]=0.0;
	Element[h][i][i]=arg[i];
      }
    }
  }
catch(std::bad_alloc){
  std::cerr << "Out of Memory" << std::endl;
  throw;
 }

Vector3d::Vector3d(const Vector3d &arg) try :
  Height(arg.Height), Element(new Matrix[Height]){
    for(int i=0;i<Height;i++){
      Element[i]=arg.Element[i];
    }
  }
catch(std::bad_alloc){
  std::cerr << "Out of Memory" << std::endl;
  throw;
 }

Vector3d::Vector3d(Vector3d &&arg)
  : Height(arg.Height), Element(arg.Element){
  arg.Height=0;
  arg.Element=nullptr;
}

//デストラクタ
Vector3d::~Vector3d(void){
  delete []Element;
}

//コピー代入
Vector3d &Vector3d::operator=(const Vector3d &arg){
  if(this==&arg) return *this;
  //Height=arg.Height;ここではHeightを更新してはいけない
  if(this->Height != arg.Height){
    Height=arg.Height;
    delete []Element;
    try{
      Element=new Matrix[Height];
    }
    catch(std::bad_alloc){
      std::cerr << "Out of Memory" << std::endl;
      throw;
    }
  }
  for(int i=0;i<Height;i++)
    Element[i]=arg.Element[i];
  return *this;
}

//ムーブ代入
Vector3d &Vector3d::operator=(Vector3d &&arg){
  if(this==&arg)
    return *this;
  else{
    Height=arg.Height;
    delete []Element;
    Element=arg.Element;
    arg.Height=0;
    arg.Element=nullptr;
    return *this;
  }
}

//高さを返す
int Vector3d::height(void) const{
  return Height;
}

//行数を返す
int Vector3d::rows(void) const{
  return Element[0].rows();
}

//列数を返す
int Vector3d::cols(void) const{
  return Element[0].cols();
}

Matrix Vector3d::operator[](int index) const{
  return Element[index];
}

Matrix &Vector3d::operator[](int index){
  return Element[index];
}

Vector3d Vector3d::operator+(void) const{
  return *this;
}


Vector3d Vector3d::operator-(void) const{
  Vector3d result=*this;
  for(int i=0;i<result.Height;i++)
    result[i]=-1.0*result[i];
  return result;
}

Vector3d &Vector3d::operator+=(const Vector3d &rhs){
  if(rhs.Height==0){
    std::cout << "Height 0" << std::endl;
    exit(1);
  }
  else if(Height!=rhs.Height){
    std::cout << "Height Unmatched" << std::endl;
    exit(1);
  }
  else{
    for(int i=0;i<Height;i++){
      Element[i]+=rhs[i];
    }
  }
  return *this;
}

Vector3d &Vector3d::operator-=(const Vector3d &rhs){
  if(rhs.Height==0){
    std::cout << "Height 0" << std::endl;
    exit(1);
  }
  else if(Height!=rhs.Height){
    std::cout << "Height Unmatched" << std::endl;
    exit(1);
  }
  else{
    for(int i=0;i<Height;i++){
      Element[i]-=rhs[i];
    }
  }
  return *this;
}


Vector3d &Vector3d::operator*=(double rhs){
  for(int i=0;i<Height;i++)
    Element[i]*=rhs;
  return *this;
}

Vector3d &Vector3d::operator/=(double rhs){
  for(int i=0;i<Height;i++)
    Element[i]/=rhs;
  return *this;
}


Vector3d operator+(const Vector3d &lhs, const Vector3d &rhs){
  Vector3d result=lhs;
  return result+=rhs;
}

Vector3d operator-(const Vector3d &lhs, const Vector3d &rhs){
  Vector3d result=lhs;
  return result-=rhs;
}


Vector3d operator*(double lhs, const Vector3d &rhs){
  if(rhs.height()==0){
    std::cout << "Height 0" << std::endl;
    exit(1);
  }
  Vector3d result=rhs;
  for(int i=0;i<result.height();i++)
    result[i]=lhs*result[i];
  return result;
}

Vector3d operator*(const Vector3d &lhs, double rhs){
  if(lhs.height()==0){
    std::cout << "Height 0" << std::endl;
    exit(1);
  }
  Vector3d result=lhs;
  for(int i=0;i<result.height();i++)
    result[i]=result[i]*rhs;
  return result;
}


Vector3d operator/(const Vector3d &lhs, double rhs){
  Vector3d result(lhs);
  return result/=rhs;
}

std::ostream &operator<<(std::ostream &os, const Vector3d &rhs){
  os << "(";
  if(rhs.height()>0){
    for(int i=0;;i++){
      os << rhs[i];
      if(i>=rhs.height()-1) break;
      os << "\n";
    }
  }
  os << ')';
  return os;
}

bool operator==(const Vector3d &lhs, const Vector3d &rhs){
  if(lhs.height()!=rhs.height()) return false;
  for(int i=0;i<lhs.height();i++){
    if(lhs[i]==rhs[i]) return true;
  }
  return false;
}

double frobenius_norm(const Vector3d &arg){
  double result=0.0;
  for(int i=0;i<arg.rows();i++)
    for(int j=0;j<arg.cols();j++)
      for(int k=0;k<arg.height();k++)
	result+=arg[i][j][k]*arg[i][j][k];
  return sqrt(result);
}
