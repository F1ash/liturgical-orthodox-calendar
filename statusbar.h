#include <QStatusBar>
#include <QProgressBar>

class StatusBar : public QStatusBar
{
  Q_OBJECT;
public :
  StatusBar(QWidget *parent);
  ~StatusBar();

  QProgressBar *progress;

public slots :
  void _loadStarted();
  void _loadFinished(bool);
  void _loadProgress(int);
};

