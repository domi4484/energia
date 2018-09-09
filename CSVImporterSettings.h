#ifndef CSVIMPORTERSETTINGS_H
#define CSVIMPORTERSETTINGS_H

// Qt includes --------------------------------------------
#include <QObject>

class CSVImporterSettings : public QObject
{
    Q_OBJECT

public:

  explicit CSVImporterSettings(QObject *parent = nullptr);

  void loadFromFile(const QString &filename);
  void saveToFile(const QString &filename);

private:

  class Correspondance
  {
  public:

    Correspondance(const QString &csvHeader,
                   const QString &databaseColumnName,
                   bool enabled)
      : m_CSVHeader(csvHeader)
      , m_DatabaseColumnName(databaseColumnName)
      , m_Enabled(enabled)
    {}

    QString m_CSVHeader;
    QString m_DatabaseColumnName;
    bool m_Enabled;

  }; // Correspondance

  QList<Correspondance> m_QList_Correspondances;

};

#endif // CSVIMPORTERSETTINGS_H
