
// File includes ------------------------------------------
#include "CSVImporterDialog.h"
#include "ui_CSVImporterDialog.h"

// Project includes
#include "Exception.h"
#include "Database/DatabaseManager.h"

// Qt includes --------------------------------------------
#include <QFileDialog>
#include <QDebug>
#include <QTimer>

const QString CSVImporterDialog::_CONST::CSV_HEADER::HEADER_TIME ("Time");

//-----------------------------------------------------------------------------------------------------------------------------

CSVImporterDialog::CSVImporterDialog(DatabaseManager *databaseManager,
                                     QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::CSVImporterDialog)
  , m_DatabaseManager(databaseManager)
  , m_CSVFilename()
  , m_QStringList_Header()
  , m_QMap_Data()
  , m_QStringList_HeaderSelected()
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
    QTimer::singleShot(0,
                       this,
                       SLOT(reject()));
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
  m_QStringList_HeaderSelected.clear();

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
  ui->m_QTreeWidget_ImportSelection->clear();
  m_QStringList_HeaderSelected.clear();

  foreach (const QString &header, m_QStringList_Header)
  {
    // Skip Time
    if(header == _CONST::CSV_HEADER::HEADER_TIME)
    {
      m_QStringList_HeaderSelected.append(header);
      continue;
    }

    // Get corresponding import settings
    CSVImporterSettings::Correspondance correspondance = m_CSVImporterSettings.GetSettingsByCSVHeader(header);

    QTreeWidgetItem *qTreeWidgetItem = new QTreeWidgetItem(ui->m_QTreeWidget_ImportSelection);
    qTreeWidgetItem->setText(0,
                             header);
    qTreeWidgetItem->setFlags(qTreeWidgetItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
    if(correspondance.m_Valid)
    {
      m_QStringList_HeaderSelected.append(header);
      qTreeWidgetItem->setCheckState(0,
                                     Qt::Checked);
      qTreeWidgetItem->setText(1,
                               correspondance.m_DatabaseColumnName);
    }
    else
    {
      qTreeWidgetItem->setCheckState(0,
                                     Qt::Unchecked);
      qTreeWidgetItem->setText(1,
                               "(not available)");
    }
    ui->m_QTreeWidget_ImportSelection->addTopLevelItem(qTreeWidgetItem);
  }

  ui->m_QTreeWidget_ImportSelection->resizeColumnToContents(0);
}

//-----------------------------------------------------------------------------------------------------------------------------

void CSVImporterDialog::updateGui_ImportData()
{
  ui->m_QTableWidget_ImportData->clear();
  m_QMap_Total_kWh.clear();

  // Set header
  ui->m_QTableWidget_ImportData->setColumnCount(m_QStringList_HeaderSelected.size());
  ui->m_QTableWidget_ImportData->setHorizontalHeaderLabels(m_QStringList_HeaderSelected);

  for (int column=0; column < m_QStringList_HeaderSelected.size(); column++)
  {
    qDebug() << m_QStringList_HeaderSelected.at(column);
    QStringList qStringList_Values = m_QMap_Data.value(m_QStringList_HeaderSelected.at(column));

    double totalWh = 0;
    for (int row=0; row < qStringList_Values.size(); row++)
    {
      if(column == 0)
        ui->m_QTableWidget_ImportData->insertRow(row);

      QTableWidgetItem *qTableWidgetItem = new QTableWidgetItem(qStringList_Values.at(row));
      ui->m_QTableWidget_ImportData->setItem(row,
                                             column,
                                             qTableWidgetItem);

      if(m_QStringList_HeaderSelected.at(column) != _CONST::CSV_HEADER::HEADER_TIME)
      {
        totalWh += qStringList_Values.at(row).toDouble();
      }
    } // for row
    if(m_QStringList_HeaderSelected.at(column) != _CONST::CSV_HEADER::HEADER_TIME)
    {
      m_QMap_Total_kWh.insert(m_QStringList_HeaderSelected.at(column),
                         totalWh);
    }
  } // for column

  ui->m_QTableWidget_ImportData->resizeColumnsToContents();
  ui->m_QTableWidget_ImportData->scrollToBottom();

  updateGui_ImportData_Totals();
}

//-----------------------------------------------------------------------------------------------------------------------------

void CSVImporterDialog::updateGui_ImportData_Totals()
{
  // Set header
  QStringList qStringList_Header(m_QStringList_HeaderSelected);
  qStringList_Header.removeFirst();
  ui->m_QTableWidget_ImportData_Totals->setColumnCount(qStringList_Header.size());
  ui->m_QTableWidget_ImportData_Totals->setHorizontalHeaderLabels(qStringList_Header);

  ui->m_QTableWidget_ImportData_Totals->insertRow(ui->m_QTableWidget_ImportData_Totals->rowCount());
  for (int column = 0; column < m_QStringList_HeaderSelected.size(); column++)
  {
    if(m_QStringList_HeaderSelected.at(column) == _CONST::CSV_HEADER::HEADER_TIME)
      continue;

    ui->m_QTableWidget_ImportData_Totals->setItem(ui->m_QTableWidget_ImportData_Totals->rowCount()-1,
                                                  column-1,
                                                  new QTableWidgetItem(QString::number(m_QMap_Total_kWh.value(m_QStringList_HeaderSelected.at(column)))));
  }

  ui->m_QTableWidget_ImportData_Totals->resizeColumnsToContents();
  ui->m_QTableWidget_ImportData_Totals->scrollToBottom();
}

//-----------------------------------------------------------------------------------------------------------------------------

void CSVImporterDialog::on_m_QDialogButtonBox_accepted()
{



//  m_DatabaseManager->GetTableEnergia->InsertRow();
}
