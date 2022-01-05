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
    SettingsWidget(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::Widget);

    QSettings *settings;

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
    int _toolBarArea;
    QPushButton *apply;
    QVBoxLayout *vbox;

public slots:
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
    void set_ToolBarArea(int i);
    QByteArray get_Geometry() const;
    Qt::ToolBarArea get_ToolBarArea() const;
    QDate selectedDate() const;
    void setSelectedDate(QDate);
    QStringList initBookmarks() const;
    QString readBookmarkLink(QString key) const;

private slots:
    void initVariables();
    void readSettings();
    void apply_Settings();
};
