#include "reportoutput.h"
#include "ui_reportoutput.h"


ReportOutput::ReportOutput(QWidget *parent, ContingencyData *contData, int *nReportType) :
    QDialog(parent),
    ui(new Ui::ReportOutput)
{
    ui->setupUi(this);

    m_OutData = *contData;
    m_nReportType = nReportType;

    setupGUI();
    copyContingenciesToArray();
    sortAscending();
    generateText();

    ui->textBrowser->setText(m_strOutputText);
    ui->textBrowser->setFont(ui->fontComboBox->font());
}

ReportOutput::~ReportOutput()
{
    delete ui;
}

void ReportOutput::on_pushButton_Close_clicked()
{
    this->close();
}
void ReportOutput::setupGUI()
{
    if(m_nReportType == 0)
        *m_nReportType = BUYERS;
    if(m_OutData.getPropertyAddress() != "")
        this->setWindowTitle(m_OutData.getPropertyAddress() + " - Milestone Report");
    else
        this->setWindowTitle("Milestone Report");

    switch (*m_nReportType) {
    case BUYERS:           { ui->radioButton_Buyers->setChecked(true); break;}
    case SELLERS:          { ui->radioButton_Sellers->setChecked(true); break;}
    case MILESTONES_ONLY:  { ui->radioButton_Milestones->setChecked(true); break;}
    }

}

void ReportOutput::copyContingenciesToArray()
{
    Contingency *x = 0;
    int nAdditionalIndex = MAX_NUM_CONTINGENCIES;
    for (int iii = 0; iii < MAX_NUM_CONTINGENCIES; iii++)
    {
       x = &m_contOutputArray[iii];
       x->m_strContingencyTitle         = m_OutData.getContingencyTitle(iii);
       x->m_strCustomText               = m_OutData.getCustomText(iii);
       x->m_dtDateOfContingency         = m_OutData.getDateOfContingency(iii);
       x->m_nCalcFrom                   = m_OutData.getCalcFrom(iii);
       x->m_nNumOfDays                  = m_OutData.getNumOfDays(iii);
       x->m_bUseBusinessDays            = m_OutData.getUseBusinessDays(iii);
       x->m_strReportInfoBuyer          = m_OutData.getReportInfoBuyer(iii);
       x->m_strReportInfoSeller         = m_OutData.getReportInfoSeller(iii);
       x->m_strDependantContingecyTitle = m_OutData.getDependantContingencyTitle(iii);
       x->m_strBusinessDayReasons.clear();

       x = 0;

    }

    x = &m_contOutputArray[nAdditionalIndex];

    x->m_strContingencyTitle = ACCEPTED_OFFER_TITLE;
    x->m_dtDateOfContingency = m_OutData.getAODate();
    x->m_nNumOfDays = 0;
    x->m_strReportInfoBuyer = ACCEPTED_OFFER_BUYER;
    x->m_strReportInfoSeller = ACCEPTED_OFFER_SELLER;
    x->m_nCalcFrom = HARD_DATE;
    x->m_bUseBusinessDays = 0;
    x->m_strCustomText = "";
    x->m_strBusinessDayReasons.clear();
    x->m_strDependantContingecyTitle.clear();

    nAdditionalIndex++;
    x = &m_contOutputArray[nAdditionalIndex];

    x->m_strContingencyTitle = CLOSING_TITLE;
    x->m_dtDateOfContingency = m_OutData.getClosingDate();
    x->m_nNumOfDays = m_OutData.getDaysClosing();
    x->m_strReportInfoBuyer = CLOSING_BUYER;
    x->m_strReportInfoSeller = CLOSING_SELLER;
    x->m_nCalcFrom = HARD_DATE;
    x->m_bUseBusinessDays = false;
    x->m_strCustomText.clear();
    x->m_strBusinessDayReasons.clear();
    x->m_strDependantContingecyTitle.clear();
}
void ReportOutput::sortAscending()
{
    Contingency Temp;
    int nLastContingency = MAX_NUM_CONTINGENCIES+ADDITIONALCONTINGENCIES;

    for(int iii = 0; iii < nLastContingency;iii++)
    {
        for(int jjj = 0; jjj < nLastContingency;jjj++)
        {
            if(m_contOutputArray[iii].m_strContingencyTitle != BLANK && m_contOutputArray[jjj].m_strContingencyTitle == BLANK)
            {
                Temp = m_contOutputArray[iii];
                m_contOutputArray[iii] = m_contOutputArray[jjj];
                m_contOutputArray[jjj] = Temp;
            }

            if((m_contOutputArray[iii].m_dtDateOfContingency < m_contOutputArray[jjj].m_dtDateOfContingency)
               && ( m_contOutputArray[iii].m_strContingencyTitle != BLANK))
            {
                Temp = m_contOutputArray[iii];
                m_contOutputArray[iii] = m_contOutputArray[jjj];
                m_contOutputArray[jjj] = Temp;
            }
            if((m_contOutputArray[iii].m_dtDateOfContingency == m_contOutputArray[jjj].m_dtDateOfContingency)
               && ( m_contOutputArray[iii].m_strContingencyTitle != BLANK))
            {
                if(m_contOutputArray[iii].m_strContingencyTitle < m_contOutputArray[jjj].m_strContingencyTitle)
                {
                    Temp = m_contOutputArray[iii];
                    m_contOutputArray[iii] = m_contOutputArray[jjj];
                    m_contOutputArray[jjj] = Temp;
                }
                if(m_contOutputArray[jjj].m_strContingencyTitle == CLOSING_TITLE )
                {
                    Temp = m_contOutputArray[iii];
                    m_contOutputArray[iii] = m_contOutputArray[jjj];
                    m_contOutputArray[jjj] = Temp;
                }
                if(m_contOutputArray[iii].m_strContingencyTitle == ACCEPTED_OFFER_TITLE )
                {
                    Temp = m_contOutputArray[iii];
                    m_contOutputArray[iii] = m_contOutputArray[jjj];
                    m_contOutputArray[jjj] = Temp;
                }
            }
        }
    }
    for(int iii = 0; iii < nLastContingency;iii++)
    {
        for(int jjj = 0; jjj < nLastContingency;jjj++)
        {
            if(m_contOutputArray[iii].m_strContingencyTitle == m_contOutputArray[jjj].m_strDependantContingecyTitle && iii > jjj && m_contOutputArray[iii].m_strContingencyTitle != BLANK)
            {
                Temp = m_contOutputArray[iii];
                m_contOutputArray[iii] = m_contOutputArray[jjj];
                m_contOutputArray[jjj] = Temp;
            }
        }
    }

}
void ReportOutput::generateText()
{
    Contingency *x = 0;
    m_strOutputText.clear();

    m_strOutputText.append("Offer Milestones: ");//.append("\n");
    if(m_OutData.getPropertyAddress() != "")
        m_strOutputText.append(m_OutData.getPropertyAddress());//.append("\n");
    if(m_OutData.getMLSNumber() != "" )
        m_strOutputText.append("\n").append("MLS #: ").append(m_OutData.getMLSNumber());
    if(*m_nReportType == MILESTONES_ONLY )
        if(m_OutData.getClientNames() != "")
            m_strOutputText.append("\n").append("Client(s): ").append(m_OutData.getClientNames() );
    m_strOutputText.append("\n\n");

    int nAllMilestones = MAX_NUM_CONTINGENCIES+ADDITIONALCONTINGENCIES;
    for(int iii = 0; iii < nAllMilestones; iii++)
    {
        x = &m_contOutputArray[iii];

        if(x->m_strContingencyTitle != BLANK)
        {
//            m_strOutputText.append("<b>");
            if(x->m_strContingencyTitle == CUSTOM_TITLE)
            {
                m_strOutputText.append(x->m_strCustomText).append("\n");
            }
            else {
                m_strOutputText.append(x->m_strContingencyTitle).append("\n");
            }
//            m_strOutputText.append("</b>");
            if(x->m_nCalcFrom != OTHER_CONT)
                m_strOutputText.append(x->m_dtDateOfContingency.toString(LONG_DATE_FORMAT));
            switch (x->m_nCalcFrom) {
                case CALC_FROM_AO:      { m_strOutputText.append("  (").append(QString::number(x->m_nNumOfDays,10));
                                            if(x->m_bUseBusinessDays)
                                                m_strOutputText.append(" business");
                                            m_strOutputText.append(" days from acceptance)\n");
                                            break;
                                        }
                case CALC_FROM_CLOSING: { m_strOutputText.append("  (").append(QString::number(x->m_nNumOfDays,10));
                                            if(x->m_bUseBusinessDays)
                                                    m_strOutputText.append(" business");
                                            m_strOutputText.append(" days from closing)\n");
                                            break;
                                        }
                case HARD_DATE:         { m_strOutputText.append("\n"); break;}

                case OTHER_CONT:      { m_strOutputText.append("(").append(QString::number(x->m_nNumOfDays,10));
                                            if(x->m_bUseBusinessDays)
                                                m_strOutputText.append(" business");
                                            m_strOutputText.append(" days from the satisfaction of ");
                                                    m_strOutputText.append(x->m_strDependantContingecyTitle).append(")\n");
                                            m_strOutputText.append(AddBlankLine("Satisfaction Date")).append("\n");
                                            m_strOutputText.append(AddBlankLine("Deadline Date")).append("\n");
                                            break;
                                        }

                break;
            default:
                break;

                }
            if(*m_nReportType == BUYERS)
                m_strOutputText.append(x->m_strReportInfoBuyer).append("\n");
            if(*m_nReportType == SELLERS)
                m_strOutputText.append(x->m_strReportInfoSeller).append("\n");
            if(*m_nReportType == MILESTONES_ONLY)
            {
                if (x->m_strContingencyTitle == CLOSING_TITLE )
                {
                    m_strOutputText.append(AddBlankLine("Location") ).append("\n");
                    m_strOutputText.append(AddBlankLine("Time") ).append("\n");

                    //  <=========================  This is where you put the blank lines!!! ======================================================================<<<
                }
            }

            m_strOutputText.append("\n");
        }
    }
    if (*m_nReportType != MILESTONES_ONLY)
        m_strOutputText.append("\n\n").append(DISCLAIMER );
}

QString ReportOutput::AddBlankLine(QString strInputText)
{
    int nMaxLength = 33;
    if(strInputText.length() > nMaxLength || strInputText.length() < 0 )
        return "Error: Input string length";

    QString strOutputText = strInputText;
    strOutputText.append(": ");

    QString strLineMark = "_";
    int nLineMarksToAdd = nMaxLength - strInputText.length();
    for (int iii = 1; iii <= nLineMarksToAdd; iii++ )
    {
        strOutputText.append(strLineMark);
    }

    return strOutputText;
}




void ReportOutput::on_radioButton_Buyers_clicked()
{
    *m_nReportType = BUYERS;
    generateText();
    ui->textBrowser->setText(m_strOutputText);
}

void ReportOutput::on_radioButton_Sellers_clicked()
{
    *m_nReportType = SELLERS;
    generateText();
    ui->textBrowser->setText(m_strOutputText);
}

void ReportOutput::on_radioButton_Milestones_clicked()
{
    *m_nReportType = MILESTONES_ONLY;
    generateText();
    ui->textBrowser->setText(m_strOutputText);
}
