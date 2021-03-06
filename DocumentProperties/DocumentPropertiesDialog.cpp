
// Files includes -----------------------------------------
#include "DocumentPropertiesDialog.h"
#include "ui_DocumentPropertiesDialog.h"

// Project includes ---------------------------------------
#include "../Database/DatabaseManager.h"
#include "../Database/DatabaseTableEnergia.h"

// Qt includes --------------------------------------------
#include <QDebug>

//-----------------------------------------------------------------------------------------------------------------------------

DocumentPropertiesDialog::DocumentPropertiesDialog(DatabaseManager *databaseManager,
                                                   QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::DocumentPropertiesDialog)
  , m_DatabaseManager(databaseManager)
{
    ui->setupUi(this);

    // Setup gui
    setupGui();
}

//-----------------------------------------------------------------------------------------------------------------------------

DocumentPropertiesDialog::~DocumentPropertiesDialog()
{
    delete ui;
}

//-----------------------------------------------------------------------------------------------------------------------------

void DocumentPropertiesDialog::setupGui()
{
  setupGui_File();
  setupGui_Content();
}

//-----------------------------------------------------------------------------------------------------------------------------

void DocumentPropertiesDialog::setupGui_File()
{
  ui->m_QLabel_File_Filename->setText(m_DatabaseManager->GetFilename());
}

//-----------------------------------------------------------------------------------------------------------------------------

void DocumentPropertiesDialog::setupGui_Content()
{
  ui->m_QLabel_Content_TotalDatabaseRows->setText(QString::number(m_DatabaseManager->GetTableEnergia()->GetRowCount()));

  ui->m_QLabel_FirstEntryDateTime->setText(m_DatabaseManager->GetTableEnergia()->GetOldestRow().value(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_TIMESTAMP).toString());
  ui->m_QLabel_LastEntryDateTime->setText(m_DatabaseManager->GetTableEnergia()->GetNewestRow().value(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_TIMESTAMP).toString());
}
