#ifndef MODELOPERATIONS_H
#define MODELOPERATIONS_H

#include <math.h>
#include <iostream>
#include <cstdio>

#include "structs.h"
#include "errors.h"

using namespace std;

int operatingModel(modelT *const model, modelProjT *const modelProj, const operParamsT *const operParams);

#endif // MODELOPERATIONS_H
