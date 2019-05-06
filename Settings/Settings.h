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

#ifndef SETTINGS_H
#define SETTINGS_H

// Qt includes -----------------------------
#include <QSettings>

class Settings : public QSettings
{
  Q_OBJECT

public:

  // Constructor
  explicit Settings(QObject *parent = 0);
  virtual ~Settings();

public:

  // Application settings
  QString get_CurrentDocument () const;
  void    set_CurrentDocument (const QString &currentDocument);

};

#endif // SETTINGS_H
