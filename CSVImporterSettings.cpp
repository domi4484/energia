
// File includes ------------------------------------------
#include "CSVImporterSettings.h"

CSVImporterSettings::CSVImporterSettings(QObject *parent)
  : QObject(parent)
  , m_QList_Correspondances()
{
  m_QList_Correspondances.append(Correspondance("Time", "", true));
  m_QList_Correspondances.append(Correspondance("Solare L1 (kWh) day", "", true));
  m_QList_Correspondances.append(Correspondance("Solare L2 (kWh) day", "", true));
  m_QList_Correspondances.append(Correspondance("Solare L3 (kWh) day", "", true));

  m_QList_Correspondances.append(Correspondance("Appartamento1 L1 (kWh) day", "", true));
  m_QList_Correspondances.append(Correspondance("Appartamento1 L2 (kWh) day", "", true));
  m_QList_Correspondances.append(Correspondance("Appartamento1 L3 (kWh) day", "", true));

  m_QList_Correspondances.append(Correspondance("Appartamento2 L1 (kWh) day", "", true));
  m_QList_Correspondances.append(Correspondance("Appartamento2 L2 (kWh) day", "", true));
  m_QList_Correspondances.append(Correspondance("Appartamento2 L3 (kWh) day", "", true));

  m_QList_Correspondances.append(Correspondance("Appartamento3 L1 (kWh) day", "", true));
  m_QList_Correspondances.append(Correspondance("Appartamento3 L2 (kWh) day", "", true));
  m_QList_Correspondances.append(Correspondance("Appartamento3 L3 (kWh) day", "", true));
}

//-----------------------------------------------------------------------------------------------------------------------------

void CSVImporterSettings::loadFromFile(const QString &filename)
{

}

//-----------------------------------------------------------------------------------------------------------------------------

void CSVImporterSettings::saveToFile(const QString &filename)
{

}
