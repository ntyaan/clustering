# https://github.com/ntyaan/some-datasets
# $ make (vectorクラス等の中間ファイル作成、-Bで強制コンパイル) 
# $ make ターゲット(.out)で実行ファイルコンパイル
# ---推薦システム---
# 実データ一覧 
# 名前		:マクロ名	
# BookCrossing	:BOOK		:1091ユーザ2248アイテム
# MovieLens1M	:MOVIE		:905ユーザ684アイテム
# Jester	:JESTER		:2916ユーザ140アイテム
# Libimseti	:LIBIMSETI	:866ユーザ1156アイテム
# Epinions	:EPINIONS	:1022ユーザ835アイテム
# Sushi		:SUSHI		:5000ユーザ100アイテム
# 実データの場合:
# $ make ターゲット data=マクロ名
# 例(klfcsをBookCrossingに適用する場合):w
# $ make rklfcs.out data=BOOK
# クラスの呼び出し等デバグしたいとき
# $ make ターゲット data=マクロ名 class=1
# 人工データの場合:
# $ make ターゲット
CXX = g++
CXXFLAGS = -O3 -Wall -Wextra -std=c++17
FS = -lstdc++fs
all = vector.o svector.o matrix.o smatrix.o \
hcm.o hcma.o hcs.o hccm.o hccmm.o
method_all = $(all) \
artificiality_firefly.out \
artificiality_grouplens.out \
artificiality_klfcs.out \
artificiality_bfcs.out \
artificiality_qfcs.out \
artificiality_klfccm.out \
artificiality_qfccm.out \
artificiality_klfccmm.out \
artificiality_qfccmm.out \
artificiality_epcs.out \
firefly.out \
grouplens.out \
bfcs.out \
klfcs.out \
qfcs.out \
bfccm.out \
klfccm.out \
qfccm.out \
klfccmm.out \
bfccmm.out \
qfccmm.out \
epcs.out \
clustering_artificiality_klfcs.out \
clustering_artificiality_bfcs.out \
clustering_artificiality_qfcs.out \
clustering_artificiality_epcs.out \
clustering_artificiality_klfccm.out \
clustering_artificiality_bfccm.out \
clustering_artificiality_qfccm.out \
clustering_artificiality_klfccmm.out \
clustering_artificiality_bfccmm.out \
clustering_artificiality_qfccmm.out \
clustering_artificiality_fccm.out \
clustering_artificiality_fccmb.out \
clustering_artificiality_k_bfcm.out \
clustering_artificiality_k_bfcs.out \
clustering_klfccm.out \
clustering_bfccm.out \
clustering_qfccm.out \
clustering_klfccmm.out \
clustering_bfccmm.out \
clustering_qfccmm.out \
clustering_klfccmp.out \
clustering_klfcs.out \
clustering_bfcs.out \
clustering_qfcs.out \
clustering_k_bfcm.out \
clustering_k_bfcs.out \
clustering_ocs_bfcs.out 
objects = vector.o svector.o matrix.o smatrix.o
hcm = $(objects) hcm.o hcma.o
hcs = $(objects) hcm.o hcma.o hcs.o
hccm = $(objects) hcm.o hcma.o hccm.o
hccmm = $(objects) hcm.o hcma.o hccm.o hccmm.o

ifdef data
	DATASET=-D$(data) 
endif
ifdef class
	MACRO=-DCHECK_CLASS 
endif

all : $(all) 

method_all : $(method_all)

vector.o : src/vector.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
svector.o : src/sparseVector.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
matrix.o : src/matrix.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
smatrix.o : src/sparseMatrix.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
3dvector.o : src/vector3d.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
hcm.o : src/hcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
hcma.o : src/hcma.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
hcs.o : src/hcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
hccm.o : src/hccm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
hccmm.o : src/hccmm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@

#推薦システム人工データ
artificiality_firefly.out : main_recom/artificiality/firefly.cxx
	$(CXX) $(CXXFLAGS) $(objects) src/recom.cxx $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_grouplens.out : main_recom/artificiality/grouplens.cxx
	$(CXX) $(CXXFLAGS) $(objects) src/recom.cxx $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_klfcs.out : main_recom/artificiality/klfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/recom.cxx src/klfcm.cxx src/klfcs.cxx $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_bfcs.out : main_recom/artificiality/bfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/recom.cxx src/bfcm.cxx src/bfcs.cxx $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_qfcs.out : main_recom/artificiality/qfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/recom.cxx src/klfcm.cxx src/bfcm.cxx \
	src/qfcm.cxx src/qfcs.cxx $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_klfccm.out : main_recom/artificiality/klfccm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccm) \
	src/recom.cxx src/klfcm.cxx src/klfccm.cxx $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_qfccm.out : main_recom/artificiality/qfccm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccm) \
	src/recom.cxx src/klfcm.cxx src/bfcm.cxx \
	src/qfcm.cxx src/qfccm.cxx $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_klfccmm.out : main_recom/artificiality/klfccmm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccmm) \
	src/recom.cxx src/klfcm.cxx src/klfccmm.cxx $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_qfccmm.out : main_recom/artificiality/qfccmm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccmm) \
	src/recom.cxx src/klfcm.cxx src/bfcm.cxx \
	src/qfcm.cxx src/qfccmm.cxx $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_epcs.out : main_recom/artificiality/epcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/recom.cxx src/klfcm.cxx src/klfcs.cxx \
	src/pcm.cxx src/epcs.cxx $^ \
	-DARTIFICIALITY $(FS) -o $@

#推薦システム実データ
firefly.out : main_recom/firefly.cxx
	$(CXX) $(CXXFLAGS) $(objects) src/recom.cxx $^ \
	$(DATASET) $(FS) -o $@
grouplens.out : main_recom/grouplens.cxx
	$(CXX) $(CXXFLAGS) $(objects) src/recom.cxx $^ \
	$(DATASET) $(FS) -o $@
bfcs.out : main_recom/bfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/recom.cxx src/bfcm.cxx src/bfcs.cxx $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
klfcs.out : main_recom/klfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/recom.cxx src/klfcm.cxx src/klfcs.cxx $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
qfcs.out : main_recom/qfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/recom.cxx src/bfcm.cxx src/klfcm.cxx \
	src/qfcm.cxx src/qfcs.cxx $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
bfccm.out : main_recom/bfccm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccm) \
	src/recom.cxx src/bfcm.cxx src/bfccm.cxx $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
klfccm.out : main_recom/klfccm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccm) \
	src/recom.cxx src/klfcm.cxx src/klfccm.cxx $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
qfccm.out : main_recom/qfccm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccm) \
	src/recom.cxx src/bfcm.cxx src/klfcm.cxx \
	src/qfcm.cxx src/qfccm.cxx $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
klfccmm.out : main_recom/klfccmm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccmm) \
	src/recom.cxx src/klfcm.cxx src/klfccmm.cxx $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
bfccmm.out : main_recom/bfccmm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccmm) \
	src/recom.cxx src/bfcm.cxx src/bfccmm.cxx $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
qfccmm.out : main_recom/qfccmm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccmm) \
	src/recom.cxx src/bfcm.cxx src/klfcm.cxx \
	src/qfcm.cxx src/qfccmm.cxx $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
epcs.out : main_recom/epcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/recom.cxx src/klfcm.cxx src/klfcs.cxx \
	src/pcm.cxx src/epcs.cxx $^ \
	$(DATASET)$(MACRO)$(FS) -o $@


#クラスタリング人工データ
clustering_artificiality_klfcs.out : main_clustering/artificiality/klfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/klfcm.cxx src/klfcs.cxx $^ \
	$(FS) -o $@
clustering_artificiality_bfcs.out : main_clustering/artificiality/bfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/bfcm.cxx src/bfcs.cxx $^ \
	$(FS) -o $@
clustering_artificiality_qfcs.out : main_clustering/artificiality/qfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/klfcm.cxx src/bfcm.cxx \
	src/qfcm.cxx src/qfcs.cxx $^ \
	$(FS) -o $@
clustering_artificiality_epcs.out : main_clustering/artificiality/epcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/klfcm.cxx src/klfcs.cxx \
	src/pcm.cxx src/epcs.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_klfccm.out : main_clustering/artificiality/klfccm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccm) \
	src/klfcm.cxx src/klfccm.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_bfccm.out : main_clustering/artificiality/bfccm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccm) \
	src/bfcm.cxx src/bfccm.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_qfccm.out : main_clustering/artificiality/qfccm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccm) \
	src/klfcm.cxx src/bfcm.cxx src/qfcm.cxx \
	src/qfccm.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_klfccmm.out : main_clustering/artificiality/klfccmm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccmm) \
	src/klfcm.cxx src/klfccmm.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_bfccmm.out : main_clustering/artificiality/bfccmm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccmm) \
	src/bfcm.cxx src/bfccmm.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_qfccmm.out : main_clustering/artificiality/qfccmm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccmm) \
	src/klfcm.cxx src/bfcm.cxx src/qfcm.cxx \
	src/qfccmm.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_fccm.out : main_clustering/artificiality/fccm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcm) \
	src/klfcm.cxx src/fccm.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_fccmb.out : main_clustering/artificiality/fccmb.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcm) \
	src/bfcm.cxx src/fccmb.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_klfccmp.out : main_clustering/artificiality/klfccmp.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccm) src/hccmp.cxx \
	src/klfcm.cxx src/klfccm.cxx src/klfccmp.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_ocs_bfcs.out : main_clustering/artificiality/ocs_bfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/bfcm.cxx src/bfcs.cxx \
	src/ocs.cxx src/ocs_bfcs.cxx $^ \
	$(FS) -o $@
clustering_artificiality_k_bfcm.out : main_clustering/artificiality/k_bfcm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcm) src/bfcm.cxx \
	src/kernel.cxx src/k_bfcm.cxx $^ \
	$(FS) -o $@
clustering_artificiality_k_bfcs.out : main_clustering/artificiality/k_bfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/bfcm.cxx src/bfcs.cxx \
	src/kernel.cxx src/k_bfcs.cxx $^ \
	$(FS) -o $@
#クラスタリング実データ
clustering_klfccm.out : main_clustering/klfccm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccm) \
	src/klfcm.cxx src/klfccm.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_bfccm.out : main_clustering/bfccm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccm) \
	src/bfcm.cxx src/bfccm.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_qfccm.out : main_clustering/qfccm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccm) \
	src/klfcm.cxx src/bfcm.cxx src/qfcm.cxx \
	src/qfccm.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_klfccmm.out : main_clustering/klfccmm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccmm) \
	src/klfcm.cxx src/klfccmm.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_bfccmm.out : main_clustering/bfccmm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccmm) \
	src/bfcm.cxx src/bfccmm.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_qfccmm.out : main_clustering/qfccmm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccmm) \
	src/klfcm.cxx src/bfcm.cxx src/qfcm.cxx \
	src/qfccmm.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_klfccmp.out : main_clustering/klfccmp.cxx
	$(CXX) $(CXXFLAGS) \
	$(hccm) src/hccmp.cxx \
	src/klfcm.cxx src/klfccm.cxx src/klfccmp.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_klfcs.out : main_clustering/klfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/klfcm.cxx src/klfcs.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_bfcs.out : main_clustering/bfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/bfcm.cxx src/bfcs.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_qfcs.out : main_clustering/qfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/klfcm.cxx src/bfcm.cxx src/qfcm.cxx \
	src/qfcs.cxx $^ \
	$(MACRO)$(FS) -o $@
clustering_k_bfcm.out : main_clustering/k_bfcm.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcm) \
	src/bfcm.cxx \
	src/kernel.cxx src/k_bfcm.cxx $^ \
	$(FS) -o $@
clustering_k_bfcs.out : main_clustering/k_bfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/bfcm.cxx src/bfcs.cxx \
	src/kernel.cxx src/k_bfcs.cxx $^ \
	$(FS) -o $@
clustering_ocs_bfcs.out : main_clustering/ocs_bfcs.cxx
	$(CXX) $(CXXFLAGS) \
	$(hcs) \
	src/bfcm.cxx src/bfcs.cxx \
	src/ocs.cxx src/ocs_bfcs.cxx $^ \
	$(FS) -o $@
clean :
	rm -f *.out
clean.o :
	rm -f *.o
