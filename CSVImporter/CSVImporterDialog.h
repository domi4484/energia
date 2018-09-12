#ifndef CSVIMPORTERDIALOG_H
#define CSVIMPORTERDIALOG_H

#include "CSVImporterSettings.h"

// Qt includes --------------------------------------------
#include <QDialog>
#include <QMap>

namespace Ui { class CSVImporterDialog; }
class DatabaseManager;

class CSVImporterDialog : public QDialog
{
  Q_OBJECT

public:

  class _CONST
  {
  public:
    class CSV_HEADER
    {
    public:
      static const QString HEADER_TIME;
    }; // CSV_HEADER
  }; // _CONST

  explicit CSVImporterDialog(DatabaseManager *databaseManager,
                             QWidget *parent = nullptr);
  ~CSVImporterDialog();

protected:

    virtual void showEvent(QShowEvent *);

private:

  Ui::CSVImporterDialog *ui;

  // Link to DatabaseManager
  DatabaseManager *m_DatabaseManager;

  CSVImporterSettings m_CSVImporterSettings;

  QString m_CSVFilename;

  // Loaded data
  QStringList m_QStringList_Header;
  QMap<QString, QStringList> m_QMap_Data;

  // Selected data
  QStringList m_QStringList_HeaderSelected;

  QMap<QString, double> m_QMap_Total_Wh;

  void loadCSV();

  void updateGui();
  void updateGui_ImportSelection();
  void updateGui_ImportData();

};

#endif // CSVIMPORTERDIALOG_H

