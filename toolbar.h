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

private:
  QToolButton *bookmarkButton;
  QAction *_bookmarkAction;
};

