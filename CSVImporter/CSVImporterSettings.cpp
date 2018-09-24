
// File includes ------------------------------------------
#include "CSVImporterSettings.h"

CSVImporterSettings::CSVImporterSettings(QObject *parent)
  : QObject(parent)
  , m_QList_Correspondances()
{
  m_QList_Correspondances.append(Correspondance("Time", "", true));

  m_QList_Correspondances.append(Correspondance("Solare L1 (kWh) night", "solare-l1", true));
  m_QList_Correspondances.append(Correspondance("Solare L2 (kWh) night", "solare-l2", true));
  m_QList_Correspondances.append(Correspondance("Solare L3 (kWh) night", "solare-l3", true));

  m_QList_Correspondances.append(Correspondance("Appartamento1 L1 (kWh) night", "casa15-appartamento1-l1", true));
  m_QList_Correspondances.append(Correspondance("Appartamento1 L2 (kWh) night", "casa15-appartamento1-l2", true));
  m_QList_Correspondances.append(Correspondance("Appartamento1 L3 (kWh) night", "casa15-appartamento1-l3", true));

  m_QList_Correspondances.append(Correspondance("Appartamento2 L1 (kWh) night", "casa15-appartamento2-l1", true));
  m_QList_Correspondances.append(Correspondance("Appartamento2 L2 (kWh) night", "casa15-appartamento2-l2", true));
  m_QList_Correspondances.append(Correspondance("Appartamento2 L3 (kWh) night", "casa15-appartamento2-l3", true));

  m_QList_Correspondances.append(Correspondance("Appartamento3 L1 (kWh) night", "casa15-appartamento3-l1", true));
  m_QList_Correspondances.append(Correspondance("Appartamento3 L2 (kWh) night", "casa15-appartamento3-l2", true));
  m_QList_Correspondances.append(Correspondance("Appartamento3 L3 (kWh) night", "casa15-appartamento3-l3", true));

  m_QList_Correspondances.append(Correspondance("Appartamento1 L1 (kWh) night", "casa17-appartamento1-l1", true));
  m_QList_Correspondances.append(Correspondance("Appartamento1 L2 (kWh) night", "casa17-appartamento1-l2", true));
  m_QList_Correspondances.append(Correspondance("Appartamento1 L3 (kWh) night", "casa17-appartamento1-l3", true));

  m_QList_Correspondances.append(Correspondance("Appartamento2 L1 (kWh) night", "casa17-appartamento2-l1", true));
  m_QList_Correspondances.append(Correspondance("Appartamento2 L2 (kWh) night", "casa17-appartamento2-l2", true));
  m_QList_Correspondances.append(Correspondance("Appartamento2 L3 (kWh) night", "casa17-appartamento2-l3", true));

  m_QList_Correspondances.append(Correspondance("Appartamento3 L1 (kWh) night", "casa17-appartamento3-l1", true));
  m_QList_Correspondances.append(Correspondance("Appartamento3 L2 (kWh) night", "casa17-appartamento3-l2", true));
  m_QList_Correspondances.append(Correspondance("Appartamento3 L3 (kWh) night", "casa17-appartamento3-l3", true));
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
