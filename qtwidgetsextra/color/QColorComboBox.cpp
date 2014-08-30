#include "QColorComboBox.h"

class QColorComboBoxPrivate : public QObject {
    Q_OBJECT

public:
    QColorComboBoxPrivate(QColorComboBox *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , model(new QColorListModel(this)) {
        Q_ASSERT(widget);

        widget->setModel(model);

        connect(widget, SIGNAL(activated(QString)), this, SLOT(activated(QString)));
        connect(widget, SIGNAL(currentIndexChanged(QString)), this, SLOT(currentIndexChanged(QString)));
        connect(widget, SIGNAL(currentTextChanged(QString)), this, SLOT(currentTextChanged(QString)));
        connect(widget, SIGNAL(editTextChanged(QString)), this, SLOT(editTextChanged(QString)));
        connect(widget, SIGNAL(highlighted(QString)), this, SLOT(highlighted(QString)));
    }

public slots:
    void activated(const QString &text) {
        emit widget->activated(QColor(text));
    }

    void currentIndexChanged(const QString &text) {
        emit widget->currentIndexChanged(QColor(text));
    }

    void currentTextChanged(const QString &text) {
        emit widget->currentColorChanged(QColor(text));
    }

    void editTextChanged(const QString &text) {
        emit widget->editColorChanged(QColor(text));
    }

    void highlighted(const QString &text) {
        emit widget->highlighted(QColor(text));
    }

public:
    QColorComboBox *widget;
    QColorListModel *model;
};

QColorComboBox::QColorComboBox(QWidget *parent)
    : QComboBox(parent)
    , d(new QColorComboBoxPrivate(this))
{
}

QColorComboBox::QColorComboBox(const QList<QColor> &colors, QWidget *parent)
    : QComboBox(parent)
    , d(new QColorComboBoxPrivate(this))
{
    d->model->setColorList(colors);
}

QColorListModel::NameFormat QColorComboBox::nameFormat() const
{
    return d->model->nameFormat();
}

void QColorComboBox::setNameFormat(QColorListModel::NameFormat nameFormat)
{
    d->model->setNameFormat(nameFormat);
}

QList<QColor> QColorComboBox::colors() const
{
    return d->model->colorList();
}

void QColorComboBox::setColors(const QList<QColor> &colors)
{
    d->model->setColorList(colors);
}

QStringList QColorComboBox::colorNames() const
{
    return d->model->colorListNames();
}

void QColorComboBox::setColorNames(const QStringList &colorNames)
{
    d->model->setColorListNames(colorNames);
}

QColor QColorComboBox::currentColor() const
{
    return QColor(currentText());
}

void QColorComboBox::setCurrentColor(const QColor &color)
{
    setCurrentText(color.name(QColor::NameFormat(d->model->nameFormat())));
}

void QColorComboBox::setEditColor(const QColor &color)
{
    setEditText(color.name(QColor::NameFormat(d->model->nameFormat())));
}

#include "QColorComboBox.moc"
