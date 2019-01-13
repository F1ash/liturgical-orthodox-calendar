#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QScrollArea>
#include <QPixmap>
#include <QClipboard>
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
    explicit MainWindow(QWidget *parent = Q_NULLPTR);

private:
    qreal firstZoom;
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
    QClipboard *clipBoard;

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
    void copySelectedObject();
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
