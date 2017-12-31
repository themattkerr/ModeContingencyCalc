#include "maincontingencywindow.h"
#include "ui_maincontingencywindow.h"

MainContingencyWindow::MainContingencyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainContingencyWindow)
{
    ui->setupUi(this);
    m_FileName = "";
    setupGUI();
    adjustSize();
    m_bUnsavedData = false;
    on_pushButton_Sort_Contingencies_clicked();
}

MainContingencyWindow::~MainContingencyWindow()
{
    if(m_bUnsavedData)
    {
        bool bSave = false;
        UnsavedChangesDialog SaveAndExit(this, &bSave);
        SaveAndExit.exec() ;
        if(bSave)
            on_actionSave_As_triggered();
    }
    delete ui;
}

//========GUI Setup Functions =============================================
void MainContingencyWindow::setupGUI()
{
    m_nRowsToShow = 2;
    showRows();
    setupComboBoxQList();
    setupCustomLineEditQList();
    setupDateEditQList();
    setupDateLabelQList();
    setupDaysSpinBoxQList();
    setupCalcFromQlists();
    setupBusinessDaysCheckboxQList();
    setupDepContComboboxesQList();

    setupTitles();
    loadTitles();

    loadCalcFrom();
    hideCustomLineEdits();
    loadDefaults();

    refreshComboBoxes();
    refreshDepContComboBoxes();
}

void MainContingencyWindow::dateErrorCheck()
{
    QDate dtTestDate;
    bool bShowAfterClosingErrorText = false;
    bool bShowBeforeAccepanceErrorText = false;
    QString strErrorList;
    QString strTemp;
    strErrorList.clear();
    strErrorList.append("Please confrim dates for the following:\n");

    for(int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
    if(m_contData.getContingencyTitle(iii) != BLANK)
    {
        if(m_contData.getCalcFrom(iii) == OTHER_CONT)
        {
            if(m_contData.getUseBusinessDays(iii))
                dtTestDate = dateBusinessDaysAway( m_contData.getDateOfContingency(iii), m_contData.getNumOfDays(iii), strTemp);
            else
                dtTestDate = m_contData.getDateOfContingency(iii).addDays(m_contData.getNumOfDays(iii) ) ;
        }
        else
            dtTestDate = m_contData.getDateOfContingency(iii);


        if(dtTestDate > m_contData.getClosingDate() )
        {
            bShowAfterClosingErrorText = true;
            strErrorList.append("->  ");
            if(m_contData.getContingencyTitle(iii) != CUSTOM_TITLE)
                strErrorList.append(m_contData.getContingencyTitle(iii)).append("\n");
            else
                strErrorList.append(m_contData.getCustomText(iii)).append("\n");
        }
        if(dtTestDate < m_contData.getAODate() )
        {
            bShowBeforeAccepanceErrorText = true;
            strErrorList.append("->  ");
            if(m_contData.getContingencyTitle(iii) != CUSTOM_TITLE)
                strErrorList.append(m_contData.getContingencyTitle(iii)).append("\n");
            else
                strErrorList.append(m_contData.getCustomText(iii)).append("\n");
        }
    }
    }
    if(bShowAfterClosingErrorText)
    {
        ui->label_Warning->show();
        ui->label_WarningMessage->show();
    }
    else
        ui->label_WarningMessage->hide();
    if(bShowBeforeAccepanceErrorText)
    {
        ui->label_Warning->show();
        ui->label_WarningBeforeAO->show();
    }
    else
        ui->label_WarningBeforeAO->hide();
    if(!(bShowAfterClosingErrorText || bShowBeforeAccepanceErrorText))
    {
        ui->label_Warning->hide();
        strErrorList.clear();
    }
    ui->label_ErrorList->setText(strErrorList);
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

void MainContingencyWindow::setupTitles()
{
    m_strlTitles.clear();
    m_strlTitles
                << BLANK
                << EARNEST_MONEY_TITLE
                << CONDITION_REPORT_TITLE
                << FINANCING_TITLE
                << APPRAISAL_TITLE
                << INSPECTION_TITLE
                << RADON_TITLE
                << WELL_TITLE
                << SEPTIC_TITLE
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
                << ORDER_TITLE_TITLE
                << HOA_DOCS_DELIVERY_TITLE
                << HOA_DOCS_REVIEW_TITLE
                << COVENANTS_RESTRICTIONS_DELIVERY_TITLE
                << COVENANTS_RESTRICTIONS_REVIEW_TITLE
                << CONDITION_REPORT_REVIEW_TITLE
                << CONDO_DOCS_REVIEW_TITLE
                << UTILITIES_TITLE
                << WATER_TEST_TITLE
                << CUSTOM_TITLE;
    m_strlTitles.removeAll("");
}

void MainContingencyWindow::editTitles(int nContingencyNum)
{
   if (m_allComboxes[nContingencyNum]->currentText() != m_contData.getContingencyTitle(nContingencyNum))
   {
       //if stored data is blank there is nothing to remove and you need put what was in the field into title list
       if (m_contData.getContingencyTitle(nContingencyNum) != BLANK &&
                m_contData.getContingencyTitle(nContingencyNum) != CUSTOM_TITLE)
            m_strlTitles << m_contData.getContingencyTitle(nContingencyNum);
       else
           m_strlTitles << (m_allComboxes[nContingencyNum]->currentText());
   }
   // Determine if the current text is a contingency and then Store it to data and make sure it cannot be used again
   if(((m_allComboxes[nContingencyNum]->currentText() != BLANK) &&
            m_allComboxes[nContingencyNum]->currentText() != CUSTOM_TITLE))
   {
       m_contData.enterContingencyTitle( m_allComboxes[nContingencyNum]->currentText(), nContingencyNum);
       m_strlTitles.removeAll (m_allComboxes[nContingencyNum]->currentText());
   }
   else
       m_contData.enterContingencyTitle(m_allComboxes[nContingencyNum]->currentText(), nContingencyNum);
   m_strlTitles.sort();
}


void MainContingencyWindow::loadTitles()
{
    for(int iii = 0 ; iii < MAX_NUM_CONTINGENCIES; iii ++)
    {
        m_strlTitles.removeAll("");
        m_allComboxes[iii]->clear();
        m_allComboxes[iii]->addItems(m_strlTitles);
        if(m_contData.getContingencyTitle(iii) != BLANK && m_contData.getContingencyTitle(iii) != CUSTOM_TITLE)
            m_allComboxes[iii]->insertItem(0, m_contData.getContingencyTitle(iii));
    }
}

void MainContingencyWindow::refreshComboBoxes()
{
    setupTitles();
    for(int iii = 0 ; iii < MAX_NUM_CONTINGENCIES ; iii ++ )
        editTitles(iii);
    loadTitles();
    for(int iii = 0 ; iii < MAX_NUM_CONTINGENCIES ; iii ++ )
    {
        m_allComboxes[iii]->setCurrentText(m_contData.getContingencyTitle(iii));
    }
}
//=======================================================================================
void MainContingencyWindow::setupDepContTitles()
{
    m_strlDependantContingencyTitle.clear();
    for(int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
        if(m_contData.getContingencyTitle(iii) != BLANK)
        {
            if(m_contData.getContingencyTitle(iii) == CUSTOM_TITLE)
                m_strlDependantContingencyTitle.append(m_contData.getCustomText(iii));
            else
                m_strlDependantContingencyTitle.append(m_contData.getContingencyTitle(iii));
         }
    }
}

void MainContingencyWindow::removeUsedDepTitles()
{
    for(int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
        if(m_contData.getDependantContingencyTitle(iii) != BLANK)
        {
              m_strlDependantContingencyTitle.removeAll(m_contData.getDependantContingencyTitle(iii));
         }
    }
    m_strlDependantContingencyTitle.removeAll("");
    m_strlDependantContingencyTitle.sort();
    m_strlDependantContingencyTitle.prepend(BLANK);
}

void MainContingencyWindow::setDepContComboBoxes()
{
    for(int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
          m_allDepContComboxes[iii]->clear();
          QStringList strlTemp = m_strlDependantContingencyTitle;
          strlTemp.removeAll(m_contData.getContingencyTitle(iii));
          strlTemp.removeAll("");
          strlTemp.prepend(m_contData.getDependantContingencyTitle(iii));
          m_allDepContComboxes[iii]->addItems(strlTemp);

          //m_allDepContComboxes[iii]->removeItem(m_contData.getContingencyTitle(iii));

          m_allDepContComboxes[iii]->setCurrentText(m_contData.getDependantContingencyTitle(iii));
    }
}
void MainContingencyWindow::refreshDepContComboBoxes()
{
    setupDepContTitles();
    removeUsedDepTitles();
    setDepContComboBoxes();
}

//========================================================================================

void MainContingencyWindow::loadCalcFrom()
{
    QStringList strlCalcFromList;
    strlCalcFromList
            << CALC_FROM_AO_TEXT
            << CALC_FROM_CLOSING_TEXT
            << HARD_DATE_TEXT
            << CALC_FROM_CONTINGENCY_TEXT ;
    for(int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
        m_allCalcFrom[iii]->addItems(strlCalcFromList);
    }
}

void MainContingencyWindow::refreshFields()
{
    //showRows();

    m_bUnsavedData = true;
    if( m_contData.getPropertyAddress() != "")
        this->setWindowTitle(m_contData.getPropertyAddress() + " - Mode RN Milestone Calculator");
    else
        this->setWindowTitle("Mode RN Milestone Calculator");

    ui->dateEditAODate->setDate(m_contData.getAODate());
    ui->spinBoxDaysToClosing->setValue(m_contData.getDaysClosing());
    ui->dateEditClosingDate->setDate(m_contData.getClosingDate());
    ui->lineEditClientNames->setText(m_contData.getClientNames() );
    ui->lineEditPropertyAddress->setText(m_contData.getPropertyAddress());
    ui->lineEditMLSNum->setText(m_contData.getMLSNumber());
    ui->lineEditEarnestMoney->setText(m_contData.getEarnestMoneyAmout());
    ui->lineEditListingBrokerTrustName->setText(m_contData.getListingBrokerTrustName());



    setupTitles();// if the title is not in the list it cannot be set to it
    loadTitles();
    for(int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
        if(m_contData.getContingencyTitle(iii) == CUSTOM_TITLE)
        {
            m_allCustomLineEdits[iii]->show();
        }
        else
            m_allCustomLineEdits[iii]->hide();
        if(m_contData.getContingencyTitle(iii) == BLANK)
        {
            m_allDateLabels[iii]->hide();
            m_allDateEdit[iii]->hide();
            m_allSpinBoxes[iii]->hide();
            m_allCalcFrom[iii]->hide();
            m_allDepContComboxes[iii]->hide();
            m_allBusinessDaysCheckBoxes[iii]->hide();
        }
        else {
            m_allDateLabels[iii]->show();
            m_allDateEdit[iii]->show();
            m_allSpinBoxes[iii]->show();
            m_allCalcFrom[iii]->show();
            m_allDepContComboxes[iii]->hide();
            m_allBusinessDaysCheckBoxes[iii]->show();
        }

        m_allCustomLineEdits[iii]->setText(m_contData.getCustomText(iii) );
        m_allComboxes[iii]->setCurrentText(m_contData.getContingencyTitle(iii));
        m_allDateEdit[iii]->setDate(m_contData.getDateOfContingency(iii) );
        m_allSpinBoxes[iii]->setValue(m_contData.getNumOfDays(iii));

       switch (m_contData.getCalcFrom(iii)) {
        case CALC_FROM_AO:          {m_allCalcFrom[iii]->setCurrentText(CALC_FROM_AO_TEXT);         break;}
        case CALC_FROM_CLOSING:     {m_allCalcFrom[iii]->setCurrentText(CALC_FROM_CLOSING_TEXT);    break;}
        case HARD_DATE:             {m_allCalcFrom[iii]->setCurrentText(HARD_DATE_TEXT );           break;}
        case OTHER_CONT:            {m_allCalcFrom[iii]->setCurrentText(CALC_FROM_CONTINGENCY_TEXT);
                                                           m_allDateLabels[iii]->hide();
                                                           m_allDateEdit[iii]->hide();
                                                           m_allDepContComboxes[iii]->show();
                                                           break;}

            break;
        default:
           m_allCalcFrom[iii]->setCurrentText("Error");
            break;
        }

        m_allBusinessDaysCheckBoxes[iii]->setChecked(m_contData.getUseBusinessDays(iii));

        loadDateLabels();


    }
    refreshComboBoxes();
    refreshDepContComboBoxes();

    dateErrorCheck();
}

void MainContingencyWindow::loadDateLabels()
{
    ui->label_AO_Date->setText(m_contData.getAODate().toString(LONG_DATE_FORMAT));
    ui->label_Closing_Date->setText(m_contData.getClosingDate().toString(LONG_DATE_FORMAT));

    for(int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
        m_allDateLabels[iii]->setText(m_contData.getDateOfContingency(iii).toString( LONG_DATE_FORMAT)  );
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
    //adjustSize();
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
            //adjustSize();
        break;
    }
   //adjustSize();
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
void MainContingencyWindow::setupDateLabelQList()
{
    m_allDateLabels.append(ui->cont1DateLabel);
    m_allDateLabels.append(ui->cont2DateLabel);
    m_allDateLabels.append(ui->cont3DateLabel);
    m_allDateLabels.append(ui->cont4DateLabel);
    m_allDateLabels.append(ui->cont5DateLabel);
    m_allDateLabels.append(ui->cont6DateLabel);
    m_allDateLabels.append(ui->cont7DateLabel);
    m_allDateLabels.append(ui->cont8DateLabel);
    m_allDateLabels.append(ui->cont9DateLabel);
    m_allDateLabels.append(ui->cont10DateLabel);
    m_allDateLabels.append(ui->cont11DateLabel);
    m_allDateLabels.append(ui->cont12DateLabel);
    m_allDateLabels.append(ui->cont13DateLabel);
    m_allDateLabels.append(ui->cont14DateLabel);
    m_allDateLabels.append(ui->cont15DateLabel);
    m_allDateLabels.append(ui->cont16DateLabel);
    m_allDateLabels.append(ui->cont17DateLabel);
    m_allDateLabels.append(ui->cont18DateLabel);
    m_allDateLabels.append(ui->cont19DateLabel);
    m_allDateLabels.append(ui->cont20DateLabel);
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

void MainContingencyWindow::setupCalcFromQlists()
{
    m_allCalcFrom.append(ui->cont1CalcFromComboBox);
    m_allCalcFrom.append(ui->cont2CalcFromComboBox);
    m_allCalcFrom.append(ui->cont3CalcFromComboBox);
    m_allCalcFrom.append(ui->cont4CalcFromComboBox);
    m_allCalcFrom.append(ui->cont5CalcFromComboBox);
    m_allCalcFrom.append(ui->cont6CalcFromComboBox);
    m_allCalcFrom.append(ui->cont7CalcFromComboBox);
    m_allCalcFrom.append(ui->cont8CalcFromComboBox);
    m_allCalcFrom.append(ui->cont9CalcFromComboBox);
    m_allCalcFrom.append(ui->cont10CalcFromComboBox);
    m_allCalcFrom.append(ui->cont11CalcFromComboBox);
    m_allCalcFrom.append(ui->cont12CalcFromComboBox);
    m_allCalcFrom.append(ui->cont13CalcFromComboBox);
    m_allCalcFrom.append(ui->cont14CalcFromComboBox);
    m_allCalcFrom.append(ui->cont15CalcFromComboBox);
    m_allCalcFrom.append(ui->cont16CalcFromComboBox);
    m_allCalcFrom.append(ui->cont17CalcFromComboBox);
    m_allCalcFrom.append(ui->cont18CalcFromComboBox);
    m_allCalcFrom.append(ui->cont19CalcFromComboBox);
    m_allCalcFrom.append(ui->cont20CalcFromComboBox);
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
void MainContingencyWindow::setupDepContComboboxesQList()
{
    m_allDepContComboxes.append(ui->cont1DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont2DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont3DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont4DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont5DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont6DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont7DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont8DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont9DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont10DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont11DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont12DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont13DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont14DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont15DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont16DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont17DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont18DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont19DepCont_comboBox);
    m_allDepContComboxes.append(ui->cont20DepCont_comboBox);
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
//--------------------Top field entry --------------------------
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
//void MainContingencyWindow::on_lineEditEarnestMoney_editingFinished()
//{
//    m_contData.enterEarnestMoneyAmount(ui->lineEditEarnestMoney->text());
//    refreshFields();
//}
void MainContingencyWindow::on_lineEditEarnestMoney_textChanged(const QString &arg1)
{
    m_contData.enterEarnestMoneyAmount(ui->lineEditEarnestMoney->text());
    refreshFields();
}
void MainContingencyWindow::on_lineEditListingBrokerTrustName_editingFinished()
{
    m_contData.enterListingBrokerTrustName(ui->lineEditListingBrokerTrustName->text());
    refreshFields();
}
// ------------ Contingency entry -------------------

void MainContingencyWindow::on_cont1TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont2TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont3TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont4TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont5TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont6TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont7TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont8TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont9TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont10TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont11TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont12TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont13TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont14TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont15TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont16TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont17TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont18TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont19TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}
void MainContingencyWindow::on_cont20TitleComboBox_activated(const QString &arg1)
{
    refreshComboBoxes();
    refreshFields();
}

void MainContingencyWindow::on_cont1CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 0;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont2CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 1;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont3CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 2;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont4CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 3;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont5CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 4;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont6CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 5;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont7CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 6;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont8CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 7;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont9CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 8;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont10CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 9;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont11CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 10;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont12CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 11;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont13CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 12;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont14CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 13;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont15CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 14;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont16CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 15;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont17CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 16;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont18CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 17;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont19CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 18;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont20CustomLineEdit_editingFinished()
{
    int nContingencyIndex = 19;
    m_contData.enterCustomText(m_allCustomLineEdits[nContingencyIndex]->text(), nContingencyIndex);
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



void MainContingencyWindow::on_cont1DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 0;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont2DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 1;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont3DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 2;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont4DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 3;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont5DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 4;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont6DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 5;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont7DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 6;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont8DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 7;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont9DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 8;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont10DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 9;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont11DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 10;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont12DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 11;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont13DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 12;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont14DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 13;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont15DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 14;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont16DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 15;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont17DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 16;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont18DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 17;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont19DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 18;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}
void MainContingencyWindow::on_cont20DaysSpinBox_valueChanged(int arg1)
{
    int nContingencyIndex = 19;
    m_contData.enterDays(arg1, nContingencyIndex);
    refreshFields();
}





void MainContingencyWindow::on_cont1CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 0;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont2CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 1;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont3CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 2;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont4CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 3;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont5CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 4;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont6CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 5;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont7CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 6;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont8CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 7;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont9CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 8;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont10CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 9;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont11CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 10;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont12CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 11;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont13CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 12;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont14CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 13;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont15CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 14;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont16CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 15;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont17CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 16;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont18CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 17;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont19CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 18;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::on_cont20CalcFromComboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 19;
    setCalcFrom(arg1, nContingencyIndex);
}
void MainContingencyWindow::setCalcFrom(QString arg1, int nContingencyIndex)
{
    if(arg1 == CALC_FROM_AO_TEXT)           {m_contData.setCalcType(CALC_FROM_AO, nContingencyIndex);       }
    if(arg1 == CALC_FROM_CLOSING_TEXT)      {m_contData.setCalcType(CALC_FROM_CLOSING, nContingencyIndex);  }
    if(arg1 == HARD_DATE_TEXT)              {m_contData.setCalcType(HARD_DATE, nContingencyIndex);          }
    if(arg1 == CALC_FROM_CONTINGENCY_TEXT)  {m_contData.setCalcType(OTHER_CONT, nContingencyIndex);         }
    if(arg1 != CALC_FROM_AO_TEXT && arg1 != CALC_FROM_CLOSING_TEXT && arg1 != HARD_DATE_TEXT && arg1 != CALC_FROM_CONTINGENCY_TEXT)
        m_contData.setCalcType(-1,nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont1BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 0;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont2BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 1;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont3BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 2;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont4BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 3;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont5BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 4;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont6BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 5;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont7BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 6;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont8BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 7;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont9BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 8;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont10BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 9;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont11BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 10;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont12BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 11;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont13BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 12;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont14BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 13;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont15BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 14;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont16BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 15;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont17BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 16;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont18BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 17;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont19BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 18;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont20BusinessDayCheckBox_clicked()
{
    int nContingencyIndex = 19;
    m_contData.setUseBusinessDays(m_allBusinessDaysCheckBoxes[nContingencyIndex]->isChecked(), nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont1DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 0;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}


void MainContingencyWindow::on_cont2DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 1;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont3DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 2;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont4DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 3;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont5DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 4;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont6DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 5;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont7DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 6;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont8DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 7;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont9DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 8;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont10DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 9;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont11DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 10;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont12DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 11;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont13DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 12;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont14DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 13;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont15DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 14;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont16DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 15;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont17DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 16;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont18DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 17;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont19DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 18;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}

void MainContingencyWindow::on_cont20DepCont_comboBox_activated(const QString &arg1)
{
    int nContingencyIndex = 19;
    m_contData.enterDependantContingencyTitle(arg1, nContingencyIndex);
    refreshFields();
}



void MainContingencyWindow::on_pushButton_Sort_Contingencies_clicked()
{
    m_contData.sortContingenciesAcending(MAX_NUM_CONTINGENCIES);
    refreshFields();
}

void MainContingencyWindow::on_pushButton_Generate_Report_clicked()
{
    refreshFields();
    ReportOutput *Report = new ReportOutput(this, &m_contData, &m_nReporType );
    Report->show();
}


void MainContingencyWindow::on_actionOpen_triggered()
{
    m_FileName = QFileDialog::getOpenFileName (this, tr("Open MileStoneFile"), "",tr("*.MDRN"));

    bool ok;
    QMessageBox openStatus;
    openStatus.setWindowTitle("");
    ok = openMilestoneFile(m_FileName, m_contData, &m_nReporType, &m_nRowsToShow );
    if(ok)
    {
        openStatus.setText("Open Successful!");
        m_bUnsavedData = false;
    }
    else
    {
        openStatus.setText("Open Failed!!!");
    }
    if(!m_bUnsavedData)
    {
        refreshFields();
        showRows();
    m_bUnsavedData = false;
    }
    openStatus.exec();
}

void MainContingencyWindow::on_actionSave_As_triggered()
{
    m_FileName = QFileDialog::getSaveFileName (this, tr("Save As MileStone File"), "",tr( "*.MDRN"));

            bool ok;
            QMessageBox SaveStatus;
            SaveStatus.setWindowTitle("");
            ok = saveMilestoneFile( m_FileName, m_contData, &m_nReporType, &m_nRowsToShow );
            if(ok)
            {
                SaveStatus.setText("Save Successful!");
                m_bUnsavedData = false;
            }
            else
            {
                SaveStatus.setText("File NOT saved.");
                SaveStatus.raise();
            }
            SaveStatus.exec();
}

void MainContingencyWindow::on_actionSave_triggered()
{
    if(m_FileName == "")
    {
      on_actionSave_As_triggered();
      return;
    }


    bool ok;
    QMessageBox SaveStatus;
    SaveStatus.setWindowTitle("");
    ok = saveMilestoneFile( m_FileName, m_contData, &m_nReporType , &m_nRowsToShow );
    if(ok)
    {
        SaveStatus.setText("Save Successful!");
        m_bUnsavedData = false;
    }
    else
    {
        SaveStatus.raise();
        SaveStatus.setText("File NOT saved.");
    }
    SaveStatus.exec();
}

void MainContingencyWindow::on_actionClear_All_triggered()
{
    m_contData.clearAll();
    refreshFields();
    showRows();

}

void MainContingencyWindow::on_actionReset_Defaults_triggered()
{
    m_contData.setDefaults();
    refreshFields();
    showRows();
}


void MainContingencyWindow::on_lineEditClientNames_editingFinished()
{
    m_contData.enterClientNames(ui->lineEditClientNames->text() );
    refreshFields();
    showRows();
}



void MainContingencyWindow::on_actionAbout_triggered()
{
    AboutDialog *x = new AboutDialog(this);
    x->exec();
    x = 0;
    delete x;
}
