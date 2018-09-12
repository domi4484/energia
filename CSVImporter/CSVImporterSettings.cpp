
// File includes ------------------------------------------
#include "CSVImporterSettings.h"

CSVImporterSettings::CSVImporterSettings(QObject *parent)
  : QObject(parent)
  , m_QList_Correspondances()
{
  m_QList_Correspondances.append(Correspondance("Time", "", true));

  m_QList_Correspondances.append(Correspondance("Solare L1 (kWh) night", "Solare-L1", true));
  m_QList_Correspondances.append(Correspondance("Solare L2 (kWh) night", "Solare-L2", true));
  m_QList_Correspondances.append(Correspondance("Solare L3 (kWh) night", "Solare-L3", true));

  m_QList_Correspondances.append(Correspondance("Appartamento1 L1 (kWh) night", "Casa15-Appartamento1-L1", true));
  m_QList_Correspondances.append(Correspondance("Appartamento1 L2 (kWh) night", "Casa15-Appartamento1-L2", true));
  m_QList_Correspondances.append(Correspondance("Appartamento1 L3 (kWh) night", "Casa15-Appartamento1-L3", true));

  m_QList_Correspondances.append(Correspondance("Appartamento2 L1 (kWh) night", "Casa15-Appartamento2-L1", true));
  m_QList_Correspondances.append(Correspondance("Appartamento2 L2 (kWh) night", "Casa15-Appartamento2-L2", true));
  m_QList_Correspondances.append(Correspondance("Appartamento2 L3 (kWh) night", "Casa15-Appartamento2-L3", true));

  m_QList_Correspondances.append(Correspondance("Appartamento3 L1 (kWh) night", "Casa15-Appartamento3-L1", true));
  m_QList_Correspondances.append(Correspondance("Appartamento3 L2 (kWh) night", "Casa15-Appartamento3-L2", true));
  m_QList_Correspondances.append(Correspondance("Appartamento3 L3 (kWh) night", "Casa15-Appartamento3-L3", true));

  m_QList_Correspondances.append(Correspondance("Appartamento1 L1 (kWh) night", "Casa17-Appartamento1-L1", true));
  m_QList_Correspondances.append(Correspondance("Appartamento1 L2 (kWh) night", "Casa17-Appartamento1-L2", true));
  m_QList_Correspondances.append(Correspondance("Appartamento1 L3 (kWh) night", "Casa17-Appartamento1-L3", true));

  m_QList_Correspondances.append(Correspondance("Appartamento2 L1 (kWh) night", "Casa17-Appartamento2-L1", true));
  m_QList_Correspondances.append(Correspondance("Appartamento2 L2 (kWh) night", "Casa17-Appartamento2-L2", true));
  m_QList_Correspondances.append(Correspondance("Appartamento2 L3 (kWh) night", "Casa17-Appartamento2-L3", true));

  m_QList_Correspondances.append(Correspondance("Appartamento3 L1 (kWh) night", "Casa17-Appartamento3-L1", true));
  m_QList_Correspondances.append(Correspondance("Appartamento3 L2 (kWh) night", "Casa17-Appartamento3-L2", true));
  m_QList_Correspondances.append(Correspondance("Appartamento3 L3 (kWh) night", "Casa17-Appartamento3-L3", true));
}

//-----------------------------------------------------------------------------------------------------------------------------

void CSVImporterSettings::LoadFromFile(const QString &filename)
{

}

//-----------------------------------------------------------------------------------------------------------------------------

void CSVImporterSettings::SaveToFile(const QString &filename)
{

}

//-----------------------------------------------------------------------------------------------------------------------------

CSVImporterSettings::Correspondance CSVImporterSettings::GetSettingsByCSVHeader(const QString &csvHeader) const
{
  foreach (const Correspondance &correspondance, m_QList_Correspondances)
  {
    if(correspondance.m_CSVHeader == csvHeader)
      return correspondance;
  }

  return Correspondance();
}
