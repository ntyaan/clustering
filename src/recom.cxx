#include"recom.h"

Recom::Recom(int user,
	     int item,
	     int user_cen,
	     int item_cen, 
	     int miss):
  Miss(miss),
  SEED(0),SEED2(0),Current(0),CCurrent(0),
  SparseIncompleteData(user, item),
  SparseCorrectData(user, item),
  KessonIndex(miss, 2),
  Similarity(user,user),
  Mem(user_cen,user),
  ItemMem(item_cen,item),
  Prediction(miss),
  SparseIndex(miss),
  TP_FN((int)return_max_value()*10),
  FP_TN((int)return_max_value()*10),
  Obje(CLUSTERINGTRIALS){
  for(int i=0;i<(int)return_max_value()*10;i++){
    TP_FN[i]=0.0;
    FP_TN[i]=0.0;
  }
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

int &Recom::miss(void){
  return Miss;
}

int Recom::seed2(void){
  return SEED2;
}

void Recom::Seed(void){
  SEED=0;
  return;
}

void Recom::Seed2(int i){
  SEED2=SEED*i;
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

void Recom::revise_missing_values(int missing){
  int tmprow,tmpcol;
  for(int m=0; m<missing;){
    /****乱数生成****/
    std::mt19937_64 mt;
    mt.seed(SEED+SEED2);
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

void Recom::defect_pred_ofile(int missing, std::string dat){
  std::ofstream ofs(dat,std::ios::app);
  if(!ofs){
    std::cerr<<"ファイルオープン失敗\n";
  }
  ofs<<missing<<"\t"<<current()<<"\t"<<SEED2
     <<"\t"<<Ccurrent()<<"\n";
  for(int m=0;m<missing;m++){
    ofs<<KessonIndex[m][0]<<"\t"
       <<KessonIndex[m][1] <<"\t"
       <<SparseCorrectData[KessonIndex[m][0]]
      .elementIndex(SparseIndex[m])<<"\t"
       <<Prediction[m]<<std::endl;
  }
  return;
}

double Recom::MAE(int missing, std::string text){
  double result=0.0,mae;
  for(int m=0;m<missing;m++){
    result+=fabs(SparseCorrectData[KessonIndex[m][0]]
		 .elementIndex(SparseIndex[m])
		 -Prediction[m]);
  }
  mae=result/missing;
  std::ofstream ofs(text,std::ios::app);
  ofs<<missing<<"\t"
     <<SEED2<<"\t"
     <<current()<<"\t"
     <<Ccurrent()<<"\t"
     <<std::fixed<<std::setprecision(10)
     <<mae<<std::endl;
  ofs.close();
  return mae;
}

double Recom::F_measure(int missing, int index,
			std::string text){
  double TP=0.0,FP=0.0,FN=0.0,TN=0.0,fmeasure=0.0;
  //閾値の設定
  double siki=index/10.0;
  for(int m=0;m<missing;m++){
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
    fmeasure=(2.0*Recall*Precision)/(Recall+Precision);
    if(std::isnan(fmeasure))
      fmeasure=0.0;
    std::ofstream ofs(text ,std::ios::app);
    ofs<<missing<<"\t"
       <<SEED2<<"\t"
       <<current()<<"\t"
       <<Ccurrent()<<"\t"
       <<TP<<" "
       <<FP<<" "
       <<FN<<" "
       <<TN<<" "
       <<std::fixed<<std::setprecision(10)<<fmeasure<<std::endl;
    ofs.close();
  }
  /*~2017/12/25
  //0で割る場合，無理やり回避
  if((TP+FN)==0||(FP+TN)==0){
  TP_FN[index]=0.0;
  FP_TN[index]=0.0;
  }
  */
  if(TP+TN==missing){
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
  return fmeasure;
}

void Recom::ROC(std::string dat){
  //ROCでプロットする点の数
  int max_index=(int)return_max_value()*10;
  //一旦保存
  Vector False=FP_TN;
  Vector True=TP_FN;
  std::ofstream ofs(dat,std::ios::app);
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

void Recom::revise_prediction(int missing){
  for(int index=0;index<missing;index++){
    double RecomUser=0.0,RecomItem=0.0;
    double RecomUSER=0.0,RecomITEM=0.0,RecomUserItem=0.0;
    double numerator=0.0,denominator=0.0;
    double numerator1=0.0,denominator1=0.0;
    double numerator2=0.0,denominator2=0.0;
    double numerator3=0.0,denominator3=0.0;
    int user_miss_index=KessonIndex[index][1];
    int user_miss_size=SparseIncompleteData[KessonIndex[index][0]]
      .essencialSize();
    /******RecomUser********/
    for(int ell=0;ell<user_miss_size;ell++){
      double user_miss_element
	=SparseIncompleteData[KessonIndex[index][0]]
	.elementIndex(ell);
      if(user_miss_element>0){
	numerator+=user_miss_element;
	denominator++;
      }
    }
    if(denominator>0)
      RecomUser=numerator/denominator;
    numerator=0.0;denominator=0.0;
    int index1=0,index2=0;
    for(int i=0;i<Mem.rows();i++){
      if(Mem[i][KessonIndex[index][0]])
	index1=i;
    }
    for(int i=0;i<ItemMem.rows();i++){
      if(ItemMem[i][KessonIndex[index][1]])
	index2=i;
    }
    for(int k=0;k<return_user_number();k++){      
      int user_size=
	SparseIncompleteData[k].essencialSize();
      /******RecomItem********/
      for(int ell=0;ell<user_size;ell++){
	int user_index=SparseIncompleteData[k].indexIndex(ell);
	if(user_index>user_miss_index)
	  break;
	int user_element=SparseIncompleteData[k].elementIndex(ell);
	if((user_element>0)&&(user_index==user_miss_index)){
	  numerator1+=user_element;
	  denominator1++;
	  break;
	}
      }      
      /******RecomUSER********/
      if(Mem[index1][k]){
	for(int ell=0;ell<user_size;ell++){
	  int user_element=SparseIncompleteData[k].elementIndex(ell);
	  if(user_element>0){
	    numerator2+=user_element;
	    denominator2++;
	  }
	}
      }
      /******RecomITEM********/
      for(int ell=0;ell<user_size;ell++){	
	int user_index=SparseIncompleteData[k].indexIndex(ell);	
	if(ItemMem[index2][user_index]){
	  int user_element=SparseIncompleteData[k].elementIndex(ell);
	  if(user_element>0){
	    numerator3+=user_element;
	    denominator3++;
	  }
	}
      }
      /******RecomUserItem********/
      if(Mem[index1][k]){
	for(int ell=0;ell<user_size;ell++){
	  int user_index=SparseIncompleteData[k].indexIndex(ell);
	  if(ItemMem[index2][user_index]){
	    int user_element=SparseIncompleteData[k]
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
	  int user1_element
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
	      int user2_element
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
	  int user1_element
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
	      int user2_element
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
void Recom::pearsonsim_for_pcm(const Matrix Membership_PCM,
			       const Vector Threshold){
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
	  int user1_element
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
	      int user2_element
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

void Recom::pearsonpred1(int missing){
  for(int index=0;index<missing;index++){
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
	  int user_element
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

void Recom::pearsonpred2(int missing){
  for(int index=0;index<missing;index++){
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
	  int user_element
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
    for(int i=0;i<Membership.rows();i++){
      Mem[i][k]=0.0;
    }
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
    for(int j=0;j<ItemMembership.rows();j++){
      ItemMem[j][ell]=0.0;
    }
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

void Recom::roc_area(std::string text1, std::string text2,
		     double mae, double f, int miss){
  int max=return_max_value()*10;
  double rocarea=0.0;
  for(int x=0;x<MISSINGTRIALS;x++){
    Vector array1(max,0.0,"all"),array2(max,0.0,"all");
    std::ifstream ifs(text1+std::to_string(miss)
		      +"_"+std::to_string(x)+"sort.txt");
    if(!ifs){
      std::cerr<<"ファイルinput失敗:trials:"
	       <<x<<"miss:"<<miss<<std::endl;
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
  std::ofstream ofs(text2,std::ios::app);
  if(!ofs)
    std::cerr<<"ファイルopen失敗\n";
  std::cout<<"miss:"<<miss<<"\tMAE="<<mae/MISSINGTRIALS
	   <<"\tF-measure="<<f/MISSINGTRIALS<<"\tROC="
	   <<rocarea/MISSINGTRIALS<<std::endl;
  ofs<<miss<<"\t"<<std::fixed<<std::setprecision(10)<<
    "\t"<<mae/MISSINGTRIALS<<"\t"<<f/MISSINGTRIALS<<"\t"<<
    rocarea/MISSINGTRIALS<<std::endl;
  return;
}

void Recom::mae_f_out(std::string file, double summae, double sumf, int miss){
  std::ofstream ofs(file,std::ios::app);
  if(!ofs)
    std::cerr<<"ファイルopen失敗\n";
  ofs<<miss<<"\t"<<std::fixed<<std::setprecision(10)<<
    "\t"<<summae/MISSINGTRIALS<<"\t"<<sumf/MISSINGTRIALS<<"\t"<<std::endl;
  return;
}

void Recom::ofs_seed(int missing, std::string text){
  std::ofstream ofs(text,std::ios::app);
  if(!ofs){
    std::cerr<<"ファイルオープン失敗\n";
    exit(1);
  }
  ofs<<missing<<"\t"<<SEED2<<"\t"<<SEED<<"\t";
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
