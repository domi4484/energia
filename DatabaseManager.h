#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>

class DatabaseManager : public QObject
{
  Q_OBJECT

public:

  explicit DatabaseManager(QObject *parent = nullptr);

  void CreateDatabase(const QString &filename);

  void Open(const QString &fileName);
  void Close();

  void AddMeasurement();

private:

  QSqlDatabase m_QSqlDatabase;

};

#endif // DATABASEMANAGER_H
