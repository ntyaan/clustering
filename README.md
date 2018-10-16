# 更新履歴

## 2018/10/16
推薦人工データ初期帰属度の与え方関数initialize_membership2をhcm.cxxに追加

```  
for(int k=0;k<data_number();k++){
  for(int i=0;i<centers_number();i++){
    if(k%centers_number()==i)
	  Membership[i][k]=1.0-(centers_number()-1.0)/100.0;
    else
	  Membership[i][k]=1.0/100.0;
  }
}

```
5クラスタと設定した場合

| class\data | 1 | 2 | 3 | 4 | 5| 6 | ...| 100 |
|-|-|-|-|-|
|1|0.96|0.01|0.01|0.01|0.01|0.96|...|0.01|
|2|0.01|0.96|0.01|0.01|0.01|0.01|...|0.01|
|3|0.01|0.01|0.96|0.01|0.01|0.01|...|0.01|
|4|0.01|0.01|0.01|0.96|0.01|0.01|...|0.01|
|5|0.01|0.01|0.01|0.01|0.96|0.01|...|0.96|


## 2018/10/10
関係性データのためのクラスタリング手法brfcm,erfcm,qrfcmを追加

[https://www.fujipress.jp/jaciii/jc/jacii002200010034/](https://www.fujipress.jp/jaciii/jc/jacii002200010034/)

## 2018/08/24

クラスタリング手法比較のためのmain追加

初期値をk-means++ライクな方法で決定する．(データから選んだデータ点をクラスタ中心とする，クラスタサイズ調整変数は1.0/クラスタ数)

10通りクラスタ中心を与え，その平均ARIが高かったパラメータ{lambda,m,t}を採用，
目的関数最小のARI，標準偏差も出力する．

## 2018/08/17

Makefileを変更
各手法のターゲットを複数にし，いちいちmake allしないで良いように書き換えた．

ターゲットのソースコード書き換え無しで再コンパイルする場合，-Bをつけるのではなく`make clean`　後に `make ターゲット` でコンパイルする．

.oディレクトリに中間ファイルを出力．

## 2018/08/13~16
推薦main関数大幅変更：

実データにおいて欠損数を変えてループしていたのを良いように欠損数を固定にする．

欠損のさせ方のSeed値が若干ずれたので注意．実データ欠損数を20480(bookcrossing:10240)を20000(bookcrossing:10000)に変更．

ファイル出力の処理(ファイル名など)を変更．

## 2018/08/03
クラスタリング手法名を[FCM.pdf](https://github.com/ntyaan/clustering/blob/master/pdf/FCM.pdf)の名称に変更 

## 2018/08/02
クラスタリング実データmain
([bfcs.cxx](https://github.com/ntyaan/clustering/blob/master/main_clustering/bfcs.cxx)， [klfcs.cxx](https://github.com/ntyaan/clustering/blob/master/main_clustering/klfcs.cxx)，[qfcs.cxx](https://github.com/ntyaan/clustering/blob/master/main_clustering/qfcs.cxx) 作成)

## 2018/08/01
クラスタリング実データmain
([bfccmm.cxx](https://github.com/ntyaan/clustering/blob/master/main_clustering/bfccmm.cxx)，[bfccmd.cxx](https://github.com/ntyaan/clustering/blob/master/main_clustering/bfccmd.cxx) 作成)

## 2018/07/23
plsa.cxx plsa.h 作りかけ

## 2018/07/17
混合多項分布bezdek-typeファジィクラスタリング log関数定義ver 
([bfccmd.cxx](https://github.com/ntyaan/clustering/blob/master/src/bfccmd.cxx) 作成)

カーネル球面bezdek-typeファジィクラスタリング 
([k_bfcs.cxx](https://github.com/ntyaan/clustering/blob/master/src/k_bfcs.cxx) 作成)

## 2018/07/14
欠損データのためのbezdez-typeファジィクラスタリング Optimal Completion Strategy Optimal Completion Strategy
([ocs.cxx](https://github.com/ntyaan/clustering/blob/master/src/ocs.cxx), [ocs_bfcs.cxx](https://github.com/ntyaan/clustering/blob/master/src/ocs_bfcs.cxx) 作成)

推薦実データmain
([ocs_bfcs.cxx](https://github.com/ntyaan/clustering/blob/master/main_recom/a_ocs_bfcs.cxx) 作りかけ)

クラスタリング実データmain
([klfccmm.cxx](https://github.com/ntyaan/clustering/blob/master/main_clustering/klfccmm.cxx)，[klfccmd.cxx](https://github.com/ntyaan/clustering/blob/master/main_clustering/klfccmd.cxx)，[qfccmm.cxx](https://github.com/ntyaan/clustering/blob/master/main_clustering/qfccmm.cxx)，[qfccmd.cxx](https://github.com/ntyaan/clustering/blob/master/main_clustering/qfccmd.cxx) 作成)

カーネルbfcm
([k_bfcm.cxx](https://github.com/ntyaan/clustering/blob/master/src/k_bfcm.cxx) 作りかけ)

## 2018/07/13
推薦
([recom.cxx](https://github.com/ntyaan/clustering/blob/master/src/recom.cxx) 関数roc_areaの引数部分変更)
これに伴いrecom.h，各推薦実データmain変更

推薦実データ エントロピー正則化可能性球面クラスタリング
([epcs.cxx](https://github.com/ntyaan/clustering/blob/master/src/epcs.cxx) 作成)

可能性クラスタリング
([pcm.cxx](https://github.com/ntyaan/clustering/blob/master/src/pcm.cxx) 初期クラスタ中心の設定更新)

## 2018/07/12 
推薦
([recom.cxx](https://github.com/ntyaan/clustering/blob/master/src/recom.cxx) ピアソン相関係数の計算更新)
これに伴いrecom.h，各推薦実データmain変更

# 推薦システム

データセット一覧: [https://github.com/ntyaan/some-datasets](https://github.com/ntyaan/some-datasets)

クラスタリング手法: [https://github.com/ntyaan/clustering/pdf/FCM.pdf](https://github.com/ntyaan/clustering/blob/master/pdf/FCM.pdf)

```
$ make (vectorクラス等の中間ファイル作成、-Bで強制コンパイル) 
$ make ターゲット(.out)で実行ファイルコンパイル
```

## 実データ一覧 

| 名前 | マクロ名 | ユーザ数 | アイテム数 |
|--------|--------|--------|--------|
| BookCrossing | BOOK | 1091 | 2248 |
|MovieLens1M | MOVIE | 905 | 684 |
|Jester	| JESTER | 2916 | 140 |
| Libimseti | LIBIMSETI	| 866 | 1156 |
| Epinions | EPINIONS | 1022 | 835 |
| Sushi	| SUSHI	| 5000 | 100 |

##### git memo

```
$ sudo apt install git
$ git config --global user.name [user]
$ git config --global user.email [email]
$ mkdir git
$ cd git
$ git init
$ git add [file]
$ git commit -m [comment]
$ git remote add origin https://github.com/ntyaan/clustering.git
$ git push -u origin [branch name]

$ git clone https://github.com/ntyaan/clustering

$ git branch [name] master
$ git checkout [name]

$ git fetch
$ git merge origin/master
```
