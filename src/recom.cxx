#include"recom.h"

Recom::Recom(int user,
	     int item,
	     int user_cen,
	     int item_cen, 
	     int miss):
  SEED(0),Current(0),CCurrent(0),Missing(0),
  SparseIncompleteData(user, item),
  SparseCorrectData(user, item),
  NormalizedData(user, item),
  KessonIndex(miss, 2),
  Similarity(user, user),
  Mem(user_cen, user),
  ItemMem(item_cen, item),
  resultMAE(METHOD_NUMBER,CLUSTERINGTRIALS),
  resultFmeasure(METHOD_NUMBER,CLUSTERINGTRIALS),
  choiceMAE(METHOD_NUMBER, MISSINGTRIALS),
  choiceFmeasure(METHOD_NUMBER, MISSINGTRIALS),
  Prediction(miss),
  SparseIndex(miss),
  TP_FN((int)return_max_value()*10),
  FP_TN((int)return_max_value()*10),
  Obje(CLUSTERINGTRIALS),
  W(user){
  for(int i=0;i<(int)return_max_value()*10;i++){
    TP_FN[i]=0.0;
    FP_TN[i]=0.0;
  }
  for(int i=0;i<CLUSTERINGTRIALS;i++)
    Obje[i]=DBL_MAX;
}

std::string &Recom::method_name(void){
  return METHOD_NAME;
}

Vector Recom::obje(void) const{
  return Obje;
}

Matrix Recom::kessonindex(void) const{
  return KessonIndex;
}

double Recom::similarity(int index1, int index2){
  return Similarity[index1][index2];
}

double &Recom::obje(int index){
  return Obje[index];
}

int &Recom::current(void){
  return Current;
}

int &Recom::Ccurrent(void){
  return CCurrent;
}

int &Recom::missing(void){
  return Missing;
}

void Recom::input(std::string InputDataName){
  std::ifstream ifs(InputDataName);
  if(!ifs){
    std::cerr << "DirectoryName" <<InputDataName
	      <<": could not open." << std::endl;
    exit(1);
  }
  for(int cnt=0;cnt<return_user_number();cnt++){
    int essencialSize;
    ifs >> essencialSize;
    SparseVector dummy(return_item_number(), essencialSize);
    for(int ell=0;ell<essencialSize;ell++){
      ifs >> dummy.indexIndex(ell) >> dummy.elementIndex(ell);
    }
    SparseCorrectData[cnt]=dummy;
  }
  ifs.close();
}

void Recom::Seed(void){
  SEED=0;
  return;
}

void Recom::reset(void){
  SparseIncompleteData=SparseCorrectData;
  for(int k=0;k<return_user_number();k++){
    for(int l=0;l<return_user_number();l++){
      Similarity[k][l]=0.0;
    }
  }
  return;
}

void Recom::reset2(){
  for(int miss=0;miss<Missing;miss++)
    Prediction[miss]=0.0;
  for(int i=0;i<(int)return_max_value()*10;i++){
    TP_FN[i]=0.0;
    FP_TN[i]=0.0;
  }
  return;
}

void Recom::revise_missing_values(void){
  int tmprow,tmpcol;
  for(int m=0; m<Missing;){
    /****乱数生成****/
    std::mt19937_64 mt;
    mt.seed(SEED);
    std::uniform_int_distribution<>
      randRow(0,return_user_number()-1);
    //ランダムに行番号生成
    tmprow=randRow(mt);
    std::uniform_int_distribution<>
      randCol(0,SparseCorrectData[tmprow].essencialSize()-1);
    //ランダムに列番号生成
    tmpcol=randCol(mt);
    //データ行すべて欠損させないように
    int c=-1;
    for(int i=0;i<SparseIncompleteData[tmprow].essencialSize();i++)
      if(SparseIncompleteData[tmprow].elementIndex(i)==0)
	c++;
    //既に欠損していない場合
    if(SparseIncompleteData[tmprow].elementIndex(tmpcol)>0
       && SparseIncompleteData[tmprow].essencialSize()>c){
      //要素を0にする
      SparseIncompleteData[tmprow].elementIndex(tmpcol)=0;
      //欠損した行番号を保存
      KessonIndex[m][0]=tmprow;
      //欠損した列番号を保存
      KessonIndex[m][1]=SparseIncompleteData[tmprow]
	.indexIndex(tmpcol);
      //スパースデータの列番号を保存
      SparseIndex[m]=tmpcol;
      m++;
    }
    SEED++;
  }
  return;
}

void Recom::mae(std::string text, int method_number){
  double result=0.0;
  for(int m=0;m<Missing;m++){
    result+=fabs(SparseCorrectData[KessonIndex[m][0]]
		 .elementIndex(SparseIndex[m])
		 -Prediction[m]);
  }
  resultMAE[method_number][CCurrent]=result/(double)Missing;
  std::ofstream ofs(text+"/"+METHOD_NAME+"MAE.txt",std::ios::app);
  ofs<<Missing<<"\t"
     <<SEED<<"\t"
     <<Current<<"\t"
     <<CCurrent<<"\t"
     <<std::fixed<<std::setprecision(10)
     <<resultMAE[method_number][CCurrent]<<std::endl;
  ofs.close();
  return;
}

void Recom::fmeasure(std::string text, int method_number){
  std::ofstream ofs(text+"/"+METHOD_NAME+"Fmeasure.txt" ,std::ios::app);
  for(int index=1;index<(int)return_max_value()*10;index++){
    double TP=0.0,FP=0.0,FN=0.0,TN=0.0;
    //閾値の設定
    double siki=(double)index/10.0;
    for(int m=0;m<Missing;m++){
      //正解値が閾値以上かつ，予測値が閾値以上場合
      if((siki<=SparseCorrectData[KessonIndex[m][0]]
	  .elementIndex(SparseIndex[m]))
	 &&(siki<=Prediction[m]))
	TP+=1.0;
      //正解値が閾値を下回ったかつ，予測値が閾値上回った場合
      else if((siki>SparseCorrectData[KessonIndex[m][0]]
	       .elementIndex(SparseIndex[m]))
	      &&(siki<=Prediction[m]))
	FP+=1.0;
      //正解値が閾値上回ったかつ，予測値が閾値を下回った場合
      else if((siki<=SparseCorrectData[KessonIndex[m][0]]
	       .elementIndex(SparseIndex[m]))
	      &&(siki>Prediction[m]))
	FN+=1.0;
      //それ以外
      else if((siki>SparseCorrectData[KessonIndex[m][0]]
	       .elementIndex(SparseIndex[m]))
	      &&(siki>Prediction[m]))
	TN+=1.0;
      else
	continue;
    }
    //閾値がF-measureで設定した閾値だった場合
    if(siki==return_threshold()){
      double Precision=TP/(TP+FP);
      double Recall=TP/(TP+FN);
      resultFmeasure[method_number][CCurrent]
	=(2.0*Recall*Precision)/(Recall+Precision);
      if(std::isnan(resultFmeasure[method_number][CCurrent]))
	resultFmeasure[method_number][CCurrent]=0.0;
      ofs<<Missing<<"\t"
	 <<SEED<<"\t"
	 <<current()<<"\t"
	 <<Ccurrent()<<"\t"
	 <<TP<<" "
	 <<FP<<" "
	 <<FN<<" "
	 <<TN<<" "
	 <<std::fixed<<std::setprecision(10)
	 <<resultFmeasure[method_number][CCurrent]
	 <<std::endl;
    }
    /*~2017/12/25
    //0で割る場合，無理やり回避
    if((TP+FN)==0||(FP+TN)==0){
    TP_FN[index]=0.0;
    FP_TN[index]=0.0;
    }
    */
    if(TP+TN==Missing){
      TP_FN[index]=1.0;
      FP_TN[index]=1.0;
    }
    //Recall，Falloutの計算
    else{
      TP_FN[index]=TP/(TP+FN);
      FP_TN[index]=FP/(FP+TN);
      if((TP+FN)==0||(FP+TN)==0){
	TP_FN[index]=1.0;
	FP_TN[index]=1.0;
      }
      //~2017/12/25
      /*
	if(TP_FN[index]==0||FP_TN[index]==0){
	TP_FN[index]=0;
	FP_TN[index]=0;
	}
      */
    }
  }
  ofs.close();
  return;
}

void Recom::roc(std::string dir){
  std::string ROC_STR
    =dir+"/ROC/"+METHOD_NAME+"ROC"
    +std::to_string(Missing)+"_"+std::to_string(Current)+"_"
    +std::to_string(CCurrent)+"sort.txt";
  //ROCでプロットする点の数
  int max_index=(int)return_max_value()*10;
  //一旦保存
  Vector False=FP_TN;
  Vector True=TP_FN;
  std::ofstream ofs(ROC_STR,std::ios::app);
  if(!ofs)
    std::cerr<<"ファイルオープン失敗\n";
  else{
    //横軸でソート
    Sort(False,True,max_index);
    for(int i=0;i<max_index;i++)
      ofs<<std::fixed<<std::setprecision(10)
	 <<False[i]<<"\t"<<True[i]<<std::endl;
  }
  ofs.close();
  return;
}

void Recom::Sort(Vector &fal, Vector &tru, int index){
  double tmp1,tmp2;
  for(int j=0;j<index-1;j++){
    for(int k=j+1;k<index;k++){
      if(fal[j]>fal[k]){
	tmp1=fal[j];
	tmp2=tru[j];
	fal[j]=fal[k];
	tru[j]=tru[k];
	fal[k]=tmp1;
	tru[k]=tmp2;
      }
    }
  } 
  return;
}

void Recom::ofs_objective(std::string dir){
  std::ofstream ofs(dir+"/object.txt",std::ios::app);
  if(!ofs){
    std::cerr<<"ファイルオープン失敗\n";
    exit(1);
  }
  ofs<<Missing<<"\t"<<SEED<<"\t";
  return;
}

void Recom::choice_mae_f(std::vector<std::string> dir){
  //最小目的関数値をとる番号を得る
  for(int method=0;method<(int)dir.size();method++){
    double tmp=DBL_MAX; int obje_index=0;
    for(int i=0;i<CLUSTERINGTRIALS;i++)
      if(tmp>Obje[i]){
	tmp=Obje[i];
	obje_index=i;
      }
    choiceMAE[method][Current]=resultMAE[method][obje_index];
    choiceFmeasure[method][Current]=resultFmeasure[method][obje_index];
    //選ばれたROCをchoiceフォルダに移す
    std::string oldname
      =dir[method]+"/ROC"+"/"+METHOD_NAME+"ROC"
      +std::to_string(Missing)+"_"
      +std::to_string(Current)+"_"
      +std::to_string(obje_index)+"sort.txt";
    std::string newname
      =dir[method]+"/ROC/choice"+"/"+METHOD_NAME+"ROC"
      +std::to_string(Missing)+"_"
      +std::to_string(Current)+"sort.txt";
    Rename(oldname,newname);
  }
  return;
}

void Recom::save_mae_f(std::vector<std::string> dir){
  for(int method=0;method<(int)dir.size();method++){
    choiceMAE[method][Current]=resultMAE[method][0];
    choiceFmeasure[method][Current]=resultFmeasure[method][0];
  }
  return;
}

void Recom::out_mae_f(std::vector<std::string> dir){
  for(int method=0;method<(int)dir.size();method++){
    std::ofstream ofs(dir[method]+"/averageMaeFmeasure.txt" ,
		      std::ios::app);
    double sumMAE=0.0,sumF=0.0;
    for(int i=0;i<MISSINGTRIALS;i++){
      sumMAE+=choiceMAE[method][i];
      sumF+=choiceFmeasure[method][i];
    }
    if(!ofs)
      std::cerr<<"ファイルopen失敗\n";
    ofs<<Missing<<"\t"<<std::fixed<<std::setprecision(10)
       <<"\t"<<sumMAE/(double)MISSINGTRIALS
       <<"\t"<<sumF/(double)MISSINGTRIALS<<std::endl;
    ofs.close();
  }
  return;
}

void Recom::precision_summury(std::vector<std::string> dir){
  int max=(int)return_max_value()*10;
  for(int method=0;method<(int)dir.size();method++){
    double rocarea=0.0;
    for(int x=0;x<MISSINGTRIALS;x++){
      Vector array1(max,0.0,"all"),array2(max,0.0,"all");
      std::ifstream ifs(dir[method]+"/ROC/choice/"+METHOD_NAME+"ROC"
			+std::to_string(Missing)
			+"_"+std::to_string(x)+"sort.txt");
      if(!ifs){
	std::cerr<<"ファイルinput失敗:trials:"
		 <<x<<"miss:"<<Missing<<std::endl;
	break;
      }
      for(int i=0;i<max;i++)
	ifs>>array1[i]>>array2[i];
      ifs.close();
      for(int i=0;i<max-1;i++){
	/*~2017/12/25
	  if((array1[i]<array1[i+1])||(array1[i]!=0)||(array2[i]!=0)){
	*/
	if((array1[i]<array1[i+1])){
	  double low=array1[i+1]-array1[i];
	  double height=fabs(array2[i+1]-array2[i]);
	  double squarearea=low*array2[i];
	  double triangle=(low*height)/2.0;
	  rocarea+=squarearea+triangle;
	}
	if(array2[i]==1.0)
	  break;
      }
    }
    double sumMAE=0.0,sumF=0.0;
    for(int i=0;i<MISSINGTRIALS;i++){
      sumMAE+=resultMAE[method][i];
      sumF+=choiceFmeasure[method][i];
    }
    std::ofstream ofs(dir[method]+"/averageMaeFmeasureAuc.txt", std::ios::app);
    if(!ofs)
      std::cerr<<"ファイルopen失敗\n";
    std::cout<<"miss:"<<Missing<<"\tMAE="<<sumMAE/(double)MISSINGTRIALS
	     <<"\tF-measure="<<sumF/(double)MISSINGTRIALS<<"\tROC="
	     <<rocarea/(double)MISSINGTRIALS<<std::endl;
    ofs<<Missing<<"\t"<<std::fixed<<std::setprecision(10)
       <<"\t"<<sumMAE/(double)MISSINGTRIALS
       <<"\t"<<sumF/(double)MISSINGTRIALS
       <<"\t"<<rocarea/(double)MISSINGTRIALS<<std::endl;
  }
  return;
}

void Recom::revise_prediction(void){
  for(int index=0;index<Missing;index++){
    double RecomItem=0.0, RecomUSER=0.0,RecomITEM=0.0,RecomUserItem=0.0;
    double numerator=0.0,denominator=0.0;
    double numerator1=0.0,denominator1=0.0;
    double numerator2=0.0,denominator2=0.0;
    double numerator3=0.0,denominator3=0.0;
    /******RecomUser********/
    double RecomUser=user_average(KessonIndex[index][0]);
    int index1=0,index2=0;
    //行クラスタと列クラスタで数が異なる場合も考える
    for(int i=0;i<Mem.rows();i++)
      if(Mem[i][KessonIndex[index][0]]==1.0)
	index1=i;
    for(int i=0;i<ItemMem.rows();i++)
      if(ItemMem[i][KessonIndex[index][1]]==1.0)
	index2=i;
    for(int k=0;k<return_user_number();k++){      
      int user_size=
	SparseIncompleteData[k].essencialSize();
      /******RecomItem********/
      for(int ell=0;ell<user_size;ell++){
	int user_index=SparseIncompleteData[k].indexIndex(ell);
	if(user_index>KessonIndex[index][1])
	  break;
	double user_element=SparseIncompleteData[k].elementIndex(ell);
	if((user_element>0)&&(user_index==KessonIndex[index][1])){
	  numerator1+=user_element;
	  denominator1++;
	  break;
	}
      }      
      /******RecomUSER********/
      if(Mem[index1][k]==1.0){
	for(int ell=0;ell<user_size;ell++){
	  double user_element=SparseIncompleteData[k].elementIndex(ell);
	  if(user_element>0){
	    numerator2+=user_element;
	    denominator2++;
	  }
	}
      }
      /******RecomITEM********/
      for(int ell=0;ell<user_size;ell++){	
	int user_index=SparseIncompleteData[k].indexIndex(ell);	
	if(ItemMem[index2][user_index]==1.0){
	  double user_element=SparseIncompleteData[k].elementIndex(ell);
	  if(user_element>0){
	    numerator3+=user_element;
	    denominator3++;
	  }
	}
      }
      /******RecomUserItem********/
      if(Mem[index1][k]==1.0){
	for(int ell=0;ell<user_size;ell++){
	  int user_index=SparseIncompleteData[k].indexIndex(ell);
	  if(ItemMem[index2][user_index]==1.0){
	    double user_element=SparseIncompleteData[k]
	      .elementIndex(ell);
	    if(user_element>0){
	      numerator+=user_element;
	      denominator++;
	    }
	  }
	}
      }
    }
    if(denominator1>0)
      RecomItem=numerator1/denominator1;
    if(denominator2>0)
      RecomUSER=numerator2/denominator2;
    if(denominator3>0)
      RecomITEM=numerator3/denominator3;
    if(denominator>0)
      RecomUserItem=numerator/denominator;
    Prediction[index]
      =RecomUser+RecomItem-RecomUSER-RecomITEM+RecomUserItem;
  }
  return;
}

void Recom::computation_w(void){
  for(int k=0;k<return_user_number();k++){
    double m=0.0,s=0.0;
    double ave=user_average(k);
    int size=SparseIncompleteData[k].essencialSize();
    for(int ell=0;ell<size;ell++){
      double element=SparseIncompleteData[k].elementIndex(ell);
      if(element>0.0){
	m++;
	s+=pow((element-ave),2.0);
      }
    }
    W[k]=m*sqrt(s/(double)size);
  }
  return;
}

void Recom::revise_prediction2(const Matrix &V){
  for(int index=0;index<Missing;index++){
    int h=0, a=KessonIndex[index][0];
    double numerator=0.0,denominator=0.0;
    for(int i=0;i<Mem.rows();i++)
      if(Mem[i][a]==1.0)
	h=i;
    for(int k=0;k<return_user_number();k++){
      double rTv=0.0;
      for(int ell=0;ell<SparseIncompleteData[k].essencialSize();ell++)
	rTv+=SparseIncompleteData[k].elementIndex(ell)
	  *V[h][SparseIncompleteData[k].indexIndex(ell)];
      denominator+=/*W[k]*/Mem[h][k]*rTv;
      for(int ell=0;ell<SparseIncompleteData[k].essencialSize();ell++){
	if(KessonIndex[index][1]
	   <SparseIncompleteData[k].indexIndex(ell))
	  break;
	if(KessonIndex[index][1]
	   ==SparseIncompleteData[k].indexIndex(ell)){
	  numerator+=/*W[k]*/Mem[h][k]*rTv
	    *SparseIncompleteData[k].elementIndex(ell);
	  break;
	}
      }
    }
    if(denominator==0)
      Prediction[index]=0.0;
    else
      Prediction[index]=numerator/denominator;
  }
  return;
}

void Recom::pearsonsim(void){
  for(int user1=0;user1<return_user_number();user1++){
    /*ユーザ1の非ゼロサイズ*/
    int user1_size=
      SparseIncompleteData[user1]
      .essencialSize();
    for(int user2=0;user2<return_user_number();user2++){
      double psum=0.0,sum1=0.0,sum2=0.0,sum1sq=0.0,sum2sq=0.0;
      double hyokasu=0.0;
      /*ユーザ1がユーザ2である場合*/
      if(user1==user2)
	Similarity[user1][user2]=0.0;
      else{
	/*ユーザ2の非ゼロサイズ*/
	int user2_size=
	  SparseIncompleteData[user2].essencialSize();
	/*ユーザ2のインデックスを0から*/
	int user2_ell=0;
	for(int ell=0;ell<user1_size;ell++){
	  /*ユーザ2のインデックスが
	    ユーザ2の非ゼロサイズを上回ったらbreak ~20180606*/
	  if(user2_size<user2_ell)break;
	  /*ユーザ1の既評価値*/
	  double user1_element
	    =SparseIncompleteData[user1]
	    .elementIndex(ell);
	  /*ユーザ1の既評価値が欠損でなければ計算*/
	  if(user1_element>0){
	    //ユーザ1のインデックス*/
	    int user1_index
	      =SparseIncompleteData[user1]
	      .indexIndex(ell);
	    while(1){
	      if(user2_size==user2_ell)break;
	      /*ユーザ2のインデックス*/
	      int user2_index
		=SparseIncompleteData[user2].indexIndex(user2_ell);
	      /*ユーザ2の方が上回ったらbreak*/
	      if(user1_index<user2_index)break;	      
	      /*ユーザ1の既評価値*/
	      double user2_element
		=SparseIncompleteData[user2].elementIndex(user2_ell);
	      /*インデックスが揃った場合とユーザ既評価値が
		欠損されてなければ計算*/
	      if((user1_index==user2_index)&&(user2_element>0)){
		hyokasu+=1.0;
		psum+=user1_element*user2_element;
		sum1+=user1_element;
		sum2+=user2_element;
		sum1sq+=pow(user1_element,2.0);
		sum2sq+=pow(user2_element,2.0);
		user2_ell++;
		break;
	      }
	      user2_ell++;
	    }
	  }
	}
	double numerator=psum-(sum1*sum2/hyokasu);
	double denominator=sqrt((sum1sq-pow(sum1,2.0)/hyokasu)
				*(sum2sq-pow(sum2,2.0)/hyokasu));
	if(denominator==0 || std::isnan(denominator))
	  Similarity[user1][user2]=0.0;
	else
	  Similarity[user1][user2]
	    =numerator/denominator;
      }
    }
  }
  return;
}


void Recom::pearsonsim_clustering(void){
  for(int user1=0;user1<return_user_number();user1++){
    /*ユーザ1の既評価数*/
    int user1_size=
      SparseIncompleteData[user1]
      .essencialSize();
    // CLUSTERING_PEAR
    int tmpcenternum=0;
    for(int i=0;i<Mem.rows();i++)
      if(Mem[i][user1]==1.0)
	tmpcenternum=i;
    for(int user2=0;user2<return_user_number();user2++){
      double psum=0.0,sum1=0.0,sum2=0.0,sum1sq=0.0,sum2sq=0.0;
      double hyokasu=0.0;
      /*ユーザ2がユーザ1である，または
	ユーザ1が属すユーザクラスタに属さないユーザであった場合
	ユーザ2とユーザ1の類似度を0にすることで計算させない*/
      if(user1==user2 || Mem[tmpcenternum][user2]==0)
	Similarity[user1][user2]=0.0;
      else{
	/*ユーザ2の既評価数*/
	int user2_size=
	  SparseIncompleteData[user2].essencialSize();
	/*現在のユーザ2の既評価値インデックス*/
	int user2_ell=0;
	for(int ell=0;ell<user1_size;ell++){
	  /*ユーザ2の既評価値インデックスがユーザ2の
	    既評価数を上回ったらbreak*/
	  if(user2_size<user2_ell)
	    break;
	  /*ユーザ1の現在の既評価値*/
	  double user1_element
	    =SparseIncompleteData[user1]
	    .elementIndex(ell);
	  /*ユーザ1の現在の既評価値が欠損されてなければ計算*/
	  if(user1_element>0){
	    /*ユーザ1の現在の評価値インデックスのインデックス*/
	    int user1_index
	      =SparseIncompleteData[user1]
	      .indexIndex(ell);
	    while(1){
	      if(user2_size==user2_ell)break;
	      /*ユーザ2の現在の評価値インデックスのインデックス*/
	      int user2_index
		=SparseIncompleteData[user2].indexIndex(user2_ell);
	      /*ユーザ2の方が上回ったらbreak*/
	      if(user1_index<user2_index)
		break;
	      /*現在のユーザの既評価値*/
	      double user2_element
		=SparseIncompleteData[user2].elementIndex(user2_ell);
	      /*インデックスが揃った場合とユーザ既評価値が
		欠損されてなければ計算*/
	      if((user1_index==user2_index)&&(user2_element>0)){
		hyokasu+=1.0;
		psum+=user1_element*user2_element;
		sum1+=user1_element;
		sum2+=user2_element;
		sum1sq+=pow(user1_element,2.0);
		sum2sq+=pow(user2_element,2.0);
		user2_ell++;
		break;
	      }
	      /*現在のユーザの既評価値インデックスインクリメント*/
	      user2_ell++;
	    }
	  }
	}
	double numerator=psum-(sum1*sum2/hyokasu);
	double denominator=sqrt((sum1sq-pow(sum1,2.0)/hyokasu)
				*(sum2sq-pow(sum2,2.0)/hyokasu));
	if(denominator==0 || std::isnan(denominator))
	  Similarity[user1][user2]=0.0;
	else
	  Similarity[user1][user2]
	    =numerator/denominator;
      }
    }
  }
  return;
}

//PCM用類似度計算
void Recom::pearsonsim_for_pcm(const Matrix &Membership_PCM,
			       const Vector &Threshold){
  for(int user1=0;user1<return_user_number();user1++){
    /*ユーザ1の既評価数*/
    int user1_size=
      SparseIncompleteData[user1]
      .essencialSize();
    for(int user2=0;user2<return_user_number();user2++){
      double psum=0.0,sum1=0.0,sum2=0.0,sum1sq=0.0,sum2sq=0.0;
      double hyokasu=0.0;
      /*ユーザ2がユーザ1である，または
	ユーザ1が属すユーザクラスタに属さないユーザであった場合
	ユーザ2とユーザ1の類似度を0にすることで計算させない*/
      if(user1==user2 || Membership_PCM[user1][user2]<Threshold[user1])
	Similarity[user1][user2]=0.0;
      else{
	/*ユーザ2の既評価数*/
	int user2_size=
	  SparseIncompleteData[user2].essencialSize();
	/*現在のユーザ2の既評価値インデックス*/
	int user2_ell=0;
	for(int ell=0;ell<user1_size;ell++){
	  /*ユーザ2の既評価値インデックスがユーザ2の
	    既評価数を上回ったらbreak*/
	  if(user2_size<user2_ell)
	    break;
	  /*ユーザ1の現在の既評価値*/
	  double user1_element
	    =SparseIncompleteData[user1]
	    .elementIndex(ell);
	  /*ユーザ1の現在の既評価値が欠損されてなければ計算*/
	  if(user1_element>0){
	    /*ユーザ1の現在の評価値インデックスのインデックス*/
	    int user1_index
	      =SparseIncompleteData[user1]
	      .indexIndex(ell);
	    while(1){
	      if(user2_size==user2_ell)break;
	      /*ユーザ2の現在の評価値インデックスのインデックス*/
	      int user2_index
		=SparseIncompleteData[user2].indexIndex(user2_ell);
	      /*ユーザ2の方が上回ったらbreak*/
	      if(user1_index<user2_index)
		break;
	      /*現在のユーザの既評価値*/
	      double user2_element
		=SparseIncompleteData[user2].elementIndex(user2_ell);
	      /*インデックスが揃った場合とユーザ既評価値が
		欠損されてなければ計算*/
	      if((user1_index==user2_index)&&(user2_element>0)){
		hyokasu+=1.0;
		psum+=user1_element*user2_element;
		sum1+=user1_element;
		sum2+=user2_element;
		sum1sq+=pow(user1_element,2.0);
		sum2sq+=pow(user2_element,2.0);
		user2_ell++;
		break;
	      }
	      /*現在のユーザの既評価値インデックスインクリメント*/
	      user2_ell++;
	    }
	  }
	}
	double numerator=psum-(sum1*sum2/hyokasu);
	double denominator=sqrt((sum1sq-pow(sum1,2.0)/hyokasu)
				*(sum2sq-pow(sum2,2.0)/hyokasu));
	if(denominator==0 || std::isnan(denominator))
	  Similarity[user1][user2]=0.0;
	else
	  Similarity[user1][user2]
	    =numerator/denominator;
      }
    }
  }
  return;
}

void Recom::pearsonpred1(void){
  for(int index=0;index<Missing;index++){
    double numerator=0.0,denominator=0.0;
    int miss_user_index=KessonIndex[index][1];
    for(int i=0;i<return_user_number();i++){
      if(Similarity[KessonIndex[index][0]][i]>0.0){
	int user_size=
	  SparseIncompleteData[i].essencialSize();
	for(int ell=0;ell<user_size;ell++){
	  int user_index
	    =SparseIncompleteData[i].indexIndex(ell);
	  if(user_index>miss_user_index)
	    break;
	  double user_element
	    =SparseIncompleteData[i].elementIndex(ell);
	  if((user_element>0.0)&&(user_index==miss_user_index)){
	    numerator+=Similarity[KessonIndex[index][0]][i]
	      *user_element;
	    denominator+=Similarity[KessonIndex[index][0]][i];
	    break;
	  }
	}
      }
    }
    if(denominator==0)
      Prediction[index]=0.0;
    else
      Prediction[index]=numerator/denominator;
  }
  return; 
}

void Recom::pearsonpred2(void){
  for(int index=0;index<Missing;index++){
    double numerator=0.0,denominator=0.0;
    int miss_user_index=KessonIndex[index][1];
    for(int i=0;i<return_user_number();i++){
      if(Similarity[KessonIndex[index][0]][i]>0.0){
	int user_size=
	  SparseIncompleteData[i].essencialSize();
	for(int ell=0;ell<user_size;ell++){
	  int user_index
	    =SparseIncompleteData[i].indexIndex(ell);
	  if(user_index>miss_user_index)
	    break;
	  double user_element
	    =SparseIncompleteData[i].elementIndex(ell);
	  if((user_element>0.0)&&(user_index==miss_user_index)){
	    numerator+=Similarity[KessonIndex[index][0]][i]
	      *(user_element-user_average(i));
	    denominator+=Similarity[KessonIndex[index][0]][i];
	    break;
	  }
	}
      }      
    }
    if(denominator==0)
      Prediction[index]=user_average(KessonIndex[index][0]);
    else {
      Prediction[index]=user_average(KessonIndex[index][0])
	+numerator/denominator;
    }
    if(std::isnan(Prediction[index]))
      Prediction[index]=0.0;
  }
  return;
}

double Recom::user_average(int index){
  double result=0.0;
  int hyokazu=0;
  for(int i=0;i<SparseIncompleteData[index].essencialSize();i++){
    if(SparseIncompleteData[index].elementIndex(i)>0.0){
      result+=SparseIncompleteData[index].elementIndex(i);
      hyokazu++;
    }
  }
  return result/hyokazu;
}

SparseMatrix Recom::sparsecorrectdata(void) const{
  return SparseCorrectData;
}

SparseVector &Recom::sparsecorrectdata(int index){
  return SparseCorrectData[index];
}

SparseMatrix Recom::sparseincompletedata(void) const{
  return SparseIncompleteData;
}

SparseVector &Recom::sparseincompletedata(const int &index){
  return SparseIncompleteData[index];
}

void Recom::crisp(const Matrix &Membership,
		  const Matrix &ItemMembership){
  for(int k=0;k<return_user_number();k++){
    for(int i=0;i<Membership.rows();i++)
      Mem[i][k]=0.0;
    double max=-DBL_MAX;
    int max_index=-1;
    for(int i=0;i<Membership.rows();i++){
      if(Membership[i][k]>max){
	max=Membership[i][k];
	max_index=i;
      }
    }
    Mem[max_index][k]=1.0;
  }
  for(int ell=0;ell<return_item_number();ell++){
    for(int j=0;j<ItemMembership.rows();j++)
      ItemMem[j][ell]=0.0;
    double max=-DBL_MAX;
    int max_index=-1;
    for(int j=0;j<ItemMembership.rows();j++){
      if(ItemMembership[j][ell]>max){
	max=ItemMembership[j][ell];
	max_index=j;
      }
    }
    ItemMem[max_index][ell]=1.0;
  }
  return;
}

int return_user_number(){
#ifdef MOVIE
  return 905;
#elif defined BOOK
  return 1091;//1090;
#elif defined JESTER
  return 2916;
#elif defined MOVIE2
  return 500;
#elif defined LIBIMSETI
  return 866;//500;
#elif defined EPINIONS
  return 1022;//2000;
#elif defined SUSHI
  return 5000;
#elif defined ARTIFICIALITY
  return 100;
#else
  std::cout<<"error recom's func return_user_number\n";
  exit(1);
#endif
}

int return_item_number(){
#ifdef MOVIE
  return 684;
#elif defined BOOK
  return 2248;//2247;
#elif defined JESTER
  return 140;
#elif defined MOVIE2
  return 2523;
#elif defined LIBIMSETI
  return 1156;//2041;
#elif defined EPINIONS
  return 835;//517;
#elif defined SUSHI
  return 100;
#elif defined ARTIFICIALITY
  return 100;
#else
  std::cout<<"error recom's func return_item_number\n";
  exit(1);
#endif
}

double return_threshold(){
#ifdef MOVIE
  return 3.5;
#elif defined BOOK
  return 7.0;
#elif defined JESTER
  return 14.7;
#elif defined MOVIE2
  return 3.5;
#elif defined LIBIMSETI
  return 7.0;
#elif defined EPINIONS
  return 3.5;
#elif defined SUSHI
  return 3.5;
#elif defined ARTIFICIALITY
  return 3.5;
#else
  std::cout<<"error recom's func return_return_threshold\n";
  exit(1);
#endif
}

double return_max_value(){
#ifdef MOVIE
  return 5.0;
#elif defined BOOK
  return 10.0;
#elif defined JESTER
  return 21.0;
#elif defined MOVIE2
  return 5.0;
#elif defined LIBIMSETI
  return 10.0;
#elif defined EPINIONS
  return 5.0;
#elif defined SUSHI
  return 5.0;
#elif defined ARTIFICIALITY
  return 5.0;
#else
  std::cout<<"error recom's func return_max_value\n";
  exit(1);
#endif
}

std::string return_data_name(){
#ifdef MOVIE
  return "movie";
#elif defined BOOK
  return "book";
#elif defined JESTER
  return "jester";
#elif defined MOVIE2
  return "movie10M";
#elif defined LIBIMSETI
  return "libimseti";
#elif defined EPINIONS
  return "epinions";
#elif defined SUSHI
  return "sushi";
#elif defined ARTIFICIALITY
  return "artificiality";
#else
  std::cout<<"error recom's func return_data_name\n";
  exit(1);
#endif
}

void FILE_ENDL(std::string text){
  std::ofstream ofs(text,std::ios::app);
  ofs<<std::endl;
  ofs.close();
  return;
}

void Rename(std::string filename, std::string newname){
  if(!access(filename.c_str(),0)){ //If the file exists
    //Successfully deleted
    if(!rename(filename.c_str(),newname.c_str())){
      std::cout<<"roctxtFile successfully  renamed"
	       <<std::endl ;
      std::cout<<newname<<std::endl;
    }
    else//Cannot rename: file not open or insufficient permissions
      {
	std::cout
	  <<"The file cannot be renamed"
	  <<" (may be the following reasons):"
	  <<std::endl;
	std::cout<<"\t"<<"1. "
		 <<newname<<" Already exists"
		 <<std::endl
		 << "\t" << "2. "<<newname
		 <<" Being used, not closed"
		 <<std::endl
		 <<"\t"<<"3. "
		 <<"You do not have permission to rename this file"
		 <<std::endl;
      }
  }else{//The file does not exist
  }
  return;
}

std::vector<std::string> MkdirFCCM(std::string method){
  std::vector<std::string> v;
  std::string c_p = current_path();
  c_p = c_p + "/../../RESULT";
  mkdir(c_p.c_str(),0755);
  for(int i=0;i<(int)FCCM.size();i++){
    std::string d=
      c_p+"/"+method+"_"+FCCM[i]
      +"_"+return_data_name()+std::to_string(KESSON);
    mkdir(d.c_str(),0755);
    v.push_back(d);
  }
  return v;
}

std::vector<std::string> MkdirFCS(std::string method){
  std::vector<std::string> v;
  std::string c_p = current_path();
  c_p = c_p + "/../../RESULT";
  mkdir(c_p.c_str(),0755);
  for(int i=0;i<(int)FCS.size();i++){
    std::string d=
      c_p+"/"+method+"_"+FCS[i]
      +"_"+return_data_name()+std::to_string(KESSON);
    mkdir(d.c_str(),0755);
    v.push_back(d);
  }
  return v;
}

std::vector<std::string>
Mkdir(std::vector<double> para, int c, std::vector<std::string> dirs){
  std::vector<std::string> v;
  std::string fuzzifier="";
  for(int i=0;i<(int)para.size();i++){
    std::ostringstream oss;
    oss<<std::setprecision(5)<<para[i];
    std::string f(oss.str());
    fuzzifier+=f+"_";
  }
  for(int i=0;i<(int)dirs.size();i++){
    const std::string dir=dirs[i]+"/"+fuzzifier+"C"+std::to_string(c);
    v.push_back(dir);
    mkdir(dir.c_str(),0755);
    //ROCフォルダ作成
    const std::string roc=dir+"/ROC";
    mkdir(roc.c_str(),0755);
    //選ばれるROCファイルをまとめるフォルダ作成
    const std::string choice=roc+"/choice";
    mkdir(choice.c_str(),0755);
  }
  return v;
}

std::vector<std::string>
Mkdir(std::vector<std::string> methods){
  std::vector<std::string> v;
  std::string c_p = current_path();
  c_p = c_p + "/../../RESULT";
  mkdir(c_p.c_str(),0755);
  for(int i=0;i<(int)methods.size();i++){
    std::string d=
      c_p+"/"+methods[i]
      +"_"+return_data_name()+std::to_string(KESSON);
    mkdir(d.c_str(),0755);
    //ROCフォルダ作成
    const std::string roc=d+"/ROC";
    mkdir(roc.c_str(),0755);
    //選ばれるROCファイルをまとめるフォルダ作成
    const std::string choice=roc+"/choice";
    mkdir(choice.c_str(),0755);
    v.push_back(d);
  }
  return v;
}
