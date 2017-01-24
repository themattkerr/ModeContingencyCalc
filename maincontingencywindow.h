#ifndef MAINCONTINGENCYWINDOW_H
#define MAINCONTINGENCYWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainContingencyWindow;
}

class MainContingencyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainContingencyWindow(QWidget *parent = 0);
    ~MainContingencyWindow();

private:
    Ui::MainContingencyWindow *ui;
    void loadTitles();
    void setDefaults();
};

#endif // MAINCONTINGENCYWINDOW_H
