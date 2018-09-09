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

  QStringList m_QStringList_Header;
  QMap<QString, QStringList> m_QMap_Data;

  void loadCSV();

  void updateGui();
  void updateGui_ImportSelection();
  void updateGui_ImportData();

};

#endif // CSVIMPORTERDIALOG_H

