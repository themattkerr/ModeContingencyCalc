#include "maincontingencywindow.h"
#include "ui_maincontingencywindow.h"

MainContingencyWindow::MainContingencyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainContingencyWindow)
{
    ui->setupUi(this);
}

MainContingencyWindow::~MainContingencyWindow()
{
    delete ui;
}
