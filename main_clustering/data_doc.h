/*
  0 cacmcisi=2
  1 citeseer=6 
  2 classic=4
  3 classic4=4
  4 cora=7 
  5 cranmed=2
  6 fbis=17
  7 hitech=6
  8 k1a=20
  9 k1b=6 
  10 la1=6
  11 la2=6
  12 la12=6
  13 mm=2
  14 new3=44
  15 ohscal=10
  16 re0=13 
  17 re1=25
  18 reviews=5
  19 sports=7
  20 tr11=9
  21 tr12=8
  22 tr23=6
  23 tr31=7
  24 tr41=10
  25 tr45=10
  26 wap=20 
  27 webkb=5
*/
#include <vector>
#include <string>
std::vector<std::string> files=
  {
   "cacmcisi" , "citeseer" , "classic", "classic4" , "cora" ,
   "cranmed" , "fbis" , "hitech" , "k1a" , "k1b" , "la1" , "la2" ,
   "la12" , "mm" , "new3" , "ohscal" , "re0" , "re1", "reviews" ,
   "sports" , "tr11" , "tr12" , "tr23" , "tr31", "tr41" , "tr45" ,
   "wap" , "webkb" 
  };
std::vector<int> centers=
  {
   2,6,4,4,7,2,17,6,20,6,6,6,6,2,44,10,13,25,5,7,9,8,6,7,10,10,20,5
  };
