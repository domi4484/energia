#include "MainWindow.h"
#include "ui_MainWindow.h"

// Project includes ---------------------------------------
#include "Exception.h"
#include "Settings/Settings.h"
#include "CSVImporter/CSVImporterDialog.h"
#include "Database/DatabaseManager.h"
#include "Database/DatabaseTableEnergia.h"
#include "DocumentProperties/DocumentPropertiesDialog.h"
#include "EnergyCalculator/EnergyCalculator.h"

// Qt includes --------------------------------------------
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

//-----------------------------------------------------------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_Settings(nullptr)
  , m_DatabaseManager(nullptr)
  , m_EnergyCalculator(nullptr)
{
  ui->setupUi(this);

  ui->m_QSplitter->setStretchFactor(0,1);
  ui->m_QSplitter->setStretchFactor(1,6);

  // Settings
  m_Settings = new Settings(this);

  // Database manager
  m_DatabaseManager = new DatabaseManager(this);

  // EnergyCalculator
  {
    EnergyCalculator::Configuration configuration;
    configuration.m_EnergyProductionEntity = EnergyCalculator::EnergyProductionEntity("Solare",
                                                                                      DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_SOLARE_L1,
                                                                                      DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_SOLARE_L2,
                                                                                      DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_SOLARE_L3);
    configuration.m_QList_EnergyConsumptionEntity << EnergyCalculator::EnergyConsumptionEntity("Casa 15 Appartamento 1",
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO1_L1,
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO1_L2,
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO1_L3,
                                                                                               2)
                                                  << EnergyCalculator::EnergyConsumptionEntity("Casa 15 Appartamento 2",
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO2_L1,
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO2_L2,
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO2_L3,
                                                                                               2)
                                                  << EnergyCalculator::EnergyConsumptionEntity("Casa 15 Appartamento 3",
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO3_L1,
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO3_L2,
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO3_L3,
                                                                                               2)
                                                  << EnergyCalculator::EnergyConsumptionEntity("Casa 17 Appartamento 1",
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO1_L1,
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO1_L2,
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO1_L3,
                                                                                               1)
                                                  << EnergyCalculator::EnergyConsumptionEntity("Casa 17 Appartamento 2",
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO2_L1,
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO2_L2,
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO2_L3,
                                                                                               1)
                                                  << EnergyCalculator::EnergyConsumptionEntity("Casa 17 Appartamento 3",
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO3_L1,
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO3_L2,
                                                                                               DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO3_L3,
                                                                                               2);

    m_EnergyCalculator = new EnergyCalculator(configuration,
                                              this);
  }

  // Load last document
  if(m_Settings->get_CurrentDocument().isEmpty() == false)
  {
    qDebug() << QString("Open last database file '%1'").arg(m_Settings->get_CurrentDocument());

    // Open database
    m_DatabaseManager->Close();
    try
    {
      m_DatabaseManager->Open(m_Settings->get_CurrentDocument());

      // Set window title
      updateWindowTitle(m_Settings->get_CurrentDocument());
    }
    catch(const Exception &exception)
    {
      qDebug() << QString("Can't open last database file '%1': %2").arg(m_Settings->get_CurrentDocument())
                                                                   .arg(exception.GetText());
    }
  }
}

//-----------------------------------------------------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
  delete m_EnergyCalculator;

  delete m_DatabaseManager;

  delete m_Settings;

  delete ui;
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_File_New_triggered()
{
  QString newFilename = QFileDialog::getSaveFileName(this,
                                                     "New database",
                                                     QString(),
                                                     QString("*%1").arg(DatabaseManager::_CONST::DATABASE_FILENAME_EXTENSION));
  if(newFilename.isEmpty())
    return;

  if(newFilename.endsWith(DatabaseManager::_CONST::DATABASE_FILENAME_EXTENSION) == false)
    newFilename.append(DatabaseManager::_CONST::DATABASE_FILENAME_EXTENSION);

  // Create new database
  m_DatabaseManager->CreateDatabase(newFilename);

  // Update current document settings
  m_Settings->set_CurrentDocument(newFilename);

  // Set window title
  updateWindowTitle(newFilename);
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_File_Open_triggered()
{
  QString openFilename = QFileDialog::getOpenFileName(this,
                                                      "Open the database",
                                                      QString(),
                                                      "*.ctb");
  if(openFilename.isEmpty())
    return;

  qDebug() << QString("Open database file '%1'").arg(openFilename);

  // Open database
  m_DatabaseManager->Close();

  try
  {
    m_DatabaseManager->Open(openFilename);
  }
  catch(const Exception &exception)
  {
    QMessageBox::critical(this,
                          "Can't open database",
                          exception.GetText());
    return;
  }

  // Update current document settings
  m_Settings->set_CurrentDocument(openFilename);

  // Set window title
  updateWindowTitle(openFilename);
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_File_DocumentProperties_triggered()
{
  DocumentPropertiesDialog documentPropertiesDialog(m_DatabaseManager,
                                                    this);
  documentPropertiesDialog.exec();
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_Edit_ImportCSVData_triggered()
{
  CSVImporterDialog cSVImporterDialog(m_DatabaseManager,
                                      this);

  cSVImporterDialog.exec();
}

//-----------------------------------------------------------------------------------------------------------------------------
void MainWindow::on_m_QCalendarWidget_From_clicked(const QDate &date)
{
  Q_UNUSED(date);

  updateGui();
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QCalendarWidget_To_clicked(const QDate &date)
{
  Q_UNUSED(date);

  updateGui();
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::updateGui()
{
  // Get selected time span
  QDate qDate_From = ui->m_QCalendarWidget_From->selectedDate();
  QDate qDate_To   = ui->m_QCalendarWidget_To->selectedDate();
  if(qDate_From > qDate_To)
  {
    qWarning() << QString("Date From (%1) > Date To (%2)").arg(qDate_From.toString())
                                                          .arg(qDate_To.toString());
    return;
  }

  // Get energy data
  QList<QVariantMap> qList_QVariantMap_Rows;
  try
  {
    qList_QVariantMap_Rows = m_DatabaseManager->GetTableEnergia()->GetRows(qDate_From,
                                                                           qDate_To);
  }
  catch(const Exception &exception)
  {
    QMessageBox::critical(this,
                          "Can't open database",
                          exception.GetText());
    return;
  }

  // Compute energy
  EnergyCalculator::Result result = m_EnergyCalculator->DistributeEnergy(qList_QVariantMap_Rows);

  // Display result
  ui->m_QTreeWidget_Data->clear();

  // Production
  {
    QTreeWidgetItem *qTreeWidgetItem = new QTreeWidgetItem(QStringList() << result.m_EnergyProductionEntity.m_Name);

    QTreeWidgetItem *qTreeWidgetItemTotal = new QTreeWidgetItem(QStringList() << "Total"
                                                                              << QString::number(result.m_EnergyProductionEntity.m_Total.m_Production)
                                                                              << QString::number(result.m_EnergyProductionEntity.m_Total.m_SelfConsumption));
    qTreeWidgetItem->addChild(qTreeWidgetItemTotal);
    QTreeWidgetItem *qTreeWidgetItemL1 = new QTreeWidgetItem(QStringList() << "L1"
                                                                           << QString::number(result.m_EnergyProductionEntity.m_L1.m_Production)
                                                                           << QString::number(result.m_EnergyProductionEntity.m_L1.m_SelfConsumption));
    qTreeWidgetItem->addChild(qTreeWidgetItemL1);
    QTreeWidgetItem *qTreeWidgetItemL2 = new QTreeWidgetItem(QStringList() << "L2"
                                                                           << QString::number(result.m_EnergyProductionEntity.m_L2.m_Production)
                                                                           << QString::number(result.m_EnergyProductionEntity.m_L2.m_SelfConsumption));
    qTreeWidgetItem->addChild(qTreeWidgetItemL2);
    QTreeWidgetItem *qTreeWidgetItemL3 = new QTreeWidgetItem(QStringList() << "L3"
                                                                           << QString::number(result.m_EnergyProductionEntity.m_L3.m_Production)
                                                                           << QString::number(result.m_EnergyProductionEntity.m_L3.m_SelfConsumption));
    qTreeWidgetItem->addChild(qTreeWidgetItemL3);

    ui->m_QTreeWidget_Data->addTopLevelItem(qTreeWidgetItem);
  }

  // Consumption
  foreach (const EnergyCalculator::Result::EnergyConsumptionEntity &energyConsumptionEntity, result.m_QMap_EnergyConsumptionEntity.values())
  {
    QTreeWidgetItem *qTreeWidgetItem = new QTreeWidgetItem(QStringList() << energyConsumptionEntity.m_Name);

    QTreeWidgetItem *qTreeWidgetItemTotal = new QTreeWidgetItem(QStringList() << "Total"
                                                                              << QString::number(energyConsumptionEntity.m_Total.m_Consumption)
                                                                              << QString::number(energyConsumptionEntity.m_Total.m_SelfConsumption));
    qTreeWidgetItem->addChild(qTreeWidgetItemTotal);
    QTreeWidgetItem *qTreeWidgetItemL1 = new QTreeWidgetItem(QStringList() << "L1"
                                                                           << QString::number(energyConsumptionEntity.m_L1.m_Consumption)
                                                                           << QString::number(energyConsumptionEntity.m_L1.m_SelfConsumption));
    qTreeWidgetItem->addChild(qTreeWidgetItemL1);
    QTreeWidgetItem *qTreeWidgetItemL2 = new QTreeWidgetItem(QStringList() << "L2"
                                                                           << QString::number(energyConsumptionEntity.m_L2.m_Consumption)
                                                                           << QString::number(energyConsumptionEntity.m_L2.m_SelfConsumption));
    qTreeWidgetItem->addChild(qTreeWidgetItemL2);
    QTreeWidgetItem *qTreeWidgetItemL3 = new QTreeWidgetItem(QStringList() << "L3"
                                                                           << QString::number(energyConsumptionEntity.m_L3.m_Consumption)
                                                                           << QString::number(energyConsumptionEntity.m_L3.m_SelfConsumption));
    qTreeWidgetItem->addChild(qTreeWidgetItemL3);

    ui->m_QTreeWidget_Data->addTopLevelItem(qTreeWidgetItem);
  }

  ui->m_QTreeWidget_Data->resizeColumnToContents(0);
  ui->m_QTreeWidget_Data->resizeColumnToContents(1);
  ui->m_QTreeWidget_Data->resizeColumnToContents(2);
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::updateWindowTitle(const QString &filename)
{
  MainWindow::setWindowTitle(QString("%1 - %2").arg(QApplication::applicationName())
                                               .arg(filename));
}


