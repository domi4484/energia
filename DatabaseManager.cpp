#include "DatabaseManager.h"

// Project includes
#include "Exception.h"

// Qt includes
#include <QSqlError>
#include <QSqlQuery>

//-----------------------------------------------------------------------------------------------------------------------------

DatabaseManager::DatabaseManager(QObject *parent)
  : QObject(parent)
{
  m_QSqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
}

//-----------------------------------------------------------------------------------------------------------------------------

void DatabaseManager::CreateDatabase(const QString &filename)
{
  DatabaseManager::Open(filename);

  // Add Table
  QSqlQuery qSqlQuery;
  qSqlQuery.exec("create table energia "
                 "(Time varchar(30) primary key, "
                 "firstname varchar(20), "
                 "lastname varchar(30), "
                 "age integer)");
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
