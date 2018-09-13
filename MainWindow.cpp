#include "MainWindow.h"
#include "ui_MainWindow.h"

// Project includes
#include "DatabaseManager.h"
#include "Exception.h"
#include "CSVImporter/CSVImporterDialog.h"

// Qt includes --------------------------------------------
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

//-----------------------------------------------------------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_DatabaseManager(nullptr)
  , m_CSVImporterDialog(nullptr)
{
  ui->setupUi(this);

  m_DatabaseManager = new DatabaseManager(this);
}

//-----------------------------------------------------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
  if (m_CSVImporterDialog != nullptr)
  {
    if(m_CSVImporterDialog->isVisible())
        m_CSVImporterDialog->reject();
    delete m_CSVImporterDialog;
  }
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
  if (m_CSVImporterDialog == nullptr)
    m_CSVImporterDialog = new CSVImporterDialog(m_DatabaseManager,
                                                this);

  m_CSVImporterDialog->show();
}
