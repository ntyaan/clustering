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
objects = .o/vector.o .o/svector.o .o/matrix.o .o/smatrix.o
klfcs = $(objects) .o/hcm.o .o/hcma.o .o/hcs.o .o/klfcm.o .o/klfcs.o
bfcs = $(objects) .o/hcm.o .o/hcma.o .o/hcs.o .o/bfcm.o .o/bfcs.o
qfcs = $(objects) .o/hcm.o .o/hcma.o .o/hcs.o \
.o/klfcm.o .o/bfcm.o .o/qfcm.o .o/qfcs.o
klfccm = $(objects) .o/hcm.o .o/hcma.o .o/hccm.o .o/klfcm.o .o/klfccm.o
bfccm = $(objects) .o/hcm.o .o/hcma.o .o/hccm.o .o/bfcm.o .o/bfccm.o
qfccm = $(objects) .o/hcm.o .o/hcma.o .o/hccm.o \
.o/klfcm.o .o/bfcm.o .o/qfcm.o .o/qfccm.o
klfccmm = $(klfccm) .o/hccmm.o .o/klfccmm.o
bfccmm = $(bfccm) .o/hccmm.o .o/bfccmm.o
qfccmm = $(qfccm) .o/hccmm.o .o/qfccmm.o
epcs = $(klfcs) .o/pcm.o .o/epcs.o

method_all = $(all) \
$(klfcs) $(bfcs) $(qfcs) \
$(klfccm) $(bfccm) $(qfccm) \
$(klfccmm) $(bfccmm) $(qfccmm) \
$(epcs) \
artificiality_grouplens.out \
artificiality_klfcs.out \
artificiality_bfcs.out \
artificiality_qfcs.out \
artificiality_klfccm.out \
artificiality_bfccm.out \
artificiality_qfccm.out \
artificiality_klfccmm.out \
artificiality_qfccmm.out \
artificiality_epcs.out \
grouplens.out \
klfcs.out \
bfcs.out \
qfcs.out \
klfccm.out \
bfccm.out \
qfccm.out \
klfccmm.out \
bfccmm.out \
qfccmm.out \
epcs.out \
clustering_artificiality_klfcs.out \
clustering_artificiality_bfcs.out \
clustering_artificiality_qfcs.out \
clustering_artificiality_klfccm.out \
clustering_artificiality_bfccm.out \
clustering_artificiality_qfccm.out \
clustering_artificiality_klfccmm.out \
clustering_artificiality_bfccmm.out \
clustering_artificiality_qfccmm.out \
clustering_artificiality_epcs.out \
clustering_klfcs.out \
clustering_bfcs.out \
clustering_qfcs.out \
clustering_klfccm.out \
clustering_bfccm.out \
clustering_qfccm.out \
clustering_klfccmm.out \
clustering_bfccmm.out \
clustering_qfccmm.out \

ifdef data
	DATASET=-D$(data) 
endif
ifdef class
	MACRO=-DCHECK_CLASS 
endif

all : $(objects) 

method_all : $(method_all)

.o/vector.o : src/vector.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/svector.o : src/sparseVector.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/matrix.o : src/matrix.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/smatrix.o : src/sparseMatrix.cxx 
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/3dvector.o : src/vector3d.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/hcm.o : src/hcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/hcma.o : src/hcma.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/hcs.o : src/hcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/hccm.o : src/hccm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/hccmm.o : src/hccmm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/pcm.o : src/pcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/klfcm.o : src/klfcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/klfcs.o : src/klfcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/bfcm.o : src/bfcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/bfcs.o : src/bfcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/qfcm.o : src/qfcm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/qfcs.o : src/qfcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/klfccm.o : src/klfccm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/bfccm.o : src/bfccm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/qfccm.o : src/qfccm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/klfccmm.o : src/klfccmm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/bfccmm.o : src/bfccmm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/qfccmm.o : src/qfccmm.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@
.o/epcs.o : src/epcs.cxx
	$(CXX) $(CXXFLAGS) $(MACRO)-c $^ -o $@

#推薦システム人工データ
artificiality_grouplens.out : $(objects) src/recom.cxx \
main_recom/artificiality/grouplens.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_klfcs.out : $(klfcs) src/recom.cxx \
main_recom/artificiality/klfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_bfcs.out : $(bfcs) src/recom.cxx \
main_recom/artificiality/bfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_qfcs.out : $(qfcs) src/recom.cxx \
main_recom/artificiality/qfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_klfccm.out : $(klfccm) src/recom.cxx \
main_recom/artificiality/klfccm.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_bfccm.out : $(bfccm) src/recom.cxx \
main_recom/artificiality/bfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_qfccm.out : $(qfccm) src/recom.cxx \
main_recom/artificiality/qfccm.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_klfccmm.out : $(klfccmm) src/recom.cxx \
main_recom/artificiality/klfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_bfccmm.out : $(bfccmm) src/recom.cxx \
main_recom/artificiality/bfccmm.cxx
	$(CXX) $(CXXFLAGS)  $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_qfccmm.out : $(qfccmm) src/recom.cxx \
main_recom/artificiality/qfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@
artificiality_epcs.out : $(epcs) src/recom.cxx \
main_recom/artificiality/epcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	-DARTIFICIALITY $(FS) -o $@

#推薦システム実データ
grouplens.out : $(objects) src/recom.cxx main_recom/grouplens.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET) $(FS) -o $@
bfcs.out : $(bfcs) src/recom.cxx main_recom/bfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
klfcs.out : $(klfcs) src/recom.cxx main_recom/klfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
qfcs.out : $(qfcs) src/recom.cxx main_recom/qfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
bfccm.out : $(bfccm) src/recom.cxx main_recom/bfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
klfccm.out : $(klfccm) src/recom.cxx main_recom/klfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
qfccm.out : $(qfccm) src/recom.cxx main_recom/qfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
klfccmm.out : $(klfccmm) src/recom.cxx main_recom/klfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
bfccmm.out : $(bfccmm) src/recom.cxx main_recom/bfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
qfccmm.out : $(qfccmm) src/recom.cxx main_recom/qfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@
epcs.out : $(epcs) src/recom.cxx main_recom/epcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(DATASET)$(MACRO)$(FS) -o $@


#クラスタリング人工データ
clustering_artificiality_klfcs.out : $(klfcs) \
main_clustering/artificiality/klfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(FS) -o $@
clustering_artificiality_bfcs.out : $(bfcs) \
main_clustering/artificiality/bfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(FS) -o $@
clustering_artificiality_qfcs.out : $(qfcs) \
main_clustering/artificiality/qfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(FS) -o $@
clustering_artificiality_klfccm.out : $(klfccm) \
main_clustering/artificiality/klfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_bfccm.out : $(bfccm) \
main_clustering/artificiality/bfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_qfccm.out : $(qfccm) \
main_clustering/artificiality/qfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_klfccmm.out : $(klfccmm) \
main_clustering/artificiality/klfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_bfccmm.out : $(bfccmm) \
main_clustering/artificiality/bfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_qfccmm.out : $(qfccmm) \
main_clustering/artificiality/qfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_artificiality_epcs.out : $(epcs) \
main_clustering/artificiality/epcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@

#クラスタリング実データ
clustering_klfcs.out : $(klfcs) main_clustering/klfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_bfcs.out : $(bfcs) main_clustering/bfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_qfcs.out : $(qfcs) main_clustering/qfcs.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_klfccm.out : $(klfccm) main_clustering/klfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_bfccm.out : $(bfccm) main_clustering/bfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_qfccm.out : $(qfccm) main_clustering/qfccm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_klfccmm.out : $(klfccmm) main_clustering/klfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_bfccmm.out : $(bfccmm) main_clustering/bfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clustering_qfccmm.out : $(qfccmm) main_clustering/qfccmm.cxx
	$(CXX) $(CXXFLAGS) $^ \
	$(MACRO)$(FS) -o $@
clean :
	rm -f *.out
clean.o :
	rm -f .o/*.o
