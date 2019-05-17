

// File includes ------------------------------------------
#include "DatabaseTableEnergia.h"

// Project includes ---------------------------------------
#include "DatabaseManager.h"
#include "Exception.h"

// Qt includes --------------------------------------------
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantMap>

//-----------------------------------------------------------------------------------------------------------------------------

const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::TABLE_NAME("energia");

const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_TIMESTAMP("timestamp");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_SOLARE_L1("solare_l1");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_SOLARE_L2("solare_l2");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_SOLARE_L3("solare_l3");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO1_L1("casa15_appartamento1_l1");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO1_L2("casa15_appartamento1_l2");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO1_L3("casa15_appartamento1_l3");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO2_L1("casa15_appartamento2_l1");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO2_L2("casa15_appartamento2_l2");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO2_L3("casa15_appartamento2_l3");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO3_L1("casa15_appartamento3_l1");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO3_L2("casa15_appartamento3_l2");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA15_APPARTAMENTO3_L3("casa15_appartamento3_l3");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO1_L1("casa17_appartamento1_l1");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO1_L2("casa17_appartamento1_l2");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO1_L3("casa17_appartamento1_l3");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO2_L1("casa17_appartamento2_l1");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO2_L2("casa17_appartamento2_l2");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO2_L3("casa17_appartamento2_l3");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO3_L1("casa17_appartamento3_l1");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO3_L2("casa17_appartamento3_l2");
const QString DatabaseTableEnergia::_CONST::DATABASE_TABLE::COLUMN_NAME_CASA17_APPARTAMENTO3_L3("casa17_appartamento3_l3");

const QStringList DatabaseTableEnergia::_CONST::DATABASE_TABLE::ALL_COLUMNS = QStringList()
    << COLUMN_NAME_TIMESTAMP
    << COLUMN_NAME_SOLARE_L1
    << COLUMN_NAME_SOLARE_L2
    << COLUMN_NAME_SOLARE_L3
    << COLUMN_NAME_CASA15_APPARTAMENTO1_L1
    << COLUMN_NAME_CASA15_APPARTAMENTO1_L2
    << COLUMN_NAME_CASA15_APPARTAMENTO1_L3
    << COLUMN_NAME_CASA15_APPARTAMENTO2_L1
    << COLUMN_NAME_CASA15_APPARTAMENTO2_L2
    << COLUMN_NAME_CASA15_APPARTAMENTO2_L3
    << COLUMN_NAME_CASA15_APPARTAMENTO3_L1
    << COLUMN_NAME_CASA15_APPARTAMENTO3_L2
    << COLUMN_NAME_CASA15_APPARTAMENTO3_L3
    << COLUMN_NAME_CASA17_APPARTAMENTO1_L1
    << COLUMN_NAME_CASA17_APPARTAMENTO1_L2
    << COLUMN_NAME_CASA17_APPARTAMENTO1_L3
    << COLUMN_NAME_CASA17_APPARTAMENTO2_L1
    << COLUMN_NAME_CASA17_APPARTAMENTO2_L2
    << COLUMN_NAME_CASA17_APPARTAMENTO2_L3
    << COLUMN_NAME_CASA17_APPARTAMENTO3_L1
    << COLUMN_NAME_CASA17_APPARTAMENTO3_L2
    << COLUMN_NAME_CASA17_APPARTAMENTO3_L3;

//-----------------------------------------------------------------------------------------------------------------------------

DatabaseTableEnergia::DatabaseTableEnergia(QSqlDatabase *qSqlDatabase,
                                           QObject *parent)
  : QObject(parent)
  , m_QSqlDatabase(qSqlDatabase)
{

}

//-----------------------------------------------------------------------------------------------------------------------------

int DatabaseTableEnergia::GetRowCount() const
{
  QSqlQuery qSqlQuery(QString("SELECT COUNT(*) FROM %1").arg(_CONST::DATABASE_TABLE::TABLE_NAME));

  qSqlQuery.first();
  return qSqlQuery.value(0).toInt();
}

//-----------------------------------------------------------------------------------------------------------------------------

void DatabaseTableEnergia::InsertRow(const QVariantMap &qVariantMap_Row)
{
  QSqlQuery qSqlQuery(*m_QSqlDatabase);
  qSqlQuery.prepare(QString("INSERT INTO %1 (%2) "
                            "VALUES (:%3)").arg(_CONST::DATABASE_TABLE::TABLE_NAME)
                                           .arg(qVariantMap_Row.keys().join(", "))
                                           .arg(qVariantMap_Row.keys().join(", :")));

  foreach (const QString &key, qVariantMap_Row.keys())
  {
    qSqlQuery.bindValue(QString(":%1").arg(key),
                        qVariantMap_Row.value(key));
  }
  qSqlQuery.exec();
}

//-----------------------------------------------------------------------------------------------------------------------------

QList<QVariantMap> DatabaseTableEnergia::GetRows(const QDate &qDate_From,
                                                 const QDate &qDate_To)
{
  //  select * from energia where `timestamp` >= '2018-09-02' and `timestamp` <= '2018-09-03'

  QSqlQuery qSqlQuery(*m_QSqlDatabase);
  qSqlQuery.setForwardOnly(true);
  qSqlQuery.prepare(QString("SELECT %1 FROM %2 "
                            "WHERE `%3` >= '%4' "
                            "AND `%3` <= '%5'").arg(_CONST::DATABASE_TABLE::ALL_COLUMNS.join(", "))
                                               .arg(_CONST::DATABASE_TABLE::TABLE_NAME)
                                               .arg(_CONST::DATABASE_TABLE::COLUMN_NAME_TIMESTAMP)
                                               .arg(qDate_From.toString(DatabaseManager::_CONST::TIMESTAMP_FORMAT))
                                               .arg(qDate_To.toString(DatabaseManager::_CONST::TIMESTAMP_FORMAT)));
  if(qSqlQuery.exec() == false)
    throw Exception(QString("Can't get database rows; %1").arg(qSqlQuery.lastError().text()));

  QList<QVariantMap> qList_QVariantMap_Rows;
  while (qSqlQuery.next())
  {
    QVariantMap qVariantMap_Row;
    for (int i=0; i < _CONST::DATABASE_TABLE::ALL_COLUMNS.size(); i++)
    {
      qVariantMap_Row.insert(_CONST::DATABASE_TABLE::ALL_COLUMNS.at(i),
                             qSqlQuery.value(i));
    }
    qList_QVariantMap_Rows.append(qVariantMap_Row);
  }

  return qList_QVariantMap_Rows;
}
