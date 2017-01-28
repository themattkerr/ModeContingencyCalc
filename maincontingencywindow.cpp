#include "maincontingencywindow.h"
#include "ui_maincontingencywindow.h"

MainContingencyWindow::MainContingencyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainContingencyWindow)
{
    ui->setupUi(this);

    setupGUI();
    adjustSize();
}

MainContingencyWindow::~MainContingencyWindow()
{
    delete ui;
}

//========GUI Setup Functions =============================================
void MainContingencyWindow::setupGUI()
{
    m_nRowsToShow = 1;
    showRows();
    setupComboBoxQList();
    setupCustomLineEditQList();
    setupDateEditQList();
    setupDaysSpinBoxQList();
    setupAORadioButtonQList();
    setupClosingRadioButtonQList();
    setupHardDateRadioButtonQList();
    setupBusinessDaysCheckboxQList();

    loadTitles();
    hideCustomLineEdits();
    loadDefaults();
}
void MainContingencyWindow::hideCustomLineEdits()
{
    for(int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
        m_allCustomLineEdits[iii]->hide();
    }
}

void MainContingencyWindow::loadDefaults()
{
    m_contData.setDefaults();
    refreshFields();

}
void MainContingencyWindow::loadTitles()
{
    QStringList strlTitles;
    strlTitles
                << BLANK
                << EARNEST_MONEY_TITLE
                << CONDITION_REPORT_TITLE
                << FINANCING_TITLE
                << APPRAISAL_TITLE
                << INSPECTION_TITLE
                << RADON_TITLE
                << WELL_SEPTIC_TITLE
                << FINAL_WALKTHROUGH_TITLE
                << HOME_INSURENCE_TITLE
                << CONDO_DOCS_TITLE
                << COMFORT_LETTER_TITLE
                << ENVIRONMENTAL_TEST_TITLE
                << ATTORNEY_REVIEW_TITLE
                << SEWER_TITLE
                << ZONING_TITLE
                << SURVEY_TITLE
                << RATE_LOCK_TITLE
                << CUSTOM_TITLE;


    for (int iii =0; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
        m_allComboxes[iii]->addItems(strlTitles);
    }
}
void MainContingencyWindow::refreshFields()
{
    // call a function here to pull and save custom text from the gui

    ui->dateEditAODate->setDate(m_contData.getAODate());
    ui->spinBoxDaysToClosing->setValue(m_contData.getDaysClosing());
    ui->dateEditClosingDate->setDate(m_contData.getClosingDate());
    ui->lineEditPropertyAddress->setText(m_contData.getPropertyAddress());
    ui->lineEditMLSNum->setText(m_contData.getMLSNumber());
    ui->lineEditEarnestMoney->setText(m_contData.getEarnestMoneyAmout());
    ui->lineEditListingBrokerTrustName->setText(m_contData.getListingBrokerTrustName());

    for(int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
        if(m_contData.getContingencyTitle(iii) == CUSTOM_TITLE)
            m_allCustomLineEdits[iii]->show();
        else
            m_allCustomLineEdits[iii]->hide();

        m_allComboxes[iii]->setCurrentText(m_contData.getContingencyTitle(iii));
        m_allDateEdit[iii]->setDate(m_contData.getDateOfContingency(iii) );
        m_allSpinBoxes[iii]->setValue(m_contData.getNumOfDays(iii));

        m_allAORadioButtons[iii]->setChecked(false);
        m_allClosingRadioButtons[iii]->setChecked(false);
        m_allHardDateRadioButtons[iii]->setChecked(false);

        switch (m_contData.getCalcFrom(iii)) {
        case CALC_FROM_AO:          {m_allAORadioButtons[iii]->setChecked(true);        break;}
        case CALC_FROM_CLOSING:     {m_allClosingRadioButtons[iii]->setChecked(true);   break;}
        case HARD_DATE:             {m_allHardDateRadioButtons[iii]->setChecked(true);  break;}

            break;
        default:
            break;
        }

        m_allBusinessDaysCheckBoxes[iii]->setChecked(m_contData.getUseBusinessDays(iii));
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
void MainContingencyWindow::setupCustomLineEditQList()
{
    m_allCustomLineEdits.append(ui->cont1CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont2CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont3CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont4CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont5CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont6CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont7CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont8CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont9CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont10CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont11CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont12CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont13CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont14CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont15CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont16CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont17CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont18CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont19CustomLineEdit);
    m_allCustomLineEdits.append(ui->cont20CustomLineEdit);
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

//======== Signal/Slot Functions =========================

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

void MainContingencyWindow::on_dateEditAODate_userDateChanged(const QDate &date)
{
    m_contData.enterAODate(date);
    refreshFields();
}

void MainContingencyWindow::on_pushButtonSetToToday_clicked()
{
    m_contData.enterAODate(QDate::currentDate());
    refreshFields();
}

void MainContingencyWindow::on_spinBoxDaysToClosing_valueChanged(int arg1)
{
    m_contData.enterDaysClosing(arg1);
    refreshFields();
}

void MainContingencyWindow::on_dateEditClosingDate_userDateChanged(const QDate &date)
{
    m_contData.enterClosingDate(date);
    refreshFields();
}

void MainContingencyWindow::on_lineEditPropertyAddress_editingFinished()
{
    m_contData.enterPropertyAddress(ui->lineEditPropertyAddress->text());
    refreshFields();
}

void MainContingencyWindow::on_lineEditMLSNum_editingFinished()
{
    m_contData.enterMLSNumber(ui->lineEditMLSNum->text());
    refreshFields();
}

void MainContingencyWindow::on_lineEditEarnestMoney_editingFinished()
{
    m_contData.enterEarnestMoneyAmount(ui->lineEditEarnestMoney->text());
    refreshFields();
}

void MainContingencyWindow::on_lineEditListingBrokerTrustName_editingFinished()
{
    m_contData.enterListingBrokerTrustName(ui->lineEditListingBrokerTrustName->text());
    refreshFields();
}


void MainContingencyWindow::on_cont1TitleComboBox_activated(const QString &arg1)
{
    int nContingency1Index = 0;
    m_contData.enterContingencyTitle(arg1, nContingency1Index);
    refreshFields();
}
void MainContingencyWindow::on_cont2TitleComboBox_activated(const QString &arg1)
{
    int nContingency2Index = 1;
    m_contData.enterContingencyTitle(arg1, nContingency2Index);
    refreshFields();
}
void MainContingencyWindow::on_cont3TitleComboBox_activated(const QString &arg1)
{
    int nContingency3Index = 2;
    m_contData.enterContingencyTitle(arg1, nContingency3Index);
    refreshFields();
}
void MainContingencyWindow::on_cont4TitleComboBox_activated(const QString &arg1)
{
    int nContingency4Index = 3;
    m_contData.enterContingencyTitle(arg1, nContingency4Index);
    refreshFields();
}
void MainContingencyWindow::on_cont5TitleComboBox_activated(const QString &arg1)
{
    int nContingency5Index = 4;
    m_contData.enterContingencyTitle(arg1, nContingency5Index);
    refreshFields();
}
void MainContingencyWindow::on_cont6TitleComboBox_activated(const QString &arg1)
{
    int nContingency6Index = 5;
    m_contData.enterContingencyTitle(arg1, nContingency6Index);
    refreshFields();
}
void MainContingencyWindow::on_cont7TitleComboBox_activated(const QString &arg1)
{
    int nContingency7Index = 6;
    m_contData.enterContingencyTitle(arg1, nContingency7Index);
    refreshFields();
}
void MainContingencyWindow::on_cont8TitleComboBox_activated(const QString &arg1)
{
    int nContingency8Index = 7;
    m_contData.enterContingencyTitle(arg1, nContingency8Index);
    refreshFields();
}
void MainContingencyWindow::on_cont9TitleComboBox_activated(const QString &arg1)
{
    int nContingency9Index = 8;
    m_contData.enterContingencyTitle(arg1, nContingency9Index);
    refreshFields();
}
void MainContingencyWindow::on_cont10TitleComboBox_activated(const QString &arg1)
{
    int nContingency10Index = 9;
    m_contData.enterContingencyTitle(arg1, nContingency10Index);
    refreshFields();
}
void MainContingencyWindow::on_cont11TitleComboBox_activated(const QString &arg1)
{
    int nContingency11Index = 10;
    m_contData.enterContingencyTitle(arg1, nContingency11Index);
    refreshFields();
}
void MainContingencyWindow::on_cont12TitleComboBox_activated(const QString &arg1)
{
    int nContingency12Index = 11;
    m_contData.enterContingencyTitle(arg1, nContingency12Index);
    refreshFields();
}
void MainContingencyWindow::on_cont13TitleComboBox_activated(const QString &arg1)
{
    int nContingency13Index = 12;
    m_contData.enterContingencyTitle(arg1, nContingency13Index);
    refreshFields();
}
void MainContingencyWindow::on_cont14TitleComboBox_activated(const QString &arg1)
{
    int nContingency14Index = 13;
    m_contData.enterContingencyTitle(arg1, nContingency14Index);
    refreshFields();
}
void MainContingencyWindow::on_cont15TitleComboBox_activated(const QString &arg1)
{
    int nContingency15Index = 14;
    m_contData.enterContingencyTitle(arg1, nContingency15Index);
    refreshFields();
}
void MainContingencyWindow::on_cont16TitleComboBox_activated(const QString &arg1)
{
    int nContingency16Index = 15;
    m_contData.enterContingencyTitle(arg1, nContingency16Index);
    refreshFields();
}
void MainContingencyWindow::on_cont17TitleComboBox_activated(const QString &arg1)
{
    int nContingency17Index = 16;
    m_contData.enterContingencyTitle(arg1, nContingency17Index);
    refreshFields();
}
void MainContingencyWindow::on_cont18TitleComboBox_activated(const QString &arg1)
{
    int nContingency18Index = 17;
    m_contData.enterContingencyTitle(arg1, nContingency18Index);
    refreshFields();
}
void MainContingencyWindow::on_cont19TitleComboBox_activated(const QString &arg1)
{
    int nContingency19Index = 18;
    m_contData.enterContingencyTitle(arg1, nContingency19Index);
    refreshFields();
}
void MainContingencyWindow::on_cont20TitleComboBox_activated(const QString &arg1)
{
    int nContingency20Index = 19;
    m_contData.enterContingencyTitle(arg1, nContingency20Index);
    refreshFields();
}


void MainContingencyWindow::on_cont1dateEdit_userDateChanged(const QDate &date)
{
    int nContingency1Index = 0;
    m_contData.enterDateOfContingency(date, nContingency1Index);
    refreshFields();
}
void MainContingencyWindow::on_cont2dateEdit_userDateChanged(const QDate &date)
{
    int nContingency2Index = 1;
    m_contData.enterDateOfContingency(date, nContingency2Index);
    refreshFields();
}
void MainContingencyWindow::on_cont3dateEdit_userDateChanged(const QDate &date)
{
    int nContingency3Index = 2;
    m_contData.enterDateOfContingency(date, nContingency3Index);
    refreshFields();
}
void MainContingencyWindow::on_cont4dateEdit_userDateChanged(const QDate &date)
{
    int nContingency4Index = 3;
    m_contData.enterDateOfContingency(date, nContingency4Index);
    refreshFields();
}
void MainContingencyWindow::on_cont5dateEdit_userDateChanged(const QDate &date)
{
    int nContingency5Index = 4;
    m_contData.enterDateOfContingency(date, nContingency5Index);
    refreshFields();
}
void MainContingencyWindow::on_cont6dateEdit_userDateChanged(const QDate &date)
{
    int nContingency6Index = 5;
    m_contData.enterDateOfContingency(date, nContingency6Index);
    refreshFields();
}
void MainContingencyWindow::on_cont7dateEdit_userDateChanged(const QDate &date)
{
    int nContingency7Index = 6;
    m_contData.enterDateOfContingency(date, nContingency7Index);
    refreshFields();
}
void MainContingencyWindow::on_cont8dateEdit_userDateChanged(const QDate &date)
{
    int nContingency8Index = 7;
    m_contData.enterDateOfContingency(date, nContingency8Index);
    refreshFields();
}
void MainContingencyWindow::on_cont9dateEdit_userDateChanged(const QDate &date)
{
    int nContingency9Index = 8;
    m_contData.enterDateOfContingency(date, nContingency9Index);
    refreshFields();
}
void MainContingencyWindow::on_cont10dateEdit_userDateChanged(const QDate &date)
{
    int nContingency10Index = 9;
    m_contData.enterDateOfContingency(date, nContingency10Index);
    refreshFields();
}
void MainContingencyWindow::on_cont11dateEdit_userDateChanged(const QDate &date)
{
    int nContingency11Index = 10;
    m_contData.enterDateOfContingency(date, nContingency11Index);
    refreshFields();
}
void MainContingencyWindow::on_cont12dateEdit_userDateChanged(const QDate &date)
{
    int nContingency12Index = 11;
    m_contData.enterDateOfContingency(date, nContingency12Index);
    refreshFields();
}
void MainContingencyWindow::on_cont13dateEdit_userDateChanged(const QDate &date)
{
    int nContingency13Index = 12;
    m_contData.enterDateOfContingency(date, nContingency13Index);
    refreshFields();
}
void MainContingencyWindow::on_cont14dateEdit_userDateChanged(const QDate &date)
{
    int nContingency14Index = 13;
    m_contData.enterDateOfContingency(date, nContingency14Index);
    refreshFields();
}
void MainContingencyWindow::on_cont15dateEdit_userDateChanged(const QDate &date)
{
    int nContingency15Index = 14;
    m_contData.enterDateOfContingency(date, nContingency15Index);
    refreshFields();
}
void MainContingencyWindow::on_cont16dateEdit_userDateChanged(const QDate &date)
{
    int nContingency16Index = 15;
    m_contData.enterDateOfContingency(date, nContingency16Index);
    refreshFields();
}
void MainContingencyWindow::on_cont17dateEdit_userDateChanged(const QDate &date)
{
    int nContingency17Index = 16;
    m_contData.enterDateOfContingency(date, nContingency17Index);
    refreshFields();
}
void MainContingencyWindow::on_cont18dateEdit_userDateChanged(const QDate &date)
{
    int nContingency18Index = 17;
    m_contData.enterDateOfContingency(date, nContingency18Index);
    refreshFields();
}
void MainContingencyWindow::on_cont19dateEdit_userDateChanged(const QDate &date)
{
    int nContingency19Index = 18;
    m_contData.enterDateOfContingency(date, nContingency19Index);
    refreshFields();
}
void MainContingencyWindow::on_cont20dateEdit_userDateChanged(const QDate &date)
{
    int nContingency20Index = 19;
    m_contData.enterDateOfContingency(date, nContingency20Index);
    refreshFields();
}
