#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>

#include <iostream>
#include <fstream>
#include <string>

#include "ui_mainwindow.h"
#include "handler.h"
#include "dataprocessing.h"
#include "computation.h"

#define SCENE_WIDTH 500
#define SCENE_HEIGHT 500

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    modelT model;
    modelProjT modelProj;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void uploadModelWithFileData();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
