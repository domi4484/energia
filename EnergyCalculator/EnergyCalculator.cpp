
// File includes ------------------------------------------
#include "EnergyCalculator.h"

// Qt includes --------------------------------------------
#include <QVariantMap>

//-----------------------------------------------------------------------------------------------------------------------------

EnergyCalculator::EnergyCalculator(const Configuration &configuration,
                                   QObject *parent)
  : QObject(parent)
  , m_Configuration(configuration)
{

}

//-----------------------------------------------------------------------------------------------------------------------------

EnergyCalculator::Result EnergyCalculator::DistributeEnergy(const QList<QVariantMap> &qList_QVariantMap_Rows)
{
  // Result entities based on configuration
  Result result;

  // Energy production
  result.m_EnergyProductionEntity.m_Name = m_Configuration.m_EnergyProductionEntity.m_Name;

  // Energy consumption
  foreach(const EnergyConsumptionEntity &energyConsumptionEntity, m_Configuration.m_QList_EnergyConsumptionEntity)
  {
    Result::EnergyConsumptionEntity resultEnergyConsumptionEntity;
    resultEnergyConsumptionEntity.m_Name = energyConsumptionEntity.m_Name;
    result.m_QMap_EnergyConsumptionEntity.insert(resultEnergyConsumptionEntity.m_Name, resultEnergyConsumptionEntity);
  }

  // Foreach row
  foreach(const QVariantMap & qVariantMap, qList_QVariantMap_Rows)
  {
    // Total production
    result.m_EnergyProductionEntity.m_L1.m_Production += qVariantMap.value(m_Configuration.m_EnergyProductionEntity.m_KeyL1).toDouble();
    result.m_EnergyProductionEntity.m_L2.m_Production += qVariantMap.value(m_Configuration.m_EnergyProductionEntity.m_KeyL2).toDouble();
    result.m_EnergyProductionEntity.m_L2.m_Production += qVariantMap.value(m_Configuration.m_EnergyProductionEntity.m_KeyL3).toDouble();
    result.m_EnergyProductionEntity.m_Total.m_Production = result.m_EnergyProductionEntity.m_Total.m_Production
                                                         + result.m_EnergyProductionEntity.m_L1.m_Production
                                                         + result.m_EnergyProductionEntity.m_L2.m_Production
                                                         + result.m_EnergyProductionEntity.m_L3.m_Production;

    // Total consumption
    foreach(const EnergyConsumptionEntity &energyConsumptionEntity, m_Configuration.m_QList_EnergyConsumptionEntity)
    {
      result.m_QMap_EnergyConsumptionEntity[energyConsumptionEntity.m_Name].m_L1.m_Consumption += qVariantMap.value(energyConsumptionEntity.m_KeyL1).toDouble();
      result.m_QMap_EnergyConsumptionEntity[energyConsumptionEntity.m_Name].m_L2.m_Consumption += qVariantMap.value(energyConsumptionEntity.m_KeyL2).toDouble();
      result.m_QMap_EnergyConsumptionEntity[energyConsumptionEntity.m_Name].m_L3.m_Consumption += qVariantMap.value(energyConsumptionEntity.m_KeyL3).toDouble();
      result.m_QMap_EnergyConsumptionEntity[energyConsumptionEntity.m_Name].m_Total.m_Consumption = result.m_QMap_EnergyConsumptionEntity.value(energyConsumptionEntity.m_Name).m_Total.m_Consumption
                                                                                                  + result.m_QMap_EnergyConsumptionEntity.value(energyConsumptionEntity.m_Name).m_L1.m_Consumption
                                                                                                  + result.m_QMap_EnergyConsumptionEntity.value(energyConsumptionEntity.m_Name).m_L2.m_Consumption
                                                                                                  + result.m_QMap_EnergyConsumptionEntity.value(energyConsumptionEntity.m_Name).m_L3.m_Consumption;
    }
  }

  return result;
}
