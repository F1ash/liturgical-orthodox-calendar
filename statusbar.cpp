#include "statusbar.h"

StatusBar::StatusBar(QWidget *parent = 0) : QStatusBar(parent)
{
  progress = new QProgressBar(this);
  this->insertWidget(0, progress);
}
StatusBar::~StatusBar()
{
  delete progress;
  progress = 0;
}
void StatusBar::_loadStarted()
{
  //qDebug()<<"started";
  progress->setEnabled(true);
  progress->setValue(0);
  this->show();
}
void StatusBar::_loadFinished(bool b)
{
  //qDebug()<<b<< "finished";
  progress->setEnabled(false);
  if (b) this->hide();
}
void StatusBar::_loadProgress(int i)
{
  //qDebug()<<i;
  if (progress->isEnabled()) progress->setValue(i);
}
