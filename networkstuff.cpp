#include "networkstuff.h"

NetworkManager::NetworkManager(QObject *parent = 0)
  : QNetworkAccessManager(parent)
{
#if QT_VERSION<0x050000
  cacheDir = QDesktopServices::storageLocation(QDesktopServices::CacheLocation);
#else
  cacheDir = QStandardPaths::standardLocations(QStandardPaths::CacheLocation).first();
#endif
  while (cacheDir.endsWith(QDir::separator())) {
      cacheDir.remove(cacheDir.length()-1, 1);
  };
  cacheDir.append(QDir::separator());
  cacheDir.append("LiturgicalOrthodoxCalendar");

  diskCache = new QNetworkDiskCache(this);
  diskCache->setCacheDirectory(cacheDir);

  setCache(diskCache);
  connect(this, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
  initTemporaryFiles();
}
NetworkManager::~NetworkManager()
{
  delete diskCache;
  diskCache = 0;
  delete fonFile;
  fonFile = 0;
  delete iconFile;
  iconFile = 0;
}
void NetworkManager::initTemporaryFiles()
{
  fileTemplate.append(QDir::tempPath());
  fileTemplate.append(QDir::separator());
  baseFile = new QTemporaryFile(this);
  baseFile->setAutoRemove(true);

  fonFile = new QTemporaryFile(this);
  fonFile->setAutoRemove(true);
  iconFile = new QTemporaryFile(this);
  iconFile->setAutoRemove(true);
}
void NetworkManager::checkCache()
{
  QNetworkRequest fonRequest = QNetworkRequest(QUrl::fromUserInput("http://www.pravoslavie.ru/images/fon1.jpg"));
  fonRequest.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
  get(fonRequest);

  QNetworkRequest iconRequest = QNetworkRequest(QUrl::fromUserInput("http://www.pravoslavie.ru/images/znak2.gif"));
  iconRequest.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
  get(iconRequest);
}
void NetworkManager::replyFinished(QNetworkReply* reply)
{
  static int count = 0;
  count++;
  //QVariant fromCache = reply->attribute(QNetworkRequest::SourceIsFromCacheAttribute);
  //qDebug() << "page from cache?" << fromCache.toBool();
  //if ( reply->error()==QNetworkReply::NoError ) qDebug()<<reply->url()<<" "<<count;
  //else qDebug()<<reply->url()<<"Error: "<<reply->error()<<" "<<count;

  QTemporaryFile *file;
  QString fileName= QString("").append(fileTemplate);
  if (reply->request().url().toString().endsWith("fon1.jpg"))
    {
      fileName.append("fon");
      file = fonFile;
    }
  else
    {
      fileName.append("icon");
      file = iconFile;
    };
  if ( reply->error()==QNetworkReply::NoError )
    {
      file->setFileName(fileName);
      file->open();
      file->write(reply->readAll());
      file->close();
    };
  reply->deleteLater();
  if (count==2)
    {
      emit cacheChecked();
      count = 0;
    };
}
