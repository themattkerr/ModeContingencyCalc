#ifndef MAINCONTINGENCYWINDOW_H
#define MAINCONTINGENCYWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QComboBox>

namespace Ui {
class MainContingencyWindow;
}

class MainContingencyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainContingencyWindow(QWidget *parent = 0);
    ~MainContingencyWindow();

private slots:
    void on_pushButton_Show_5_More_clicked();

    void on_pushButton_Show_5_Fewer_clicked();

private:
    Ui::MainContingencyWindow *ui;
    void loadTitles();
    void setDefaults();
    void showRows();
    void setupComboBoxQList();
    QList <QComboBox*> m_allComboxes;
    int     m_nRowsToShow;

};

#endif // MAINCONTINGENCYWINDOW_H
