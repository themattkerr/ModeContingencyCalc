#include "maincontingencywindow.h"
#include "ui_maincontingencywindow.h"

MainContingencyWindow::MainContingencyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainContingencyWindow)
{
    ui->setupUi(this);
    //ui->Row1->hide();
    //ui->Row2->hide();
    //ui->Row3->hide();
    //ui->Row4->hide();
   // ui->pushButton_Show6Thru10->hide();

    adjustSize();
}

MainContingencyWindow::~MainContingencyWindow()
{
    delete ui;
}
void MainContingencyWindow::setDefaults()
{

}
void MainContingencyWindow::loadTitles()
{

}
