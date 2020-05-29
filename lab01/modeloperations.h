#ifndef MODELOPERATIONS_H
#define MODELOPERATIONS_H

#include <math.h>
#include <iostream>
#include <cstdio>

#include "dataprocessing.h"


enum coordTypeT { X, Y, Z };

enum operTypeT { UPLOAD, SCALE, MOVE_X, MOVE_Y, MOVE_Z, ROTATE_X, ROTATE_Y, ROTATE_Z, FREE };

typedef struct {
    operTypeT operType;
    double value;
} operParamsT;

typedef struct {
    double **matrix;
    int rows;
    int columns;
} matrixT;

int operatingModel(modelT *const model, modelProjT *const modelProj, const double value, const operTypeT operType);

#endif // MODELOPERATIONS_H
