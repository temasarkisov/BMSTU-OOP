#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <iostream>
#include <cstdio>
#include <iosfwd>
#include <fstream>
#include <string>

#include "structs.h"
#include "errors.h"

using namespace std;

int uploadModel(modelT *const model, const char *const fileName);

int modelProjFormation(modelProjT *const modelProj, const modelT *const model);

#endif // DATAPROCESSING_H
