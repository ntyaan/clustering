#include"hcm.h"

#ifndef __OCS__
#define __OCS__

class OCS: virtual public HCM{
protected:
  SparseMatrix IncompleteData;
  SparseMatrix CorrectData;
  Matrix IncompleteIndex;
  int NumberOfMissingValues;
public:
  OCS(int dimension,
      int data_number,
      int centers_number,
      int number_of_missing_values);
  double incompleteindex(int index1, int index2);
  SparseMatrix correctdata(void);
  SparseVector correctdata(int index);
  void IncompleIndexForRecom(const Matrix &Index);
  Vector PredictionForRecom(const Matrix &IndexRow,
			    const Vector &IndexCol);
  Vector PredictionForRecomForSpherical(const Matrix &IndexRow,
					const Vector &IndexCol,
					const SparseMatrix &SD);
  virtual void revise_data(void);
  void set_missing_values(int seed_of_random_number,
			  int missing_at_a_time);
};

#endif
