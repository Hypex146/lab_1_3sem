//
// Created by vlad_ on 05.09.2021.
//

#include "Matrix.h"

Item::Item() {
    this->order = -1;
    this->value = 0;
}

Line::Line() {
    this->countItem = 0;
    this->item = nullptr;
}

Line::~Line() {
    delete[] this->item;
}

Matrix::Matrix() {
    this->line = nullptr;
    this->countLines = 0;
    this->countColumns = 0;
}

Matrix::~Matrix() {
    delete[] this->line;
}

int Matrix::getLimitedInt(int start, int end, const std::string &errMessage) {
    int result;
    do {
        result = getValue<int>();
        if (result < start || result > end) { std::cout << errMessage << std::endl; }
    } while (result < start || result > end);
    return result;
}

int Matrix::getLimitedInt(int border, bool isStartBorder, const std::string &errMessage) {
    int result;
    if (isStartBorder) {
        do {
            result = getValue<int>();
            if (result < border) { std::cout << errMessage << std::endl; }
        } while (result < border);
    } else {
        do {
            result = getValue<int>();
            if (result > border) { std::cout << errMessage << std::endl; }
        } while (result > border);
    }

    return result;
}

bool Matrix::isEqualsSum(int num1, int num2) {
    int sum1 = 0, sum2 = 0;
    while (num1 != 0) {
        sum1 += num1 % 10;
        num1 /= 10;
    }
    while (num2 != 0) {
        sum2 += num2 % 10;
        num2 /= 10;
    }
    if (sum1 == sum2 || sum1 == (-1) * sum2) { return true; }
    return false;
}
/*
int *Matrix::resizeIntArray(const int *array, int nowSize, int newSize) {
    int *newArray;
    try{
        newArray = new int[newSize];
    } catch (std::bad_alloc &err) {
        std::cout << "[ERROR] Bad alloc! " << err.what() << std::endl;
        return nullptr;
    }
    for (int i = 0; i < nowSize; i++) {
        if (i >= newSize) { break; }
        newArray[i] = array[i];
    }
    delete[] array;
    return newArray;
}
*/
int Line::addItem(int value, int order) {
    if (this->item == nullptr) { return -1; }
    for (int i = 0; i < this->countItem; i++) {
        if (order > this->item[i].order && this->item[i].order != -1) { continue; }
        if (order == this->item[i].order && this->item[i].order != -1) { return -2; }
        int tmpValue, tmpOrder;
        tmpValue = this->item[i].value;
        tmpOrder = this->item[i].order;
        this->item[i].value = value;
        this->item[i].order = order;
        value = tmpValue;
        order = tmpOrder;
    }
    return 0;
}

Item *Line::getItem(int order) {
    for (int i = 0; i < this->countItem; i++) {
        if (this->item[i].order == order) { return &this->item[i]; }
    }
    return nullptr;
}

Matrix *Matrix::solve() {
    Matrix *newMatrix;
    try{
        newMatrix = new Matrix();
    } catch (std::bad_alloc &err) {
        std::cout << "[ERROR] Bad alloc! " << err.what() << std::endl;
        return nullptr;
    }
    newMatrix->countColumns = this->countColumns;
    newMatrix->countLines = this->countLines;
    try{
        newMatrix->line = new Line[newMatrix->countLines]();
    } catch (std::bad_alloc &err) {
        std::cout << "[ERROR] Bad alloc! " << err.what() << std::endl;
        return nullptr;
    }
    for (int i = 0; i < this->countLines; i++) {
        int countItem = 0;
        Item *lastItem = this->line[i].getItem(this->countColumns - 1);
        if (lastItem) {
            for (int j = 0; j < this->line[i].countItem; j++) {
                if (isEqualsSum(this->line[i].item[j].value, lastItem->value)) { countItem++; }
            }
            newMatrix->line[i].countItem = countItem;
            try{
                newMatrix->line[i].item = new Item[newMatrix->line[i].countItem]();
            } catch (std::bad_alloc &err) {
                std::cout << "[ERROR] Bad alloc! " << err.what() << std::endl;
                return nullptr;
            }
            for (int j = 0; j < newMatrix->line[i].countItem; j++) {
                if (isEqualsSum(this->line[i].item[j].value, lastItem->value)) {
                    newMatrix->line[i].addItem(this->line[i].item[j].value, this->line[i].item[j].order);
                }
            }
        }
    }
    return newMatrix;
}

int Matrix::fill() {
    std::cout << "Enter count of lines" << std::endl;
    this->countLines = getLimitedInt(1, true, "Wrong count of lines!");
    std::cout << "Enter count of columns" << std::endl;
    this->countColumns = getLimitedInt(1, true, "Wrong count of columns!");
    try{
        this->line = new Line[this->countLines]();
    } catch (std::bad_alloc &err) {
        std::cout << "[ERROR] Bad alloc! " << err.what() << std::endl;
        return -1;
    }
    for (int i = 0; i < this->countLines; i++) {
        std::cout << "Enter count of non-null element " << i << std::endl;
        this->line[i].countItem = getLimitedInt(
                0, this->countColumns, "Wrong count of non-null element");
        try{
            this->line[i].item = new Item[this->line[i].countItem]();
        } catch (std::bad_alloc &err) {
            std::cout << "[ERROR] Bad alloc! " << err.what() << std::endl;
            return -1;
        }
        for (int j = 0; j < this->line[i].countItem; j++) {
            std::cout << "Enter the value" << std::endl;
            int value = getValue<int>();
            while (value == 0) {
                std::cout << "Wrong value! Try again" << std::endl;
                value = getValue<int>();
            }
            std::cout << "Enter the order" << std::endl;
            int order = getLimitedInt(0, this->countColumns - 1, "Wrong order! Try again'");
            while (this->line[i].addItem(value, order) != 0) {
                std::cout << "Wrong order! Try again" << std::endl;
                order = getValue<int>();
            }
        }
    }
    return 0;
}

void Matrix::print() {
    std::cout << std::endl;
    for (int i = 0; i < this->countLines; i++) {
        int lastIndex = -1;
        for (int j = 0; j < this->line[i].countItem; j++) {
            for (int k = 0; k < this->line[i].item[j].order - lastIndex - 1; k++) {
                std::cout << "0 ";
            }
            std::cout << this->line[i].item[j].value << " ";
            lastIndex = this->line[i].item[j].order;
        }
        for (int k = 0; k < this->countColumns - lastIndex - 1; k++) {
            std::cout << "0 ";
        }
        std::cout << std::endl;
    }
}
