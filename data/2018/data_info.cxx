#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <unistd.h>
#include <iomanip>
//#include <Eigen/Dense>
int main(){
  //  std::string file="sparse_book_1091_2248.txt";
  //  std::string file="sparse_epinions_1022_835.txt";
  //  std::string file="sparse_jester_2916_140.txt";
  //std::string file="sparse_libimseti_866_1156.txt";
  //std::string file="sparse_movie_905_684.txt";
  std::string file="sparse_sushi_5000_100.txt";
  std::ifstream ifs(file);
  if(ifs.fail()){
    std::cerr<<"ifs error"<<std::endl;
    exit(1);
  }
  //  int row=1091,col=2248;
  //int row=1022,col=835;
  //  int row=2916,col=140;
  //  int row=866,col=1156;
  //int row=905,col=684;
  int row=5000,col=100;
    int size,sum=0;
  double value;
    //Eigen::MatrixXd Data=Eigen::MatrixXd::Zero(row,col);
    for(int k=0;k<row;k++){
      ifs>>size;
      sum+=size;
      //std::cout<<sum<<std::endl;
      for(int ell=0;ell<size;ell++)
        ifs>>value>>value;
    }
      std::cout<<" ";
    std::cout<<" & "<<row
	     <<" & "<<sum
	     <<" & "<<std::setprecision(6)<<(1.0-sum/double(row*col))*100.0
	     <<"\\%"
	     <<" \\\\\\hline"
	     <<std::endl;
    ifs.close();
  return 0;
}
