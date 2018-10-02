#include "MainWindow.h"
#include "ui_MainWindow.h"

// Project includes
#include "Exception.h"
#include "CSVImporter/CSVImporterDialog.h"
#include "Database/DatabaseManager.h"
#include "Database/DatabaseTableEnergia.h"

// Qt includes --------------------------------------------
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

//-----------------------------------------------------------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_DatabaseManager(nullptr)
{
  ui->setupUi(this);

  ui->m_QSplitter->setStretchFactor(0,1);
  ui->m_QSplitter->setStretchFactor(1,6);

  m_DatabaseManager = new DatabaseManager(this);
}

//-----------------------------------------------------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
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

  m_DatabaseManager->CreateDatabase(newFilename);
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
  }
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_File_Import_triggered()
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


