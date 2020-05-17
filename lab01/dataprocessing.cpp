#include "dataprocessing.h"

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

static int allocLinksMatrix(modelT *const model)
{
    model->linksMatrix = (int **)calloc(model->pointsNumber, sizeof (int *));
    if (!model->linksMatrix)
    {
        //freePointsArray(model);
        return ERROR_ALLOC_LINKS_MATRIX;
    }

    for (int row = 0; row < model->pointsNumber; row++)
    {
        model->linksMatrix[row] = (int *)calloc(model->pointsNumber, sizeof (int));
        if (!model->linksMatrix[row])
        {
            //freePointsArray(model);

            for (int i = 0; i < row; i++)
            {
                free(model->linksMatrix[i]);
            }
            free(model->linksMatrix);

            return ERROR_ALLOC_LINKS_MATRIX;
        }
    }

    return SUCCESS;
}

int allocModel(modelT *const model)
{
    int errorCode = 0;

    errorCode = allocPointsArray(model);
    if (errorCode != SUCCESS)
    {
        //freePointsArray(model);
        return errorCode;
    }

    errorCode = allocLinksMatrix(model);
    if (errorCode != SUCCESS)
    {
        //freePointsArray(model);
        //freeLinksMatrix(model);
        delete model;
    }

    return SUCCESS;
}

void printData(const modelT *const model)
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

int getFileData(const string fileName)
{
    modelT model;
    int errorCode = 0, linksNumber = 0;

    ifstream file(fileName);
    if (!file.is_open())
    {
        return ERROR_FILE_OPEN;
    }

    file >> model.pointsNumber >> linksNumber;
    if (file.fail() || model.pointsNumber < 1 || linksNumber < 1)
    {
        return ERROR_FILE_DATA;
    }

    errorCode = allocModel(&model);
    if (errorCode != SUCCESS)
    {
        return errorCode;
    }

    for (int i = 0; i < model.pointsNumber; i++)
    {
        file >> model.pointsArray[i].x;
        file >> model.pointsArray[i].y;
        file >> model.pointsArray[i].z;
    }

    if (file.fail())
    {
        return ERROR_FILE_DATA;
    }

    for (int i = 0; i < linksNumber; i++)
    {
        int firstPointIndex = 0, secondPointIndex = 0;
        file >> firstPointIndex >> secondPointIndex;
        if (firstPointIndex < 1 || firstPointIndex > model.pointsNumber ||
            secondPointIndex < 1 || secondPointIndex > model.pointsNumber)
        {
            return ERROR_FILE_DATA;
        }
        model.linksMatrix[firstPointIndex - 1][secondPointIndex - 1] = 1;
        model.linksMatrix[secondPointIndex - 1][firstPointIndex - 1] = 1;
    }

    if (file.fail())
    {
        return ERROR_FILE_DATA;
    }

    setCenter(&model);
    printData(&model);
    //rotateModel(&model);

    file.close();
    return SUCCESS;
}