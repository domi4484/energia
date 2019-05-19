
// File includes ------------------------------------------
#include "EnergyCalculator.h"

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
  Result result;

  foreach(const QVariantMap & qVariantMap, qList_QVariantMap_Rows)
  {

  }
}
