#include "modeloperations.h"

static void freeMatrix(matrixT *const matrix){
    for (int row = 0; row < matrix->rows; row++)
    {
        free(matrix->matrix[row]);
    }

    free(matrix->matrix);
}

static int allocMatrix(matrixT *const matrix, const int rows, const int columns)
{
    matrix->rows = rows;
    matrix->columns = columns;

    matrix->matrix = (double **)calloc(matrix->rows, sizeof (double *));
    if (!matrix->matrix)
    {
        return ERROR_ALLOC_MATRIX;
    }

    for (int row = 0; row < matrix->rows; row++)
    {
        matrix->matrix[row] = (double *)calloc(matrix->columns, sizeof (double));
        if (!matrix->matrix[row])
        {
            freeMatrix(matrix);
            return ERROR_ALLOC_MATRIX;
        }

        for (int column = 0; column < matrix->columns; column++)
        {
            matrix->matrix[row][column] = 0;
        }
    }

    return SUCCESS;
}

static void matrixOriginalFormation(matrixT *const matrixOriginal, const modelT *const model, const operTypeT operType)
{
    for (int i = 0; i < model->pointsNumber; i++)
    {
        matrixOriginal->matrix[i][0] = model->pointsArray[i].x;
        matrixOriginal->matrix[i][1] = model->pointsArray[i].y;
        matrixOriginal->matrix[i][2] = model->pointsArray[i].z;

        if (operType == MOVE_X || operType == MOVE_Y || operType == MOVE_Z)
        {
            matrixOriginal->matrix[i][3] = 1;
        }
    }
}

static void matrixOperatingRotateFormation(matrixT *const matrixOperatingRotate, const double value, const coordTypeT coordType)
{
    if (coordType == X)
    {
        matrixOperatingRotate->matrix[0][0] = 1.0;
        matrixOperatingRotate->matrix[1][1] = cos(value * 3.14 / 180);
        matrixOperatingRotate->matrix[1][2] = -sin(value * 3.14 / 180);
        matrixOperatingRotate->matrix[2][1] = sin(value * 3.14 / 180);
        matrixOperatingRotate->matrix[2][2] = cos(value * 3.14 / 180);
    }
    else if (coordType == Y)
    {
        matrixOperatingRotate->matrix[0][0] = cos(value * 3.14 / 180);
        matrixOperatingRotate->matrix[0][2] = sin(value * 3.14 / 180);
        matrixOperatingRotate->matrix[1][1] = 1.0;
        matrixOperatingRotate->matrix[2][0] = -sin(value * 3.14 / 180);
        matrixOperatingRotate->matrix[2][2] = cos(value * 3.14 / 180);
     }
     else if (coordType == Z)
     {
        matrixOperatingRotate->matrix[0][0] = cos(value * 3.14 / 180);
        matrixOperatingRotate->matrix[0][1] = -sin(value * 3.14 / 180);
        matrixOperatingRotate->matrix[1][0] = sin(value * 3.14 / 180);
        matrixOperatingRotate->matrix[1][1] = cos(value * 3.14 / 180);
        matrixOperatingRotate->matrix[2][2] = 1.0;
    }
}

static void matrixOperatingMoveFormation(matrixT *const matrixOperatingMove, const double value, const coordTypeT coordType) {
    matrixOperatingMove->matrix[0][0] = 1.0;
    matrixOperatingMove->matrix[1][1] = 1.0;
    matrixOperatingMove->matrix[2][2] = 1.0;
    matrixOperatingMove->matrix[3][3] = 1.0;

    if (coordType == X)
    {
        matrixOperatingMove->matrix[3][0] = value;
    }
    else if (coordType == Y)
    {
        matrixOperatingMove->matrix[3][1] = value;
    }
    else if (coordType == Z)
    {
        matrixOperatingMove->matrix[3][2] = value;
    }
}

static void matrixOperatingScaleFormation(matrixT *const matrixOperatingScale, const double value)
{
    for (int i = 0; i < matrixOperatingScale->rows; ++i)
    {
        matrixOperatingScale->matrix[i][i] = value;
    }
}

static int multiplicationMatrix(matrixT *const matrixOriginal, matrixT *const matrixOperating) {
    int errorCode = 0;

    matrixT matrixResult;
    errorCode = allocMatrix(&matrixResult, matrixOriginal->rows, matrixOperating->columns);
    if (errorCode != SUCCESS)
    {
        return ERROR_ALLOC_MATRIX;
    }

    for (int i = 0; i < matrixOriginal->rows; i++)
    {
        for (int j = 0; j < matrixOperating->columns; j++)
        {
            matrixResult.matrix[i][j] = 0;
            for (int k = 0; k < matrixOriginal->columns; k++)
            {
                matrixResult.matrix[i][j] += matrixOriginal->matrix[i][k] * matrixOperating->matrix[k][j];
            }
        }
    }

    for (int i = 0; i < matrixOriginal->rows; i++)
    {
        for (int j = 0; j < matrixOriginal->columns; j++)
        {
            matrixOriginal->matrix[i][j] = matrixResult.matrix[i][j];
        }
    }

    freeMatrix(&matrixResult);

    return SUCCESS;
}

static void offsetModelCenter(modelT *const model, const bool isCenter)
{
    double offsetX = 0, offsetY = 0, offsetZ = 0;

    if (isCenter)
    {
        offsetX = (model->center.x);
        offsetY = (model->center.x);
        offsetZ = (model->center.x);
    }
    else
    {
        offsetX = -(model->center.x);
        offsetY = -(model->center.x);
        offsetZ = -(model->center.x);
    }

    for (int i = 0; i < model->pointsNumber; i++)
    {
        model->pointsArray[i].x += offsetX;
        model->pointsArray[i].y += offsetY;
        model->pointsArray[i].z += offsetZ;
    }
}

int operatingModel(modelT *const model, const operParamsT *const operParams)
{
    int errorCode = 0;
    int elementsNumber = 0;
    matrixT matrixOriginal, matrixOperating;

    if (model->isLoad == true)
    {
        offsetModelCenter(model, false);

        if (operParams->operType == MOVE_X || operParams->operType == MOVE_Y || operParams->operType == MOVE_Z)
        {
            elementsNumber = 4;
        }
        else if (operParams->operType == ROTATE_X || operParams->operType == ROTATE_Y || operParams->operType == ROTATE_Z || operParams->operType == SCALE)
        {
            elementsNumber = 3;
        }

        errorCode = allocMatrix(&matrixOriginal, model->pointsNumber, elementsNumber);
        if (errorCode != SUCCESS)
        {
            return ERROR_ALLOC_MATRIX;
        }

        errorCode = allocMatrix(&matrixOperating, elementsNumber, elementsNumber);
        if (errorCode != SUCCESS)
        {
            freeMatrix(&matrixOriginal);
            return ERROR_ALLOC_MATRIX;
        }

        if (operParams->operType == ROTATE_X)
        {
            matrixOperatingRotateFormation(&matrixOperating, operParams->value, X);
        }
        else if (operParams->operType == ROTATE_Y)
        {
            matrixOperatingRotateFormation(&matrixOperating, operParams->value, Y);
        }
        else if (operParams->operType == ROTATE_Z)
        {
            matrixOperatingRotateFormation(&matrixOperating, operParams->value, Z);
        }
        else if (operParams->operType == MOVE_X)
        {
            matrixOperatingMoveFormation(&matrixOperating, operParams->value, X);
        }
        else if (operParams->operType == MOVE_Y)
        {
            matrixOperatingMoveFormation(&matrixOperating, operParams->value, Y);
        }
        else if (operParams->operType == MOVE_Z)
        {
            matrixOperatingMoveFormation(&matrixOperating, operParams->value, Z);
        }
        else if (operParams->operType == SCALE)
        {
            matrixOperatingScaleFormation(&matrixOperating, operParams->value);
        }

        matrixOriginalFormation(&matrixOriginal, model, operParams->operType);

        errorCode = multiplicationMatrix(&matrixOriginal, &matrixOperating);
        if (errorCode != SUCCESS)
        {
            freeMatrix(&matrixOriginal);
            freeMatrix(&matrixOperating);
        }

        for (int i = 0; i < model->pointsNumber; i++)
        {
                model->pointsArray[i].x = matrixOriginal.matrix[i][0];
                model->pointsArray[i].y = matrixOriginal.matrix[i][1];
                model->pointsArray[i].z = matrixOriginal.matrix[i][2];
        }

        freeMatrix(&matrixOriginal);
        freeMatrix(&matrixOperating);

        offsetModelCenter(model, true);
        //setModelProjData(modelProj, model);

        return SUCCESS;
    }

    return ERROR_LOAD_MODEL;
}







