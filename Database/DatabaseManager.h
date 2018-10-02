#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H


// Qt includes --------------------------------------------
#include <QObject>
#include <QSqlDatabase>

class DatabaseTableEnergia;

class DatabaseManager : public QObject
{
  Q_OBJECT

public:

  class _CONST
  {
  public:
    static const QString TIMESTAMP_FORMAT;
  }; // _CONST

  explicit DatabaseManager(QObject *parent = nullptr);
  virtual ~DatabaseManager();

  void CreateDatabase(const QString &filename);

  void Open(const QString &fileName);
  void Close();

  DatabaseTableEnergia *GetTableEnergia();

private:

  QSqlDatabase m_QSqlDatabase;

  DatabaseTableEnergia *m_DatabaseTableEnergia;

};

#endif // DATABASEMANAGER_H
