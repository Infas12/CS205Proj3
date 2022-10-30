#ifndef MATRIX_H
#define MATRIX_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_SIZE 1024
#define ILLEGAL_SIZE 10

#define MAT_MIN -3.4E+38
#define MAT_MAX  3.4E+38


#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// row major
// the [i,j]th element is data[i*column+j]
typedef struct
{
    int row; 
    int column;
    float data[MAX_SIZE];
} Matrix;

typedef enum
{
    MAT_SUCCESS = 0,
    MAT_ILLEGAL_SIZE_ERROR = 1,
    MAT_NULLPTR_ERROR = 2,
    MAT_SIZE_MISMATCH_ERROR = 3,
} calc_status;

void error_handler(calc_status status);

Matrix* create_empty_matrix(int row, int column);

Matrix* create_matrix(int row, int column, float* data);

calc_status copy_matrix(Matrix* dest, Matrix* src);

calc_status delete_matrix(Matrix** p_mat);

calc_status add_matrix(Matrix* left_op, Matrix* right_op, Matrix* result);

calc_status substract_matrix(Matrix* left_op, Matrix* right_op, Matrix* result);

calc_status multiply_matrix(Matrix* left_op, Matrix* right_op, Matrix* result);

calc_status add_scalar_to_matrix(Matrix* p_mat, int scalar);

calc_status substract_scalar_from_matrix(Matrix* p_mat, int scalar);

calc_status multiply_scalar(Matrix* p_mat, int scalar);

calc_status print_matrix(Matrix* p_mat);

calc_status max_element(Matrix* p_mat, float* result);

calc_status min_element(Matrix* p_mat, float* result);

#ifdef __cplusplus
}
#endif

#endif

