// Copyright (C) 2016 hutchimw@miamiOH.edu

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlockMatrixOps.cpp
 * Author: Mark Hutchinson
 *
 * Created on September 30, 2017, 8:46 PM
 */

#include <cstdlib>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include "MatrixOps.h"

int row;
int col;

Matrix load(const std::string& filePath) {
    std::ifstream f(filePath);
    f >> row >> col;
    Matrix matrix(row, std::vector<Val>(col));
    int n;
    for (int i = 0; i < row && !f.eof(); i++) {
        for (int j = 0; j < col && !f.eof(); j++) {
            f >> n;
            matrix[i][j] = n;
            std::cout << matrix[i][j];
        }
    }
    f.close();
    return matrix;
}

void write(const std::string& filePath, const Matrix& mat) {
    std::ofstream f(filePath);
    int n = 0;
    f << mat.size() << " ";
    f << mat[0].size() << "\n";
    for (unsigned int i = 0; i < mat.size(); i++) {
        f << " " << "\n";
        for (unsigned int k = 0; k < mat[0].size(); k++) {
            n = mat[i][k];
            f << n << " ";
        }
    }
}

Matrix blockMultiply(const Matrix& matrix1, const Matrix& matrix2,
        const size_t blockSize) {
    size_t size = matrix1.size(), col = matrix1[0].size();
    Matrix mat(size, std::vector<Val>(size));
    for (size_t i = 0; i < size; i += (i + blockSize > size) ? 
        (size % blockSize) : blockSize) {
        for (size_t j = 0; j < size; j += (j + blockSize > size) ? 
            (size % blockSize) : blockSize) {
            for (size_t k = 0; k < col; k += (k + blockSize > col) ? 
                (col % blockSize) : blockSize) {
                for (size_t x = i; x < std::min(i + blockSize, size); x++) {
                    for (size_t y = j; y < std::min(j + blockSize, size); y++) {
                        Val sum = 0;
                        for (size_t z = k; z < std::min(k + blockSize, col);
                                z++) {
                            sum += matrix1[x][z] * matrix2[z][y];
                        }
                        mat[x][y] += sum;
                    }
                }
            }
        }
    }
    return mat;
}
