#include "dataprocessing.h"

static void freeLinksMatrix(int **matrix, const int rows){
    for (int row = 0; row < rows; row++)
    {
        free(matrix[row]);
    }

    free(matrix);
}

static void freePointsArray(pointT *pointsArray)
{
    free(pointsArray);
}

static void freePointsProjArray(pointProjT *pointsProjArray)
{
    free(pointsProjArray);
}

static int coordMaxIndexDef(const modelT *const model, const char coordType)
{
    int coordMaxIndex = 0;

    if (coordType == 'x')
    {
        for (int i = 0; i < model->pointsNumber; i++)
        {
            if (model->pointsArray[i].x > model->pointsArray[coordMaxIndex].x)
            {
                coordMaxIndex = i;
            }
        }
    }
    else if (coordType == 'y')
    {
        for (int i = 0; i < model->pointsNumber; i++)
        {
            if (model->pointsArray[i].y > model->pointsArray[coordMaxIndex].y)
            {
                coordMaxIndex = i;
            }
        }
    }
    else if (coordType == 'z')
    {
        for (int i = 0; i < model->pointsNumber; i++)
        {
            if (model->pointsArray[i].z > model->pointsArray[coordMaxIndex].z)
            {
                coordMaxIndex = i;
            }
        }
    }

    return coordMaxIndex;
}

static int coordMinIndexDef(const modelT *const model, const char coordType)
{
    int coordMinIndex = 0;

    if (coordType == 'x')
    {
        for (int i = 0; i < model->pointsNumber; i++)
        {
            if (model->pointsArray[i].x < model->pointsArray[coordMinIndex].x)
            {
                coordMinIndex = i;
            }
        }
    }
    else if (coordType == 'y')
    {
        for (int i = 0; i < model->pointsNumber; i++)
        {
            if (model->pointsArray[i].y < model->pointsArray[coordMinIndex].y)
            {
                coordMinIndex = i;
            }
        }
    }
    else if (coordType == 'z')
    {
        for (int i = 0; i < model->pointsNumber; i++)
        {
            if (model->pointsArray[i].z < model->pointsArray[coordMinIndex].z)
            {
                coordMinIndex = i;
            }
        }
    }

    return coordMinIndex;
}

static void setCenter(modelT *const model)
{
    int indexMinX = 0, indexMinY = 0, indexMinZ = 0;
    int indexMaxX = 0, indexMaxY = 0, indexMaxZ = 0;

    indexMinX = coordMinIndexDef(model, 'x');  // Fix
    indexMinY = coordMinIndexDef(model, 'y');
    indexMinZ = coordMinIndexDef(model, 'z');

    indexMaxX = coordMaxIndexDef(model, 'x');
    indexMaxY = coordMaxIndexDef(model, 'y');
    indexMaxZ = coordMaxIndexDef(model, 'z');

    model->center.x = (model->pointsArray[indexMaxX].x + model->pointsArray[indexMinX].x) / 2;
    model->center.y = (model->pointsArray[indexMaxY].y + model->pointsArray[indexMinY].y) / 2;
    model->center.z = (model->pointsArray[indexMaxZ].z + model->pointsArray[indexMinZ].z) / 2;
}

static int allocPointsArray(modelT *const model)
{
    model->pointsArray = (pointT *)calloc(model->pointsNumber, sizeof (pointT));
    if (!model->pointsArray)
    {
        return ERROR_ALLOC_POINTS_ARRAY;
    }

    return SUCCESS;
}

static int allocPointsProjArray(modelProjT *const modelProj)
{
    modelProj->pointsProjArray = (pointProjT *)calloc(modelProj->pointsProjNumber, sizeof (pointProjT));
    if (!modelProj->pointsProjArray)
    {
        return ERROR_ALLOC_POINTS_PROJ_ARRAY;
    }

    return SUCCESS;
}

static int allocLinksMatrix(modelT *const model)
{
    model->linksMatrix = (int **)calloc(model->pointsNumber, sizeof (int *));
    if (!model->linksMatrix)
    {
        freePointsArray(model->pointsArray);
        return ERROR_ALLOC_LINKS_MATRIX;
    }

    for (int row = 0; row < model->pointsNumber; row++)
    {
        model->linksMatrix[row] = (int *)calloc(model->pointsNumber, sizeof (int));
        if (!model->linksMatrix[row])
        {
            freePointsArray(model->pointsArray);
            freeLinksMatrix(model->linksMatrix, model->pointsNumber);

            return ERROR_ALLOC_LINKS_MATRIX;
        }
    }

    return SUCCESS;
}

static int allocLinksMatrix(modelProjT *const modelProj)
{
    modelProj->linksMatrix = (int **)calloc(modelProj->pointsProjNumber, sizeof (int *));
    if (!modelProj->linksMatrix)
    {
        freePointsProjArray(modelProj->pointsProjArray);
        return ERROR_ALLOC_LINKS_MATRIX;
    }

    for (int row = 0; row < modelProj->pointsProjNumber; row++)
    {
        modelProj->linksMatrix[row] = (int *)calloc(modelProj->pointsProjNumber, sizeof (int));
        if (!modelProj->linksMatrix[row])
        {
            freePointsProjArray(modelProj->pointsProjArray);
            freeLinksMatrix(modelProj->linksMatrix, modelProj->pointsProjNumber);

            return ERROR_ALLOC_LINKS_MATRIX;
        }
    }

    return SUCCESS;
}

static int allocModel(modelT *const model)
{
    int errorCode = 0;

    errorCode = allocPointsArray(model);
    if (errorCode != SUCCESS)
    {
        return errorCode;
    }

    errorCode = allocLinksMatrix(model);
    if (errorCode != SUCCESS)
    {
        freePointsArray(model->pointsArray);
        freeLinksMatrix(model->linksMatrix, model->pointsNumber);
        delete model;
    }

    return SUCCESS;
}

static int allocModelProj(modelProjT *const modelProj)
{
    int errorCode = 0;

    errorCode = allocPointsProjArray(modelProj);
    if (errorCode != SUCCESS)
    {
        return errorCode;
    }

    errorCode = allocLinksMatrix(modelProj);
    if (errorCode != SUCCESS)
    {
        freePointsProjArray(modelProj->pointsProjArray);
        freeLinksMatrix(modelProj->linksMatrix, modelProj->pointsProjNumber);
    }

    return SUCCESS;
}

static void printModelData(const modelT *const model)
{
    cout << "\n\n";
    for (int i = 0; i < model->pointsNumber; i++)
    {
        cout << model->pointsArray[i].x;
        cout << " ";
        cout << model->pointsArray[i].y;
        cout << " ";
        cout << model->pointsArray[i].z;
        cout << " ";
    }

    cout << "\n\n";
    for (int i = 0; i < model->pointsNumber; i++)
    {
        for (int j = 0; j < model->pointsNumber; j++)
        {
            cout << model->linksMatrix[i][j];
            cout << " ";
        }

        cout << "\n";
    }

    cout << "\nCenter:\n";
    cout << model->center.x << " "<< model->center.y << " " << model->center.z << " ";
}

static void printModelProjData(const modelProjT *const modelProj)
{
    cout << "\n\n";
    for (int i = 0; i < modelProj->pointsProjNumber; i++)
    {
        cout << modelProj->pointsProjArray[i].x;
        cout << " ";
        cout << modelProj->pointsProjArray[i].z;
        cout << " ";
    }

    cout << "\n\n";
    for (int i = 0; i < modelProj->pointsProjNumber; i++)
    {
        for (int j = 0; j < modelProj->pointsProjNumber; j++)
        {
            cout << modelProj->linksMatrix[i][j];
            cout << " ";
        }

        cout << "\n";
    }

    cout << "\nCenter:\n";
    cout << modelProj->center.x << " " << modelProj->center.z << " ";
}

static void copyModel(modelT *const model, const modelT *const modelTemp)
{
    model->pointsArray = modelTemp->pointsArray;
    model->pointsNumber = modelTemp->pointsNumber;
    model->linksMatrix = modelTemp->linksMatrix;
    model->center = modelTemp->center;
    model->isLoad = modelTemp->isLoad;
}

static int pointsLinksNumbersScan(int *const pointsNumber, int *const linksNumber, FILE *const filePtr)
{
    int errorCode = 0;

    errorCode = fscanf(filePtr, "%d", pointsNumber);
    if (errorCode == SUCCESS)
    {
        fscanf(filePtr, "%d", linksNumber);
        if (errorCode == SUCCESS_SCAN)
        {
            if (*(pointsNumber) >= 1 && *(linksNumber) >= 1)
            {
                return SUCCESS;
            }
        }
    }

    return ERROR_FILE_DATA;
}

static int pointArrayScan(pointT *const pointsArray, const int pointsNumber, FILE *const filePtr)
{
    int errorCode = 0;

    for (int i = 0; i < pointsNumber; i++)
    {
        errorCode = fscanf(filePtr, "%lf %lf %lf", &(pointsArray[i].x), &(pointsArray[i].y), &(pointsArray[i].z));
        if (errorCode != 3)
        {
            return ERROR_FILE_DATA;
        }
    }

    return SUCCESS;
}

static int linksMatrixScan(int *const*const linksMatrix, const int linksNumber, const int pointsNumber, FILE *const filePtr)
{
    int errorCode = 0;
    int firstPointIndex = 0, secondPointIndex = 0;

    for (int i = 0; i < linksNumber; i++)
    {
        errorCode = fscanf(filePtr, "%d %d", &firstPointIndex, &secondPointIndex);
        if (errorCode == 2)
        {
            if (firstPointIndex >= 1 && firstPointIndex <= pointsNumber && secondPointIndex >= 1 && secondPointIndex <= pointsNumber)
            {
                linksMatrix[firstPointIndex - 1][secondPointIndex - 1] = 1;
                linksMatrix[secondPointIndex - 1][firstPointIndex - 1] = 1;
            }
        }

        else
        {
            return ERROR_FILE_DATA;
        }
    }

    return SUCCESS;
}

static int setModelDataWithFile(modelT *const model, const char *const fileName)
{
    int errorCode = 0, linksNumber = 0;
    FILE *filePtr;

    filePtr = fopen(fileName, "r");

    if (filePtr != NULL)
    {
        errorCode = pointsLinksNumbersScan(&(model->pointsNumber), &(linksNumber), filePtr);
        if (errorCode == SUCCESS)
        {
            errorCode = allocModel(model);
            if (errorCode == SUCCESS)
            {
                errorCode = pointArrayScan(model->pointsArray, model->pointsNumber, filePtr);
                if (errorCode == SUCCESS)
                {
                    errorCode = linksMatrixScan(model->linksMatrix, linksNumber, model->pointsNumber, filePtr);
                    if (errorCode == SUCCESS)
                    {
                        setCenter(model);
                        fclose(filePtr);
                        return SUCCESS;
                    }
                }
            }
        }
    }

    return ERROR_FILE_OPEN;
}

static void setModelProjData(modelProjT *const modelProj, const modelT *const model)
{
    modelProj->pointsProjNumber = model->pointsNumber;

    for (int i = 0; i < modelProj->pointsProjNumber; i++)
    {
        modelProj->pointsProjArray[i].x = model->pointsArray[i].x;
        modelProj->pointsProjArray[i].z = model->pointsArray[i].z;
    }

    for (int i = 0; i < modelProj->pointsProjNumber; i++)
    {
        for (int j = 0; j < modelProj->pointsProjNumber; j++)
        {
            modelProj->linksMatrix[i][j] = model->linksMatrix[i][j];
        }
    }

    modelProj->center.x = model->center.x;
    modelProj->center.z = model->center.z;
}

int uploadModel(modelT *const model, modelProjT *const modelProj, const char *const fileName)
{
    int errorCode = 0;

    modelT modelTemp;

    errorCode = setModelDataWithFile(&modelTemp, fileName);
    if (errorCode == SUCCESS)
    {
        copyModel(model, &modelTemp);

        modelProj->pointsProjNumber = model->pointsNumber;
        errorCode = allocModelProj(modelProj);
        if (errorCode == SUCCESS)
        {
            setModelProjData(modelProj, model);
            model->isLoad = true;

            printModelData(model);
            printModelProjData(modelProj);
        }
    }

    return errorCode;
}
