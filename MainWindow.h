#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt includes --------------------------------------------
#include <QMainWindow>

// Class forward declarations -----------------------------
namespace Ui { class MainWindow; }
class DatabaseManager;
class CSVImporterDialog;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:

  void on_m_QAction_File_New_triggered();
  void on_m_QAction_File_Open_triggered();
  void on_m_QAction_File_Import_triggered();

private:

  Ui::MainWindow *ui;

  DatabaseManager *m_DatabaseManager;

  CSVImporterDialog *m_CSVImporterDialog;

};

#endif // MAINWINDOW_H
