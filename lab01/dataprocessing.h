#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <iostream>
#include <cstdio>
#include <iosfwd>
#include <fstream>
#include <string>

#include "errors.h"
#include "interaction.h"

using namespace std;

typedef struct {
    double x;
    double z;
} pointProjT;

typedef struct {
    double x;
    double y;
    double z;
} pointT;

typedef struct {
    pointProjT *pointsProjArray;
    int pointsProjNumber;
    int **linksMatrix;
    pointProjT center;
} modelProjT;

typedef struct {
    pointT *pointsArray;
    int pointsNumber;
    int **linksMatrix;
    pointT center;
    bool isLoad = false;
} modelT;

typedef struct {
    double **matrix;
    int rows;
    int columns;
} matrixT;

int getFileData(const string fileName);

#endif // DATAPROCESSING_H
