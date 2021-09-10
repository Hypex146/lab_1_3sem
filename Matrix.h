//
// Created by vlad_ on 05.09.2021.
//

#ifndef LAB_1_MATRIX_H
#define LAB_1_MATRIX_H

#include <iostream>

typedef struct Item {
    int value;
    int order;

    Item();
} Item;

typedef struct Line {
    int countItem;
    Item *item;

    int addItem(int value, int order);

    Item *getItem(int order);

    Line();

    ~Line();
} Line;

class Matrix {
private:
    Line *line;
    int countLines;
    int countColumns;

    //static int *resizeIntArray(const int *array, int nowSize, int newSize);

    static bool isEqualsSum(int num1, int num2);

    static int getLimitedInt(int start, int end, const std::string &errMessage);

    static int getLimitedInt(int border, bool isStartBorder, const std::string &errMessage);

public:
    Matrix();

    Matrix *solve();

    void print();

    int fill();

    ~Matrix();
};

template<typename T>
int getValueOnce(T *value) {
    std::cin >> *value;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore();
        return -1;
    }
    return 0;
}

template<typename T>
T getValue() {
    T value;
    while (getValueOnce(&value) != 0) {
        std::cout << "Wrong input!" << std::endl;
    }
    return value;
}

#endif //LAB_1_MATRIX_H
