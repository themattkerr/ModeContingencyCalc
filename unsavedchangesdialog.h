#ifndef UNSAVEDCHANGESDIALOG_H
#define UNSAVEDCHANGESDIALOG_H

#include <QDialog>

namespace Ui {
class UnsavedChangesDialog;
}

class UnsavedChangesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UnsavedChangesDialog(QWidget *parent = 0, bool *bSave = 0);
    ~UnsavedChangesDialog();

private slots:
//    void on_pushButton_clicked();

    void on_pushButton_SaveNow_clicked();

    void on_pushButton_DoNotSave_clicked();

private:
    Ui::UnsavedChangesDialog *ui;

    bool *m_bSave = 0;
};

#endif // UNSAVEDCHANGESDIALOG_H
