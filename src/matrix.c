#include "matrix.h"

#ifdef __cplusplus
extern "C" {
#endif

void __attribute__((weak)) error_handler(calc_status status)
{   
    switch(status){
        case MAT_ILLEGAL_SIZE_ERROR:
            printf("creating a matrix with illegal size\n");
            break;
        case MAT_NULLPTR_ERROR:
            printf("operand is null\n");
            break;            
        case MAT_SIZE_MISMATCH_ERROR:
            printf("Operand size mismatch\n");
            break;      
    }
}

Matrix* create_empty_matrix(int row, int column)
{
    /* Check if the size is legal. */
    if( row < 0 || column < 0 || row * column > MAX_SIZE){
        error_handler(MAT_ILLEGAL_SIZE_ERROR);
        return NULL;
    }

    /* Create Matrix */
    Matrix* p_Mat = (Matrix*) malloc (sizeof(Matrix));

    if(p_Mat != NULL){ //if malloc is successful
        p_Mat->row = row;
        p_Mat->column = column;
        for(int i = 0; i < MAX_SIZE; i++){
            p_Mat->data[i] = 0.0;
        }
    }

    return p_Mat;
}

Matrix* create_matrix(int row, int column, float* data)
{
    Matrix* p_Mat = create_empty_matrix(row,column);
    memcpy(p_Mat->data,data,row*column*sizeof(float));
    return p_Mat;
}

calc_status copy_matrix(Matrix* dest, Matrix* src)
{
    if(dest == NULL || src == NULL){
        return MAT_NULLPTR_ERROR;
    }
    memcpy(dest,src,sizeof(Matrix));    
    return MAT_SUCCESS;
}

calc_status delete_matrix(Matrix** pp_mat)
{

    if(*pp_mat == NULL){
        return MAT_NULLPTR_ERROR;
    }
    free(*pp_mat);
    *pp_mat = NULL;
    return MAT_SUCCESS;
}

calc_status add_matrix(Matrix* left_op,Matrix* right_op, Matrix* result)
{

    if(left_op == NULL || right_op == NULL || result == NULL){
        return MAT_NULLPTR_ERROR;
    }

    if(left_op -> row != right_op->row || left_op -> column != right_op -> column){
        return MAT_SIZE_MISMATCH_ERROR;
    }

    result -> row = left_op -> row;
    result -> column = left_op -> column;
    for(int i = 0; i < MAX_SIZE; i++){
        result -> data[i] = left_op -> data[i] + right_op -> data[i];
    }
    return MAT_SUCCESS;

}

calc_status substract_matrix(Matrix* left_op, Matrix* right_op, Matrix* result)
{
    if(left_op == NULL || right_op == NULL || result == NULL){
        return MAT_NULLPTR_ERROR;
    }

    if(left_op -> row != right_op->row || left_op -> column != right_op -> column){
        return MAT_SIZE_MISMATCH_ERROR;
    }

    result -> row = left_op -> row;
    result -> column = left_op -> column;
    for(int i = 0; i < MAX_SIZE; i++){
        result -> data[i] = left_op -> data[i] - right_op -> data[i];
    }

    return MAT_SUCCESS;

}

calc_status multiply_matrix(Matrix* left_op, Matrix* right_op, Matrix* result)
{
    if(left_op == NULL || right_op == NULL || result == NULL){
        return MAT_NULLPTR_ERROR;
    }

    if(left_op -> column != right_op->row){
        return MAT_SIZE_MISMATCH_ERROR;
    }

    if(left_op -> row * right_op -> column > MAX_SIZE){
        return MAT_ILLEGAL_SIZE_ERROR;
    }


    int result_row = left_op->row;
    int result_col = right_op->column;

    result->row = result_row;
    result->column = result_col;
    

    for(int i = 0; i < result_row; i++){    
        for(int j = 0; j < result_col; j++){
            result->data[i*result_col+j] = 0.0;
            for(int k=0;k<left_op->column;k++){    
                result->data[i*result_col+j] += 
                    left_op->data[i*left_op->column+k] * right_op->data[k*right_op->column+j];
            }    
        }    
    }        

    return MAT_SUCCESS;
}

calc_status max_element(Matrix* p_mat, float* result)
{
    if(p_mat == NULL){
        return MAT_NULLPTR_ERROR;
    }

    int size = p_mat->column * p_mat->row;
    float max = MAT_MIN;
    for(int i = 0; i < size; i++){
        if(p_mat->data[i] > max) max = p_mat->data[i];
    }

    *result = max;
    return MAT_SUCCESS;
}

calc_status min_element(Matrix* p_mat, float* result)
{
    if(p_mat == NULL){
        return MAT_NULLPTR_ERROR;
    }

    int size = p_mat->column * p_mat->row;
    float min = MAT_MAX;
    for(int i = 0; i < size; i++){
        if(p_mat->data[i] < min) min = p_mat->data[i];
    }
    *result = min;
    return MAT_SUCCESS;
}

calc_status add_scalar_to_matrix(Matrix* p_mat, int scalar)
{
    if(p_mat == NULL){
        return MAT_NULLPTR_ERROR;
    }    

    int size = p_mat->column * p_mat->row;
    for(int i = 0; i < size; i++){
        p_mat->data[i] += scalar;
    }   
    return MAT_SUCCESS;
}

calc_status minus_scalar_from_matrix(Matrix* p_mat, int scalar)
{
    if(p_mat == NULL){
        return MAT_NULLPTR_ERROR;
    }    

    int size = p_mat->column * p_mat->row;
    for(int i = 0; i < size; i++){
        p_mat->data[i] -= scalar;
    }   

    return MAT_SUCCESS;
}

calc_status multiply_scalar(Matrix* p_mat, int scalar)
{
    if(p_mat == NULL){
        return MAT_NULLPTR_ERROR;
    }    

    int size = p_mat->column * p_mat->row;
    for(int i = 0; i < size; i++){
        p_mat->data[i] *= scalar;
    }   

    return MAT_SUCCESS;
}

calc_status print_matrix(Matrix* p_mat)
{
    if(p_mat == NULL){
        return MAT_NULLPTR_ERROR;
    }

    for(int i = 0; i < p_mat->row; i++){
        for(int j = 0; j < p_mat->column; j++){
            printf("%3f ",p_mat->data[i*p_mat->column+j]);
        }
        printf("\n");
    }

    return MAT_SUCCESS;
}

#ifdef __cplusplus
}
#endif