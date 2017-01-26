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
    setupDateEditQList();
    setupDaysSpinBoxQList();
    setupAORadioButtonQList();
    setupClosingRadioButtonQList();
    setupHardDateRadioButtonQList();
    setupBusinessDaysCheckboxQList();

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

void MainContingencyWindow::setupDateEditQList()
{
    m_allDateEdit.append(ui->cont1dateEdit);
    m_allDateEdit.append(ui->cont2dateEdit);
    m_allDateEdit.append(ui->cont3dateEdit);
    m_allDateEdit.append(ui->cont4dateEdit);
    m_allDateEdit.append(ui->cont5dateEdit);
    m_allDateEdit.append(ui->cont6dateEdit);
    m_allDateEdit.append(ui->cont7dateEdit);
    m_allDateEdit.append(ui->cont8dateEdit);
    m_allDateEdit.append(ui->cont9dateEdit);
    m_allDateEdit.append(ui->cont10dateEdit);
    m_allDateEdit.append(ui->cont11dateEdit);
    m_allDateEdit.append(ui->cont12dateEdit);
    m_allDateEdit.append(ui->cont13dateEdit);
    m_allDateEdit.append(ui->cont14dateEdit);
    m_allDateEdit.append(ui->cont15dateEdit);
    m_allDateEdit.append(ui->cont16dateEdit);
    m_allDateEdit.append(ui->cont17dateEdit);
    m_allDateEdit.append(ui->cont18dateEdit);
    m_allDateEdit.append(ui->cont19dateEdit);
    m_allDateEdit.append(ui->cont20dateEdit);
}

void MainContingencyWindow::setupDaysSpinBoxQList()
{
    m_allSpinBoxes.append(ui->cont1DaysSpinBox);
    m_allSpinBoxes.append(ui->cont2DaysSpinBox);
    m_allSpinBoxes.append(ui->cont3DaysSpinBox);
    m_allSpinBoxes.append(ui->cont4DaysSpinBox);
    m_allSpinBoxes.append(ui->cont5DaysSpinBox);
    m_allSpinBoxes.append(ui->cont6DaysSpinBox);
    m_allSpinBoxes.append(ui->cont7DaysSpinBox);
    m_allSpinBoxes.append(ui->cont8DaysSpinBox);
    m_allSpinBoxes.append(ui->cont9DaysSpinBox);
    m_allSpinBoxes.append(ui->cont10DaysSpinBox);
    m_allSpinBoxes.append(ui->cont11DaysSpinBox);
    m_allSpinBoxes.append(ui->cont12DaysSpinBox);
    m_allSpinBoxes.append(ui->cont13DaysSpinBox);
    m_allSpinBoxes.append(ui->cont14DaysSpinBox);
    m_allSpinBoxes.append(ui->cont15DaysSpinBox);
    m_allSpinBoxes.append(ui->cont16DaysSpinBox);
    m_allSpinBoxes.append(ui->cont17DaysSpinBox);
    m_allSpinBoxes.append(ui->cont18DaysSpinBox);
    m_allSpinBoxes.append(ui->cont19DaysSpinBox);
    m_allSpinBoxes.append(ui->cont20DaysSpinBox);
}

void MainContingencyWindow::setupAORadioButtonQList()
{
    m_allAORadioButtons.append(ui->cont1FromAOradioButton);
    m_allAORadioButtons.append(ui->cont2FromAOradioButton);
    m_allAORadioButtons.append(ui->cont3FromAOradioButton);
    m_allAORadioButtons.append(ui->cont4FromAOradioButton);
    m_allAORadioButtons.append(ui->cont5FromAOradioButton);
    m_allAORadioButtons.append(ui->cont6FromAOradioButton);
    m_allAORadioButtons.append(ui->cont7FromAOradioButton);
    m_allAORadioButtons.append(ui->cont8FromAOradioButton);
    m_allAORadioButtons.append(ui->cont9FromAOradioButton);
    m_allAORadioButtons.append(ui->cont10FromAOradioButton);
    m_allAORadioButtons.append(ui->cont11FromAOradioButton);
    m_allAORadioButtons.append(ui->cont12FromAOradioButton);
    m_allAORadioButtons.append(ui->cont13FromAOradioButton);
    m_allAORadioButtons.append(ui->cont14FromAOradioButton);
    m_allAORadioButtons.append(ui->cont15FromAOradioButton);
    m_allAORadioButtons.append(ui->cont16FromAOradioButton);
    m_allAORadioButtons.append(ui->cont17FromAOradioButton);
    m_allAORadioButtons.append(ui->cont18FromAOradioButton);
    m_allAORadioButtons.append(ui->cont19FromAOradioButton);
    m_allAORadioButtons.append(ui->cont20FromAOradioButton);
}

void MainContingencyWindow::setupClosingRadioButtonQList()
{
    m_allClosingRadioButtons.append(ui->cont1FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont2FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont3FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont4FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont5FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont6FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont7FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont8FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont9FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont10FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont11FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont12FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont13FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont14FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont15FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont16FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont17FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont18FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont19FromClosingRadioButton);
    m_allClosingRadioButtons.append(ui->cont20FromClosingRadioButton);
}

void MainContingencyWindow::setupHardDateRadioButtonQList()
{
    m_allHardDateRadioButtons.append(ui->cont1HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont2HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont3HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont4HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont5HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont6HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont7HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont8HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont9HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont10HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont11HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont12HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont13HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont14HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont15HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont16HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont17HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont18HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont19HardDateRadioButton);
    m_allHardDateRadioButtons.append(ui->cont20HardDateRadioButton);

}

void MainContingencyWindow::setupBusinessDaysCheckboxQList()
{
    m_allBusinessDaysCheckBoxes.append(ui->cont1BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont2BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont3BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont4BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont5BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont6BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont7BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont8BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont9BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont10BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont11BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont12BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont13BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont14BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont15BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont16BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont17BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont18BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont19BusinessDayCheckBox);
    m_allBusinessDaysCheckBoxes.append(ui->cont20BusinessDayCheckBox);

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
