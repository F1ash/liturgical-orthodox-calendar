#include "calendarwidget.h"

CalendarView::CalendarView(QWidget *parent)
    : QWebView(parent)
{
    settings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
    settings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
    settings()->setOfflineWebApplicationCacheQuota(50000000);
    settings()->setOfflineStorageDefaultQuota(50000000);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    page()->setLinkDelegationPolicy(QWebPage::DelegateExternalLinks);
    page()->settings()->setMaximumPagesInCache(100);

    initActions();
}

void CalendarView::initActions()
{
    _reloadAction = new QAction(QString::fromUtf8("Обновить"), this);
    _reloadAction->setIcon ( QIcon::fromTheme("view-refresh") );
    _stopAction = new QAction(QString::fromUtf8("Остановить"), this);
    _stopAction->setIcon ( QIcon::fromTheme("process-stop") );
    _forwardAction = new QAction(QString::fromUtf8("Вперёд"), this);
    _forwardAction->setIcon ( QIcon::fromTheme("go-next") );
    _backwardAction = new QAction(QString::fromUtf8("Назад"), this);
    _backwardAction->setIcon ( QIcon::fromTheme("go-previous") );
    //_settingsAction = new QAction(QString::fromUtf8("Настройки"), this);
    //_settingsAction->setIcon ( QIcon::fromTheme("settings") );
    _bookmarkAddAction = new QAction(QString::fromUtf8("Добавить в закладки"), this);
    _bookmarkAddAction->setIcon ( QIcon::fromTheme("bookmark-new") );
    _copyAction = new QAction (QString::fromUtf8("Копировать"), this);
    _copyAction->setIcon ( QIcon::fromTheme("edit-copy") );

    addAction(_reloadAction);
    addAction(_stopAction);
    addAction(_forwardAction);
    addAction(_backwardAction);
    //addAction(_settingsAction);
    addAction(_bookmarkAddAction);
    addAction(_copyAction);
}
void CalendarView::loader(QUrl& url)
{
    QNetworkRequest request = QNetworkRequest(url);
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute,
                         QNetworkRequest::PreferCache);
    this->load(request);
}
