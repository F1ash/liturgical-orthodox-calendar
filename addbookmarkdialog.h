#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDialog>

class BookmarkDialog : public QDialog
{
  Q_OBJECT
public :
  explicit BookmarkDialog (
            QWidget *parent   = 0);

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
