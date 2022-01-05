#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QMenu>

class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit ToolBar(QWidget *parent = Q_NULLPTR);

    QAction *_reloadAction;
    QAction *_stopAction;
    QAction *_forwardAction;
    QAction *_backwardAction;
    QAction *_zoomUpAction;
    QAction *_zoomOrigAction;
    QAction *_zoomDownAction;
    QAction *_settingsAction;
    QAction *_bookmarkAddAction;
    QAction *_nextDayAction;
    QAction *_prevDayAction;

    QMenu *bookmarkMenu;
    QMenu *historyMenu;

signals:
    void actionRemoved(QString);
    void historyItemRemoved(QString);

private:
    QToolButton *bookmarkButton;
    QAction *_bookmarkAction;
    QMenu *clearMenu;
    QToolButton *historyButton;
    QAction *_historyAction;
    QMenu *clearHistoryMenu;
    QAction *_clearAction;
    QAction *_clearHistoryAction;
    QAction *currentAction;

private slots:
    void initActions();
    void addToolButton();
    void showCustomMenu(QPoint);
    void clearAction();
    void addHistoryToolButton();
    void showHistoryMenu(QPoint);
    void clearHistoryAction();
};

