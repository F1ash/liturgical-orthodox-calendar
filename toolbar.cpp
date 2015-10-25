#include "toolbar.h"
#include <QDebug>

ToolBar::ToolBar (QWidget *parent) : QToolBar(parent)
{
  setAllowedAreas(Qt::AllToolBarAreas);
  setMovable(true);
  setFloatable(true);

  initActions();
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
  _settingsAction->setIcon ( QIcon().fromTheme("configure") );
  _bookmarkAddAction = new QAction(QString().fromUtf8("Добавить в закладки"), this);
  _bookmarkAddAction->setIcon ( QIcon().fromTheme("bookmark-new") );
  _clearAction = new QAction(QString::fromUtf8("Очистить"), this);
  connect(_clearAction, SIGNAL(triggered()), this, SLOT(clearAction()));
  _clearHistoryAction = new QAction(QString::fromUtf8("Очистить"), this);
  connect(_clearHistoryAction, SIGNAL(triggered()), this, SLOT(clearHistoryAction()));
  _prevDayAction = new QAction(QString().fromUtf8("Предыдущий день"), this);
  _prevDayAction->setIcon ( QIcon().fromTheme("draw-arrow-back") );
  _nextDayAction = new QAction(QString().fromUtf8("Следующий день"), this);
  _nextDayAction->setIcon ( QIcon().fromTheme("draw-arrow-forward") );

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
  addHistoryToolButton();
  addSeparator();
  addAction(_prevDayAction);
  addAction(_nextDayAction);
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
void ToolBar::addHistoryToolButton()
{
  historyButton = new QToolButton(this);
  historyButton->setCheckable(false);
  historyButton->setIcon(QIcon::fromTheme("address-book-new"));
  historyButton->setToolTip(QString::fromUtf8("История сессии"));
  connect(historyButton, SIGNAL(clicked(bool)), historyButton, SLOT(showMenu()));
  _historyAction = this->addWidget(historyButton);
  historyMenu = new QMenu(historyButton);
  historyMenu->setContextMenuPolicy ( Qt::CustomContextMenu );
  connect(historyMenu, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showHistoryMenu(QPoint)));
  historyButton->setMenu(historyMenu);
  clearHistoryMenu = new QMenu(historyMenu);
  clearHistoryMenu->addAction(_clearHistoryAction);
}
void ToolBar::showHistoryMenu(QPoint pos)
{
  clearHistoryMenu->show();
  clearHistoryMenu->move(historyMenu->mapToGlobal(pos));
  currentAction = historyMenu->activeAction();
}
void ToolBar::clearHistoryAction()
{
  historyMenu->removeAction(currentAction);
  emit historyItemRemoved(currentAction->text());
}
