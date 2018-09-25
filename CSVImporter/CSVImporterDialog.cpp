
// File includes ------------------------------------------
#include "CSVImporterDialog.h"
#include "ui_CSVImporterDialog.h"

// Project includes
#include "Exception.h"
#include "Database/DatabaseManager.h"
#include "Database/DatabaseTableEnergia.h"

// Qt includes --------------------------------------------
#include <QFileDialog>
#include <QDebug>
#include <QTimer>
#include <QSqlQuery>
#include <QVariantMap>

const QString CSVImporterDialog::_CONST::CSV_HEADER::HEADER_TIME ("Time");

//-----------------------------------------------------------------------------------------------------------------------------

CSVImporterDialog::CSVImporterDialog(DatabaseManager *databaseManager,
                                     QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::CSVImporterDialog)
  , m_DatabaseManager(databaseManager)
  , m_CSVFilename()
  , m_QStringList_Header()
  , m_QList_Data()
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
  m_QList_Data.clear();
  m_QStringList_HeaderSelected.clear();
  m_QMap_Total_kWh.clear();

  m_QStringList_Header = QString(qFile.readLine()).split(',');

  while (qFile.atEnd() == false)
  {
    QStringList qStringlist_Data = QString(qFile.readLine()).split(',');
    m_QList_Data.append(qStringlist_Data);

    for (int i = 1; i < qStringlist_Data.size(); i++)
    {
      double currentValueKWh = m_QMap_Total_kWh.value(m_QStringList_Header.at(i),
                                                      0.0);
      currentValueKWh += qStringlist_Data.at(i).toDouble();
      m_QMap_Total_kWh.insert(m_QStringList_Header.at(i),
                              currentValueKWh);
    } // foreach
  } // while
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

  // Set header
  ui->m_QTableWidget_ImportData->setColumnCount(m_QStringList_HeaderSelected.size());
  ui->m_QTableWidget_ImportData->setHorizontalHeaderLabels(m_QStringList_HeaderSelected);

  foreach (const QStringList &qStringList_RowData, m_QList_Data)
  {
    // Insert new row in table
    ui->m_QTableWidget_ImportData->insertRow(ui->m_QTableWidget_ImportData->rowCount());

    for (int column=0; column < m_QStringList_HeaderSelected.size(); column++)
    {
      for (int headerIndex = 0; headerIndex < m_QStringList_Header.size(); headerIndex++)
      {
        if(m_QStringList_Header.at(headerIndex) != m_QStringList_HeaderSelected.at(column))
          continue;

        QTableWidgetItem *qTableWidgetItem = new QTableWidgetItem(qStringList_RowData.at(headerIndex));
        ui->m_QTableWidget_ImportData->setItem(ui->m_QTableWidget_ImportData->rowCount()-1,
                                               column,
                                               qTableWidgetItem);

      } // for headerIndex
    } // for column
  } // foreach data row

  ui->m_QTableWidget_ImportData->resizeColumnsToContents();
  ui->m_QTableWidget_ImportData->scrollToBottom();

  updateGui_ImportData_Totals();
}

//-----------------------------------------------------------------------------------------------------------------------------

void CSVImporterDialog::updateGui_ImportData_Totals()
{
  ui->m_QTableWidget_ImportData_Totals->clear();

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
  foreach (const QStringList &dataRow, m_QList_Data)
  {
    QVariantMap qVariantMap_Row;

    for (int headerIndex = 0; headerIndex < m_QStringList_Header.size(); headerIndex++)
    {
      if(m_QStringList_HeaderSelected.contains(m_QStringList_Header.at(headerIndex)) == false)
          continue;

      QString databaseColumnName = m_CSVImporterSettings.GetSettingsByCSVHeader(m_QStringList_Header.at(headerIndex)).m_DatabaseColumnName;
      qVariantMap_Row.insert(databaseColumnName,
                             dataRow.at(headerIndex));
    } // for header

    m_DatabaseManager->GetTableEnergia()->InsertRow(qVariantMap_Row);
  } // foreach row

  QDialog::accept();
}
