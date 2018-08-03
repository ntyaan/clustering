#include<iostream>
#include<cstdlib>
#include<cmath>
#include<fstream>
#include<iomanip>
#include<cstring>
#include<vector>
#define REP(i,n) for(int i=(0);i<(n);i++)
using namespace std;
int main(const int argc, const char *argv[]){
  std::string argv0=argv[1];
  const int row=atoi(argv[2]);
  const int col=atoi(argv[3]);
  std::ifstream ifs(argv0);
  if(!ifs){
    cout<<"could not file"<<endl;
    exit(1);
  }
  vector< vector<double> > A;
  A.resize(row);
  for( int i=0; i<row; i++ ){
    A[i].resize(col);
  }
    int tmp=0;
    REP(i,row){
      REP(j,col){
	ifs>>tmp;
	A[i][j]=tmp;
      }
    }
  ofstream ofs_new_sparse("sparse_"+argv0);
  vector<int> c;
  c.resize(row);
  REP(i,row){
    c[i]=0;
    REP(j,col){
      if(A[i][j]>0)c[i]++;
      }
  }
  REP(i,row){
    ofs_new_sparse<<c[i]<<" ";
    REP(j,col){
      if(A[i][j]>0){
        ofs_new_sparse<<j<<" "<<A[i][j]<<" ";
      }
    }
      ofs_new_sparse<<endl;
    }
    return 0;
}
