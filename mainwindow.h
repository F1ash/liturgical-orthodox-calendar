#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QCloseEvent>
#include <QScrollArea>
#include "settingswidget.h"
#include "networkstuff.h"
#include "traywidget.h"
#include "toolbar.h"
#include "calendarwidget.h"
#include "addbookmarkdialog.h"
#include "statusbar.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    qreal firstZoom;
    bool closeFlag;
    QScrollArea *scroll;
    QDockWidget *settingsDock;
    SettingsWidget *settingsWidget;
    NetworkManager *netManager;
    TrayIcon *trayIcon;
    ToolBar *toolBar;
    StatusBar *statusBar;
    CalendarView *calendarView;
    BookmarkDialog *dialog;
    QStringList history;

private slots:
    void initialSettingsDock();
    void initNetworkStuff();
    void initAppWidgets();
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
    void closeEvent(QCloseEvent *);
    void zoomUpAction();
    void zoomOrigAction();
    void zoomDownAction();
    void closeCalendar();
    void trayIconActivated(QSystemTrayIcon::ActivationReason r);
    void reloadCalendar();
    void clickedLink(QUrl);
    void addBookmark(QString &);
    void addBookmarkAction(QString &);
    void addBookmarkDialog();
    void initBookmarks();
    void loadBookmarkLink(QAction*);
    void removeBookmark(QString);
    void reloadAppAction();
    void initHistory(QUrl);
    void removeHistoryItem(QString);
    void loadHistoryLink(QAction*);
    void showPrevDay();
    void showNextDay();
};

#endif // MAINWINDOW_H
