
#include <QDir>
#include <QTemporaryFile>
#include <QDesktopServices>
#include <QNetworkDiskCache>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class NetworkManager : public QNetworkAccessManager
{
  Q_OBJECT;
public :
  NetworkManager(QObject *parent);
  ~NetworkManager();

  QString fileTemplate;
  QTemporaryFile *baseFile;
  QTemporaryFile *fonFile;
  QTemporaryFile *iconFile;
  QString cacheDir;

private :
  QNetworkDiskCache *diskCache;

signals:
  void cacheChecked();

public slots :
  void checkCache();

private slots :
  void initTemporaryFiles();
  void replyFinished(QNetworkReply*);
};
