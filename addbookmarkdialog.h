#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDialog>

class BookmarkDialog : public QDialog
{
  Q_OBJECT;
public :
  BookmarkDialog (QWidget *parent, Qt::WindowFlags f);
  ~BookmarkDialog();

signals :
  void bookmarkName(QString&);

private :
  QString _bookmarkName;
  QLineEdit *bookmarkNameEdit;
  QPushButton *ok;
  QPushButton *cancel;
  QVBoxLayout *myLayout;
  QHBoxLayout *buttonLayout;

private slots :
  void setBookmarkName();
  void closeDialog();
};
