#ifndef CSVIMPORTERSETTINGS_H
#define CSVIMPORTERSETTINGS_H

// Qt includes --------------------------------------------
#include <QObject>

class CSVImporterSettings : public QObject
{
    Q_OBJECT

public:

  class Correspondance
  {
  public:

    Correspondance()
      : m_Valid(false)
      , m_CSVHeader()
      , m_DatabaseColumnName()
      , m_Enabled()
    {}

    Correspondance(const QString &csvHeader,
                   const QString &databaseColumnName,
                   bool enabled)
      : m_Valid(true)
      , m_CSVHeader(csvHeader)
      , m_DatabaseColumnName(databaseColumnName)
      , m_Enabled(enabled)
    {}

    bool m_Valid;
    QString m_CSVHeader;
    QString m_DatabaseColumnName;
    bool m_Enabled;

  }; // Correspondance

  explicit CSVImporterSettings(QObject *parent = nullptr);

  void LoadFromFile(const QString &filename);
  void SaveToFile(const QString &filename);

  Correspondance GetSettingsByCSVHeader(const QString &csvHeader) const;

private:


  QList<Correspondance> m_QList_Correspondances;

};

#endif // CSVIMPORTERSETTINGS_H
