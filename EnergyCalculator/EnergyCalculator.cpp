
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

  } // Production/consumption

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

      if(   L1_Production == 0.0
         && L2_Production == 0.0
         && L3_Production == 0.0)
        continue;

      // For each group ordered by priority
      foreach (const QList<EnergyConsumptionEntity> & qList_EnergyConsumptionGroup, qList_EnergyConsumptionGroups)
      {
        // L1
        {
          QMap<QString, double> qMap_Entity_SelfConsumption;
          QList<EnergyConsumptionEntity> qList_EnegyConsumptionGroupNotDone;
          foreach (const EnergyConsumptionEntity &energyConsumptionEntity, qList_EnergyConsumptionGroup)
            qList_EnegyConsumptionGroupNotDone.append(energyConsumptionEntity);

          double productionToDistribute = L1_Production;
          while(true)
          {
            double partPerEntity = productionToDistribute / (double)qList_EnegyConsumptionGroupNotDone.size();
            double effectivelyDistributed = 0.0;

            foreach (const EnergyConsumptionEntity &energyConsumptionEntity, qList_EnegyConsumptionGroupNotDone)
            {
              effectivelyDistributed = qMin(partPerEntity,
                                              qVariantMap.value(energyConsumptionEntity.m_KeyL1).toDouble()
                                            - qMap_Entity_SelfConsumption.value(energyConsumptionEntity.m_Name, 0.0));

              qMap_Entity_SelfConsumption.insert(energyConsumptionEntity.m_Name,
                                                 (qMap_Entity_SelfConsumption.value(energyConsumptionEntity.m_Name, 0.0)
                                                  + effectivelyDistributed));

              if( (qVariantMap.value(energyConsumptionEntity.m_KeyL1).toDouble()
                  - qMap_Entity_SelfConsumption.value(energyConsumptionEntity.m_Name, 0.0))
                 <= 0.0)
                qList_EnegyConsumptionGroupNotDone.removeOne(energyConsumptionEntity);

            } // foreach entity

            productionToDistribute -= effectivelyDistributed;
            L1_Production -= effectivelyDistributed;

            if(qList_EnegyConsumptionGroupNotDone.isEmpty())
              break;

            if(productionToDistribute < 0.00001)
              break;

          } // while

          foreach(const QString &entityName, qMap_Entity_SelfConsumption.keys())
          {
            result.m_QMap_EnergyConsumptionEntity[entityName].m_L1.m_SelfConsumption += qMap_Entity_SelfConsumption.value(entityName);
            result.m_EnergyProductionEntity.m_L1.m_SelfConsumption += qMap_Entity_SelfConsumption.value(entityName);
          }

        } // L1

        // L2
        {
          QMap<QString, double> qMap_Entity_SelfConsumption;
          QList<EnergyConsumptionEntity> qList_EnegyConsumptionGroupNotDone;
          foreach (const EnergyConsumptionEntity &energyConsumptionEntity, qList_EnergyConsumptionGroup)
            qList_EnegyConsumptionGroupNotDone.append(energyConsumptionEntity);

          double productionToDistribute = L2_Production;
          while(true)
          {
            double partPerEntity = productionToDistribute / (double)qList_EnegyConsumptionGroupNotDone.size();
            double effectivelyDistributed = 0.0;

            foreach (const EnergyConsumptionEntity &energyConsumptionEntity, qList_EnegyConsumptionGroupNotDone)
            {
              effectivelyDistributed = qMin(partPerEntity,
                                              qVariantMap.value(energyConsumptionEntity.m_KeyL2).toDouble()
                                            - qMap_Entity_SelfConsumption.value(energyConsumptionEntity.m_Name, 0.0));

              qMap_Entity_SelfConsumption.insert(energyConsumptionEntity.m_Name,
                                                 (qMap_Entity_SelfConsumption.value(energyConsumptionEntity.m_Name, 0.0)
                                                  + effectivelyDistributed));

              if( (qVariantMap.value(energyConsumptionEntity.m_KeyL2).toDouble()
                  - qMap_Entity_SelfConsumption.value(energyConsumptionEntity.m_Name, 0.0))
                 <= 0.0)
                qList_EnegyConsumptionGroupNotDone.removeOne(energyConsumptionEntity);

            } // foreach entity

            productionToDistribute -= effectivelyDistributed;
            L2_Production -= effectivelyDistributed;

            if(qList_EnegyConsumptionGroupNotDone.isEmpty())
              break;

            if(productionToDistribute < 0.00001)
              break;

          } // while

          foreach(const QString &entityName, qMap_Entity_SelfConsumption.keys())
          {
            result.m_QMap_EnergyConsumptionEntity[entityName].m_L2.m_SelfConsumption += qMap_Entity_SelfConsumption.value(entityName);
            result.m_EnergyProductionEntity.m_L2.m_SelfConsumption += qMap_Entity_SelfConsumption.value(entityName);
          }

        } // L2

        // L3
        {
          QMap<QString, double> qMap_Entity_SelfConsumption;
          QList<EnergyConsumptionEntity> qList_EnegyConsumptionGroupNotDone;
          foreach (const EnergyConsumptionEntity &energyConsumptionEntity, qList_EnergyConsumptionGroup)
            qList_EnegyConsumptionGroupNotDone.append(energyConsumptionEntity);

          double productionToDistribute = L3_Production;
          while(true)
          {
            double partPerEntity = productionToDistribute / (double)qList_EnegyConsumptionGroupNotDone.size();
            double effectivelyDistributed = 0.0;

            foreach (const EnergyConsumptionEntity &energyConsumptionEntity, qList_EnegyConsumptionGroupNotDone)
            {
              effectivelyDistributed = qMin(partPerEntity,
                                              qVariantMap.value(energyConsumptionEntity.m_KeyL3).toDouble()
                                            - qMap_Entity_SelfConsumption.value(energyConsumptionEntity.m_Name, 0.0));

              qMap_Entity_SelfConsumption.insert(energyConsumptionEntity.m_Name,
                                                 (qMap_Entity_SelfConsumption.value(energyConsumptionEntity.m_Name, 0.0)
                                                  + effectivelyDistributed));

              if( (qVariantMap.value(energyConsumptionEntity.m_KeyL3).toDouble()
                  - qMap_Entity_SelfConsumption.value(energyConsumptionEntity.m_Name, 0.0))
                 <= 0.0)
                qList_EnegyConsumptionGroupNotDone.removeOne(energyConsumptionEntity);

            } // foreach entity

            productionToDistribute -= effectivelyDistributed;
            L3_Production -= effectivelyDistributed;

            if(qList_EnegyConsumptionGroupNotDone.isEmpty())
              break;

            if(productionToDistribute < 0.00001)
              break;

          } // while

          foreach(const QString &entityName, qMap_Entity_SelfConsumption.keys())
          {
            result.m_QMap_EnergyConsumptionEntity[entityName].m_L3.m_SelfConsumption += qMap_Entity_SelfConsumption.value(entityName);
            result.m_EnergyProductionEntity.m_L3.m_SelfConsumption += qMap_Entity_SelfConsumption.value(entityName);
          }

        } // L3

      } // foreach qList_EnergyConsumptionGroup
    } // foreach row

    // Totals
    {
      result.m_EnergyProductionEntity.m_Total.m_SelfConsumption = result.m_EnergyProductionEntity.m_L1.m_SelfConsumption
                                                                + result.m_EnergyProductionEntity.m_L2.m_SelfConsumption
                                                                + result.m_EnergyProductionEntity.m_L3.m_SelfConsumption;

      foreach(const EnergyConsumptionEntity &energyConsumptionEntity, m_Configuration.m_QList_EnergyConsumptionEntity)
        result.m_QMap_EnergyConsumptionEntity[energyConsumptionEntity.m_Name].m_Total.m_SelfConsumption = result.m_QMap_EnergyConsumptionEntity.value(energyConsumptionEntity.m_Name).m_L1.m_SelfConsumption
                                                                                                        + result.m_QMap_EnergyConsumptionEntity.value(energyConsumptionEntity.m_Name).m_L2.m_SelfConsumption
                                                                                                        + result.m_QMap_EnergyConsumptionEntity.value(energyConsumptionEntity.m_Name).m_L3.m_SelfConsumption;
    }

  } // Self consumption

  return result;
}
