#ifndef ENERGYCALCULATOR_H
#define ENERGYCALCULATOR_H

// Qt includes --------------------------------------------
#include <QObject>
#include <QMap>

class EnergyCalculator : public QObject
{
  Q_OBJECT

public:

  class EnergyProductionEntity
  {
  public:

    EnergyProductionEntity()
      : m_Name()
      , m_KeyL1()
      , m_KeyL2()
      , m_KeyL3()
    {}

    EnergyProductionEntity(const QString &name,
                           const QString &keyL1,
                           const QString &keyL2,
                           const QString &keyL3)
      : m_Name(name)
      , m_KeyL1(keyL1)
      , m_KeyL2(keyL2)
      , m_KeyL3(keyL3)
    {}

    QString m_Name;

    QString m_KeyL1;
    QString m_KeyL2;
    QString m_KeyL3;

  }; // EnergyProductionEntity

  class EnergyConsumptionEntity
  {
  public:

    EnergyConsumptionEntity()
      : m_Name()
      , m_KeyL1()
      , m_KeyL2()
      , m_KeyL3()
      , m_Priority(0)
    {}

    EnergyConsumptionEntity(const QString &name,
                            const QString &keyL1,
                            const QString &keyL2,
                            const QString &keyL3,
                            int priority)
      : m_Name(name)
      , m_KeyL1(keyL1)
      , m_KeyL2(keyL2)
      , m_KeyL3(keyL3)
      , m_Priority(priority)
    {}

    bool operator ==(const EnergyConsumptionEntity &other)
    {
      return m_Name == other.m_Name;
    }

    QString m_Name;

    QString m_KeyL1;
    QString m_KeyL2;
    QString m_KeyL3;

    int m_Priority;

  }; // EnergyConsumptionEntity

  class Configuration
  {
  public:

    Configuration()
      : m_EnergyProductionEntity()
      , m_QList_EnergyConsumptionEntity()
    {}

    EnergyProductionEntity m_EnergyProductionEntity;

    QList<EnergyConsumptionEntity> m_QList_EnergyConsumptionEntity;

  }; // Configuration

  class Result
  {
  public:

    class EnergyProductionEntity
    {
    public:

      QString m_Name;

      class L1
      {
      public:

        L1()
          : m_Production(0.0)
          , m_SelfConsumption(0.0)
        {}

        double m_Production;
        double m_SelfConsumption;
      }; // L1

      L1 m_L1;

      class L2
      {
      public:

        L2()
          : m_Production(0.0)
          , m_SelfConsumption(0.0)
        {}

        double m_Production;
        double m_SelfConsumption;
      }; // L2

      L2 m_L2;

      class L3
      {
      public:

        L3()
          : m_Production(0.0)
          , m_SelfConsumption(0.0)
        {}

        double m_Production;
        double m_SelfConsumption;
      }; // L3

      L3 m_L3;

      class Total
      {
      public:

        Total()
          : m_Production(0.0)
          , m_SelfConsumption(0.0)
        {}

        double m_Production;
        double m_SelfConsumption;
      }; // Total

      Total m_Total;

    }; // EnergyProductionEntity

    EnergyProductionEntity m_EnergyProductionEntity;

    class EnergyConsumptionEntity
    {
    public:

      QString m_Name;

      class L1
      {
      public:

        L1()
          : m_Consumption(0.0)
          , m_SelfConsumption(0.0)
        {}

        double m_Consumption;
        double m_SelfConsumption;
      }; // L1

      L1 m_L1;

      class L2
      {
      public:

        L2()
          : m_Consumption(0.0)
          , m_SelfConsumption(0.0)
        {}

        double m_Consumption;
        double m_SelfConsumption;
      }; // L2

      L2 m_L2;

      class L3
      {
      public:

        L3()
          : m_Consumption(0.0)
          , m_SelfConsumption(0.0)
        {}

        double m_Consumption;
        double m_SelfConsumption;
      }; // L3

      L3 m_L3;

      class Total
      {
      public:

        Total()
          : m_Consumption(0.0)
          , m_SelfConsumption(0.0)
        {}

        double m_Consumption;
        double m_SelfConsumption;
      }; // Total

      Total m_Total;

    }; // EnergyConsumptionEntity

    QMap<QString, EnergyConsumptionEntity> m_QMap_EnergyConsumptionEntity;

  }; // Result

  explicit EnergyCalculator(const Configuration &configuration,
                            QObject *parent = nullptr);


  Result DistributeEnergy(const QList<QVariantMap> &qList_QVariantMap_Rows);

private:

  Configuration m_Configuration;

};

#endif // ENERGYCALCULATOR_H
