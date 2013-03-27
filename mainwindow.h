#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QString>
#include <QIcon>
#include <QtWebKit/QWebView>
#include <QDockWidget>
#include <QFocusEvent>
#include <QSettings>
#include <QTemporaryFile>
#include <QByteArray>
#include <QDate>
#include <QDir>
#include <QScrollArea>
#include "settingswidget.h"
#include <QDesktopServices>
#include <QNetworkDiskCache>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QSystemTrayIcon *trayIcon;
    QWebView *calendarView;
    QMenu *trayIconMenu;
    QAction *showSettings;
    QAction *hideAction;
    QAction *closeAction;
    QAction *_reloadAction;
    QAction *_forwardAction;
    QAction *_backwardAction;
    QAction *_settingsAction;
    QDockWidget *settingsDock;
    SettingsWidget *settingsWidget;
    QScrollArea *scroll;
    void initialSettingsDock();
    void leaveEvent(QEvent *);
    void closeEvent(QCloseEvent *);
    bool closeFlag;
    QString fileTemplate;
    QTemporaryFile *baseFile;
    QTemporaryFile *fonFile;
    QTemporaryFile *iconFile;
    QNetworkAccessManager *manager;
    QNetworkDiskCache *diskCache;
    QString cacheDir;

signals:
    void cacheChecked();

private slots:
    void trayIconInitiate();
    void showCalendar();
    QByteArray buildScript();
    bool readStartVisibility();
    void changeCalendarVisibility(const bool invert);
    void changeCalendarVisibility();
    void settingsAction();
    void reloadAction();
    void forwardAction();
    void backwardAction();
    void closeCalendar();
    void trayIconActivated(QSystemTrayIcon::ActivationReason r);
    void reloadCalendar();
    void checkCache();
    void replyFinished(QNetworkReply*);
};

#endif // MAINWINDOW_H
