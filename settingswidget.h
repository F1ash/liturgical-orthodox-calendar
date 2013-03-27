#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QCalendarWidget>
#include <QSettings>

class SettingsWidget : public QWidget
{
  Q_OBJECT
public:
  SettingsWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);
  ~SettingsWidget();

  QSettings *settings;
  int showInStart() const;
  int showDayIcon() const;
  int showImages() const;
  int showBold() const;
  int showVek() const;
  int showPara() const;
  int showTipikon() const;
  int showTrapeza() const;
  int showFeofan() const;
  int showChurch() const;
  int showChten() const;
  int showLiturgy() const;
  void setFocusToSettings();
  void set_Geometry(QByteArray geometry);
  QByteArray get_Geometry() const;
  QDate selectedDate() const;

signals:
  void settingsApplied();

private:
  QWidget *parentWdg;
  QCheckBox *day_Icon;
  QCheckBox *images;
  QCheckBox *vek;
  QCheckBox *bold;
  QCheckBox *para;
  QCheckBox *tipikon;
  QCheckBox *trapeza;
  QCheckBox *feofan;
  QComboBox *church;
  QCheckBox *chten;
  QCheckBox *liturgical;
  QCheckBox *visibleInStart;
  QCalendarWidget *customDate;
  int _showInStart;
  int _showDayIcon;
  int _showImages;
  int _showVek;
  int _showBold;
  int _showPara;
  int _showTipikon;
  int _showTrapeza;
  int _showFeofan;
  int _showChurch;
  int _showChten;
  int _showLiturgy;
  QByteArray _geometry;
  QPushButton *apply;
  QVBoxLayout *vbox;
  void initVariables();
  void readSettings();

private slots:
  void apply_Settings();
};
