#include "tabcreate.h"
#include "ui_tabcreate.h"
#include "tabwidget.h"
#include <QFileDialog>
#include <QMessageBox>

TabCreate::TabCreate(QWidget *parent,TabWidget *tabWidget) :
    QWidget(parent),
    ui(new Ui::TabCreate)
{
    ui->setupUi(this);
    m_tabWidget = tabWidget;
    connect (ui->spinRows, SIGNAL(valueChanged(int)), this, SLOT(onSpinRows(int)));
    connect (ui->spinColumns, SIGNAL(valueChanged(int)), this, SLOT(onSpinColumns(int)));
    connect (ui->randomButton, SIGNAL(clicked()), this, SLOT(onRandomButton()));
    connect (ui->noButton, SIGNAL(clicked()), this, SLOT(onNoButton()));
    connect (ui->minRandomBox, SIGNAL(valueChanged(int)), this, SLOT(onMinRandomSpin(int)));
    connect (ui->maxRandomBox, SIGNAL(valueChanged(int)), this, SLOT(onMaxRandomSpin(int)));
    connect (ui->csvButton, SIGNAL(clicked()), this, SLOT(onCsvButton()));
    connect (ui->xlsxButton, SIGNAL(clicked()), this, SLOT(onXlsxButton()));
    connect (ui->buttonBox, SIGNAL(accepted()), this, SLOT(onOkButton()));
}

TabCreate::~TabCreate()
{
    delete ui;
}

void TabCreate::onSpinRows(int arg1)
{
    m_rows = arg1;
}

void TabCreate::onSpinColumns(int arg1)
{
    m_columns = arg1;
}

void TabCreate::onRandomButton()
{
    m_is_random = true;
    ui->noButton->setChecked(false);
    ui->randomButton->setChecked(true);
}

void TabCreate::onNoButton()
{
    m_is_random = false;
    ui->randomButton->setChecked(false);
    ui->noButton->setChecked(true);
}

void TabCreate::onMinRandomSpin(int arg1)
{
    m_min_rand = arg1;
}

void TabCreate::onMaxRandomSpin(int arg1)
{
    m_max_rand = arg1;
}

void TabCreate::onCsvButton()
{
    if(m_is_csv) m_is_csv = false;
    else m_is_csv = true;
}

void TabCreate::onXlsxButton()
{
    if(m_is_xlsx) m_is_xlsx = false;
    else m_is_xlsx = true;
}

void TabCreate::onOkButton()
{
    QString fileName;
    if(!m_is_random)
    {
        m_min_rand = 0;
        m_max_rand = 1;
    }
    if(m_is_csv||m_is_xlsx)
    {
        bool stop = false;
        QMessageBox qMessageBox;
        QString message = "";
        if(m_rows<= 0)
        {
            message +="Le nombre de row doit être strictement superieur à 0 \n";
            stop = true;
        }
        if(m_columns<= 0)
        {
            message +="Le nombre de column doit être strictement superieur à 0 \n";
            stop = true;
        }
        if(m_min_rand>=m_max_rand)
        {
            message +="max rand doit être strictement superieur à min rand";
            stop = true;
        }
        if(stop)
        {
            qMessageBox.setText(message);
            qMessageBox.exec();
            return;
        }
        fileName = QFileDialog::getSaveFileName(this, "Save File", "../projetIHM/testData", "Excel Files");

        if(fileName == "")
        {
            QMessageBox qMessageBox;
            qMessageBox.setText("choisissez un nom");
            qMessageBox.exec();
            return;
        }
    }
    if(m_is_csv)
    {
       emit m_tabWidget->write_csv_file(fileName + ".csv",m_rows+1,m_columns,m_min_rand,m_max_rand);
        close();
    }
    if(m_is_xlsx)
    {
        emit m_tabWidget->write_xlsx_file(fileName + ".xlsx",m_rows+1,m_columns,m_min_rand,m_max_rand);
        close();
    }
    if(!m_is_csv && !m_is_xlsx)
    {
       QMessageBox qMessageBox;
       qMessageBox.setText("choisissez au moins un format");
       qMessageBox.exec();
    }

}
