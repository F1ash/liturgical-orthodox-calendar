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
  bookmarkButton->setMenu(bookmarkMenu);
}
