
// File includes ------------------------------------------
#include "CSVImporterSettings.h"

CSVImporterSettings::CSVImporterSettings(QObject *parent)
  : QObject(parent)
  , m_QList_Correspondances()
{
  m_QList_Correspondances.append(Correspondance("Time", "timestamp", true));

  m_QList_Correspondances.append(Correspondance("Solare-L1 (kWh) night", "solare_l1", true));
  m_QList_Correspondances.append(Correspondance("Solare-L2 (kWh) night", "solare_l2", true));
  m_QList_Correspondances.append(Correspondance("Solare-L3 (kWh) night", "solare_l3", true));

  m_QList_Correspondances.append(Correspondance("15App1-L1 (kWh) night", "casa15_appartamento1_l1", true));
  m_QList_Correspondances.append(Correspondance("15App1-L2 (kWh) night", "casa15_appartamento1_l2", true));
  m_QList_Correspondances.append(Correspondance("15App1-L3 (kWh) night", "casa15_appartamento1_l3", true));

  m_QList_Correspondances.append(Correspondance("15App2-L1 (kWh) night", "casa15_appartamento2_l1", true));
  m_QList_Correspondances.append(Correspondance("15App2-L2 (kWh) night", "casa15_appartamento2_l2", true));
  m_QList_Correspondances.append(Correspondance("15App2-L3 (kWh) night", "casa15_appartamento2_l3", true));

  m_QList_Correspondances.append(Correspondance("15App3-L1 (kWh) night", "casa15_appartamento3_l1", true));
  m_QList_Correspondances.append(Correspondance("15App3-L2 (kWh) night", "casa15_appartamento3_l2", true));
  m_QList_Correspondances.append(Correspondance("15App3-L3 (kWh) night", "casa15_appartamento3_l3", true));

  m_QList_Correspondances.append(Correspondance("17App1-L1 (kWh) night", "casa17_appartamento1_l1", true));
  m_QList_Correspondances.append(Correspondance("17App1-L2 (kWh) night", "casa17_appartamento1_l2", true));
  m_QList_Correspondances.append(Correspondance("17App1-L3 (kWh) night", "casa17_appartamento1_l3", true));

  m_QList_Correspondances.append(Correspondance("17App2-L1 (kWh) night", "casa17_appartamento2_l1", true));
  m_QList_Correspondances.append(Correspondance("17App2-L2 (kWh) night", "casa17_appartamento2_l2", true));
  m_QList_Correspondances.append(Correspondance("17App2-L3 (kWh) night", "casa17_appartamento2_l3", true));

  m_QList_Correspondances.append(Correspondance("17App3-L1 (kWh) night", "casa17_appartamento3_l1", true));
  m_QList_Correspondances.append(Correspondance("17App3-L2 (kWh) night", "casa17_appartamento3_l2", true));
  m_QList_Correspondances.append(Correspondance("17App3-L3 (kWh) night", "casa17_appartamento3_l3", true));
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
