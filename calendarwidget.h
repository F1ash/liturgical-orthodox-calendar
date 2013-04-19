
#include <QtWebKit/QWebView>
#include <QAction>

class CalendarView : public QWebView
{
  Q_OBJECT;
public :
  CalendarView(QWidget *parent);
  ~CalendarView();

  QAction *_reloadAction;
  QAction *_stopAction;
  QAction *_forwardAction;
  QAction *_backwardAction;
  //QAction *_settingsAction;
  QAction *_bookmarkAddAction;

private slots :
  void initActions();
};
