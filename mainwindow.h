#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QString>
#include <QIcon>
#include <QtWebKit/QWebView>
#include <QDockWidget>
#include <QCloseEvent>
#include <QSettings>
#include <QTemporaryFile>
#include <QByteArray>
#include <QDate>
#include <QDir>
#include <QScrollArea>
#include <QToolBar>
#include <QStatusBar>
#include <QProgressBar>
#include <QDesktopServices>
#include <QNetworkDiskCache>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include "settingswidget.h"
#include "toolbar.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    SettingsWidget *settingsWidget;

private:
    qreal firstZoom;
    QSystemTrayIcon *trayIcon;
    QWebView *calendarView;
    QMenu *trayIconMenu;
    QAction *hideAction;
    QAction *closeAction;
    QAction *_reloadAction;
    QAction *_stopAction;
    QAction *_forwardAction;
    QAction *_backwardAction;
    QAction *_zoomUpAction;
    QAction *_zoomOrigAction;
    QAction *_zoomDownAction;
    QAction *_settingsAction;
    QAction *_bookmarkAddAction;
    QAction *_bookmarkDelAction;
    QDockWidget *settingsDock;
    QScrollArea *scroll;
    void initialSettingsDock();
    void closeEvent(QCloseEvent *);
    bool closeFlag;
    QString fileTemplate;
    QTemporaryFile *baseFile;
    QTemporaryFile *fonFile;
    QTemporaryFile *iconFile;
    QNetworkAccessManager *manager;
    QNetworkDiskCache *diskCache;
    QString cacheDir;
    ToolBar *toolBar;
    QProgressBar *progress;
    QStatusBar *StatusBar;

signals:
    void cacheChecked();

private slots:
    void initAppWidgets();
    void initActions();
    void initToolBar();
    void initTrayIcon();
    void initCalendar();
    QByteArray buildScript();
    bool readStartVisibility();
    void changeCalendarVisibility(const bool invert);
    void changeCalendarVisibility();
    void settingsAction();
    void reloadAction();
    void stopAction();
    void forwardAction();
    void backwardAction();
    void zoomUpAction();
    void zoomOrigAction();
    void zoomDownAction();
    void closeCalendar();
    void trayIconActivated(QSystemTrayIcon::ActivationReason r);
    void reloadCalendar();
    void checkCache();
    void replyFinished(QNetworkReply*);
    void clickedLink(QUrl);
    void _loadStarted();
    void _loadFinished(bool);
    void _loadProgress(int);
    void addBookmarkAction();
    void initBookmarks();
    void loadBookmarkLink(QAction*);
};

#endif // MAINWINDOW_H
