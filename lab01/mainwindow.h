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
#include "modeloperations.h"
#include "modelshow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    modelT model;
    modelProjT modelProj;
    char *fileName;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonSelectFile_clicked();

    void on_buttonProgress_clicked();

    void on_buttonRefresh_clicked();

    void on_buttonShow_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
