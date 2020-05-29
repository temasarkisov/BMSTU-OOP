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

int uploadModel(modelT *const model, modelProjT *const modelProj, const char *const fileName);

#endif // DATAPROCESSING_H
