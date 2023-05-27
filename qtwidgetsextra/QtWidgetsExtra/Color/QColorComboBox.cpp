#include "QColorComboBox.h"

#include <QLineEdit>

class QColorComboBoxPrivate : public QObject {
    Q_OBJECT

public:
    explicit QColorComboBoxPrivate(QColorComboBox *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , model(new QColorListModel(this)) {
        Q_ASSERT(widget);

        widget->setModel(model);
        updateValidator();

        connect(widget, &QComboBox::textActivated, this, &QColorComboBoxPrivate::textActivated);
        connect(widget, qOverload<int>(&QComboBox::currentIndexChanged), this,
                &QColorComboBoxPrivate::currentIndexChanged);
        connect(widget, &QComboBox::currentTextChanged, this, &QColorComboBoxPrivate::currentTextChanged);
        connect(widget, &QComboBox::editTextChanged, this, &QColorComboBoxPrivate::editTextChanged);
        connect(widget, &QComboBox::textHighlighted, this, &QColorComboBoxPrivate::textHighlighted);
    }

    void updateValidator() {
        if (widget->lineEdit()) {
            QString mask = QStringLiteral("\\#HHHhhh");

            if (model->nameFormat() == QColorListModel::NameFormat::HexArgb) {
                mask = QStringLiteral("\\#HHHhhhhh");
            }

            if (widget->lineEdit()->inputMask() != mask) {
                widget->lineEdit()->setInputMask(mask);
            }
        }
    }

    QString internalColorName(const QColor &color) const {
        return color.name(QColor::HexArgb);
    }

    void textActivated(const QString &text) {
        Q_EMIT widget->colorActivated(QColor(text));
    }

    void currentIndexChanged(int index) {
        Q_EMIT widget->currentColorChanged(QColor(widget->itemText(index)));
    }

    void currentTextChanged(const QString &text) {
        Q_EMIT widget->currentTextColorChanged(QColor(text));
    }

    void editTextChanged(const QString &text) {
        Q_EMIT widget->editTextColorChanged(QColor(text));
    }

    void textHighlighted(const QString &text) {
        Q_EMIT widget->colorHighlighted(QColor(text));
    }

public:
    QColorComboBox *widget;
    QColorListModel *model;
};

QColorComboBox::QColorComboBox(QWidget *parent)
    : QComboBox(parent)
    , d(new QColorComboBoxPrivate(this)) {
}

QColorComboBox::QColorComboBox(const QStringList &colorNames, QWidget *parent)
    : QComboBox(parent)
    , d(new QColorComboBoxPrivate(this)) {
    d->model->setColorListNames(colorNames);
}

QColorComboBox::QColorComboBox(const QList<QColor> &colors, QWidget *parent)
    : QComboBox(parent)
    , d(new QColorComboBoxPrivate(this)) {
    d->model->setColorsList(colors);
}

QColorListModel::NameFormat QColorComboBox::nameFormat() const {
    return d->model->nameFormat();
}

void QColorComboBox::setNameFormat(QColorListModel::NameFormat nameFormat) {
    d->model->setNameFormat(nameFormat);
    d->updateValidator();
}

QStringList QColorComboBox::colorNames() const {
    return d->model->colorListNames();
}

void QColorComboBox::setColorNames(const QStringList &colorNames) {
    d->model->setColorListNames(colorNames);
}

QList<QColor> QColorComboBox::colors() const {
    return d->model->colorsList();
}

void QColorComboBox::setColors(const QList<QColor> &colors) {
    d->model->setColorsList(colors);
}

QString QColorComboBox::currentColorName() const {
    return currentData(static_cast<int>(QColorListModel::Role::HexArgbName)).toString();
}

void QColorComboBox::setCurrentColorName(const QString &colorName) {
    setCurrentIndex(
        findData(d->internalColorName(QColor(colorName)), static_cast<int>(QColorListModel::Role::HexArgbName)));
}

QString QColorComboBox::currentTextColorName() const {
    return d->internalColorName(QColor(currentText()));
}

void QColorComboBox::setCurrentTextColorName(const QString &colorName) {
    setCurrentText(d->internalColorName(QColor(colorName)));
}

void QColorComboBox::setEditTextColorName(const QString &colorName) {
    setEditText(d->internalColorName(QColor(colorName)));
}

QColor QColorComboBox::currentColor() const {
    return QColor(currentColorName());
}

void QColorComboBox::setCurrentColor(const QColor &color) {
    setCurrentColorName(d->internalColorName(color));
}

QColor QColorComboBox::currentTextColor() const {
    return QColor(currentTextColorName());
}

void QColorComboBox::setCurrentTextColor(const QColor &color) {
    setCurrentTextColorName(d->internalColorName(color));
}

void QColorComboBox::setEditTextColor(const QColor &color) {
    setEditTextColorName(d->internalColorName(color));
}

void QColorComboBox::paintEvent(QPaintEvent *event) {
    QComboBox::paintEvent(event);

    // there is no real way to be notified about "editable" property change so let check it here...
    d->updateValidator();
}

#include "QColorComboBox.moc"
