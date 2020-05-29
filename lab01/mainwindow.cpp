#include "mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_buttonSelectFile_clicked()
{
    int errorCode = 0;
    operParamsT operParams;

    QString filePath = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath());
    fileName = (char *)calloc(filePath.length(), sizeof (char));
    strcpy(fileName, filePath.toStdString().c_str());

    operParams = {fileName, UPLOAD, 0, NULL};
    errorCode = handler(&model, &modelProj, &operParams);
}

void MainWindow::on_buttonProgress_clicked()
{
    int errorCode = 0;
    double value = 0;
    operParamsT operParams;

    printModelProjData(&modelProj);

    value = ui->spinBoxScale->value();
    if (value != 0)
    {
        operParams = {NULL, SCALE, value, NULL};
        errorCode = handler(&model, &modelProj, &operParams);
    }
    value = ui->spinBoxMoveX->value();
    if (value != 0)
    {
        operParams = {NULL, MOVE_X, value, NULL};
        errorCode = handler(&model, &modelProj, &operParams);
    }
    value = ui->spinBoxMoveY->value();
    if (value != 0)
    {
        operParams = {NULL, MOVE_Y, value, NULL};
        errorCode = handler(&model, &modelProj, &operParams);
    }
    value = ui->spinBoxMoveZ->value();
    if (value != 0)
    {
        operParams = {NULL, MOVE_Z, value, NULL};
        errorCode = handler(&model, &modelProj, &operParams);
    }
    value = ui->spinBoxRotateX->value();
    if (value != 0)
    {
        operParams = {NULL, ROTATE_X, value, NULL};
        errorCode = handler(&model, &modelProj, &operParams);
    }
    value = ui->spinBoxRotateY->value();
    if (value != 0)
    {
        operParams = {NULL, ROTATE_Y, value, NULL};
        errorCode = handler(&model, &modelProj, &operParams);
    }
    value = ui->spinBoxRotateZ->value();
    if (value != 0)
    {
        operParams = {NULL, ROTATE_Z, value, NULL};
        errorCode = handler(&model, &modelProj, &operParams);
    }

    printModelProjData(&modelProj);
}

void MainWindow::on_buttonRefresh_clicked()
{
    int errorCode = 0;
    operParamsT operParams;

    operParams = {fileName, UPLOAD, 0, NULL};
    errorCode = handler(&model, &modelProj, &operParams);
}

void MainWindow::on_buttonShow_clicked()
{
    int errorCode = 0;
    operParamsT operParams;

    QGraphicsScene *graphicsScene = new QGraphicsScene();

    operParams = {NULL, SHOW, 0, graphicsScene};
    errorCode = handler(&model, &modelProj, &operParams);

    ui->graphicsView->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    ui->graphicsView->setScene(graphicsScene);
}
