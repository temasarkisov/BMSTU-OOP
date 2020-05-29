#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <iostream>
#include <cstdio>
#include <iosfwd>
#include <fstream>
#include <string>

#include "errors.h"

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

int uploadModel(modelT *const model, modelProjT *const modelProj, const string fileName);

void setModelProjData(modelProjT *const modelProj, const modelT *const model);

#endif // DATAPROCESSING_H
