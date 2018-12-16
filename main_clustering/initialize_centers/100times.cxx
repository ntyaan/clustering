#include"../../src/klfcs.h"
#include"../../src/klfccm.h"
#include"../../src/klfccmm.h"
#include"../../src/bfcs.h"
#include"../../src/bfccm.h"
#include"../../src/bfccmm.h"
#include"../../src/qfcs.h"
#include"../../src/qfccm.h"
#include"../../src/qfccmm.h"
#include"../data_doc.h"
constexpr int DataIndex=3;
#ifdef KLFCCM0
std::vector<double> klfccm0=
  {
   0.5,1.0,0.5,1.0,1.0,10,1.0,1.0,1.0,1.0,
   1.0,1.0,1.0,1.0,10,1.0,1.0,1.0,1.0,1.0,
   1.0,1.0,1.0,1.0,1.0,1.0,1.0
  };
std::string method="klfccm0_100times_list.txt";
#endif
#ifdef KLFCCM1
std::vector<double> klfccm1=
  {
   1.0,1.0,0.5,0.5,1.0,10,10,1.0,1.0,1.0,
   1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
   1.0,1.0,1.0,1.0,1.0,1.0,1.0
  };
std::string method="klfccm1_100times_list.txt";
#endif
#ifdef KLFCCM2
std::vector<double> klfccm2=
  {
   0.5,1.0,0.5,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
   1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,
   1.0,1.0,1.0,1.0,1.0,1.0,1.0
  };
std::string method="klfccm2_100times_list.txt";
#endif
#ifdef BFCCM0
std::string method="bfccm0_100times_list.txt";
#endif
#ifdef BFCCM1
std::string method="bfccm1_100times_list.txt";
#endif
#ifdef BFCCM2
std::string method="bfccm2_100times_list.txt";
#endif
/*
  #ifdef BFCCM012
  std::vector<double> bfccm012=
  {
  1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
  1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
  1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
  1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
  1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
  1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
  1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2
  };
  #endif
*/
#ifdef QFCCM0
std::vector<double> qfccm0l=
  {
   10,10,10,10,100,10,10,10,10,10,
   10,10,10,100,10,10,10,10,100,10,
   10,10,10,10,10,100,10,
  };
std::vector<double> qfccm0m=
  {
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-15,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-15,
  };
std::string method="qfccm0_100times_list.txt";
#endif
#ifdef QFCCM1
std::vector<double> qfccm1l=
  {
   10,10,10,10,100,10,10,10,10,10,
   10,10,10,10,10,10,10,10,10,10,
   10,10,10,10,10,10,1000,
  };
std::vector<double> qfccm1m=
  {
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-4,1.0+1.0E-15,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
  };
std::string method="qfccm1_100times_list.txt";
#endif
#ifdef QFCCM2
std::vector<double> qfccm2l=
  {
   10,10,10,10,10,10,100,10,10,10,
   10,10,10,100,10,10,10,10,10,10,
   10,10,10,10,10,10,100
  };
/*
  std::vector<double> qfccm2m=
  {
  1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
  1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
  1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
  1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
  1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
  1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
  1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2
  };
*/
std::string method="qfccm2_100times_list.txt";
#endif
#ifdef KLFCCMM0
std::vector<double> klfccmm0l=
  {
   1000,10,10,10,10,10,10,DBL_MAX,10,10,
   10,10,10,DBL_MAX,10,100,1000,DBL_MAX,10,10,
   10,10,10,10,10,10,100
  };
std::vector<double> klfccmm0t=
  {
   1.0E-1,1.0E-1,1.0E-1,1.0E-1,1.0E-2,1.0E-1,
   1.0E-1,0.5,1.0E-1,1.0E-1,1.0E-1,1.0E-1,
   1.0E-1,0.5,1.0E-2,1.0E-1,0.5,0.5,
   1.0E-1,1.0E-1,1.0E-1,1.0E-1,1.0E-1,1.0E-1,
   1.0E-1,1.0E-2,1.0E-1
  };
std::string method="klfccmm0_100times_list.txt";
#endif
#ifdef KLFCCMM1
std::vector<double> klfccmm1l=
  {
   DBL_MAX,10,10,DBL_MAX,DBL_MAX,10,10,DBL_MAX,10,10,
   10,10,10,DBL_MAX,DBL_MAX,DBL_MAX,1000,DBL_MAX,10,DBL_MAX,
   DBL_MAX,DBL_MAX,10,10,DBL_MAX,DBL_MAX,DBL_MAX
  };
std::vector<double> klfccmm1t=
  {
   0.5,1.0E-1,1.0E-1,0.5,0.5,1.0E-1,
   1.0E-1,0.5,1.0E-1,1.0E-1,1.0E-1,1.0E-1,
   1.0E-1,0.5,0.5,0.5,0.5,0.5,
   1.0E-1,0.5,0.5,0.5,1.0E-1,1.0E-1,
   0.5,0.5,0.5
  };
std::string method="klfccmm1_100times_list.txt";
#endif
#ifdef KLFCCMM2
std::vector<double> klfccmm2l=
  {
   DBL_MAX,10,10,DBL_MAX,DBL_MAX,10,10,DBL_MAX,10,10,
   DBL_MAX,DBL_MAX,10,DBL_MAX,DBL_MAX,DBL_MAX,1000,DBL_MAX,
   DBL_MAX,DBL_MAX,DBL_MAX,DBL_MAX,10,10,DBL_MAX,DBL_MAX,
   DBL_MAX
  };
std::vector<double> klfccmm2t=
  {
   0.5,1.0E-1,1.0E-1,0.5,0.5,1.0E-1,
   1.0E-1,0.5,1.0E-1,1.0E-1,0.5,0.5,
   1.0E-1,0.5,0.5,0.5,0.5,0.5,
   0.5,0.5,0.5,0.5,1.0E-1,1.0E-1,
   0.5,0.5,0.5
  };
std::string method="klfccmm2_100times_list.txt";
#endif
#ifdef BFCCMM0
std::vector<double> bfccmm0m=
  {
   1.0+1.0E-3,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-4,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-4,1.0+1.0E-4,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-4,1.0+1.0E-4,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-2
  };
std::vector<double> bfccmm0t=
  {
   1.0E-1,1.0E-1,1.0E-1,1.0E-1,1.0E-1,1.0E-1,
   1.0E-1,0.5,1.0E-1,1.0E-1,1.0E-1,1.0E-1,
   1.0E-1,0.5,1.0E-1,1.0E-1,0.5,0.5,
   1.0E-1,1.0E-1,0.5,0.5,1.0E-1,1.0E-1,
   1.0E-1,1.0E-1,1.0E-1
  };
std::string method="bfccmm0_100times_list.txt";
#endif
#ifdef BFCCMM1
std::vector<double> bfccmm1m=
  {
   1.0+1.0E-15,1.0+1.0E-4,1.0+1.0E-5,1.0+1.0E-5,1.0+1.0E-4,
   1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-5,1.0+1.0E-4,1.0+1.0E-4,
   1.0+1.0E-5,1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-5,1.0+1.0E-5,
   1.0+1.0E-5,1.0+1.0E-4,1.0+1.0E-5,1.0+1.0E-4,1.0+1.0E-4,
   1.0+1.0E-4,1.0+1.0E-4,1.0+1.0E-4,1.0+1.0E-4,1.0+1.0E-4,
   1.0+1.0E-4,1.0+1.0E-5
  };
std::vector<double> bfccmm1t=
  {
   0.5,0.5,0.5,0.5,0.5,0.5,
   1.0E-1,0.5,0.5,0.5,0.5,0.5,
   1.0E-1,0.5,0.5,0.5,0.5,0.5,
   0.5,0.5,0.5,0.5,0.5,0.5,
   0.5,0.5,0.5
  };
std::string method="bfccmm1_100times_list.txt";
#endif
#ifdef BFCCMM2
std::vector<double> bfccmm2m=
  {
   1.0+1.0E-15,1.0+1.0E-4,1.0+1.0E-5,1.0+1.0E-5,1.0+1.0E-4,
   1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-5,1.0+1.0E-4,1.0+1.0E-4,
   1.0+1.0E-5,1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-5,1.0+1.0E-5,
   1.0+1.0E-4,1.0+1.0E-4,1.0+1.0E-5,1.0+1.0E-5,1.0+1.0E-4,
   1.0+1.0E-4,1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-4,1.0+1.0E-5,
   1.0+1.0E-4,1.0+1.0E-15
  };
std::vector<double> bfccmm2t=
  {
   0.5,0.5,0.5,0.5,0.5,0.5,
   1.0E-1,0.5,0.5,0.5,0.5,0.5,
   1.0E-1,0.5,0.5,0.5,0.5,0.5,
   0.5,0.5,0.5,0.5,1.0E-1,0.5,
   0.5,0.5,0.5
  };
std::string method="bfccmm2_100times_list.txt";
#endif
#ifdef QFCCMM0
std::vector<double> qfccmm0l=
  {
   1000,100,1000,100,1000,10,10,DBL_MAX,100,10,
   100,10,1000,DBL_MAX,100,1000,1000,DBL_MAX,10,10,
   DBL_MAX,100,10,10,100,100,100
  };
std::vector<double> qfccmm0m=
  {
   1.0+1.0E-4,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-5,1.0+1.0E-5,1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-3,
   1.0+1.0E-2,1.0+1.0E-4,1.0+1.0E-2,1.0+1.0E-4,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-4,1.0+1.0E-4,1.0+1.0E-4,1.0+1.0E-4,
   1.0+1.0E-4,1.0+1.0E-2,1.0+1.0E-4,1.0+1.0E-4,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-2
  };
std::vector<double> qfccmm0t=
  {
   1.0E-1,1.0E-1,1.0E-1,1.0E-1,1.0E-1,1.0E-1,
   1.0E-1,0.5,1.0E-1,1.0E-1,1.0E-1,1.0E-1,
   1.0E-1,0.5,1.0E-1,1.0E-1,0.5,0.5,
   1.0E-1,1.0E-1,0.5,1.0E-1,1.0E-1,1.0E-1,
   1.0E-1,1.0E-1,1.0E-1
  };
std::string method="qfccmm0_100times_list.txt";
#endif
#ifdef QFCCMM1
std::vector<double> qfccmm1l=
  {
   DBL_MAX,DBL_MAX,DBL_MAX,DBL_MAX,DBL_MAX,10,10,DBL_MAX,10,10,
   DBL_MAX,DBL_MAX,100,DBL_MAX,DBL_MAX,DBL_MAX,1000,DBL_MAX,10,DBL_MAX,
   DBL_MAX,DBL_MAX,10,DBL_MAX,DBL_MAX,DBL_MAX,DBL_MAX
  };
std::vector<double> qfccmm1m=
  {
   1.0+1.0E-15,1.0+1.0E-4,1.0+1.0E-5,1.0+1.0E-5,1.0+1.0E-4,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-5,1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-5,1.0+1.0E-5,
   1.0+1.0E-5,1.0+1.0E-15,1.0+1.0E-5,1.0+1.0E-3,1.0+1.0E-4,
   1.0+1.0E-4,1.0+1.0E-4,1.0+1.0E-2,1.0+1.0E-4,1.0+1.0E-4,
   1.0+1.0E-4,1.0+1.0E-5
  };
std::vector<double> qfccmm1t=
  {
   0.5,0.5,0.5,0.5,0.5,1.0E-1,
   1.0E-1,0.5,1.0E-1,1.0E-1,0.5,0.5,
   1.0E-1,0.5,0.5,0.5,0.5,0.5,
   1.0E-1,0.5,0.5,0.5,1.0E-1,0.5,
   0.5,0.5,0.5
  };
std::string method="qfccmm1_100times_list.txt";
#endif
#ifdef QFCCMM2
std::vector<double> qfccmm2l=
  {
   DBL_MAX,DBL_MAX,DBL_MAX,DBL_MAX,DBL_MAX,10,10,DBL_MAX,DBL_MAX,10,
   DBL_MAX,DBL_MAX,1000,DBL_MAX,DBL_MAX,DBL_MAX,1000,DBL_MAX,
   DBL_MAX,DBL_MAX,DBL_MAX,DBL_MAX,100,DBL_MAX,DBL_MAX,DBL_MAX,
   DBL_MAX
  };
std::vector<double> qfccmm2m=
  {
   1.0+1.0E-15,1.0+1.0E-4,1.0+1.0E-5,1.0+1.0E-5,1.0+1.0E-4,
   1.0+1.0E-2,1.0+1.0E-15,1.0+1.0E-5,1.0+1.0E-4,1.0+1.0E-2,
   1.0+1.0E-5,1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-5,1.0+1.0E-5,
   1.0+1.0E-4,1.0+1.0E-5,1.0+1.0E-5,1.0+1.0E-5,1.0+1.0E-4,
   1.0+1.0E-4,1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-4,1.0+1.0E-5,
   1.0+1.0E-4,1.0+1.0E-15
  };
std::vector<double> qfccmm2t=
  {
   0.5,0.5,0.5,0.5,0.5,1.0E-1,
   1.0E-1,0.5,0.5,1.0E-1,0.5,0.5,
   1.0E-1,0.5,0.5,0.5,0.5,0.5,
   0.5,0.5,0.5,0.5,1.0E-1,0.5,
   0.5,0.5,0.5
  };
std::string method="qfccmm2_100times_list.txt";
#endif
#ifdef KLFCS0
std::vector<double> klfcs0=
  {
   1.0,100,DBL_MAX,100,100,100,100,DBL_MAX,DBL_MAX,100,
   1000,1000,DBL_MAX,100,1000,1000,100,100,1000,DBL_MAX,
   100,1000,100,100,100,1000,DBL_MAX
  };
std::string method="klfcs0_100times_list.txt";
#endif
#ifdef KLFCS1
std::vector<double> klfcs1=
  {
   DBL_MAX,100,1000,DBL_MAX,1000,DBL_MAX,100,100,100,100,
   100,100,1000,1000,1000,1000,100,100,1000,100,
   100,100,DBL_MAX,100,100,100,DBL_MAX
  };
std::string method="klfcs1_100times_list.txt";
#endif
#ifdef KLFCS2
std::vector<double> klfcs2=
  {
   DBL_MAX,100,DBL_MAX,DBL_MAX,100,1000,100,1000,100,100,
   1000,1000,1000,1000,DBL_MAX,1000,100,1000,1000,100,
   100,100,1000,100,100,100,100
  };
std::string method="klfcs2_100times_list.txt";
#endif
#ifdef BFCS0
std::vector<double> bfcs0=
  {
   1.0+1.0E-5,1.0+1.0E-4,1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-15,1.0+1.0E-15,1.0+1.0E-4,
   1.0+1.0E-3,1.0+1.0E-4,1.0+1.0E-3,1.0+1.0E-2,1.0+1.0E-15,
   1.0+1.0E-1,1.0+1.0E-2,1.0+1.0E-5,1.0+1.0E-15,1.0+1.0E-4,
   1.0+1.0E-3,1.0+1.0E-2,1.0+1.0E-1,1.0+1.0E-2,1.0+1.0E-2
   1.0+1.0E-5,1.0+1.0E-5
  };
std::string method="bfcs0_100times_list.txt";
#endif
#ifdef BFCS1
std::vector<double> bfcs1=
  {
   1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-3,1.0+1.0E-4,1.0+1.0E-3,
   1.0+1.0E-15,1.0+1.0E-2,1.0+1.0E-15,1.0+1.0E-3,1.0+1.0E-2,
   1.0+1.0E-3,1.0+1.0E-2,1.0+1.0E-3,1.0+1.0E-3,1.0+1.0E-5,
   1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-15,1.0+1.0E-3,1.0+1.0E-1,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-4,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-4,1.0+1.0E-3
  };
std::string method="bfcs1_100times_list.txt";
#endif
#ifdef BFCS2
std::vector<double> bfcs2=
  {
  };
std::string method="bfcs2_100times_list.txt";
#endif
#ifdef QFCS0
std::vector<double> qfcs0l=
  {
   1.0,100,1000,1000,1000,100,100,1000,1000,100,
   1000,1000,100,100,1000,100,100,100,1000,1000,
   100,1000,1000,100,1000,1000,1000
  };
std::vector<double> qfcs0m=
  {
   1.0+1.0E-5,1.0+1.0E-15,1.0+1.0E-15,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-15,1.0+1.0E-15,1.0+1.0E-4,
   1.0+1.0E-3,1.0+1.0E-4,1.0+1.0E-3,1.0+1.0E-3,1.0+1.0E-15,
   1.0+1.0E-1,1.0+1.0E-2,1.0+1.0E-5,1.0+1.0E-15,1.0+1.0E-4,
   1.0+1.0E-3,1.0+1.0E-2,1.0+1.0E-1,1.0+1.0E-2,1.0+1.0E-2
   1.0+1.0E-5,1.0+1.0E-5
  };
std::string method="qfcs0_100times_list.txt";
#endif
#ifdef QFCS1
std::vector<double> qfcs1l=
  {
   DBL_MAX,1000,1000,1000,1000,1000,100,100,100,100,
   1000,1000,1000,DBL_MAX,1000,1000,100,100,1000,1000,
   100,100,1000,100,100,100,1000
  };
std::vector<double> qfcs1m=
  {
   1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-3,1.0+1.0E-4,1.0+1.0E-3,
   1.0+1.0E-15,1.0+1.0E-2,1.0+1.0E-15,1.0+1.0E-3,1.0+1.0E-2,
   1.0+1.0E-3,1.0+1.0E-2,1.0+1.0E-3,1.0+1.0E-5,1.0+1.0E-5,
   1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-15,1.0+1.0E-3,1.0+1.0E-1,
   1.0+1.0E-2,1.0+1.0E-2,1.0+1.0E-4,1.0+1.0E-2,1.0+1.0E-2,
   1.0+1.0E-4,1.0+1.0E-3
  };
std::string method="qfcs1_100times_list.txt";
#endif
#ifdef QFCS2
std::vector<double> qfcs2l=
  {
   1000,1000,1000,100,1000,1000,100,1000,100,100,
   1000,1000,1000,1000,1000,1000,100,1000,1000,100,
   100,100,1000,100,100,1000,1000
  };
std::vector<double> qfcs2m=
  {
   1.0+1.0E-5,1.0+1.0E-3,1.0+1.0E-5,1.0+1.0E-15,1.0+1.0E-2,
   1.0+1.0E-15,1.0+1.0E-2,1.0+1.0E-15,1.0+1.0E-3,1.0+1.0E-2,
   1.0+1.0E-4,1.0+1.0E-5,1.0+1.0E-15,1.0+1.0E-3,1.0+1.0E-15,
   1.0+1.0E-5,1.0+1.0E-2,1.0+1.0E-3,1.0+1.0E-3,1.0+1.0E-2,
   1.0+1.0E-3,1.0+1.0E-5,1.0+1.0E-3,1.0+1.0E-2,1.0+1.0E-5,
   1.0+1.0E-2,1.0+1.0E-2   
  };
std::string method="qfcs2_100times_list.txt";
#endif
//収束条件
#define MAX_ITERATES 10000
#define DIFF_FOR_STOP 1.0E-6
constexpr int INIT_CENTERS = 100;

int main(void){
  std::string c_p = current_path();
  std::ofstream ofs_summary("100times.txt", std::ios::app);
  std::ofstream ofs_list(method, std::ios::app);
  for(int INDEX=DataIndex;INDEX<(int)centers.size();INDEX++){
    const int centers_number=centers[INDEX];
    const std::string file=files[INDEX];
    ofs_list<<files[INDEX]<<"\t";
    std::cout<<files[INDEX]<<std::endl;
    //読み込むデータファイル
    std::string filenameData 
      =c_p+"/../../data/"+files[INDEX]+"/sparse_"+files[INDEX]+".txt";
    //読み込むデータファイルの正解の帰属度ファイル
    std::string filenameCorrectCrispMembership
      =c_p+"/../../data/"+files[INDEX]+"/"+files[INDEX]+"_correct.txt";
    //データの読み込み
    std::ifstream ifs(filenameData);
    if(!ifs){
      std::cerr << "File:" << filenameData
		<< " could not open." << std::endl;
      exit(1);
    }
    //読み込んだデータ行数，データ列数を格納
    int data_number, data_dimension;
    ifs >> data_number;
    ifs >> data_dimension;
    SparseMatrix Data(data_number, data_dimension);
    //読み込んだデータを格納
    for(int cnt=0;cnt<data_number;cnt++){
      int essencialSize;
      ifs >> essencialSize;
      SparseVector dummy(data_dimension, essencialSize);
      for(int ell=0;ell<essencialSize;ell++){
	ifs >> dummy.indexIndex(ell) >> dummy.elementIndex(ell);
      }
      Data[cnt]=dummy;
    }
    ifs.close();
#ifdef KLFCCM0
    ofs_list<<"tfidfなし"<<std::endl;
    KLFCCM test(data_dimension, data_number, centers_number, klfccm0[INDEX]);
#endif
#ifdef KLFCCM1
    ofs_list<<"tfidfA"<<std::endl;
    tfidf1(Data);
    KLFCCM test(data_dimension, data_number, centers_number, klfccm1[INDEX]);
#endif
#ifdef KLFCCM2
    ofs_list<<"tfidfB"<<std::endl;
    tfidf2(Data);
    KLFCCM test(data_dimension, data_number, centers_number, klfccm2[INDEX]);
#endif
#ifdef BFCCM0
    ofs_list<<"tfidfなし"<<std::endl;
    BFCCM test(data_dimension, data_number, centers_number, 1.0+1.0E-2);
#endif
#ifdef BFCCM1
    ofs_list<<"tfidfA"<<std::endl;
    tfidf1(Data);
    BFCCM test(data_dimension, data_number, centers_number, 1.0+1.0E-2);
#endif
#ifdef BFCCM2
    ofs_list<<"tfidfB"<<std::endl;
    tfidf2(Data);
    BFCCM test(data_dimension, data_number, centers_number, 1.0+1.0E-2);
#endif
#ifdef QFCCM0
    ofs_list<<"tfidfなし"<<std::endl;
    QFCCM test(data_dimension, data_number, centers_number,
	       qfccm0m[INDEX], qfccm0l[INDEDX]);
#endif
#ifdef QFCCM1
    ofs_list<<"tfidfA"<<std::endl;
    tfidf1(Data);
    QFCCM test(data_dimension, data_number, centers_number,
	       qfccm1m[INDEX], qfccm1l[INDEDX]);
#endif
#ifdef QFCCM2
    ofs_list<<"tfidfB"<<std::endl;
    tfidf2(Data);
    QFCCM test(data_dimension, data_number, centers_number,
	       1.0+1.0E-2, qfccm2l[INDEDX]);
#endif
#ifdef KLFCCMM0
    ofs_list<<"tfidfなし"<<std::endl;
    KLFCCMM test(data_dimension, data_number, centers_number,
		 klfccmm0l[INDEX], klfccmm0t[INDEX]);
#endif
#ifdef KLFCCMM1
    ofs_list<<"tfidfA"<<std::endl;
    tfidf1(Data);
    KLFCCMM test(data_dimension, data_number, centers_number,
		 klfccmm1l[INDEX], klfccmm1t[INDEX]);
#endif
#ifdef KLFCCMM2
    ofs_list<<"tfidfB"<<std::endl;
    tfidf2(Data);
    KLFCCMM test(data_dimension, data_number, centers_number,
		 klfccmm2l[INDEX], klfccmm2t[INDEX]);
#endif
#ifdef BFCCMM0
    ofs_list<<"tfidfなし"<<std::endl;
    BFCCMM test(data_dimension, data_number, centers_number,
		bfccmm0m[INDEX], bfccmm0t[INDEX]);
#endif
#ifdef BFCCMM1
    ofs_list<<"tfidfA"<<std::endl;
    tfidf1(Data);
    BFCCMM test(data_dimension, data_number, centers_number,
		bfccmm1m[INDEX], bfccmm1t[INDEX]);
#endif
#ifdef BFCCMM2
    ofs_list<<"tfidfB"<<std::endl;
    tfidf2(Data);
    BFCCMM test(data_dimension, data_number, centers_number,
		bfccmm2m[INDEX], bfccmm2t[INDEX]);
#endif
#ifdef QFCCMM0
    ofs_list<<"tfidfなし"<<std::endl;
    QFCCMM test(data_dimension, data_number, centers_number,
		qfccmm0m[INDEX], qfccmm0l[INDEX], qfccmm0t[INDEX]);
#endif 
#ifdef QFCCMM1
    ofs_list<<"tfidfA"<<std::endl;
    tfidf1(Data);
    QFCCMM test(data_dimension, data_number, centers_number,
		qfccmm1m[INDEX], qfccmm1l[INDEX], qfccmm1t[INDEX]);
#endif    
#ifdef QFCCMM2
    ofs_list<<"tfidfB"<<std::endl;
    tfidf2(Data);
    QFCCMM test(data_dimension, data_number, centers_number,
		qfccmm2m[INDEX], qfccmm2l[INDEX], qfccmm2t[INDEX]);
#endif
#ifdef KLFCS0
    ofs_list<<"tfidfなし"<<std::endl;
    KLFCS test(data_dimension, data_number, centers_number, klfcs0[INDEX]);
#endif
#ifdef KLFCS1
    ofs_list<<"tfidfA"<<std::endl;
    tfidf1(Data);
    KLFCS test(data_dimension, data_number, centers_number, klfcs1[INDEX]);
#endif
#ifdef KLFCS2
    ofs_list<<"tfidfB"<<std::endl;
    tfidf2(Data);
    KLFCS test(data_dimension, data_number, centers_number, klfcs2[INDEX]);
#endif
#ifdef BFCS0
    ofs_list<<"tfidfなし"<<std::endl;
    BFCS test(data_dimension, data_number, centers_number, bfcs0[INDEX]);
#endif 
#ifdef BFCS1
    ofs_list<<"tfidfA"<<std::endl;
    tfidf1(Data);
    BFCS test(data_dimension, data_number, centers_number, bfcs1[INDEX]);
#endif
#ifdef BFCS2
    ofs_list<<"tfidfB"<<std::endl;
    tfidf2(Data);
    //BFCS test(data_dimension, data_number, centers_number, bfcs2[INDEX]);
#endif
#ifdef QFCS0
    ofs_list<<"tfidfなし"<<std::endl;
    QFCS test(data_dimension, data_number, centers_number,
	      qfcs0m[INDEX], qfcs0l[INDEX]);
#endif 
#ifdef QFCS1
    ofs_list<<"tfidfA"<<std::endl;
    tfidf1(Data);
    QFCS test(data_dimension, data_number, centers_number,
	      qfcs1m[INDEX], qfcs1l[INDEX]);
#endif
#ifdef QFCS2
    ofs_list<<"tfidfB"<<std::endl;
    tfidf2(Data);
    QFCS test(data_dimension, data_number, centers_number,
	      qfcs2m[INDEX], qfcs2l[INDEX]);
#endif     
    //正解の帰属度の読み込み
    std::ifstream ifs_correctCrispMembership
      (filenameCorrectCrispMembership);
    if(!ifs_correctCrispMembership){
      std::cerr << "File:" << filenameCorrectCrispMembership
		<< "could not open." << std::endl;
      exit(1);
    }
    //読み込んだ正解の帰属度を格納
    for(int i=0;i<centers_number;i++)
      for(int k=0;k<data_number;k++)
	ifs_correctCrispMembership >> test.correctCrispMembership(i,k);
    ifs_correctCrispMembership.close();
    //データを与える
    test.copydata(Data);
#if defined (KLFCS0) || (KLFCS1) || (KLFCS2) || (BFCS0) || (BFCS1) || (BFCS2) || (QFCS0) || (QFCS1) || (QFCS2)
    test.ForSphericalData();
#else
    test.ForMMMData();
#endif
    double average_ari=-1.0, sd=0.0, min_obje_ari=0.0;
    std::vector<double> ARIs(INIT_CENTERS);
    int FALSE=0, Index=0; double sumARI=0.0, min_objective=DBL_MAX;
    for(int ite=0;ite<INIT_CENTERS;ite++){
      test.reset();
      //初期クラスタサイズ調整変数
      test.initialize_clustersize();
      //初期クラスタ中心
      test.initialize_centers(ite+FALSE);
      //時間計測
      auto start=std::chrono::system_clock::now();
      //更新式ループ回数
      test.iterates()=0;
      int p=1;
      double savediff=0.0;
      while(1){
	test.revise_dissimilarities();
	test.revise_membership();
	test.revise_centers();
	test.revise_clusters_size();
	//帰属度の収束具合
	double diff_u=max_norm(test.tmp_membership()-test.membership());
	//クラスタ中心の収束具合
	double diff_v=max_norm(test.tmp_centers()-test.centers());
	//クラスタ混合比の収束具合
	double diff_p=max_norm(test.tmp_clusters_size()
			       -test.clusters_size());
	//全体の収束具合
	double diff=diff_u+diff_v+diff_p;
	savediff=diff;
	//収束したらクラスタリング終了
	if(diff<DIFF_FOR_STOP)break;
	if(test.iterates()>=MAX_ITERATES){
	  FALSE=INIT_CENTERS;
	  break;
	}
	test.iterates()++;
	if(std::isnan(diff)){
	  FALSE++;
	  ite--;
	  p=-1;
	  break;
	}
      }
      if(FALSE>=INIT_CENTERS){
	ofs_list<<"FALSE\t"
		<<test.iterates()<<std::endl;
	break;
      }
      if(p==1){
	test.set_crispMembership();
	test.set_contingencyTable();
	test.set_objective();
	ARIs[ite]=test.ARI();
	//計測終了
	auto end=std::chrono::system_clock::now();
	auto endstart=end-start;
	ofs_list<<ARIs[ite]<<"\t"
		<<savediff<<"\t"
		<<test.iterates()<<"\t"
		<<test.objective()<<"\t"
		<<std::chrono::duration_cast
	  <std::chrono::hours>(endstart).count()<<":"
		<<std::chrono::duration_cast
	  <std::chrono::minutes>(endstart).count()%60<<":"
		<<std::chrono::duration_cast
	  <std::chrono::seconds>(endstart).count()%60<<"\t";
	for(int j=0;j<test.initialize_c().size();j++)
	  ofs_list<<test.initialize_c()[j]<<" ";
	ofs_list<<std::endl;
	if(min_objective>test.objective()){
	  Index=ite;
	  min_objective=test.objective();
	}
	sumARI+=ARIs[ite];
      }
      else
	ofs_list<<"nan\t"
		<<savediff<<"\t"
		<<test.iterates()<<std::endl;
    }
    sumARI/=(double)INIT_CENTERS;
    double s=0.0;
    for(int j=0;j<INIT_CENTERS;j++)
      s+=pow(ARIs[j]-sumARI,2.0);
    if(sumARI>average_ari){
      average_ari=sumARI;
      sd=sqrt(s/(double)INIT_CENTERS);
      min_obje_ari=ARIs[Index];
    }
    ofs_summary<<files[INDEX]<<"\t";
#ifdef KLFCCM0
    ofs_summary<<"tfidfなし"<<std::endl
	       <<"KLFCCM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $\\lambda=" << test.fuzzifierLambda()
	       << "$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef KLFCCM1
    ofs_summary<<"tfidfA"<<std::endl
	       <<"KLFCCM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $\\lambda=" << test.fuzzifierLambda()
	       << "$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef KLFCCM2
    ofs_summary<<"tfidfB"<<std::endl
	       <<"KLFCCM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $\\lambda=" << test.fuzzifierLambda()
	       << "$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef BFCCM0
    ofs_summary<<"tfidfなし"<<std::endl
	       <<"BFCCM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $m=" << "1+10^{-2}"
	       << "$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef BFCCM1
    ofs_summary<<"tfidfA"<<std::endl
	       <<"BFCCM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $m=" << "1+10^{-2}"
	       << "$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef BFCCM2
    ofs_summary<<"tfidfB"<<std::endl
	       <<"BFCCM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $m=" << "1+10^{-2}"
	       << "$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef QFCCM0
    ofs_summary<<"tfidfなし"<<std::endl
	       <<"QFCCM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $(\\\\lambda,m)=("
	       << test.fuzzifierLambda() <<","
	       << test.fuzzifierEm() 
	       << ")$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef QFCCM1
    ofs_summary<<"tfidfA"<<std::endl
	       <<"QFCCM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $(\\\\lambda,m)=("
	       << test.fuzzifierLambda() <<","
	       << test.fuzzifierEm() 
	       << ")$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef QFCCM2
    ofs_summary<<"tfidfB"<<std::endl
	       <<"QFCCM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $(\\\\lambda,m)=("
	       << test.fuzzifierLambda() <<","
	       << "1+10^{-2})$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef KLFCCMM0
    ofs_summary<<"tfidfなし"<<std::endl
	       <<"KLFCCMM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $(\\\\lambda,t)=("
	       << test.fuzzifierLambda() <<","
	       << test.fuzzifierEt() 
	       << ")$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef KLFCCMM1
    ofs_summary<<"tfidfA"<<std::endl
	       <<"KLFCCMM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $(\\\\lambda,t)=("
	       << test.fuzzifierLambda() <<","
	       << test.fuzzifierEt() 
	       << ")$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef KLFCCMM2
    ofs_summary<<"tfidfB"<<std::endl
	       <<"KLFCCMM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $(\\\\lambda,t)=("
	       << test.fuzzifierLambda() <<","
	       << test.fuzzifierEt() 
	       << ")$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef BFCCMM0
    ofs_summary<<"tfidfなし"<<std::endl
	       <<"BFCCMM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $(m,t)=("
	       << test.fuzzifierEm() <<","
	       << test.fuzzifierEt() 
	       << ")$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif     
#ifdef BFCCMM1
    ofs_summary<<"tfidfA"<<std::endl
	       <<"BFCCMM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $(m,t)=("
	       << test.fuzzifierEm() <<","
	       << test.fuzzifierEt() 
	       << ")$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef BFCCMM2
    ofs_summary<<"tfidfB"<<std::endl
	       <<"BFCCMM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $(m,t)=("
	       << test.fuzzifierEm() <<","
	       << test.fuzzifierEt() 
	       << ")$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef QFCCMM0
    ofs_summary<<"tfidfなし"<<std::endl
	       <<"QFCCMM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $(\\\\lambda,m,t)=("
	       << test.fuzzifierLambda() <<","
	       << test.fuzzifierEm() <<","
	       << test.fuzzifierEt() 
	       << ")$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef QFCCMM1
    ofs_summary<<"tfidfA"<<std::endl
	       <<"QFCCMM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $(\\\\lambda,m,t)=("
	       << test.fuzzifierLambda() <<","
	       << test.fuzzifierEm() <<","
	       << test.fuzzifierEt() 
	       << ")$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef QFCCMM2
    ofs_summary<<"tfidfB"<<std::endl
	       <<"QFCCMM    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $(\\\\lambda,m,t)=("
	       << test.fuzzifierLambda() <<","
	       << test.fuzzifierEm() <<","
	       << test.fuzzifierEt() 
	       << ")$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif    
#ifdef KLFCS0
    ofs_summary<<"tfidfなし"<<std::endl
	       <<"KLFCS    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $\\lambda=" << test.fuzzifierLambda()
	       << "$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef KLFCS1
    ofs_summary<<"tfidfA"<<std::endl
	       <<"KLFCS    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $\\lambda=" << test.fuzzifierLambda()
	       << "$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif       
#ifdef KLFCS2
    ofs_summary<<"tfidfB"<<std::endl
	       <<"KLFCS    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $\\lambda=" << test.fuzzifierLambda()
	       << "$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef BFCS0
    ofs_summary<<"tfidfなし"<<std::endl
	       <<"BFCS    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $m="
	       << test.fuzzifierEm() 
	       << "$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef BFCS1
    ofs_summary<<"tfidfA"<<std::endl
	       <<"BFCS    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $m="
	       << test.fuzzifierEm() 
	       << "$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef BFCS2
    ofs_summary<<"tfidfB"<<std::endl
	       <<"BFCS    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $m="
	       << test.fuzzifierEm() 
	       << "$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef QFCS0
    ofs_summary<<"tfidfなし"<<std::endl
	       <<"QFCS    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $(\\\\lambda,m)=("
	       << test.fuzzifierLambda() <<","
	       << test.fuzzifierEm() 
	       << ")$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef QFCS1
    ofs_summary<<"tfidfA"<<std::endl
	       <<"QFCS    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $(\\\\lambda,m)=("
	       << test.fuzzifierLambda() <<","
	       << test.fuzzifierEm() 
	       << ")$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif
#ifdef QFCS2
    ofs_summary<<"tfidfB"<<std::endl
	       <<"QFCS    & "<< average_ari
	       << " & " << sd
	       << " & " << min_obje_ari
	       << " & $(\\\\lambda,m)=("
      	       << test.fuzzifierLambda() <<","
	       << test.fuzzifierEm() 
	       << ")$ \\\\\\hline"
	       << " " << min_objective<<std::endl;
#endif    
  }
  return 0;
}
