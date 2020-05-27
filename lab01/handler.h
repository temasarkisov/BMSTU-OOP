#ifndef HANDLER_H
#define HANDLER_H

#include "dataprocessing.h"

enum operTypeT { UPLOAD, SCALE, MOVING_X, MOVING_Y, MOVING_Z, ROTATION_X, ROTATION_Y, ROTATION_Z, FREE };

typedef struct {
    std::string fileName;
    operTypeT operType;
    double value;
} operParamsT;

int handler(modelT *const model, modelProjT *const modelProj, const operParamsT *const operParams);

#endif // HANDLER_H
