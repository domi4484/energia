#include "DatabaseManager.h"

// Project includes
#include "Exception.h"

// Qt includes
#include <QSqlError>

//-----------------------------------------------------------------------------------------------------------------------------

DatabaseManager::DatabaseManager(QObject *parent)
  : QObject(parent)
{
  m_QSqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
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
