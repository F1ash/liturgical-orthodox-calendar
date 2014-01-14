#include "traywidget.h"

TrayIcon::TrayIcon(QWidget *parent = 0)
  : QSystemTrayIcon(parent)
{
  setIcon(QIcon::fromTheme("xorg"));
  hideAction = new QAction(QString().fromUtf8(""), this);
  reloadAction = new QAction(QString().fromUtf8("Перезапустить"), this);
  reloadAction->setIcon ( QIcon::fromTheme("view-refresh") );
  closeAction = new QAction(QString().fromUtf8("Закрыть"), this);
  closeAction->setIcon ( QIcon::fromTheme("application-exit") );

  trayIconMenu = new QMenu(parent);
  trayIconMenu->addAction(hideAction);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(reloadAction);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(closeAction);

  setToolTip(QString().fromLocal8Bit("Православный Календарь 2014"));
  setContextMenu(trayIconMenu);
  show();
}
TrayIcon::~TrayIcon()
{
  trayIconMenu->clear();
  delete trayIconMenu;
  trayIconMenu = 0;
  delete hideAction;
  hideAction = 0;
  delete closeAction;
  closeAction = 0;
}
