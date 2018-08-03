#include"vector.h"
#include"matrix.h"

//コンストラクタ
Matrix::Matrix(int rows, int cols) try :
  Rows(rows), Element(new Vector[Rows]){
    for(int i=0;i<Rows;i++){
      Element[i]=Vector(cols);
    }
  }
catch(std::bad_alloc){
  std::cerr << "Out of Memory" << std::endl;
  throw;
 }

//全ての要素をargで初期化
Matrix::Matrix(int rows, int cols, double arg) try :
  Rows(rows), Element(new Vector[Rows]){
    for(int i=0;i<Rows;i++)
      Element[i]=Vector(cols);
    for(int i=0;i<Rows;i++)
      for(int j=0;j<cols;j++)
	Element[i][j]=arg;
  }
catch(std::bad_alloc){
  std::cerr << "Out of Memory" << std::endl;
  throw;
 }

//初期化子並びコンストラクタ
Matrix::Matrix(const i_list& args) try :
  Rows(args.size()), Element(new Vector[args.size()]){
    std::copy(args.begin(),args.end(),&Element[0]);
    Vector tmp(Rows,Element[0].size(),"all");
    for(int i=1;i<Rows;i++){
      if(tmp[i]!=Element[i].size()){
	std::cerr<<"not macth cols"<<std::endl;
	exit(1);
      }
    }
  }
catch(std::bad_alloc){
  std::cerr << "Matrix::Matrix(initializer_list<std::initializer_list<double>>&) : Out of Memory!"<< std::endl;
  throw;
 }

Matrix::Matrix(int dim, const char *s) try :
  Rows(dim), Element(new Vector[Rows]){
    if(strcmp(s, "I")!=0){
      std::cerr << "Invalid string parameter" << std::endl;
      exit(1);
    }
    //Rows*Rowsの行列生成
    for(int i=0;i<Rows;i++)
      Element[i]=Vector(dim);
    //単位行列生成
    for(int i=0;i<Rows;i++){
      for(int j=0;j<Rows;j++){
	Element[i][j]=0.0;
      }
      Element[i][i]=1.0;
    }
  }
catch(std::bad_alloc){
  std::cerr << "Out of Memory" << std::endl;
  throw;
 }

Matrix::Matrix(const Vector &arg, const char *s) try : 
  Rows(arg.size()), Element(new Vector[Rows]){
    if(strcmp(s, "diag")!=0){
      std::cerr << "Invalid string parameter" << std::endl;
      exit(1);
		
    }
    //arg.size()*arg.size()の行列生成
    for(int i=0;i<Rows;i++)
      Element[i]=Vector(Rows);
    //Vectorの要素を対角成分とする対角行列生成
    for(int i=0;i<Rows;i++){
      for(int j=0;j<Rows;j++)
	Element[i][j]=0.0;
      Element[i][i]=arg[i];
    }
  }
catch(std::bad_alloc){
  std::cerr << "Out of Memory" << std::endl;
  throw;
 }

Matrix::Matrix(const Matrix &arg) try :
  Rows(arg.Rows), Element(new Vector[Rows]){
    for(int i=0;i<Rows;i++){
      Element[i]=arg.Element[i];
    }
  }
catch(std::bad_alloc){
  std::cerr << "Out of Memory" << std::endl;
  throw;
 }

Matrix::Matrix(Matrix &&arg)
  : Rows(arg.Rows), Element(arg.Element){
  arg.Rows=0;
  arg.Element=nullptr;
}

//デストラクタ
Matrix::~Matrix(void){
  delete []Element;
}

//コピー代入
Matrix &Matrix::operator=(const Matrix &arg){
  if(this==&arg)	return *this;
  //Rows=arg.Rows;ここではRowsを更新してはいけない
  if(this->Rows != arg.Rows || this->cols() != arg.cols()){
    Rows=arg.Rows;
    delete []Element;
    try{
      Element=new Vector[Rows];
    }
    catch(std::bad_alloc){
      std::cerr << "Out of Memory" << std::endl;
      throw;
    }
  }
  for(int i=0;i<Rows;i++){
    Element[i]=arg.Element[i];
  }
  return *this;
}

//ムーブ代入
Matrix &Matrix::operator=(Matrix &&arg){
  if(this==&arg){
    return *this;
  }
  else{
    Rows=arg.Rows;
    delete []Element;
    Element=arg.Element;
    arg.Rows=0;
    arg.Element=nullptr;
    return *this;
  }
}

//行数を返す
int Matrix::rows(void) const{
  return Rows;
}

//列数を返す
int Matrix::cols(void) const{
  return Element[0].size();
}

Vector Matrix::operator[](int index) const{
  return Element[index];
}

Vector &Matrix::operator[](int index){
  return Element[index];
}

Matrix Matrix::operator+(void) const{
  return *this;
}

Matrix Matrix::operator-(void) const{
  Matrix result=*this;
  for(int i=0;i<result.Rows;i++){
    result[i]=-1.0*result[i];
  }
  return result;
}

Matrix &Matrix::operator+=(const Matrix &rhs){
  if(rhs.Rows==0){
    std::cout << "Rows 0" << std::endl;
    exit(1);
  }
  else if(Rows!=rhs.Rows){
    std::cout << "Rows Unmatched" << std::endl;
    exit(1);
  }
  else{
    for(int i=0;i<Rows;i++){
      Element[i]+=rhs[i];
    }
  }
  return *this;
}

Matrix &Matrix::operator-=(const Matrix &rhs){
  if(rhs.Rows==0){
    std::cout << "Rows 0" << std::endl;
    exit(1);
  }
  else if(Rows!=rhs.Rows){
    std::cout << "Rows Unmatched" << std::endl;
    exit(1);
  }
  else{
    for(int i=0;i<Rows;i++){
      Element[i]-=rhs[i];
    }
  }
  return *this;
}

Matrix &Matrix::operator*=(double rhs){
  for(int i=0;i<Rows;i++)
    Element[i]*=rhs;
  return *this;
}

Matrix &Matrix::operator/=(double rhs){
  for(int i=0;i<Rows;i++)
    Element[i]/=rhs;
  return *this;
}

Matrix Matrix::sub(int row_begin, int row_end,
		   int col_begin, int col_end) const{
  if(row_end<row_begin || col_end<col_begin){
    std::cerr << "Matrix::sub:invalid parameter" << std::endl;
    std::cerr << "row_begin:" << row_begin << std::endl;
    std::cerr << "row_end:" << row_end << std::endl;
    std::cerr << "col_begin:" << col_begin << std::endl;
    std::cerr << "col_end:" << col_end << std::endl;
    exit(1);
  }
  if(row_end>=this->rows() || col_end>=this->cols()){
    std::cerr << "Matrix::sub:invalid parameter" << std::endl;
    std::cerr << "row_end:" << row_end << std::endl;
    std::cerr << "Rows:" << this->rows() << std::endl;
    std::cerr << "col_end:" << col_end << std::endl;
    std::cerr << "Cols:" << this->cols() << std::endl;
    exit(1);
  }
  if(row_begin<0 || col_begin<0){
    std::cerr << "Matrix::sub:invalid parameter" << std::endl;
    std::cerr << "row_begin:" << row_begin << std::endl;
    std::cerr << "col_begin:" << col_begin << std::endl;
    exit(1);
  }
  Matrix result(row_end-row_begin+1, col_end-col_begin+1);
  for(int i=0;i<result.rows();i++){
    for(int j=0;j<result.cols();j++)
      result[i][j]=Element[i+row_begin][j+col_begin];
  }
  return result;
}

void Matrix::set_sub(int row_begin, int row_end,
		     int col_begin, int col_end,
		     const Matrix &arg){
	
  if(row_end<row_begin || col_end<col_begin){
    std::cerr << "Matrix::sub:invalid parameter" << std::endl;
    exit(1);
  }
  for(int i=row_begin;i<=row_end;i++){
    for(int j=col_begin;j<=col_end;j++){
      Element[i][j]=arg[i-row_begin][j-col_begin];
    }}
  return;
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs){
  Matrix result=lhs;
  return result+=rhs;
}

Matrix operator-(const Matrix &lhs, const Matrix &rhs){
  Matrix result=lhs;
  return result-=rhs;
}

Matrix operator*(double lhs, const Matrix &rhs){
  if(rhs.rows()==0){
    std::cout << "Rows 0" << std::endl;
    exit(1);
  }
  Matrix result=rhs;
  for(int i=0;i<result.rows();i++)
    result[i]=lhs*result[i];
  return result;
}

Matrix operator*(const Matrix &lhs, double rhs){
  if(lhs.rows()==0){
    std::cout << "Rows 0" << std::endl;
    exit(1);
  }
  Matrix result=lhs;
  for(int i=0;i<result.rows();i++)
    result[i]=result[i]*rhs;
  return result;
}

Vector operator*(const Matrix &lhs, const Vector &rhs){
  if(lhs.rows()<1 || lhs.cols()<1 || rhs.size()<1 || lhs.cols()!=rhs.size()){
    std::cout << "operator*(const Matrix &, const Vector):";
    std::cout << "Can't calculate innerproduct ";
    std::cout << "for 0-sized vector ";
    std::cout << "or for different sized vector:";
    std::cout << "lhs.Cols=" << lhs.cols() << ", ";
    std::cout << "lhs.Rows=" << lhs.rows() << ", ";
    std::cout << "rhs.Size=" << rhs.size();
    std::cout << std::endl;
    exit(1);
  }
  Vector result(lhs.rows());
  for(int i=0;i<lhs.rows();i++)
    result[i]=lhs[i]*rhs;
  return result;
}

Matrix operator*(const Vector &lhs, const Matrix &rhs){
  if(rhs.rows()!=1){
    std::cerr << "Size unmatched for Vector*Matrix:"
	      << rhs.rows() << ":" << rhs.cols() << std::endl;
    exit(1);
  }
  Matrix result(lhs.size(), rhs.cols());
  for(int i=0;i<result.rows();i++){
    for(int j=0;j<result.cols();j++)
      result[i][j]=lhs[i]*rhs[0][j];
  }
  return result;
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs){
  if(lhs.rows()<1 || rhs.cols()<1 || lhs.cols()!=rhs.rows()){
    std::cout << "Can't calculate innerproduct";
    std::cout << "for 0-sized vector";
    std::cout << "or for different sized vector";
    std::cout << std::endl;
    exit(1);
  }
  Matrix result(lhs.rows(), rhs.cols());
  for(int i=0;i<result.rows();i++){
    for(int j=0;j<result.cols();j++){
      result[i][j]=0.0;
      for(int k=0;k<lhs.cols();k++){
	result[i][j]+=lhs[i][k]*rhs[k][j];
      }
    }
  }
  return result;
}

Matrix operator/(const Matrix &lhs, double rhs){
  Matrix result(lhs);
  return result/=rhs;
}

std::ostream &operator<<(std::ostream &os, const Matrix &rhs){
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

bool operator==(const Matrix &lhs, const Matrix &rhs){
  if(lhs.rows()!=rhs.rows())	return false;
  for(int i=0;i<lhs.rows();i++){
    if(lhs[i]!=rhs[i])	return false;
  }
  return true;
}

double abssum(const Vector &arg){
  double result=fabs(arg[0]);
  for(int i=1;i<arg.size();i++){
    result+=fabs(arg[i]);
  }
  return result;
}

double max_norm(const Matrix &arg){
  if(arg.rows()<1){
    std::cout << "Can't calculate norm for 0-sized vector" << std::endl;
    exit(1);
  }
  double result=abssum(arg[0]);
  for(int i=1;i<arg.rows();i++){
    double tmp=abssum(arg[i]);
    if(result<tmp)	result=tmp;
  }
  return result;
}

double frobenius_norm(const Matrix &arg){
  double result=0.0;
  for(int i=0;i<arg.rows();i++){
    for(int j=0;j<arg.cols();j++)
      result+=arg[i][j]*arg[i][j];
  }
  return sqrt(result);
}

Matrix transpose(const Matrix &arg){
  Matrix result(arg.cols(), arg.rows());
  for(int i=0;i<result.rows();i++){
    for(int j=0;j<result.cols();j++)
      result[i][j]=arg[j][i];
  }
  return result;
}

Vector diag(const Matrix &arg){
  if(arg.rows()!=arg.cols()){
    std::cerr << "No Diag" << std::endl;
    exit(1);
  }
  Vector result(arg.rows());
  for(int i=0;i<result.size();i++){
    result[i]=arg[i][i];
  }
  return result;
}

Matrix pow(const Matrix &arg, double power){
  Matrix result(arg);
  for(int i=0;i<result.rows();i++){
    for(int j=0;j<result.cols();j++)
      result[i][j]=pow(result[i][j],power);
  }
  return result;
}

Matrix transpose(const Vector &arg){
  Matrix result(1, arg.size());
  for(int j=0;j<result.cols();j++)
    result[0][j]=arg[j];
  return result;
}

Matrix fraction(const Matrix &arg){
  Matrix result(arg);
  for(int i=0;i<arg.rows();i++){
    for(int j=0;j<arg.cols();j++)
      result[i][j]=1.0/arg[i][j];
  }
  return result;
}
	
Matrix max_fraction(const Matrix &arg){
  Matrix result(arg);
  double max=-DBL_MAX;
  for(int i=0;i<arg.rows();i++){
    for(int j=0;j<arg.cols();j++)
      if(max<arg[i][j])
	max=arg[i][j];
  }
  return result/max;
}

Matrix sum_fraction(const Matrix &arg){
  Matrix result(arg);
  for(int i=0;i<arg.rows();i++){
    double sum=0;
    for(int j=0;j<arg.cols();j++)
      sum+=arg[i][j];
    for(int j=0;j<arg.cols();j++)
      result[i][j]=arg[i][j]/sum;
  }
  return result;
}
