#include "mainwindow.h"
#include "data.cpp"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  closeFlag = false;
  initialSettingsDock();
  setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
  restoreGeometry(settingsWidget->get_Geometry());
  setMinimumSize(100, 100);
  statusBar = new StatusBar(this);
  setStatusBar(statusBar);

  initNetworkStuff();
}

MainWindow::~MainWindow()
{
    delete settingsWidget;
    settingsWidget = 0;
    delete settingsDock;
    settingsDock = 0;
    delete netManager;
    netManager = 0;
    delete calendarView;
    calendarView = 0;
    delete statusBar;
    statusBar = 0;
    delete toolBar;
    toolBar = 0;
    delete trayIcon;
    trayIcon = 0;
}
void MainWindow::initialSettingsDock ()
{
  settingsDock = new QDockWidget(QString().fromUtf8("Настройки"), this );
  scroll = new QScrollArea(settingsDock);
  settingsWidget = new SettingsWidget( scroll );
  scroll->setWidget(settingsWidget);
  settingsDock->setWidget ( scroll );

  settingsDock->setAllowedAreas ( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
  settingsDock->setFeatures ( QDockWidget::AllDockWidgetFeatures );

  addDockWidget( Qt::LeftDockWidgetArea, settingsDock );
  settingsDock->hide();
  connect(settingsWidget, SIGNAL(settingsApplied()), this, SLOT(reloadCalendar()));
}
void MainWindow::initNetworkStuff()
{
  netManager = new NetworkManager(this);
  connect(netManager, SIGNAL(cacheChecked()), this, SLOT(initAppWidgets()));
  netManager->checkCache();
}
void MainWindow::initAppWidgets()
{
  disconnect(netManager, SIGNAL(cacheChecked()), this, SLOT(initAppWidgets()));
  initTrayIcon();
  initToolBar();
  initCalendar();
}
void MainWindow::initToolBar()
{
  toolBar = new ToolBar(this);
  this->initBookmarks();
  this->addToolBar(settingsWidget->get_ToolBarArea(), toolBar);
  connect(toolBar->bookmarkMenu, SIGNAL(triggered(QAction*)), this, SLOT(loadBookmarkLink(QAction*)));
  connect(toolBar, SIGNAL(actionRemoved(QString)), this, SLOT(removeBookmark(QString)));
  connect(toolBar->_reloadAction, SIGNAL(triggered()), this, SLOT(reloadAction()));
  connect(toolBar->_stopAction, SIGNAL(triggered()), this, SLOT(stopAction()));
  connect(toolBar->_forwardAction, SIGNAL(triggered()), this, SLOT(forwardAction()));
  connect(toolBar->_backwardAction, SIGNAL(triggered()), this, SLOT(backwardAction()));
  connect(toolBar->_zoomUpAction, SIGNAL(triggered()), this, SLOT(zoomUpAction()));
  connect(toolBar->_zoomOrigAction, SIGNAL(triggered()), this, SLOT(zoomOrigAction()));
  connect(toolBar->_zoomDownAction, SIGNAL(triggered()), this, SLOT(zoomDownAction()));
  connect(toolBar->_settingsAction, SIGNAL(triggered()), this, SLOT(settingsAction()));
  connect(toolBar->_bookmarkAddAction, SIGNAL(triggered()), this, SLOT(addBookmarkDialog()));
}
void MainWindow::initTrayIcon()
{
  trayIcon = new TrayIcon(this);
  if (netManager->iconFile->exists())
    trayIcon->setIcon(QIcon(netManager->iconFile->fileName()));
  else trayIcon->setIcon(QIcon::fromTheme("dialog-cancel"));
  connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, \
  SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
  connect(trayIcon->hideAction, SIGNAL(triggered()), this, SLOT(changeCalendarVisibility()));
  connect(trayIcon->reloadAction, SIGNAL(triggered()), this, SLOT(reloadAppAction()));
  connect(trayIcon->closeAction, SIGNAL(triggered()), this, SLOT(closeCalendar()));
}
void MainWindow::initCalendar()
{
  calendarView = new CalendarView(this);
  firstZoom = calendarView->zoomFactor();
  calendarView->settings()->setOfflineStoragePath(netManager->cacheDir);
  calendarView->settings()->setIconDatabasePath(netManager->cacheDir);
  calendarView->settings()->setLocalStoragePath(netManager->cacheDir);

  connect(calendarView, SIGNAL(linkClicked(QUrl)), this, SLOT(clickedLink(QUrl)));
  connect(calendarView, SIGNAL(loadStarted()), statusBar, SLOT(_loadStarted()));
  connect(calendarView, SIGNAL(loadFinished(bool)), statusBar, SLOT(_loadFinished(bool)));
  connect(calendarView, SIGNAL(loadProgress(int)), statusBar, SLOT(_loadProgress(int)));

  connect(calendarView->_reloadAction, SIGNAL(triggered()), this, SLOT(reloadAction()));
  connect(calendarView->_stopAction, SIGNAL(triggered()), this, SLOT(stopAction()));
  connect(calendarView->_forwardAction, SIGNAL(triggered()), this, SLOT(forwardAction()));
  connect(calendarView->_backwardAction, SIGNAL(triggered()), this, SLOT(backwardAction()));
  //connect(calendarView->_settingsAction, SIGNAL(triggered()), this, SLOT(settingsAction()));
  connect(calendarView->_bookmarkAddAction, SIGNAL(triggered()), this, SLOT(addBookmarkDialog()));

  this->setCentralWidget(calendarView);
  this->setFocusProxy(calendarView);
  this->setDockOptions(QMainWindow::AnimatedDocks);
  reloadCalendar();
  calendarView->show();
  changeCalendarVisibility(true);
}
QByteArray MainWindow::buildScript()
{
  QString param1 = "";
  QString param2 = "";
  QString param3 = "";

  param2.append( QString("&dayicon=%1").arg(settingsWidget->showDayIcon()) );
  param2.append( QString("&target=0") ); // open links in old (current) window
  param2.append( QString("&name=0&life=1") );
  param2.append( QString("&images=%1").arg(settingsWidget->showImages()) );
  param2.append( QString("&vek=%1").arg(settingsWidget->showVek()) );
  param2.append( QString("&bold=%1").arg(settingsWidget->showBold()) );
  param2.append( QString("&para=%1").arg(settingsWidget->showPara()) );
  param2.append( QString("&tipikon=%1").arg(settingsWidget->showTipikon()) );
  param2.append( QString("&trapeza=%1").arg(settingsWidget->showTrapeza()) );
  param2.append( QString("&feofan=%1").arg(settingsWidget->showFeofan()) );
  QString church;
  if (settingsWidget->showChurch()==2) church = QString("&church=all");
  else church = QString("&church=%1").arg(settingsWidget->showChurch());
  param2.append( church );
  param2.append( QString("&chten=%1").arg(settingsWidget->showChten()) );
  param2.append( QString("&hrams=0&hram=0") );
  QDate date = settingsWidget->selectedDate();
  //qDebug()<<date.toString(Qt::ISODate)<<" "<<QDate::fromJulianDay(date.toJulianDay()-13);
  QString _date = date.toString(Qt::ISODate);
  QStringList _d = _date.split("-");
  _d.removeFirst();
  param2.append(QString("&date=%1").arg(_d.join("")));
  if (settingsWidget->showLiturgy()) param3 = LITURGY.arg(_date);

  QString data = SCRIPT.arg(netManager->fonFile->fileName()).arg(SEARCH);
  data.append(param1);
  data.append(SCRIPT1);
  data.append(param2);
  data.append(SCRIPT2);
  data.append(param3);
  data.append(SCRIPT3);
  //qDebug()<<data;
  return data.toUtf8();
}
bool MainWindow::readStartVisibility()
{
  if (settingsWidget->showInStart()) return true;
  else return false;
}
void MainWindow::changeCalendarVisibility(const bool invert)
{
  bool visible;
  if (!invert) visible = this->isVisible();
  else visible = !readStartVisibility();
  if (visible)
    {
      this->hide();
      trayIcon->hideAction->setText (QString().fromUtf8("Развернуть"));
      trayIcon->hideAction->setIcon ( QIcon().fromTheme("arrow-up"));
    }
  else
    {
      this->show();
      trayIcon->hideAction->setText (QString().fromUtf8("Свернуть"));
      trayIcon->hideAction->setIcon ( QIcon().fromTheme("arrow-down"));
    };
}
void MainWindow::changeCalendarVisibility()
{
  changeCalendarVisibility(false);
}
void MainWindow::settingsAction ()
{
  if (!settingsDock->isVisible())
    {
      settingsDock->show();
      settingsWidget->setFocusToSettings();
      if (!this->isVisible()) changeCalendarVisibility();
    }
  else settingsDock->hide();
}
void MainWindow::reloadAction()
{
  calendarView->reload();
}
void MainWindow::stopAction()
{
  statusBar->progress->setEnabled(false);
  calendarView->stop();
}
void MainWindow::forwardAction()
{
  calendarView->forward();
}
void MainWindow::backwardAction()
{
  calendarView->back();
}
void MainWindow::closeEvent(QCloseEvent *ev)
{
  if (!closeFlag)
    {
      this->changeCalendarVisibility();
      ev->ignore();
    }
  else ev->accept();
}
void MainWindow::closeCalendar()
{
  closeFlag = true;
  settingsWidget->set_Geometry(this->saveGeometry());
  settingsWidget->set_ToolBarArea(this->toolBarArea(toolBar));
  this->close();
}
void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason r)
{
  if (r==QSystemTrayIcon::Trigger) changeCalendarVisibility();
}
void MainWindow::reloadCalendar()
{
  if (netManager->baseFile->exists()) netManager->baseFile->remove();
  netManager->baseFile->setFileName(QString("").append(netManager->fileTemplate).append("_orthodox_calendar.html"));
  netManager->baseFile->open();
  netManager->baseFile->write(buildScript().constData());
  netManager->baseFile->close();
  calendarView->load(QUrl::fromUserInput(netManager->baseFile->fileName()));
}
void MainWindow::clickedLink(QUrl url)
{
  //qDebug()<<url;
  calendarView->load(url);
}
void MainWindow::zoomUpAction()
{
  qreal zoom = calendarView->zoomFactor()*1.333;
  calendarView->setZoomFactor(zoom);
}
void MainWindow::zoomDownAction()
{
  qreal zoom = calendarView->zoomFactor()*0.75;
  calendarView->setZoomFactor(zoom);
}
void MainWindow::zoomOrigAction()
{
  calendarView->setZoomFactor(firstZoom);
}
void MainWindow::addBookmarkAction(QString &bookmarkName)
{
  //qDebug()<< bookmarkName<<" <||>"<<calendarView->url();
  settingsWidget->settings->beginGroup("bookmarks");
  QStringList keys = settingsWidget->settings->allKeys();
  if (!keys.contains(bookmarkName) and !bookmarkName.isEmpty())
    {
      settingsWidget->settings->setValue(bookmarkName, QVariant(calendarView->url().toString()));
    };
  settingsWidget->settings->endGroup();
  settingsWidget->settings->sync();
  initBookmarks();
}
void MainWindow::addBookmarkDialog()
{
  dialog = new BookmarkDialog(this, Qt::Dialog);
  connect(dialog, SIGNAL(bookmarkName(QString&)), this, SLOT(addBookmark(QString&)));
  dialog->setAttribute( Qt::WA_DeleteOnClose , true);
  //qDebug()<<dialog->testAttribute ( Qt::WA_DeleteOnClose )<<" ::WA_DeleteOnClose";
  dialog->exec();
}
void MainWindow::addBookmark(QString &s)
{
  disconnect(dialog, SIGNAL(bookmarkName(QString&)), this, SLOT(addBookmark(QString&)));
  addBookmarkAction(s);
}
void MainWindow::initBookmarks()
{
  QStringList bookmarks;
  bookmarks = settingsWidget->initBookmarks();
  toolBar->bookmarkMenu->clear();
  //qDebug()<< iconFile->fileName();
  toolBar->bookmarkMenu->setCursor(QCursor(Qt::PointingHandCursor));
  //toolBar->bookmarkMenu->setCursor(QCursor(QPixmap(netManager->iconFile->fileName())));
  toolBar->bookmarkMenu->setToolTip(QString::fromUtf8("ЗАКЛАДКИ"));
  toolBar->bookmarkMenu->addSeparator();
  for (int i = 0; i < bookmarks.size(); ++i)
    {
      toolBar->bookmarkMenu->addAction(bookmarks.at(i));
      if (i==2)
        {
          toolBar->bookmarkMenu->addAction(QString::fromUtf8("Начальная страница"));
          toolBar->bookmarkMenu->addSeparator();
        };
    };
}
void MainWindow::loadBookmarkLink(QAction* act)
{
  QString link;
  if ( act->text() == QString::fromUtf8("Начальная страница") )
    link = netManager->baseFile->fileName();
  else link = settingsWidget->readBookmarkLink(act->text());
  calendarView->load(QUrl::fromUserInput(link));
}
void MainWindow::removeBookmark(QString key)
{
  //qDebug()<<key<<" removed";
  settingsWidget->settings->beginGroup("bookmarks");
  settingsWidget->settings->remove(key);
  settingsWidget->settings->endGroup();
  settingsWidget->settings->sync();
  initBookmarks();
}
void MainWindow::reloadAppAction()
{
  netManager->checkCache();
  initBookmarks();
  if (netManager->iconFile->exists())
    trayIcon->setIcon(QIcon(netManager->iconFile->fileName()));
  else trayIcon->setIcon(QIcon::fromTheme("dialog-cancel"));
  reloadCalendar();
  calendarView->show();
  changeCalendarVisibility(true);
}
