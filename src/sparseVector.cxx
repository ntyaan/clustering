#include"sparseVector.h"
#include"vector.h"

//コンストラクタ
SparseVector::SparseVector(int size, int essencialSize) try :
  Size(size),
    EssencialSize(essencialSize),
    Index(new int[EssencialSize]),
    Element(new double[EssencialSize]){
  }
catch(std::bad_alloc){
  std::cerr << "SparseVector::SparseVector(int essencialSize): Out of Memory!"
	    << std::endl;
  throw;
 }

//コピーコンストラクタ
SparseVector::SparseVector(const SparseVector &arg) try :
  Size(arg.Size),
    EssencialSize(arg.EssencialSize),
    Index(new int[EssencialSize]),
    Element(new double[EssencialSize]){
    for(int i=0;i<EssencialSize;i++){
      Index[i]=arg.Index[i];
      Element[i]=arg.Element[i];
    }
  }
catch(std::bad_alloc){
  std::cerr << "SparseVector::SparseVector(const SparseVector &): Out of Memory!"
	    << std::endl;
  throw;
 }

//ムーブコンストラクタ
SparseVector::SparseVector(SparseVector &&arg)
  : Size(arg.Size),
    EssencialSize(arg.EssencialSize),
    Index(arg.Index),
    Element(arg.Element){
  arg.Size=0;
  arg.EssencialSize=0;
  arg.Index=nullptr;
  arg.Element=nullptr;
}


//デストラクタ
SparseVector::~SparseVector(void){
  delete []Index;
  delete []Element;
}

//コピー代入
SparseVector &SparseVector::operator=(const SparseVector &arg){
  if(this==&arg) return *this;
  if(this->EssencialSize != arg.EssencialSize){
    EssencialSize=arg.EssencialSize;
    delete []Index;
    delete []Element;
    try{
      Index=new int[EssencialSize];
      Element=new double[EssencialSize];
    }
    catch(std::bad_alloc){
      std::cerr << "Out of Memory" << std::endl;
      throw;
    }
  }
  Size=arg.Size;
  for(int i=0;i<EssencialSize;i++){
    Index[i]=arg.Index[i];
    Element[i]=arg.Element[i];
  }
  return *this;
}

//ムーブ代入
SparseVector &SparseVector::operator=(SparseVector &&arg){
  if(this==&arg) return *this;
  Size=arg.Size;
  EssencialSize=arg.EssencialSize;
  delete []Index;
  delete []Element;
  Element=arg.Element;
  Index=arg.Index;
  arg.EssencialSize=0;
  arg.Index=nullptr;
  arg.Element=nullptr;
  return *this;
}

int SparseVector::size(void) const{
  return Size;
}

int SparseVector::essencialSize(void) const{
  return EssencialSize;
}

int SparseVector::indexIndex(int index) const{
  return Index[index];
}

int &SparseVector::indexIndex(int index){
  return Index[index];
}

double SparseVector::elementIndex(int index) const{
  return Element[index];
}

double &SparseVector::elementIndex(int index){
  return Element[index];
}

SparseVector SparseVector::operator+(void) const{
  return *this;
}

SparseVector SparseVector::operator-(void) const{
  SparseVector result=*this;
  for(int i=0;i<result.EssencialSize;i++)
    result.elementIndex(i)*=-1.0;
  return result;
}

bool SparseVector::operator==(const SparseVector &rhs) const{
  if(Size!=rhs.Size||EssencialSize!=rhs.essencialSize()) return false;
  for(int i=0;i<EssencialSize;i++){
    if(Element[i]!=rhs.elementIndex(i)||Index[i]!=rhs.indexIndex(i))
      return false;
  }
  return true;
}

bool SparseVector::operator!=(const SparseVector &rhs) const{
  if(Size!=rhs.Size||EssencialSize!=rhs.essencialSize()) return true;
  for(int i=0;i<EssencialSize;i++){
    if(Element[i]!=rhs.elementIndex(i)||Index[i]!=rhs.indexIndex(i))
      return true;
  }
  return false;
}

std::ostream &operator<<(std::ostream &os, const SparseVector &rhs){
  os << "(";
  if(rhs.essencialSize()>0){
    for(int i=0;;i++){
      os << rhs.indexIndex(i) << ":" << rhs.elementIndex(i);
      if(i>=rhs.essencialSize()-1) break;
      os << ", ";
    }
  }
  os << ')';
  return os;
}

double max_norm(const SparseVector &arg){
  if(arg.essencialSize()<1){
    std::cout << "Can't calculate norm for 0-sized vector"
	      << std::endl;
    exit(1);
  }
  double result=fabs(arg.elementIndex(0));
  for(int i=1;i<arg.essencialSize();i++){
    double tmp=fabs(arg.elementIndex(i));
    if(result<tmp) result=tmp;
  }
  return result;
}

double squared_norm(const SparseVector &arg){
  return sqrt(norm_square(arg));
}

double norm_square(const SparseVector &arg){
  double result=0.0;
  for(int i=0;i<arg.essencialSize();i++){
    result+=arg.elementIndex(i)*arg.elementIndex(i);
  }
  return result;
}

double L1norm_square(const SparseVector &arg){
  double result=0.0;
  for(int i=0;i<arg.essencialSize();i++){
    result+=fabs(arg.elementIndex(i));
  }
  return result;
}

double operator*(const SparseVector &lhs, const Vector &rhs){
  double result=0.0;
  for(int ell=0;ell<lhs.essencialSize();ell++){
    result+=lhs.elementIndex(ell)*rhs[lhs.indexIndex(ell)];
  }
  return result;
}

double operator*(const Vector &lhs, const SparseVector &rhs){
  double result=0.0;
  for(int ell=0;ell<rhs.essencialSize();ell++){
    result+=rhs.elementIndex(ell)*lhs[rhs.indexIndex(ell)];
  }
  return result;
}
