#include "MainWindow.h"
#include "ui_MainWindow.h"

// Project includes
#include "Exception.h"
#include "Settings/Settings.h"
#include "CSVImporter/CSVImporterDialog.h"
#include "Database/DatabaseManager.h"
#include "Database/DatabaseTableEnergia.h"
#include "DocumentProperties/DocumentPropertiesDialog.h"

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
{
  ui->setupUi(this);

  ui->m_QSplitter->setStretchFactor(0,1);
  ui->m_QSplitter->setStretchFactor(1,6);

  // Settings
  m_Settings = new Settings(this);

  // Database manager
  m_DatabaseManager = new DatabaseManager(this);

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
  delete m_Settings;

  delete m_DatabaseManager;

  delete ui;
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_File_New_triggered()
{
  QString newFilename = QFileDialog::getSaveFileName(this,
                                                     "New database",
                                                     QString(),
                                                     "*.ctb");
  if(newFilename.isEmpty())
    return;

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
  QDate qDate_From = ui->m_QCalendarWidget_From->selectedDate();
  QDate qDate_To   = ui->m_QCalendarWidget_To->selectedDate();

  if(qDate_From > qDate_To)
  {
    qWarning() << QString("Date From (%1) > Date To (%2)").arg(qDate_From.toString())
                                                          .arg(qDate_To.toString());
    return;
  }

  //  m_DatabaseManager->GetTableEnergia()->GetRows
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::updateWindowTitle(const QString &filename)
{
  MainWindow::setWindowTitle(QString("%1 - %2").arg(QApplication::applicationName())
                                               .arg(filename));
}


