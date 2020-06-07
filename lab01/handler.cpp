#include "handler.h"

int handler(modelT *const model, modelProjT *const modelProj, const operParamsT *const operParams)
{
    int errorCode = 0;

    if (operParams->operType == UPLOAD)
    {
        errorCode = uploadModel(model, operParams->filename);
    }
    if (operParams->operType == SCALE)
    {
        errorCode = operatingModel(model, operParams);
    }
    else if (operParams->operType == MOVE_X)
    {
        errorCode = operatingModel(model, operParams);
    }
    else if (operParams->operType == MOVE_Y)
    {
        errorCode = operatingModel(model, operParams);
    }
    else if (operParams->operType == MOVE_Z)
    {
        errorCode = operatingModel(model, operParams);
    }
    else if (operParams->operType == ROTATE_X)
    {
        errorCode = operatingModel(model, operParams);
    }
    else if (operParams->operType == ROTATE_Y)
    {
        errorCode = operatingModel(model, operParams);
    }
    else if (operParams->operType == ROTATE_Z)
    {
        errorCode = operatingModel(model, operParams);
    }
    else if (operParams->operType == SHOW)
    {
        errorCode = showModelProj(operParams->graphicsScene, modelProj, model);
    }

    return errorCode;
}
