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

static void showModelProj(QGraphicsScene *const graphicsScene, const modelProjT *const modelProj)
{
    QPen outlinePen(Qt::black);

    double dX = SCENE_WIDTH / 2 - modelProj->center.x;
    double dZ = SCENE_HEIGHT / 2 - modelProj->center.z;

    for (int i = 0; i < modelProj->pointsProjNumber; i++)
    {
        for (int j = 0; j < modelProj->pointsProjNumber; j++)
        {
            if (modelProj->linksMatrix[i][j])
            {
                double xB = modelProj->pointsProjArray[i].x + dX;
                double xE = modelProj->pointsProjArray[j].x + dX;
                double zB = modelProj->pointsProjArray[i].z + dZ;
                double zE = modelProj->pointsProjArray[j].z + dZ;
                graphicsScene->addLine(xB, zB, xE, zE, outlinePen);;
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    int errorCode = 0;

    QString filePath = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath());
    string fileName = filePath.toStdString();

    errorCode = uploadModel(&model, &modelProj, fileName);
    if (errorCode == SUCCESS)
    {
        ui->graphicsView->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
        QGraphicsScene *graphicsScene = new QGraphicsScene();
        showModelProj(graphicsScene, &modelProj);
        ui->graphicsView->setScene(graphicsScene);
    }
}

//void MainWindow::on_pushButton_2_clicked()
//{
    //int errorCode = 0;
    //operParamsT operParams;

    //double scaleValue = ui->spinBoxScale->value();
    //if (scaleValue != 0)
    //{
    //    operParams = {SCALE, scaleValue};
    //}
//}
