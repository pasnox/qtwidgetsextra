#include "QColorComboBox.h"

#include <QLineEdit>

class QColorComboBoxPrivate : public QObject {
    Q_OBJECT

public:
    QColorComboBoxPrivate(QColorComboBox *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , model(new QColorListModel(this)) {
        Q_ASSERT(widget);

        widget->setModel(model);
        updateValidator();

        connect(widget, SIGNAL(activated(QString)), this, SLOT(activated(QString)));
        connect(widget, SIGNAL(currentIndexChanged(QString)), this, SLOT(currentIndexChanged(QString)));
        connect(widget, SIGNAL(currentTextChanged(QString)), this, SLOT(currentTextChanged(QString)));
        connect(widget, SIGNAL(editTextChanged(QString)), this, SLOT(editTextChanged(QString)));
        connect(widget, SIGNAL(highlighted(QString)), this, SLOT(highlighted(QString)));
    }

    void updateValidator() {
        if (widget->lineEdit()) {
            QString mask = QLatin1String("\\#HHHhhh");

            if (model->nameFormat() == QColorListModel::HexArgb) {
                mask = QLatin1String("\\#HHHhhhhh");
            }

            if (widget->lineEdit()->inputMask() != mask) {
                widget->lineEdit()->setInputMask(mask);
            }
        }
    }

    QString internalColorName(const QColor &color) const {
        return color.name(QColor::HexArgb);
    }

public slots:
    void activated(const QString &text) {
        emit widget->activated(QColor(text));
    }

    void currentIndexChanged(const QString &text) {
        emit widget->currentIndexChanged(QColor(text));
    }

    void currentTextChanged(const QString &text) {
        emit widget->currentTextChanged(QColor(text));
    }

    void editTextChanged(const QString &text) {
        emit widget->editTextChanged(QColor(text));
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

QColorComboBox::QColorComboBox(const QStringList &colorListNames, QWidget *parent)
    : QComboBox(parent)
    , d(new QColorComboBoxPrivate(this))
{
    d->model->setColorListNames(colorListNames);
}

QColorComboBox::QColorComboBox(const QList<QColor> &colors, QWidget *parent)
    : QComboBox(parent)
    , d(new QColorComboBoxPrivate(this))
{
    d->model->setColorsList(colors);
}

QColorListModel::NameFormat QColorComboBox::nameFormat() const
{
    return d->model->nameFormat();
}

void QColorComboBox::setNameFormat(QColorListModel::NameFormat nameFormat)
{
    d->model->setNameFormat(nameFormat);
    d->updateValidator();
}

QStringList QColorComboBox::colorListNames() const
{
    return d->model->colorListNames();
}

void QColorComboBox::setColorListNames(const QStringList &colorNames)
{
    d->model->setColorListNames(colorNames);
}

QList<QColor> QColorComboBox::colorsList() const
{
    return d->model->colorsList();
}

void QColorComboBox::setColorsList(const QList<QColor> &colors)
{
    d->model->setColorsList(colors);
}

QString QColorComboBox::currentColorName() const
{
    return currentData(QColorListModel::HexArgbName).toString();
}

void QColorComboBox::setCurrentColorName(const QString &colorName)
{
    setCurrentIndex(findData(d->internalColorName(QColor(colorName)), QColorListModel::HexArgbName));
}

QString QColorComboBox::currentTextColorName() const
{
    return d->internalColorName(QColor(currentText()));
}

void QColorComboBox::setCurrentTextColorName(const QString &colorName)
{
    setCurrentText(d->internalColorName(QColor(colorName)));
}

void QColorComboBox::setEditTextColorName(const QString &colorName)
{
    setEditText(d->internalColorName(QColor(colorName)));
}

QColor QColorComboBox::currentColor() const
{
    return QColor(currentColorName());
}

void QColorComboBox::setCurrentColor(const QColor &color)
{
    setCurrentColorName(d->internalColorName(color));
}

QColor QColorComboBox::currentTextColor() const
{
    return QColor(currentTextColorName());
}

void QColorComboBox::setCurrentTextColor(const QColor &color)
{
    setCurrentTextColorName(d->internalColorName(color));
}

void QColorComboBox::setEditTextColor(const QColor &color)
{
    setEditTextColorName(d->internalColorName(color));
}

void QColorComboBox::paintEvent(QPaintEvent *event)
{
    QComboBox::paintEvent(event);

    // there is no real way to be notified about "editable" property change so let check it here...
    d->updateValidator();
}

#include "QColorComboBox.moc"
