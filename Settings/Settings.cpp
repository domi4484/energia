/********************************************************************
 *                                                                 *
 * Lowerspot                                                       *
 *                                                                 *
 * Author:       Damiano Lombardi                                  *
 * Created:      26.05.2015                                        *
 *                                                                 *
 * Copiright (c) 2015 Damiano Lombardi                             *
 *                                                                 *
********************************************************************/

// Files includes --------------------------
#include "Settings.h"

//-----------------------------------------------------------------------------------------------------------------------------

Settings::Settings(QObject *parent)
  : QSettings(parent)
{
}

//-----------------------------------------------------------------------------------------------------------------------------

Settings::~Settings()
{

}

//-----------------------------------------------------------------------------------------------------------------------------

QString Settings::get_CurrentDocument() const
{
  return QSettings::value("CurrentDocument", "").toString();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Settings::set_CurrentDocument(const QString &currentDocument)
{
  QSettings::setValue("CurrentDocument", currentDocument);
}

