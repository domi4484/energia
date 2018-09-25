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

private slots:

  void on_m_QDialogButtonBox_accepted();

private:

  Ui::CSVImporterDialog *ui;

  // Link to DatabaseManager
  DatabaseManager *m_DatabaseManager;

  CSVImporterSettings m_CSVImporterSettings;

  QString m_CSVFilename;

  // Loaded data
  QStringList m_QStringList_Header;
  QList<QStringList> m_QList_Data;

  // Selected data
  QStringList m_QStringList_HeaderSelected;

  QMap<QString, double> m_QMap_Total_kWh;

  void loadCSV();

  void updateGui();
  void updateGui_ImportSelection();
  void updateGui_ImportData();
  void updateGui_ImportData_Totals();

};

#endif // CSVIMPORTERDIALOG_H

