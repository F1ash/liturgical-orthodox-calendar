#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QMenu>

class ToolBar : public QToolBar
{
  Q_OBJECT;
public:
  ToolBar(QWidget *parent);
  ~ToolBar();

  QAction *_reloadAction;
  QAction *_stopAction;
  QAction *_forwardAction;
  QAction *_backwardAction;
  QAction *_zoomUpAction;
  QAction *_zoomOrigAction;
  QAction *_zoomDownAction;
  QAction *_settingsAction;
  QAction *_bookmarkAddAction;

  QMenu *bookmarkMenu;

signals:
  void actionRemoved(QString);

private:
  QToolButton *bookmarkButton;
  QAction *_bookmarkAction;
  QMenu *clearMenu;
  QAction *_clearAction;
  QAction *currentAction;

private slots:
  void initActions();
  void addToolButton();
  void showCustomMenu(QPoint);
  void clearAction();
};

