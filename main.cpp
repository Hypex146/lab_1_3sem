#include <iostream>
#include "Matrix.h"

int main() {
    Matrix *matrix;
    matrix = new Matrix();
    matrix->fill();
    matrix->print();
    Matrix *newMatrix = matrix->solve();
    if (newMatrix) { newMatrix->print(); }
    delete matrix;
    delete newMatrix;
    return 0;
}
