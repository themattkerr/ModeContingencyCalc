#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->ProgramVersionLabel->setText(CURRENT_VERSION);
    ui->BetaBuildInfolabel->setText(BETA_BUILD_INFO);
    ui->CalculationsVersionLabel->setText(VERSION_OF_MATTCALCULATIONS);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
