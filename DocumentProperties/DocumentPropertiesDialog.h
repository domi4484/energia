#ifndef DOCUMENTPROPERTIESDIALOG_H
#define DOCUMENTPROPERTIESDIALOG_H

#include <QDialog>

namespace Ui { class DocumentPropertiesDialog; }
class DatabaseManager;

class DocumentPropertiesDialog : public QDialog
{
    Q_OBJECT

public:

    explicit DocumentPropertiesDialog(DatabaseManager *databaseManager,
                                      QWidget *parent = nullptr);
    ~DocumentPropertiesDialog();

private:

    void setupGui();
    void setupGui_File();
    void setupGui_Content();

    Ui::DocumentPropertiesDialog *ui;

    // Link to DatabaseManager
    DatabaseManager *m_DatabaseManager;
};

#endif // DOCUMENTPROPERTIESDIALOG_H
