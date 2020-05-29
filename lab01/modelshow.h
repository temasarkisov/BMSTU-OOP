#ifndef MODELSHOW_H
#define MODELSHOW_H

#include <QGraphicsScene>

#include "structs.h"
#include "errors.h"

#define SCENE_WIDTH 500
#define SCENE_HEIGHT 500

void showModelProj(QGraphicsScene *const graphicsScene, const modelProjT *const modelProj);

#endif // MODELSHOW_H
