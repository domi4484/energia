#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt includes --------------------------------------------
#include <QMainWindow>

// Class forward declarations -----------------------------
namespace Ui { class MainWindow; }
class DatabaseManager;
class Settings;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:

  void on_m_QAction_File_New_triggered();
  void on_m_QAction_File_Open_triggered();
  void on_m_QAction_File_DocumentProperties_triggered();

  void on_m_QAction_Edit_ImportCSVData_triggered();

  void on_m_QCalendarWidget_From_clicked(const QDate &date);
  void on_m_QCalendarWidget_To_clicked(const QDate &date);

private:

  Ui::MainWindow *ui;

  // Settings
  Settings        *m_Settings;

  // DatabaseManager
  DatabaseManager *m_DatabaseManager;

  void updateGui();
  void updateWindowTitle(const QString &filename);
};

#endif // MAINWINDOW_H
