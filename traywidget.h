#include "time.h"
#include <QSystemTrayIcon>
#include <QMenu>

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public :
    explicit TrayIcon(QWidget *parent = Q_NULLPTR);

    //QAction *hideAction;
    QAction *reloadAction;
    QAction *closeAction;

private :
    QMenu *trayIconMenu;
};

