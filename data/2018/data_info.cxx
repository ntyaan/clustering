#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <unistd.h>
#include <iomanip>
//#include <Eigen/Dense>
int main(){
  std::string file1="sparse_book_1091_2248.txt";
  std::string file2="sparse_epinions_1022_835.txt";
  std::string file3="sparse_jester_2916_140.txt";
  std::string file4="sparse_libimseti_866_1156.txt";
  std::string file5="sparse_movie_905_684.txt";
  std::string file6="sparse_sushi_5000_100.txt";
  std::ifstream ifs1(file1);
  std::ifstream ifs2(file2);
  std::ifstream ifs3(file3);
  std::ifstream ifs4(file4);
  std::ifstream ifs5(file5);
  std::ifstream ifs6(file6);
	  
  int row1=1091,col1=2248;
  int row2=1022,col2=835;
  int row3=2916,col3=140;
  int row4=866,col4=1156;
  int row5=905,col5=684;
  int row6=5000,col6=100;
  int size,sum;
  double value;
  sum=0;
  for(int k=0;k<row1;k++){
    ifs1>>size;
    sum+=size;
    //std::cout<<sum<<std::endl;
    for(int ell=0;ell<size;ell++)
      ifs1>>value>>value;
  }
  std::cout<<" ";
  std::cout<<" & "<<row1
	   <<" & "<<sum
	   <<" & "<<std::setprecision(6)<<(1.0-sum/double(row1*col1))*100.0
	   <<"\\%"
	   <<" \\\\\\hline"
	   <<std::endl;
  ifs1.close();
  sum=0;
  for(int k=0;k<row2;k++){
    ifs2>>size;
    sum+=size;
    //std::cout<<sum<<std::endl;
    for(int ell=0;ell<size;ell++)
      ifs2>>value>>value;
  }
  std::cout<<" ";
  std::cout<<" & "<<row2
	   <<" & "<<sum
	   <<" & "<<std::setprecision(6)<<(1.0-sum/double(row2*col2))*100.0
	   <<"\\%"
	   <<" \\\\\\hline"
	   <<std::endl;
  ifs2.close();
  sum=0;
  for(int k=0;k<row3;k++){
    ifs3>>size;
    sum+=size;
    //std::cout<<sum<<std::endl;
    for(int ell=0;ell<size;ell++)
      ifs3>>value>>value;
  }
  std::cout<<" ";
  std::cout<<" & "<<row3
	   <<" & "<<sum
	   <<" & "<<std::setprecision(6)<<(1.0-sum/double(row3*col3))*100.0
	   <<"\\%"
	   <<" \\\\\\hline"
	   <<std::endl;
  ifs3.close();
  sum=0;
  for(int k=0;k<row4;k++){
    ifs4>>size;
    sum+=size;
    //std::cout<<sum<<std::endl;
    for(int ell=0;ell<size;ell++)
      ifs4>>value>>value;
  }
  std::cout<<" ";
  std::cout<<" & "<<row4
	   <<" & "<<sum
	   <<" & "<<std::setprecision(6)<<(1.0-sum/double(row4*col4))*100.0
	   <<"\\%"
	   <<" \\\\\\hline"
	   <<std::endl;
  ifs4.close();
  sum=0;
  for(int k=0;k<row5;k++){
    ifs5>>size;
    sum+=size;
    //std::cout<<sum<<std::endl;
    for(int ell=0;ell<size;ell++)
      ifs5>>value>>value;
  }
  std::cout<<" ";
  std::cout<<" & "<<row5
	   <<" & "<<sum
	   <<" & "<<std::setprecision(6)<<(1.0-sum/double(row5*col5))*100.0
	   <<"\\%"
	   <<" \\\\\\hline"
	   <<std::endl;
  ifs5.close();
      sum=0;
  for(int k=0;k<row6;k++){
    ifs6>>size;
    sum+=size;
    //std::cout<<sum<<std::endl;
    for(int ell=0;ell<size;ell++)
      ifs6>>value>>value;
  }
  std::cout<<" ";
  std::cout<<" & "<<row6
	   <<" & "<<sum
	   <<" & "<<std::setprecision(6)<<(1.0-sum/double(row6*col6))*100.0
	   <<"\\%"
	   <<" \\\\\\hline"
	   <<std::endl;
  ifs6.close();
  return 0;
}
