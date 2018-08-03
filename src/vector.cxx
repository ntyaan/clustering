#include"vector.h"
#include"sparseVector.h"

//tryで例外処理
Vector::Vector(int size) try :
  //Sizeをsizeで初期化，Elementをdouble型Size分だけ動的確保
  //:の後をメンバ初期化子並びという
  Size(size), Element(new double[Size]){
  }
//例外が発生したら(メモリ確保の失敗，Sizeがあまりにも大きいなど)
catch(std::bad_alloc){
  std::cerr << "Vector::Vector(int size): Out of Memory!" << std::endl;
  //エラーメッセージを投げる
  throw;
 }

//動的確保したElementを開放
Vector::~Vector(void){
  delete []Element;
}

//要素数，値，"all"
//Vector vec(10, 0.0, "all");みたいに使う
Vector::Vector(int dim, double arg, const char *s) try :
  Size(dim), Element(new double[Size]){
    //s="all"じゃなかったら終了
    if(strcmp(s, "all")!=0){
      std::cerr << "Invalid string parameter" << std::endl;
      exit(1);
    }
    //Size分だけargで初期化
    for(int i=0;i<Size;i++){
      Element[i]=arg;
    }
  }
catch(std::bad_alloc){
  std::cerr << "Vector::Vector(int, double, const char *): Out of Memory!"
	    << std::endl;
  throw;
 }

//Vector vec{10, 24, 0.2, 3.5}みたいに使う
Vector::Vector(std::initializer_list<double> args) try :
  Size(args.size()), Element(new double[Size]){
    //for(auto x: args)
    //for(int i=0;i!=(int)args.size();++i)
    //Element[i]=args.begin()[i];
    std::copy(args.begin(),args.end(),&Element[0]);
  }
catch(std::bad_alloc){
  std::cerr << "Vector::Vector(std::initializer_list<double>): Out of Memory!"
	    << std::endl;
  throw;
 }

Vector::Vector(const Vector &arg) try :
  Size(arg.Size), Element(new double[Size]){
    for(int i=0;i<Size;i++){
      Element[i]=arg.Element[i];
    }
  }
catch(std::bad_alloc){
  std::cerr << "Vector::Vector(const Vector &): Out of Memory!" << std::endl;
  throw;
 }

//コピーと違って元が開放される
Vector::Vector(Vector &&arg)
  : Size(arg.Size), Element(arg.Element){
  arg.Size=0;
  arg.Element=nullptr;
}

//コピー代入
Vector &Vector::operator=(const Vector &arg){
  if(this==&arg){
    Vector tmp(arg);
    //コピーが成功した場合のみswapが実行される
    std::swap(tmp,*this);
    return *this;
  }
  if(this->Size != arg.Size){
    Size=arg.Size;
    delete []Element;
    try{
      Element=new double[Size];
    }
    catch(std::bad_alloc){
      std::cerr << "Out of Memory" << std::endl;
      throw;
    }
  }
  for(int i=0;i<Size;i++){
    Element[i]=arg.Element[i];
  }
  return *this;
}
 
//スパース用コピー代入
Vector &Vector::operator=(const SparseVector &arg){
  if(this->Size != arg.size()){
    Size=arg.size();
    delete []Element;
    try{
      Element=new double[Size];
    }
    catch(std::bad_alloc){
      std::cerr << "Out of Memory" << std::endl;
      throw;
    }
  }
  for(int i=0;i<Size;i++){
    Element[i]=0.0;
  }
  for(int ell=0;ell<arg.essencialSize();ell++){
    Element[arg.indexIndex(ell)]=arg.elementIndex(ell);
  }
  return *this;
}

//コピー代入と違って元が開放される
Vector &Vector::operator=(Vector &&arg){
  if(this==&arg)	return *this;
  Size=arg.Size;
  delete []Element;
  Element=arg.Element;
  arg.Size=0;
  arg.Element=nullptr;
  return *this;
}

//Sizeを返す
int Vector::size(void) const{
  return Size;
}

//クラスオブジェクトに対し添字演算を可能とする
double Vector::operator[](int index) const{
  return Element[index];
}

double &Vector::operator[](int index){
  return Element[index];
}

Vector Vector::operator+(void) const{
  return *this;
}

Vector Vector::operator-(void) const{
  Vector result=*this;
  for(int i=0;i<result.Size;i++){
    result[i]*=-1.0;
  }
  return result;
}

Vector &Vector::operator+=(const Vector &rhs){
  if(rhs.Size==0){
    std::cout << "Vector::operator+=:Size 0" << std::endl;
    exit(1);
  }
  else if(Size!=rhs.Size){
    std::cout << "Vector::operator+=:Size Unmatched" << std::endl;
    exit(1);
  }
  else{
    for(int i=0;i<Size;i++){
      Element[i]+=rhs[i];
    }
  }
  return *this;
}

Vector &Vector::operator-=(const Vector &rhs){
  if(rhs.Size==0){
    std::cout << "Vector::operator-=:Size 0" << std::endl;
    exit(1);
  }
  else if(Size!=rhs.Size){
    std::cout << "Vector::operator-=:Size Unmatched" << std::endl;
    exit(1);
  }
  else{
    for(int i=0;i<Size;i++){
      Element[i]-=rhs[i];
    }
  }
  return *this;
}

Vector &Vector::operator*=(double rhs){
  for(int i=0;i<Size;i++){
    Element[i]*=rhs;
  }
  return *this;
}

Vector &Vector::operator/=(double rhs){
  for(int i=0;i<Size;i++){
    Element[i]/=rhs;
  }
  return *this;
}

Vector Vector::operator+(const Vector &rhs) const{
  Vector result=*this;
  return result+=rhs;
}

Vector Vector::operator-(const Vector &rhs) const{
  Vector result=*this;
  return result-=rhs;
}

//内積
double Vector::operator*(const Vector &rhs) const{
  if(Size<1 || rhs.size()<1 || Size!=rhs.size()){
    std::cout << "Can't calculate innerproduct";
    std::cout << "for 0-sized vector";
    std::cout << "or for different sized vector";
    std::cout << std::endl;
    exit(1);
  }
  double result=Element[0]*rhs[0];
  for(int i=1;i<Size;i++){
    result+=Element[i]*rhs[i];
  }
  return result;
}

bool Vector::operator==(const Vector &rhs) const{
  if(Size!=rhs.size())	return false;
  for(int i=0;i<Size;i++){
    if(Element[i]!=rhs[i])	return false;
  }
  return true;
}

bool Vector::operator!=(const Vector &rhs) const{
  if(Size!=rhs.size())	return true;
  for(int i=0;i<Size;i++){
    if(Element[i]!=rhs[i])	return true;
  }
  return false;
}

Vector Vector::sub(int begin, int end) const{
  if(end<begin){
    std::cerr << "Vector::sub:invalid parameter" << std::endl;
    exit(1);
  }
  Vector result(end-begin+1);
  for(int i=0;i<result.size();i++){
    result[i]=Element[begin+i];
  }
  return result;
}

void Vector::set_sub(int begin, int end, const Vector &arg){
  if(end<begin){
    std::cerr << "Vector::sub:invalid parameter" << std::endl;
    exit(1);
  }
  if(end-begin+1!=arg.size()){
    std::cerr << "Vector::sub:invalid parameter" << std::endl;
    exit(1);
  }
  for(int i=0;i<arg.size();i++){
    Element[begin+i]=arg[i];
  }
  return;
}

Vector operator*(double lhs, const Vector &rhs){
  if(rhs.size()==0){
    std::cout << "Vector operator*:Size 0" << std::endl;
    exit(1);
  }
  Vector result=rhs;
  for(int i=0;i<result.size();i++){
    result[i]*=lhs;
  }
  return result;
}

Vector operator*(const Vector &lhs, double rhs){
  if(lhs.size()==0){
    std::cout << "Vector operator*:Size 0" << std::endl;
    exit(1);
  }
  Vector result=lhs;
  for(int i=0;i<result.size();i++){
    result[i]*=rhs;
  }
  return result;
}

Vector operator/(const Vector &lhs, double rhs){
  if(lhs.size()==0){
    std::cout << "Vector operator/:Size 0" << std::endl;
    exit(1);
  }
  Vector result(lhs);
  return (result/=rhs);
}

Vector fraction(const Vector &arg){
  Vector result(arg.size());
  for(int i=0;i<result.size();i++){
    result[i]=1.0/arg[i];
  }
  return result;
}

Vector max_fraction(const Vector &arg){
  if(arg.size()<1){
    std::cout << "Can't calculate max_fraction for 0-sized vector"
	      << std::endl;
    exit(1);
  }
  Vector result(arg.size());
  double max=arg[0];
  for(int i=1;i<arg.size();i++){
    if(max<arg[i])
      max=arg[i];
  }
  for(int i=0;i<result.size();i++)
    result[i]=arg[i]/max;
  return result;
}

Vector sum_fraction(const Vector &arg){
  if(arg.size()<1){
    std::cout << "Can't calculate max_fraction for 0-sized vector"
	      << std::endl;
    exit(1);
  }
  Vector result(arg.size());
  double sum=arg[0];
  for(int i=1;i<arg.size();i++)
    sum+=arg[i];
  for(int i=0;i<result.size();i++)
    result[i]=arg[i]/sum;
  return result;
}

std::ostream &operator<<(std::ostream &os, const Vector &rhs){
  os << "(";
  if(rhs.size()>0){
    for(int i=0;;i++){
      os << rhs[i];
      if(i>=rhs.size()-1) break;
      os << ", ";
    }
  }
  os << ')';
  return os;
}


double max_norm(const Vector &arg){
  if(arg.size()<1){
    std::cout << "Can't calculate norm for 0-sized vector" << std::endl;
    exit(1);
  }
  double result=fabs(arg[0]);
  for(int i=1;i<arg.size();i++){
    double tmp=fabs(arg[i]);
    if(result<tmp)	result=tmp;
  }
  return result;
}

double squared_norm(const Vector &arg){
  return sqrt(norm_square(arg));
}

double norm_square(const Vector &arg){
  double result=0.0;
  for(int i=0;i<arg.size();i++){
    result+=arg[i]*arg[i];
  }
  return result;
}

double L1norm_square(const Vector &arg){
  double result=0.0;
  for(int i=0;i<arg.size();i++){
    result+=fabs(arg[i]);
  }
  return result;
}
