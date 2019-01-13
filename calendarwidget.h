
#include <QWebView>
#include <QAction>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

class CalendarView : public QWebView
{
  Q_OBJECT
public :
  explicit CalendarView(QWidget *parent = Q_NULLPTR);

  QAction *_reloadAction;
  QAction *_stopAction;
  QAction *_forwardAction;
  QAction *_backwardAction;
  //QAction *_settingsAction;
  QAction *_bookmarkAddAction;
  QAction *_copyAction;

public slots :
  void loader(QUrl& url);

private slots :
  void initActions();
};
