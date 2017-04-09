#include "unsavedchangesdialog.h"
#include "ui_unsavedchangesdialog.h"

UnsavedChangesDialog::UnsavedChangesDialog(QWidget *parent, bool *bSave) :
    QDialog(parent),
    ui(new Ui::UnsavedChangesDialog)
{
    ui->setupUi(this);
    m_bSave = bSave;

}

UnsavedChangesDialog::~UnsavedChangesDialog()
{
    delete ui;
}

//void UnsavedChangesDialog::on_pushButton_clicked()
//{

//}

void UnsavedChangesDialog::on_pushButton_SaveNow_clicked()
{
    *m_bSave = true;
    this->close();
}

void UnsavedChangesDialog::on_pushButton_DoNotSave_clicked()
{
    *m_bSave = false;
    this->close();
}
