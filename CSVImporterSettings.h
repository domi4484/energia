#ifndef CSVIMPORTERSETTINGS_H
#define CSVIMPORTERSETTINGS_H

#include <QObject>

class CSVImporterSettings : public QObject
{
    Q_OBJECT
public:
    explicit CSVImporterSettings(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CSVIMPORTERSETTINGS_H