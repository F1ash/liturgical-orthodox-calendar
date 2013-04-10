#include "settingswidget.h"
#include <QDebug>

SettingsWidget::SettingsWidget (QWidget *parent, Qt::WindowFlags f) :
  QWidget(parent, f)
{
  settings = new QSettings("LiturgicalOrthodoxCalendar", "LiturgicalOrthodoxCalendar");

  visibleInStart = new QCheckBox(QString().fromUtf8("показывать при запуске"));
  day_Icon = new QCheckBox(QString().fromUtf8("икона дня"));
  customDate = new QCalendarWidget(this);
  customDate->setMinimumDate(QDate(2013, 1, 1));
  customDate->setMaximumDate(QDate(2013, 12, 31));
  customDate->setFirstDayOfWeek(Qt::Monday);
  images = new QCheckBox(QString().fromUtf8("ссылки на житие, иконы, храм,\nтропарь в виде картинок"));
  vek = new QCheckBox(QString().fromUtf8("выводить год/век события"));
  bold = new QCheckBox(QString().fromUtf8("выделять особо почитаемых святых"));
  para = new QCheckBox(QString().fromUtf8("разбивать текст на абзацы"));
  tipikon = new QCheckBox(QString().fromUtf8("выводить значки типикона"));
  trapeza = new QCheckBox(QString().fromUtf8("выводить сведения о трапезе"));
  feofan = new QCheckBox(QString().fromUtf8("выводить \"Мысли на каждый день года\"\nсвт. Феофана Затворника"));
  church = new QComboBox(this);
  church->addItem(QString::fromUtf8("Русская Православная Церковь"), 0);
  church->addItem(QString::fromUtf8("РПЦ + РПЦ За_Рубежём"), 1);
  church->addItem(QString::fromUtf8("РПЦ + РПЦ За_Рубежём + все доступные"), 2);
  church->setToolTip(QString::fromUtf8("Святцы"));
  chten = new QCheckBox(QString().fromUtf8("выводить чтения дня"));
  liturgical = new QCheckBox(QString().fromUtf8("богослужебные указания"));

  vbox = new QVBoxLayout;
  vbox->addWidget( visibleInStart );
  vbox->addWidget( customDate );
  vbox->addWidget( day_Icon );
  vbox->addWidget( images );
  vbox->addWidget( vek );
  vbox->addWidget( bold );
  vbox->addWidget( para );
  vbox->addWidget( tipikon );
  vbox->addWidget( trapeza );
  vbox->addWidget( feofan );
  vbox->addWidget( church );
  vbox->addWidget( chten );
  vbox->addWidget( liturgical );

  apply = new QPushButton(QString().fromUtf8("Применить"));
  vbox->addWidget( apply );
  connect(apply, SIGNAL(clicked()), this, SLOT(apply_Settings()));

  setLayout( vbox );
  readSettings();
}
SettingsWidget::~SettingsWidget ()
{
  delete day_Icon;
  day_Icon = 0;
  delete customDate;
  customDate = 0;
  delete images;
  images = 0;
  delete vek;
  vek = 0;
  delete bold;
  bold = 0;
  delete para;
  para = 0;
  delete tipikon;
  tipikon = 0;
  delete trapeza;
  trapeza = 0;
  delete feofan;
  feofan = 0;
  delete church;
  church = 0;
  delete chten;
  chten = 0;
  delete visibleInStart;
  visibleInStart = 0;
  delete liturgical;
  liturgical = 0;
  delete apply;
  apply = 0;
  delete vbox;
  vbox = 0;
}
int SettingsWidget::showInStart() const
{
  return _showInStart;
}
int SettingsWidget::showDayIcon() const
{
  return _showDayIcon;
}
int SettingsWidget::showImages() const
{
  return _showImages;
}
int SettingsWidget::showVek() const
{
  return _showVek;
}
int SettingsWidget::showBold() const
{
  return _showBold;
}
int SettingsWidget::showPara() const
{
  return _showPara;
}
int SettingsWidget::showTipikon() const
{
  return _showTipikon;
}
int SettingsWidget::showTrapeza() const
{
  return _showTrapeza;
}
int SettingsWidget::showFeofan() const
{
  return _showFeofan;
}
int SettingsWidget::showChurch() const
{
  return _showChurch;
}
int SettingsWidget::showChten() const
{
  return _showChten;
}
int SettingsWidget::showLiturgy() const
{
  return _showLiturgy;
}
void SettingsWidget::setFocusToSettings()
{
  this->setFocusProxy(apply);
}
void SettingsWidget::initVariables()
{
  _showInStart = settings->value("VisibleInStart", 0).toInt() / 2;
  _showDayIcon = settings->value("ShowDayIcon", 1).toInt() / 2;
  _showImages = settings->value("ShowImages", 0).toInt() / 2;
  _showVek = settings->value("ShowVek", 0).toInt() / 2;
  _showBold = settings->value("ShowBold", 0).toInt() / 2;
  _showPara = settings->value("ShowPara", 0).toInt() / 2;
  _showTipikon = settings->value("ShowTipikon", 0).toInt() / 2;
  _showTrapeza = settings->value("ShowTrapeza", 1).toInt() / 2;
  _showFeofan = settings->value("ShowFeofan", 0).toInt() / 2;
  _showChurch = settings->value("ShowChurch", 0).toInt();
  _showChten = settings->value("ShowChten", 1).toInt() / 2;
  _showLiturgy = settings->value("ShowLiturgy", 0).toInt() / 2;
  _geometry = settings->value("Geometry").toByteArray();
}
QStringList SettingsWidget::initBookmarks() const
{
  settings->beginGroup("bookmarks");
  QStringList keys = settings->allKeys();
  if (keys.isEmpty())
    {
      settings->setValue(QString::fromUtf8("Основы соц.концепции РПЦ"), QString::fromUtf8("http://www.patriarchia.ru/db/text/141422.html"));
      settings->setValue(QString::fromUtf8("Христианство.ру"), QString::fromUtf8("http://www.hristianstvo.ru/"));
      settings->setValue(QString::fromUtf8("Православная Энциклопедия"), QString::fromUtf8("http://www.pravenc.ru/"));
      keys = settings->allKeys();
    };
  settings->endGroup();
  return keys;
}
void SettingsWidget::readSettings()
{
  initVariables();
  if (_showInStart)
    visibleInStart->setCheckState(Qt::Checked);
  else visibleInStart->setCheckState(Qt::Unchecked);

  if (_showDayIcon)
    day_Icon->setCheckState(Qt::Checked);
  else day_Icon->setCheckState(Qt::Unchecked);

  if (_showImages)
    images->setCheckState(Qt::Checked);
  else images->setCheckState(Qt::Unchecked);

  if (_showVek)
    vek->setCheckState(Qt::Checked);
  else vek->setCheckState(Qt::Unchecked);

  if (_showBold)
    bold->setCheckState(Qt::Checked);
  else bold->setCheckState(Qt::Unchecked);

  if (_showPara)
    para->setCheckState(Qt::Checked);
  else para->setCheckState(Qt::Unchecked);

  if (_showTipikon)
    tipikon->setCheckState(Qt::Checked);
  else tipikon->setCheckState(Qt::Unchecked);

  if (_showTrapeza)
    trapeza->setCheckState(Qt::Checked);
  else trapeza->setCheckState(Qt::Unchecked);

  if (_showFeofan)
    feofan->setCheckState(Qt::Checked);
  else feofan->setCheckState(Qt::Unchecked);

  church->setCurrentIndex(_showChurch);

  if (_showChten)
    chten->setCheckState(Qt::Checked);
  else chten->setCheckState(Qt::Unchecked);

  if (_showLiturgy)
    liturgical->setCheckState(Qt::Checked);
  else liturgical->setCheckState(Qt::Unchecked);
}
void SettingsWidget::apply_Settings()
{
  settings->setValue("VisibleInStart", visibleInStart->checkState());
  settings->setValue("ShowDayIcon", day_Icon->checkState());
  settings->setValue("ShowImages", images->checkState());
  settings->setValue("ShowVek", vek->checkState());
  settings->setValue("ShowBold", bold->checkState());
  settings->setValue("ShowPara", para->checkState());
  settings->setValue("ShowTipikon", tipikon->checkState());
  settings->setValue("ShowTrapeza", trapeza->checkState());
  settings->setValue("ShowFeofan", feofan->checkState());
  settings->setValue("ShowChurch", church->currentIndex());
  settings->setValue("ShowChten", chten->checkState());
  settings->setValue("ShowLiturgy", liturgical->checkState());
  settings->sync();
  parentWidget()->parentWidget()->parentWidget()->hide();

  initVariables();
  emit settingsApplied();
}
void SettingsWidget::set_Geometry(QByteArray geometry)
{
  _geometry = geometry;
  settings->setValue("Geometry", geometry);
}
QByteArray SettingsWidget::get_Geometry() const
{
  return _geometry;
}
QDate SettingsWidget::selectedDate() const
{
  return customDate->selectedDate();
}
QString SettingsWidget::readBookmarkLink(QString key) const
{
  QString link;
  settings->beginGroup("bookmarks");
  link = settings->value(key, QVariant("")).toString();
  settings->endGroup();
  return link;
}
