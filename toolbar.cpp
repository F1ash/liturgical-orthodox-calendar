#include "toolbar.h"
#include <QDebug>

ToolBar::ToolBar (QWidget *parent = 0) : QToolBar(parent)
{
  setAllowedAreas(Qt::AllToolBarAreas);
  setMovable(true);
  setFloatable(true);

  initActions();
}
ToolBar::~ToolBar()
{
  clearMenu->clear();
  bookmarkMenu->clear();
  delete clearMenu;
  clearMenu = 0;
  delete _clearAction;
  _clearAction = 0;
  delete bookmarkMenu;
  bookmarkMenu = 0;
  delete bookmarkButton;
  bookmarkButton = 0;
  delete _reloadAction;
  _reloadAction = 0;
  delete _stopAction;
  _stopAction = 0;
  delete _forwardAction;
  _forwardAction = 0;
  delete _backwardAction;
  _backwardAction = 0;
  delete _zoomUpAction;
  _zoomUpAction = 0;
  delete _zoomOrigAction;
  _zoomOrigAction = 0;
  delete _zoomDownAction;
  _zoomDownAction = 0;
  delete _settingsAction;
  _settingsAction = 0;
  delete _bookmarkAddAction;
  _bookmarkAddAction = 0;
}
void ToolBar::initActions()
{
  _reloadAction = new QAction(QString().fromUtf8("Обновить"), this);
  _reloadAction->setIcon ( QIcon().fromTheme("view-refresh") );
  _stopAction = new QAction(QString().fromUtf8("Остановить"), this);
  _stopAction->setIcon ( QIcon().fromTheme("process-stop") );
  _forwardAction = new QAction(QString().fromUtf8("Вперёд"), this);
  _forwardAction->setIcon ( QIcon().fromTheme("go-next") );
  _backwardAction = new QAction(QString().fromUtf8("Назад"), this);
  _backwardAction->setIcon ( QIcon().fromTheme("go-previous") );
  _zoomUpAction = new QAction(QString().fromUtf8("Увеличить"), this);
  _zoomUpAction->setIcon ( QIcon().fromTheme("zoom-in") );
  _zoomOrigAction = new QAction(QString().fromUtf8("Оригинальный"), this);
  _zoomOrigAction->setIcon ( QIcon().fromTheme("zoom-original") );
  _zoomDownAction = new QAction(QString().fromUtf8("Уменьшить"), this);
  _zoomDownAction->setIcon ( QIcon().fromTheme("zoom-out") );
  _settingsAction = new QAction(QString().fromUtf8("Настройки"), this);
  _settingsAction->setIcon ( QIcon().fromTheme("settings") );
  _bookmarkAddAction = new QAction(QString().fromUtf8("Добавить в закладки"), this);
  _bookmarkAddAction->setIcon ( QIcon().fromTheme("bookmark-new") );
  _clearAction = new QAction(QString::fromUtf8("Очистить"), this);
  connect(_clearAction, SIGNAL(triggered()), this, SLOT(clearAction()));

  addAction(_reloadAction);
  addAction(_stopAction);
  addAction(_backwardAction);
  addAction(_forwardAction);
  addSeparator();
  addAction(_zoomUpAction);
  addAction(_zoomOrigAction);
  addAction(_zoomDownAction);
  addSeparator();
  addAction(_settingsAction);
  addSeparator();
  addToolButton();
  addAction(_bookmarkAddAction);
  addSeparator();
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
  clearMenu->addAction(_clearAction);
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
