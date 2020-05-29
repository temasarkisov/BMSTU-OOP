#ifndef STRUCTS_H
#define STRUCTS_H

#include <QGraphicsScene>

//modeloperations.cpp

enum coordTypeT { X, Y, Z };

enum operTypeT { UPLOAD, SCALE, MOVE_X, MOVE_Y, MOVE_Z, ROTATE_X, ROTATE_Y, ROTATE_Z, FREE, SHOW };

typedef struct {
    char *filename;
    operTypeT operType;
    double value;
    QGraphicsScene *graphicsScene;
} operParamsT;

typedef struct {
    double **matrix;
    int rows;
    int columns;
} matrixT;

//dataprocessing.cpp

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

#endif // STRUCTS_H
