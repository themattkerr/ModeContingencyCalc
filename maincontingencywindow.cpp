#include "maincontingencywindow.h"
#include "ui_maincontingencywindow.h"

MainContingencyWindow::MainContingencyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainContingencyWindow)
{
    ui->setupUi(this);
    m_nRowsToShow = 1;
    showRows();
    setupComboBoxQList();
    loadTitles();

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
    QStringList strlTitles;
    strlTitles << "-" << "Financing" << "Appraisal" << "Earnest Money" << "Inspection" << "Final Walk-through" << "Radon Test" << "Condo Docs" <<
                  "Well & Septic" << "Comfort Letter" << "Environmental Test" <<
                  "Attorney Review" << "Home-Owner Insurance" << "Condition Report" <<
                  "Sewer" << "Zoning" << "Survey" << "Loan Rate Lock Expiration";

    for (int iii =0; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
        m_allComboxes[iii]->addItems(strlTitles);
    }


}
void MainContingencyWindow::showRows()
{
    if (m_nRowsToShow == 1)
        ui->pushButton_Show_5_Fewer->hide();
    if (m_nRowsToShow == 4)
        ui->pushButton_Show_5_More->hide();
    if (m_nRowsToShow == 2 || m_nRowsToShow == 3)
        {ui->pushButton_Show_5_Fewer->show(); ui->pushButton_Show_5_More->show();}

    ui->Row2->hide();
    ui->Row3->hide();
    ui->Row4->hide();
    adjustSize();
    switch (m_nRowsToShow) {
    case 4: ui->Row4->show();
    case 3: ui->Row3->show();
    case 2: ui->Row2->show();
    case 1: ui->Row1->show();

        break;
    default:
            ui->Row2->hide();
            ui->Row3->hide();
            ui->Row4->hide();
        break;
    }
    adjustSize();
}
void MainContingencyWindow::setupComboBoxQList()
{
    m_allComboxes.append(ui->cont1TitleComboBox);
    m_allComboxes.append(ui->cont2TitleComboBox);
    m_allComboxes.append(ui->cont3TitleComboBox);
    m_allComboxes.append(ui->cont4TitleComboBox);
    m_allComboxes.append(ui->cont5TitleComboBox);
    m_allComboxes.append(ui->cont6TitleComboBox);
    m_allComboxes.append(ui->cont7TitleComboBox);
    m_allComboxes.append(ui->cont8TitleComboBox);
    m_allComboxes.append(ui->cont9TitleComboBox);
    m_allComboxes.append(ui->cont10TitleComboBox);
    m_allComboxes.append(ui->cont11TitleComboBox);
    m_allComboxes.append(ui->cont12TitleComboBox);
    m_allComboxes.append(ui->cont13TitleComboBox);
    m_allComboxes.append(ui->cont14TitleComboBox);
    m_allComboxes.append(ui->cont15TitleComboBox);
    m_allComboxes.append(ui->cont16TitleComboBox);
    m_allComboxes.append(ui->cont17TitleComboBox);
    m_allComboxes.append(ui->cont18TitleComboBox);
    m_allComboxes.append(ui->cont19TitleComboBox);
    m_allComboxes.append(ui->cont20TitleComboBox);
}

void setupDateEditQList()
{

}

void setupDaysSpinBoxQList()
{

}


void setupAORadioButtonQList()
{

}

void setupClosingRadioButtonQList()
{

}

void setupHardDateRadioButtonQList()
{

}

void setupBusinessDaysCheckboxQList()
{

}


void MainContingencyWindow::on_pushButton_Show_5_More_clicked()
{
    m_nRowsToShow++;
    if (m_nRowsToShow > 4)
        m_nRowsToShow = 4;
    showRows();
}

void MainContingencyWindow::on_pushButton_Show_5_Fewer_clicked()
{
    m_nRowsToShow--;
    if(m_nRowsToShow < 1)
        m_nRowsToShow = 1;
    showRows();
}
