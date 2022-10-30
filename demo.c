#include "matrix.h"

int main(){


    //construction
    float data[3] = {1.0,2.0,1.0};
    Matrix* example_vector = create_matrix(1,3,data);

    float identity[9] = {1.0,0.0,0.0,
                         0.0,1.0,0.0,
                         0.0,0.0,1.0};
    Matrix* example_mat = create_matrix(3,3,identity);

    //Basic Calculation

    printf("----Test1: multiplication----\n");
    Matrix* example_output = create_empty_matrix(1,1);
    calc_status status = multiply_matrix(example_vector,example_mat,example_output);
    if(status == MAT_SUCCESS){
        print_matrix(example_output);
    }else{
        error_handler(status);
    }

    //Basic Calculation
    printf("----Test2: Addition----\n");
    status = add_matrix(example_mat,example_mat,example_output);
    if(status == MAT_SUCCESS){
        print_matrix(example_output);
    }else{
        error_handler(status);
    }

    //try with error
    printf("----Test3: ErrorHandling----\n");
    status = add_matrix(example_vector,example_mat,example_output);
    if(status == MAT_SUCCESS){
        print_matrix(example_output);
    }else{
        error_handler(status);
    }

    //Other simple utilities
    printf("----Test4: Adding scalar----\n");
    status = add_scalar_to_matrix(example_mat,1);
    if(status == MAT_SUCCESS){
        print_matrix(example_mat);
    }else{
        error_handler(status);
    }

    printf("----Test5: Multiplying scalar----\n");
    status = multiply_scalar(example_mat,-1);
    if(status == MAT_SUCCESS){
        print_matrix(example_mat);
    }else{
        error_handler(status);
    }

    printf("----Test6: Finding Max----\n");
    float max_element_in_mat;
    status = max_element(example_mat, &max_element_in_mat);
    if(status == MAT_SUCCESS){
        printf("the maximum element is : %f. \n", max_element_in_mat);
    }else{
        error_handler(status);
    }
    
    printf("----Test8: Free----\n");
    status = delete_matrix(&example_output);
    if(status == MAT_SUCCESS){
        if(example_output==NULL){
            printf("Mat is successfully freed.\n");
        }
    }else{
        error_handler(status);
    }    

    printf("----Test9: Null checking----\n");
    status = max_element(example_output, &max_element_in_mat);
    if(status == MAT_SUCCESS){
        printf("the maximum element is : %f. \n", max_element_in_mat);
    }else{
        error_handler(status);
    }


    return 0;
}
