#include "traywidget.h"

TrayIcon::TrayIcon(QWidget *parent)
  : QSystemTrayIcon(parent)
{
  setIcon(QIcon(":/icons/logo.png"));
  //hideAction = new QAction(QString::fromUtf8(""), this);
  reloadAction = new QAction(QString::fromUtf8("Перезапустить"), this);
  reloadAction->setIcon ( QIcon::fromTheme("view-refresh") );
  closeAction = new QAction(QString::fromUtf8("Закрыть"), this);
  closeAction->setIcon ( QIcon::fromTheme("application-exit") );

  trayIconMenu = new QMenu(parent);
  //trayIconMenu->addAction(hideAction);
  //trayIconMenu->addSeparator();
  trayIconMenu->addAction(reloadAction);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(closeAction);

  time_t rawtime;
  struct tm * timeinfo;
  char buffer [80];
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  strftime (buffer,80,"%Y",timeinfo);
  QString _title = QString::fromLocal8Bit("Православный Календарь");
  setToolTip(QString("%1 %2").arg(_title).arg(buffer));
  setContextMenu(trayIconMenu);
  show();
}
