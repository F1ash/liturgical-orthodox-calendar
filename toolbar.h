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

  QMenu *bookmarkMenu;
  void addToolButton();
  void initBookmarks();

signals:
  void actionRemoved(QString);

private:
  QToolButton *bookmarkButton;
  QAction *_bookmarkAction;
  QMenu *clearMenu;
  QAction *currentAction;

private slots:
  void showCustomMenu(QPoint);
  void clearAction();
};

