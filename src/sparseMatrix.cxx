#include"sparseVector.h"
#include"sparseMatrix.h"

//コンストラクタ
SparseMatrix::SparseMatrix(int rows, int cols) try :
  Rows(rows), Cols(cols), Element(new SparseVector[Rows]){
  }
catch(std::bad_alloc){
  std::cerr << "Out of Memory" << std::endl;
  throw;
 }

//コピーコンストラクタ
SparseMatrix::SparseMatrix(const SparseMatrix &arg) try :
  Rows(arg.Rows), Cols(arg.Cols), Element(new SparseVector[Rows]){
    for(int i=0;i<Rows;i++)
      Element[i]=arg.Element[i];
  }
catch(std::bad_alloc){
  std::cerr << "Out of Memory" << std::endl;
  throw;
 }

//ムーブコンストラクタ
SparseMatrix::SparseMatrix(SparseMatrix &&arg)
  : Rows(arg.Rows), Cols(arg.Cols), Element(arg.Element){
  arg.Rows=0;
  arg.Cols=0;
  arg.Element=nullptr;
}

//デストラクタ
SparseMatrix::~SparseMatrix(void){
  delete []Element;
}

//コピー代入
SparseMatrix &SparseMatrix::operator=(const SparseMatrix &arg){
  if(this==&arg)	return *this;
  //Rows=arg.Rows;ここではRowsを更新してはいけない
  if(this->Rows != arg.Rows || this->Cols != arg.Cols){
    Rows=arg.Rows;
    Cols=arg.Cols;
    delete []Element;
    try{
      Element=new SparseVector[Rows];
    }
    catch(std::bad_alloc){
      std::cerr << "Out of Memory" << std::endl;
      throw;
    }
  }
  for(int i=0;i<Rows;i++)
    Element[i]=arg.Element[i];
  return *this;
}

//ムーブ代入
SparseMatrix &SparseMatrix::operator=(SparseMatrix &&arg){
  if(this==&arg){
    return *this;
  }
  else{
    Rows=arg.Rows;
    Cols=arg.Cols;
    delete []Element;
    Element=arg.Element;
    arg.Rows=0;
    arg.Cols=0;
    arg.Element=nullptr;
    return *this;
  }
}

int SparseMatrix::rows(void) const{
  return Rows;
}

int SparseMatrix::cols(void) const{
  return Cols;
}

SparseVector SparseMatrix::operator[](int index) const{
  return Element[index];
}

SparseVector &SparseMatrix::operator[](int index){
  return Element[index];
}

SparseMatrix SparseMatrix::operator+(void) const{
  return *this;
}

SparseMatrix SparseMatrix::operator-(void) const{
  SparseMatrix result=*this;
  for(int i=0;i<result.Rows;i++){
    result[i]=-result[i];
  }
  return result;
}

std::ostream &operator<<(std::ostream &os, const SparseMatrix &rhs){
  os << "(";
  if(rhs.rows()>0){
    for(int i=0;;i++){
      os << rhs[i];
      if(i>=rhs.rows()-1) break;
      os << "\n";
    }
  }
  os << ')';
  return os;
}

bool operator==(const SparseMatrix &lhs, const SparseMatrix &rhs){
  if(lhs.rows()!=rhs.rows())	return false;
  for(int i=0;i<lhs.rows();i++){
    if(lhs[i]!=rhs[i])	return false;
  }
  return true;
}

double frobenius_norm(const SparseMatrix &arg){
  double result=0.0;
  for(int i=0;i<arg.rows();i++){
    result+=norm_square(arg[i]);
  }
  return sqrt(result);
}
