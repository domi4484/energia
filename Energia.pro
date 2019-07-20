#-------------------------------------------------
#
# Project created by QtCreator 2018-09-06T23:04:32
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EnergiaCalculator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Exception.cpp \
    CSVImporter/CSVImporterDialog.cpp \
    CSVImporter/CSVImporterSettings.cpp \
    Database/DatabaseManager.cpp \
    Database/DatabaseTableEnergia.cpp \
    DocumentProperties/DocumentPropertiesDialog.cpp \
    EnergyCalculator/EnergyCalculator.cpp \
    Settings/Settings.cpp

HEADERS += \
    MainWindow.h \
    Exception.h \
    CSVImporter/CSVImporterDialog.h \
    CSVImporter/CSVImporterSettings.h \
    Database/DatabaseManager.h \
    Database/DatabaseTableEnergia.h \
    DocumentProperties/DocumentPropertiesDialog.h \
    EnergyCalculator/EnergyCalculator.h \
    Settings/Settings.h

FORMS += \
    MainWindow.ui \
    CSVImporter/CSVImporterDialog.ui \
    DocumentProperties/DocumentPropertiesDialog.ui
