
// File includes ------------------------------------------
#include "CSVImporterDialog.h"
#include "ui_CSVImporterDialog.h"

// Project includes
#include "DatabaseManager.h"
#include "Exception.h"

// Qt includes --------------------------------------------
#include <QFileDialog>
#include <QDebug>

//-----------------------------------------------------------------------------------------------------------------------------

CSVImporterDialog::CSVImporterDialog(DatabaseManager *databaseManager,
                                     QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::CSVImporterDialog)
  , m_DatabaseManager(databaseManager)
  , m_CSVFilename()
{
  ui->setupUi(this);
}

//-----------------------------------------------------------------------------------------------------------------------------

CSVImporterDialog::~CSVImporterDialog()
{
    delete ui;
}

//-----------------------------------------------------------------------------------------------------------------------------

void CSVImporterDialog::showEvent(QShowEvent *)
{
  if(m_CSVFilename.isEmpty() == false)
    return;

  m_CSVFilename = QFileDialog::getOpenFileName(this,
                                               "Select the CSV file",
                                               QString(),
                                               "*.csv");
  if(m_CSVFilename.isEmpty())
  {
    hide();
    return;
  }

  loadCSV();
}

//-----------------------------------------------------------------------------------------------------------------------------

void CSVImporterDialog::loadCSV()
{
  QFile qFile(m_CSVFilename);
  if (qFile.open(QIODevice::ReadOnly) == false)
    throw  Exception(qFile.errorString());

  m_QStringList_Header.clear();
  m_QMap_Data.clear();

  m_QStringList_Header = QString(qFile.readLine()).split(',');

  while (qFile.atEnd() == false)
  {
    QStringList qStringList_Line = QString(qFile.readLine()).split(',');
    for (int i = 0; i < qStringList_Line.size(); i++)
      m_QMap_Data[m_QStringList_Header.at(i)].append(qStringList_Line.at(i));
  }

  updateGui();
}

//-----------------------------------------------------------------------------------------------------------------------------

void CSVImporterDialog::updateGui()
{
  updateGui_ImportSelection();
  updateGui_ImportData();
}

//-----------------------------------------------------------------------------------------------------------------------------

void CSVImporterDialog::updateGui_ImportSelection()
{
  ui->m_QListWidget_ImportSelection->clear();

  foreach (const QString &header, m_QStringList_Header)
  {
    // Skip Time
    if(header == m_QStringList_Header.first())
      continue;

    QListWidgetItem *qListWidgetItem = new QListWidgetItem(header,
                                                           ui->m_QListWidget_ImportSelection);
    ui->m_QListWidget_ImportSelection->addItem(qListWidgetItem);
  }
}

//-----------------------------------------------------------------------------------------------------------------------------

void CSVImporterDialog::updateGui_ImportData()
{

}



