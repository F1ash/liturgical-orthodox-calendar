#include "mainwindow.h"
#include <QDebug>

QString SCRIPT = QString::fromUtf8("<html><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" /><body background=\"%1\" > <h1 align=\"center\"><font color=\"red\">ПРАВОСЛАВНЫЙ КАЛЕНДАРЬ</font></h1> <div align=\"center\">");
QString SCRIPT1 = QString::fromUtf8("</div> <div><script language=\"Javascript\"> var d=new Date(); var to=-4-d.getTimezoneOffset()/60; document.write ( '<script language=\"Javascript\" src=\"http://script.days.ru/calendar.php?tmshift='+to +'");
QString SCRIPT2 = QString::fromUtf8("\"><\\/script>');</script></br>");
QString SCRIPT3 = QString::fromUtf8("</div></body></html>");

QString LITURGY = QString::fromUtf8("<div class=\"sluzh\"><a href=\"http://www.patriarchia.ru/bu/%1/print.html\">Богослужебные указания</a>");

//QString ICON_SCRIPT = QString::fromUtf8("<script language=\"Javascript\" src=\"http://script.pravoslavie.ru/icon.php\"></script>");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    closeFlag = false;
    this->initialSettingsDock();
    readStartVisibility();
    this->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    this->restoreGeometry(settingsWidget->get_Geometry());
    this->setMinimumSize(100, 100);

    fileTemplate.append(QDir::tempPath());
    fileTemplate.append(QDir::separator());
    baseFile = new QTemporaryFile(this);
    baseFile->setAutoRemove(true);
    connect(settingsWidget, SIGNAL(settingsApplied()), this, SLOT(reloadCalendar()));

    fonFile = new QTemporaryFile(this);
    fonFile->setAutoRemove(true);
    iconFile = new QTemporaryFile(this);
    iconFile->setAutoRemove(true);

    manager = new QNetworkAccessManager(this);
    diskCache = new QNetworkDiskCache(this);
    cacheDir = QDesktopServices::storageLocation(QDesktopServices::CacheLocation);
    while (cacheDir.endsWith(QDir::separator()))
      {
        cacheDir.remove(cacheDir.length()-1, 1);
      };
    cacheDir.append(QDir::separator()).append("LiturgicalOrthodoxCalendar");
    diskCache->setCacheDirectory(cacheDir);
    manager->setCache(diskCache);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    connect(this, SIGNAL(cacheChecked()), this, SLOT(trayIconInitiate()));
    checkCache();
}

MainWindow::~MainWindow()
{
    delete calendarView;
    calendarView = 0;
    delete trayIconMenu;
    trayIconMenu = 0;
    delete trayIcon;
    trayIcon = 0;
    delete settingsWidget;
    settingsWidget = 0;
    delete settingsDock;
    settingsDock = 0;
    delete baseFile;
    baseFile = 0;
    delete fonFile;
    fonFile = 0;
    delete iconFile;
    iconFile = 0;
    delete manager;
    manager = 0;
    delete diskCache;
    diskCache = 0;
    delete _reloadAction;
    _reloadAction = 0;
    delete _forwardAction;
    _forwardAction = 0;
    delete _backwardAction;
    _backwardAction = 0;
    delete _settingsAction;
    _settingsAction = 0;
}
void MainWindow::trayIconInitiate()
{
    trayIconMenu = new QMenu(this);
    hideAction = trayIconMenu->addAction(QString(" "));
    trayIconMenu->addSeparator();
    showSettings = trayIconMenu->addAction(QString().fromUtf8("Настройки"));
    showSettings->setIcon ( QIcon().fromTheme("settings") );
    closeAction = trayIconMenu->addAction(QString().fromUtf8("Закрыть"));
    closeAction->setIcon ( QIcon().fromTheme("shutdown") );
    connect(hideAction, SIGNAL(triggered()), this, SLOT(changeCalendarVisibility()));
    connect(showSettings, SIGNAL(triggered()), this, SLOT(settingsAction()));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(closeCalendar()));

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setToolTip(QString().fromLocal8Bit("Православный Календарь"));
    trayIcon->setIcon(QIcon(iconFile->fileName()));
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, \
    SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    showCalendar();
}
void MainWindow::showCalendar()
{
    calendarView = new QWebView(this);
    calendarView->settings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
    calendarView->settings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    calendarView->settings()->setOfflineWebApplicationCacheQuota(50000000);
    calendarView->settings()->setOfflineStorageDefaultQuota(50000000);
    calendarView->settings()->setOfflineStoragePath(cacheDir);
    calendarView->settings()->setOfflineWebApplicationCachePath(cacheDir);
    calendarView->settings()->setIconDatabasePath(cacheDir);

    calendarView->setContextMenuPolicy(Qt::ActionsContextMenu);
    _reloadAction = new QAction(QString().fromUtf8("Обновить"), calendarView);
    _reloadAction->setIcon ( QIcon().fromTheme("view-refresh") );
    calendarView->addAction(_reloadAction);
    connect(_reloadAction, SIGNAL(triggered()), this, SLOT(reloadAction()));
    _forwardAction = new QAction(QString().fromUtf8("Вперёд"), calendarView);
    _forwardAction->setIcon ( QIcon().fromTheme("go-next") );
    calendarView->addAction(_forwardAction);
    connect(_forwardAction, SIGNAL(triggered()), this, SLOT(forwardAction()));
    _backwardAction = new QAction(QString().fromUtf8("Назад"), calendarView);
    _backwardAction->setIcon ( QIcon().fromTheme("go-previous") );
    calendarView->addAction(_backwardAction);
    connect(_backwardAction, SIGNAL(triggered()), this, SLOT(backwardAction()));
    _settingsAction = new QAction(QString().fromUtf8("Настройки"), calendarView);
    _settingsAction->setIcon ( QIcon().fromTheme("settings") );
    calendarView->addAction(_settingsAction);
    connect(_settingsAction, SIGNAL(triggered()), this, SLOT(settingsAction()));

    reloadCalendar();
    calendarView->show();
    this->setCentralWidget(calendarView);
    this->setFocusProxy(calendarView);
    this->setDockOptions(QMainWindow::AnimatedDocks);
    changeCalendarVisibility(true);
}
QByteArray MainWindow::buildScript()
{
  QString param1 = "";
  QString param2 = "";
  QString param3 = "";

  //if (settingsWidget->showDayIcon()) param1 = ICON_SCRIPT;

  param2.append( QString("&dayicon=%1").arg(settingsWidget->showDayIcon()) );
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
  //qDebug()<<date.toString(Qt::ISODate);
  if (settingsWidget->showLiturgy())
    {
      QString _date = date.toString(Qt::ISODate);
      QStringList _d = _date.split("-");
      _d.removeFirst();
      param2.append(QString("&date=%1").arg(_d.join("")));
      param3 = LITURGY.arg(_date);
    };

  QString data = SCRIPT.arg(fonFile->fileName());
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
}
void MainWindow::changeCalendarVisibility(const bool invert)
{
  bool visible;
  if (!invert) visible = this->isVisible();
  else visible = !readStartVisibility();
  if (visible)
    {
      this->hide();
      hideAction->setText (QString().fromUtf8("Развернуть"));
      hideAction->setIcon ( QIcon().fromTheme("arrow-up"));
    }
  else
    {
      this->show();
      hideAction->setText (QString().fromUtf8("Свернуть"));
      hideAction->setIcon ( QIcon().fromTheme("arrow-down"));
    };
}
void MainWindow::changeCalendarVisibility()
{
  changeCalendarVisibility(false);
}
void MainWindow::settingsAction ()
{
  settingsDock->show();
  settingsWidget->setFocusToSettings();
  if (!this->isVisible()) changeCalendarVisibility();
}
void MainWindow::reloadAction()
{
  calendarView->reload();
}
void MainWindow::forwardAction()
{
  calendarView->forward();
}
void MainWindow::backwardAction()
{
  calendarView->back();
}
void MainWindow::leaveEvent(QEvent *ev)
{
  qDebug("jkljljllj");  //Qt::ActiveWindowFocusReason
  if (ev->type()==QEvent::FocusOut or ev->type()==QEvent::GraphicsSceneHoverLeave)
    {
      ev->ignore();
      this->changeCalendarVisibility();
    };
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
  this->close();
}
void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason r)
{
  if (r==QSystemTrayIcon::Trigger) changeCalendarVisibility();
}
void MainWindow::reloadCalendar()
{
  if (baseFile->exists()) baseFile->remove();
  baseFile->setFileName(QString("").append(fileTemplate).append("_orthodox_calendar.html"));
  baseFile->open();
  baseFile->write(buildScript().constData());
  baseFile->close();
  calendarView->load(QUrl::fromUserInput(baseFile->fileName()));
}
void MainWindow::checkCache()
{
  QNetworkRequest fonRequest = QNetworkRequest(QUrl::fromUserInput("http://www.pravoslavie.ru/images/fon1.jpg"));
  fonRequest.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
  manager->get(fonRequest);

  QNetworkRequest iconRequest = QNetworkRequest(QUrl::fromUserInput("http://www.pravoslavie.ru/images/znak2.gif"));
  iconRequest.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
  manager->get(iconRequest);
}
void MainWindow::replyFinished(QNetworkReply* reply)
{
  static int count = 0;
  count++;
  //QVariant fromCache = reply->attribute(QNetworkRequest::SourceIsFromCacheAttribute);
  //qDebug() << "page from cache?" << fromCache.toBool();
  //if ( reply->error()==QNetworkReply::NoError ) qDebug()<<reply->url()<<" "<<count;
  //else qDebug()<<reply->url()<<"Error: "<<reply->error()<<" "<<count;

  QTemporaryFile *file;
  QString fileName= QString("").append(fileTemplate);
  if (reply->request().url().toString().endsWith("fon1.jpg"))
    {
      fileName.append("fon");
      file = fonFile;
    }
  else
    {
      fileName.append("icon");
      file = iconFile;
    };
  file->setFileName(fileName);
  file->open();
  file->write(reply->readAll());
  file->close();
  reply->deleteLater();
  if (count==2)
    {
      emit cacheChecked();
      count = 0;
    };
}
