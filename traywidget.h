#include "time.h"
#include <QSystemTrayIcon>
#include <QMenu>

class TrayIcon : public QSystemTrayIcon
{
  Q_OBJECT
public :
  explicit TrayIcon(QWidget *parent = 0);

  //QAction *hideAction;
  QAction *reloadAction;
  QAction *closeAction;

private :
  QMenu *trayIconMenu;
};

