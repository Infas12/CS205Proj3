#include "matrix.h"
#include <iostream>

//Simple wrapper for the matrix
class SimpleMat{
    
    private:
        Matrix* pImpl;
        int m_row;
        int m_column;
    
    public:
        
        SimpleMat(int row, int column) : m_row(row),m_column(column)
        {
            pImpl = create_empty_matrix(row,column);
        }

        SimpleMat(int row, int column, float* data) : m_row(row),m_column(column)
        {
            pImpl = create_matrix(row,column,data);
        }

        friend SimpleMat operator * (const SimpleMat& leftop, const SimpleMat& rightop);
        
        friend std::ostream& operator << (std::ostream& os, const SimpleMat& mat);

        ~SimpleMat()
        {
            delete_matrix(&pImpl);
        }

};


SimpleMat operator * (const SimpleMat& leftop, const SimpleMat& rightop){
    Matrix* result = new Matrix;
    calc_status status = multiply_matrix(leftop.pImpl,rightop.pImpl,result);
    if(status != MAT_SUCCESS){
        throw std::exception();
    }
    SimpleMat mat(result->row,result->column,result->data);
    delete result;
    return mat;
};

std::ostream& operator << (std::ostream& os, const SimpleMat& mat){
    float* data = mat.pImpl->data;
    for(int i = 0; i < mat.m_row; i++){
        for(int j = 0; j < mat.m_column; j++){
            os << data[i*mat.m_column+j] << " ";
        }
        os << std::endl;
    }
    return os;
}

int main(){

    float data[3] = {1.0,
                     2.0,
                     1.0};

    SimpleMat Mat1(3,1,data);

    float identity[9] = {1.0,0.0,0.0,
                         0.0,1.0,0.0,
                         0.0,0.0,1.0};

    SimpleMat Mat2(3,3,identity);
    
    try{
        std::cout << Mat2*Mat2*Mat1 << std::endl;
        std::cout << Mat1*Mat1 << std::endl;
    }catch(std::exception e){
        std::cout << "error happened during calculation" << std::endl;
    }
    
    return 0;
}