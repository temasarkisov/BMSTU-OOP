#ifndef MODELSHOW_H
#define MODELSHOW_H

#include <QGraphicsScene>

#include "structs.h"
#include "errors.h"
#include "dataprocessing.h"

#define SCENE_WIDTH 500
#define SCENE_HEIGHT 500

int showModelProj(QGraphicsScene *const graphicsScene, modelProjT *const modelProj, const modelT *const model);

#endif // MODELSHOW_H
