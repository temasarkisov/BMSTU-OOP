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


void MainWindow::on_pushButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                "Open file", QDir::homePath());

    string filePathStr = filePath.toStdString();

    int errorCode = getFileData(filePathStr);
    cout << "\n\n" << errorCode;
}

