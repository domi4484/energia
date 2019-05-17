#ifndef DATABASETABLE_ENERGIA_H
#define DATABASETABLE_ENERGIA_H

// Qt includes --------------------------------------------
#include <QObject>

class QSqlDatabase;

class DatabaseTableEnergia : public QObject
{
  Q_OBJECT

public:

  class _CONST
  {
  public:
    class DATABASE_TABLE
    {
    public:

      static const QString TABLE_NAME;

      static const QString COLUMN_NAME_TIMESTAMP;
      static const QString COLUMN_NAME_SOLARE_L1;
      static const QString COLUMN_NAME_SOLARE_L2;
      static const QString COLUMN_NAME_SOLARE_L3;
      static const QString COLUMN_NAME_CASA15_APPARTAMENTO1_L1;
      static const QString COLUMN_NAME_CASA15_APPARTAMENTO1_L2;
      static const QString COLUMN_NAME_CASA15_APPARTAMENTO1_L3;
      static const QString COLUMN_NAME_CASA15_APPARTAMENTO2_L1;
      static const QString COLUMN_NAME_CASA15_APPARTAMENTO2_L2;
      static const QString COLUMN_NAME_CASA15_APPARTAMENTO2_L3;
      static const QString COLUMN_NAME_CASA15_APPARTAMENTO3_L1;
      static const QString COLUMN_NAME_CASA15_APPARTAMENTO3_L2;
      static const QString COLUMN_NAME_CASA15_APPARTAMENTO3_L3;
      static const QString COLUMN_NAME_CASA17_APPARTAMENTO1_L1;
      static const QString COLUMN_NAME_CASA17_APPARTAMENTO1_L2;
      static const QString COLUMN_NAME_CASA17_APPARTAMENTO1_L3;
      static const QString COLUMN_NAME_CASA17_APPARTAMENTO2_L1;
      static const QString COLUMN_NAME_CASA17_APPARTAMENTO2_L2;
      static const QString COLUMN_NAME_CASA17_APPARTAMENTO2_L3;
      static const QString COLUMN_NAME_CASA17_APPARTAMENTO3_L1;
      static const QString COLUMN_NAME_CASA17_APPARTAMENTO3_L2;
      static const QString COLUMN_NAME_CASA17_APPARTAMENTO3_L3;

      static const QStringList ALL_COLUMNS;

    }; // DATABASE_TABLE

  }; // _CONST

  DatabaseTableEnergia(QSqlDatabase *qSqlDatabase,
                       QObject *parent = nullptr);

  int GetRowCount() const;

  void InsertRow(const QVariantMap &qVariantMap_Row);

  QList<QVariantMap> GetRows(const QDate &qDate_From,
                      const QDate &qDate_To);

private:

  // Link to database
  QSqlDatabase *m_QSqlDatabase;
};

#endif // DATABASETABLE_ENERGIA_H
