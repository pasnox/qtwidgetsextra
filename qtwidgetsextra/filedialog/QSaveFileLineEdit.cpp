#include "QSaveFileLineEdit.h"
#include "QSaveFileButton.h"

#include <QHBoxLayout>
#include <QStyle>

class QSaveFileLineEditPrivate : public QObject
{
    Q_OBJECT

public:
    QSaveFileLineEditPrivate(QSaveFileLineEdit *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , button(new QSaveFileButton(widget))
    {
        Q_ASSERT(widget);

        const int frameMargin = widget->style()->pixelMetric(QStyle::PM_DefaultFrameWidth, 0, widget);
        const int height = widget->sizeHint().height() -(frameMargin *4);
        QMargins margins(widget->textMargins());

        button->setCursor(Qt::ArrowCursor);
        button->setEmbeded(true);
        button->setFixedSize(height, height);

        margins.setLeft(margins.left() +(frameMargin *4));

        QHBoxLayout* hl = new QHBoxLayout(widget);
        hl->setSpacing(0);
        hl->setContentsMargins(margins);
        hl->addWidget(button);
        hl->addStretch();

        margins.setLeft(margins.left() +height);
        widget->setTextMargins(margins);

        connect(widget, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
        connect(button, SIGNAL(filePathChanged(QString)), this, SLOT(filePathChanged(QString)));
        connect(button, SIGNAL(filePathChanged(QString)), widget, SIGNAL(filePathChanged(QString)));
    }

public slots:
    void textChanged(const QString &text) {
        button->setFilePath(text);
    }

    void filePathChanged(const QString &text) {
        if (widget->text() != text) {
            widget->setText(text);
        }
    }

public:
    QSaveFileLineEdit* widget;
    QSaveFileButton* button;
};

QSaveFileLineEdit::QSaveFileLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , d(new QSaveFileLineEditPrivate(this))
{
}

QString QSaveFileLineEdit::filePath() const
{
    return d->button->filePath();
}

void QSaveFileLineEdit::setFilePath(const QString &filePath)
{
    d->button->setFilePath(filePath);
}

QString QSaveFileLineEdit::caption() const
{
    return d->button->caption();
}

void QSaveFileLineEdit::setCaption(const QString &caption)
{
    d->button->setCaption(caption);
}

QString QSaveFileLineEdit::directory() const
{
    return d->button->directory();
}

void QSaveFileLineEdit::setDirectory(const QString &directory)
{
    d->button->setDirectory(directory);
}

QStringList QSaveFileLineEdit::filter() const
{
    return d->button->filter();
}

void QSaveFileLineEdit::setFilter(const QStringList &filter)
{
    d->button->setFilter(filter);
}

QFileDialog::Options QSaveFileLineEdit::options() const
{
    return d->button->options();
}

void QSaveFileLineEdit::setOptions(QFileDialog::Options options)
{
    d->button->setOptions(options);
}

void QSaveFileLineEdit::resetFilePath()
{
    QMetaObject::invokeMethod(d->button, "resetFilePath");
}

void QSaveFileLineEdit::resetCaption()
{
    QMetaObject::invokeMethod(d->button, "resetCaption");
}

void QSaveFileLineEdit::resetDirectory()
{
    QMetaObject::invokeMethod(d->button, "resetDirectory");
}

void QSaveFileLineEdit::resetFilter()
{
    QMetaObject::invokeMethod(d->button, "resetFilter");
}

void QSaveFileLineEdit::resetOptions()
{
    QMetaObject::invokeMethod(d->button, "resetOptions");
}

#include "QSaveFileLineEdit.moc"
