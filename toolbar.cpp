#include "toolbar.h"
#include <QDebug>

ToolBar::ToolBar (QWidget *parent = 0) : QToolBar(parent)
{
  setAllowedAreas(Qt::AllToolBarAreas);
  setMovable(true);
  setFloatable(true);
}
ToolBar::~ToolBar()
{
  delete bookmarkMenu;
  delete bookmarkButton;
}
void ToolBar::addToolButton()
{
  bookmarkButton = new QToolButton(this);
  bookmarkButton->setCheckable(false);
  bookmarkButton->setIcon(QIcon::fromTheme("bookmark-toolbar"));
  bookmarkButton->setToolTip(QString::fromUtf8("Закладки"));
  connect(bookmarkButton, SIGNAL(clicked(bool)), bookmarkButton, SLOT(showMenu()));
  _bookmarkAction = this->addWidget(bookmarkButton);
  bookmarkMenu = new QMenu(bookmarkButton);
  bookmarkMenu->setContextMenuPolicy ( Qt::CustomContextMenu );
  connect(bookmarkMenu, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showCustomMenu(QPoint)));
  bookmarkButton->setMenu(bookmarkMenu);
  clearMenu = new QMenu(bookmarkMenu);
  QAction *clearAction = clearMenu->addAction(QString::fromUtf8("Очистить"));
  connect(clearAction, SIGNAL(triggered()), this, SLOT(clearAction()));
}
void ToolBar::showCustomMenu(QPoint pos)
{
  clearMenu->show();
  clearMenu->move(bookmarkMenu->mapToGlobal(pos));
  currentAction = bookmarkMenu->activeAction();
}
void ToolBar::clearAction()
{
  bookmarkMenu->removeAction(currentAction);
  emit actionRemoved(currentAction->text());
}
