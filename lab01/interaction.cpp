#include "interaction.h"

static void matrixDataRotateFormation(matrixT *const matrixDataRotate, const modelT *const model)
{
    matrixDataRotate->matrix = (double **)calloc(model->pointsNumber, sizeof (double* ));
    for (int i = 0; i < model->pointsNumber; i++)
    {
        matrixDataRotate->matrix[i] = (double *)calloc(MATRIX_ROTATE_COLUMNS, sizeof (double));
    }

    matrixDataRotate->rows = model->pointsNumber;
    matrixDataRotate->columns = MATRIX_ROTATE_COLUMNS;

    for (int i = 0; i < model->pointsNumber; i++)
    {
        matrixDataRotate->matrix[i][0] = model->pointsArray[i].x;
        matrixDataRotate->matrix[i][1] = model->pointsArray[i].y;
        matrixDataRotate->matrix[i][2] = model->pointsArray[i].z;
    }
}

void matrixTransformRotateFormation(matrixT *const matrixTransformRotate, const double angle, const char coordType)
{
    if (coordType == 'x')
    {
        matrixTransformRotate->matrix[0][0] = 1.0;
        matrixTransformRotate->matrix[1][1] = cos(angle * 3.14 / 180);
        matrixTransformRotate->matrix[1][2] = -sin(angle * 3.14 / 180);
        matrixTransformRotate->matrix[2][1] = sin(angle * 3.14 / 180);
        matrixTransformRotate->matrix[2][2] = cos(angle * 3.14 / 180);
    }
    else if (coordType == 'y')
    {
        matrixTransformRotate->matrix[0][0] = cos(angle * 3.14 / 180);
        matrixTransformRotate->matrix[0][2] = sin(angle * 3.14 / 180);
        matrixTransformRotate->matrix[1][1] = 1.0;
        matrixTransformRotate->matrix[2][0] = -sin(angle * 3.14 / 180);
        matrixTransformRotate->matrix[2][2] = cos(angle * 3.14 / 180);
     }
     else if (coordType == 'z')
     {
        matrixTransformRotate->matrix[0][0] = cos(angle * 3.14 / 180);
        matrixTransformRotate->matrix[0][1] = -sin(angle * 3.14 / 180);
        matrixTransformRotate->matrix[1][0] = sin(angle * 3.14 / 180);
        matrixTransformRotate->matrix[1][1] = cos(angle * 3.14 / 180);
        matrixTransformRotate->matrix[2][2] = 1.0;
    }
}

void outputMatrix(const matrixT matrixDataRotate)
{
    cout << "\n";
    for (int i = 0; i < matrixDataRotate.rows; i++)
    {
        for (int j = 0; j < matrixDataRotate.columns; j++)
        {
            cout << matrixDataRotate.matrix[i][j];
            cout << " ";
        }
        cout << "\n";
    }
}

void rotateModel(const modelT *const model)
{
    matrixT matrixDataRotate;
    matrixT matrixTransfotrmRotate;

    matrixDataRotateFormation(&matrixDataRotate, model);
    matrixTransformRotateFormation(&matrixTransfotrmRotate, 180, 'x');  // Fix

    outputMatrix(matrixDataRotate);
    outputMatrix(matrixTransfotrmRotate);
}
