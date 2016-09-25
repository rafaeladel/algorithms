#include <iostream>

int* multiply(int*, int*, int, int, int, int);

int main()
{
    const int m1_rows = 2, m1_cols = 3, 
                m2_rows = 3, m2_cols = 1;
    int m1[m1_rows][m1_cols] = {{1, 2, 3}, {5, 1, 2}};
    int m2[m2_rows][m2_cols] = {{4}, {5}, {6}};

    int* result = multiply(&m1[0][0], &m2[0][0], m1_rows, m1_cols, m2_rows, m2_cols);

    for(int i = 0; i < m1_rows; i++){
        for(int j = 0 ; j < m2_cols; j++) {
            std::cout << result[i * m1_rows + j] << " ";
        }
        std::cout << std::endl;
    }
    
}

int* multiply(int* m1, int* m2, int m1_rows, int m1_cols, int m2_rows, int m2_cols)
{

    int result_rows = m1_rows, result_cols = m1_cols;

    if(m1_rows != m2_rows) {
        result_cols = m2_cols;
    }

    int* result = new (std::nothrow) int[result_rows * result_cols];
    int sum = 0;

    for(int i = 0; i < result_rows; i++){
        for(int j = 0; j < result_cols; j++) {
            for(int k = 0; k < m1_cols; k++) {
                sum += m1[i*m1_cols+ k] * m2[k*m2_cols + j];
            }
            result[i * result_rows + j] = sum;
            sum = 0;
        }
    }

    
    return result;
}