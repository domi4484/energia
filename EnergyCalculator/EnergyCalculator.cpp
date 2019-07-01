
// File includes ------------------------------------------
#include "EnergyCalculator.h"

// Qt includes --------------------------------------------
#include <QDebug>
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

  // Production/consumption
  {
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
      result.m_EnergyProductionEntity.m_L3.m_Production += qVariantMap.value(m_Configuration.m_EnergyProductionEntity.m_KeyL3).toDouble();

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

    // Totals
    {
      result.m_EnergyProductionEntity.m_Total.m_Production = result.m_EnergyProductionEntity.m_L1.m_Production
                                                           + result.m_EnergyProductionEntity.m_L2.m_Production
                                                           + result.m_EnergyProductionEntity.m_L3.m_Production;

      foreach(const EnergyConsumptionEntity &energyConsumptionEntity, m_Configuration.m_QList_EnergyConsumptionEntity)
        result.m_QMap_EnergyConsumptionEntity[energyConsumptionEntity.m_Name].m_Total.m_Consumption = result.m_QMap_EnergyConsumptionEntity.value(energyConsumptionEntity.m_Name).m_L1.m_Consumption
                                                                                                    + result.m_QMap_EnergyConsumptionEntity.value(energyConsumptionEntity.m_Name).m_L2.m_Consumption
                                                                                                    + result.m_QMap_EnergyConsumptionEntity.value(energyConsumptionEntity.m_Name).m_L3.m_Consumption;
    }
  }

  // Self consumption
  {
    // Get priority groups
    QList<QList<EnergyConsumptionEntity> > qList_EnergyConsumptionGroups;
    {
      QList<int> qList_Priorities;
      foreach(const EnergyConsumptionEntity &energyConsumptionEntity, m_Configuration.m_QList_EnergyConsumptionEntity)
      {
        if(qList_Priorities.contains(energyConsumptionEntity.m_Priority) == false)
          qList_Priorities.append(energyConsumptionEntity.m_Priority);
      }
      std::sort(qList_Priorities.begin(), qList_Priorities.end());

      foreach (int priority, qList_Priorities)
      {
        QList<EnergyConsumptionEntity> qList_EnergyConsumptionGroup;
        foreach(const EnergyConsumptionEntity &energyConsumptionEntity, m_Configuration.m_QList_EnergyConsumptionEntity)
        {
          if(energyConsumptionEntity.m_Priority == priority)
            qList_EnergyConsumptionGroup.append(energyConsumptionEntity);
        }
        if(qList_EnergyConsumptionGroup.isEmpty() == false)
          qList_EnergyConsumptionGroups.append(qList_EnergyConsumptionGroup);
      }
    }

    // Foreach row
    foreach(const QVariantMap & qVariantMap, qList_QVariantMap_Rows)
    {
      // Total production
      double L1_Production = qVariantMap.value(m_Configuration.m_EnergyProductionEntity.m_KeyL1).toDouble();
      double L2_Production = qVariantMap.value(m_Configuration.m_EnergyProductionEntity.m_KeyL2).toDouble();
      double L3_Production = qVariantMap.value(m_Configuration.m_EnergyProductionEntity.m_KeyL3).toDouble();

      // For each group ordered by priority
      foreach (const QList<EnergyConsumptionEntity> & qList_EnergyConsumptionGroup, qList_EnergyConsumptionGroups)
      {
//        foreach(const EnergyConsumptionEntity &energyConsumptionEntity, priorityGroups)
//        {
//          result.m_QMap_EnergyConsumptionEntity[energyConsumptionEntity.m_Name].m_L1.m_Consumption += qVariantMap.value(energyConsumptionEntity.m_KeyL1).toDouble();
//          result.m_QMap_EnergyConsumptionEntity[energyConsumptionEntity.m_Name].m_L2.m_Consumption += qVariantMap.value(energyConsumptionEntity.m_KeyL2).toDouble();
//          result.m_QMap_EnergyConsumptionEntity[energyConsumptionEntity.m_Name].m_L3.m_Consumption += qVariantMap.value(energyConsumptionEntity.m_KeyL3).toDouble();
//          result.m_QMap_EnergyConsumptionEntity[energyConsumptionEntity.m_Name].m_Total.m_Consumption = result.m_QMap_EnergyConsumptionEntity.value(energyConsumptionEntity.m_Name).m_Total.m_Consumption
//              + result.m_QMap_EnergyConsumptionEntity.value(energyConsumptionEntity.m_Name).m_L1.m_Consumption
//              + result.m_QMap_EnergyConsumptionEntity.value(energyConsumptionEntity.m_Name).m_L2.m_Consumption
//              + result.m_QMap_EnergyConsumptionEntity.value(energyConsumptionEntity.m_Name).m_L3.m_Consumption;
//        }
      } // foreach qList_EnergyConsumptionGroup
    } // foreach row
  }

  return result;
}
