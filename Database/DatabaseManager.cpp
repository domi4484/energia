
// File includes ------------------------------------------
#include "DatabaseManager.h"

// Project includes ---------------------------------------
#include "DatabaseTableEnergia.h"
#include "Exception.h"

// Qt includes --------------------------------------------
#include <QString>
#include <QSqlError>
#include <QSqlQuery>

//-----------------------------------------------------------------------------------------------------------------------------

const QString DatabaseManager::_CONST::TIMESTAMP_FORMAT ("yyyy-MM-dd hh:mm:ss");

//-----------------------------------------------------------------------------------------------------------------------------

DatabaseManager::DatabaseManager(QObject *parent)
  : QObject(parent)
  , m_DatabaseTableEnergia(nullptr)
{
  m_QSqlDatabase = QSqlDatabase::addDatabase("QSQLITE");

  m_DatabaseTableEnergia = new DatabaseTableEnergia(&m_QSqlDatabase,
                                                    this);
}

//-----------------------------------------------------------------------------------------------------------------------------

DatabaseManager::~DatabaseManager()
{
  delete m_DatabaseTableEnergia;
}

//-----------------------------------------------------------------------------------------------------------------------------

void DatabaseManager::CreateDatabase(const QString &filename)
{
  DatabaseManager::Open(filename);

  // Prepare add table query
  QString tableName = DatabaseTableEnergia::_CONST::DATABASE_TABLE::TABLE_NAME;
  QStringList qStringList_Columns;
  qStringList_Columns << QString("%1 varchar(19) primary key").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_TIMESTAMP);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_SOLARE_L1);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_SOLARE_L2);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_SOLARE_L3);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO1_L1);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO1_L2);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO1_L3);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO2_L1);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO2_L2);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO2_L3);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO3_L1);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO3_L2);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO3_L3);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO1_L1);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO1_L2);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO1_L3);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO2_L1);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO2_L2);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO2_L3);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO3_L1);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO3_L2);
  qStringList_Columns << QString("%1 REAL DEFAULT 0.0").arg(DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO3_L3);

  // Add Table
  QSqlQuery qSqlQuery;
  qSqlQuery.exec(QString("CREATE TABLE %1 ( %2 );").arg(tableName)
                                                   .arg(qStringList_Columns.join(", ")));
}

//-----------------------------------------------------------------------------------------------------------------------------

void DatabaseManager::Open(const QString &fileName)
{
  m_QSqlDatabase.setDatabaseName(fileName);

  if (m_QSqlDatabase.open() == false)
  {
    throw Exception(QString("Can't connect to database '%1'; %2").arg(fileName)
                                                                 .arg(m_QSqlDatabase.lastError().text()));
  }
}

//-----------------------------------------------------------------------------------------------------------------------------

void DatabaseManager::Close()
{
  m_QSqlDatabase.close();
}

//-----------------------------------------------------------------------------------------------------------------------------

DatabaseTableEnergia *DatabaseManager::GetTableEnergia()
{
  return m_DatabaseTableEnergia;
}
