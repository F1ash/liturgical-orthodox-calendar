#include <QStatusBar>
#include <QProgressBar>

class StatusBar : public QStatusBar
{
  Q_OBJECT
public :
  explicit StatusBar(QWidget *parent = Q_NULLPTR);

  QProgressBar *progress;

public slots :
  void _loadStarted();
  void _loadFinished(bool);
  void _loadProgress(int);
};

