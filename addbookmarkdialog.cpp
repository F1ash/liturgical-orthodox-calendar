#include "addbookmarkdialog.h"

BookmarkDialog::BookmarkDialog(QWidget *parent)
    : QDialog(parent)
{
  _bookmarkName = QString();
  bookmarkNameEdit = new QLineEdit(this);
  bookmarkNameEdit->setToolTip(QString::fromUtf8("Введите название новой закладки"));
  myLayout = new QVBoxLayout(this);
  ok = new QPushButton(QIcon::fromTheme("dialog-ok"), QString::fromUtf8("OK"), this);
  cancel = new QPushButton(QIcon::fromTheme("dialog-cancel"), QString::fromUtf8("Отмена"), this);
  buttonLayout = new QHBoxLayout(this);
  buttonLayout->addWidget(ok);
  buttonLayout->addWidget(cancel);
  myLayout->addWidget(bookmarkNameEdit);
  myLayout->addItem(buttonLayout);
  setLayout(myLayout);
  connect(ok, SIGNAL(clicked()), this, SLOT(setBookmarkName()));
  connect(cancel, SIGNAL(clicked()), this, SLOT(closeDialog()));
}

void BookmarkDialog::setBookmarkName()
{
  _bookmarkName = bookmarkNameEdit->text();
  closeDialog();
}
void BookmarkDialog::closeDialog()
{
  myLayout->removeItem(buttonLayout);
  myLayout->removeWidget(ok);
  myLayout->removeWidget(cancel);
  myLayout->removeWidget(bookmarkNameEdit);
  emit bookmarkName(_bookmarkName);
  this->done(0);
}
