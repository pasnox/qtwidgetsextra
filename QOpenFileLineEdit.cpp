#include "QOpenFileLineEdit.h"
#include "QOpenFileButton.h"

#include <QHBoxLayout>
#include <QStyle>

class QOpenFileLineEditPrivate : public QObject
{
    Q_OBJECT

public:
    QOpenFileLineEditPrivate(QOpenFileLineEdit *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , button(new QOpenFileButton(widget))
    {
        Q_ASSERT(widget);

        const int frameMargin = widget->style()->pixelMetric(QStyle::PM_DefaultFrameWidth, 0, widget);
        const int height = widget->sizeHint().height() -(frameMargin *4);
        QMargins margins(widget->textMargins());

        button->setCursor(Qt::ArrowCursor);
        button->setEmbeded(true);
        button->setFixedSize(height, height);

        margins.setRight(margins.right() +(frameMargin *2));

        QHBoxLayout* hl = new QHBoxLayout(widget);
        hl->setSpacing(0);
        hl->setContentsMargins(margins);
        hl->addStretch();
        hl->addWidget(button);

        margins.setRight(margins.right() +height +(frameMargin *2));
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
        if (widget->text() == text) {
            return;
        }

        widget->setText(text);
    }

public:
    QOpenFileLineEdit* widget;
    QOpenFileButton* button;
};

QOpenFileLineEdit::QOpenFileLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , d(new QOpenFileLineEditPrivate(this))
{
}

QString QOpenFileLineEdit::filePath() const
{
    return d->button->filePath();
}

void QOpenFileLineEdit::setFilePath(const QString &filePath)
{
    d->button->setFilePath(filePath);
}

QString QOpenFileLineEdit::caption() const
{
    return d->button->caption();
}

void QOpenFileLineEdit::setCaption(const QString &caption)
{
    d->button->setCaption(caption);
}

QString QOpenFileLineEdit::directory() const
{
    return d->button->directory();
}

void QOpenFileLineEdit::setDirectory(const QString &directory)
{
    d->button->setDirectory(directory);
}

QStringList QOpenFileLineEdit::filter() const
{
    return d->button->filter();
}

void QOpenFileLineEdit::setFilter(const QStringList &filter)
{
    d->button->setFilter(filter);
}

QFileDialog::Options QOpenFileLineEdit::options() const
{
    return d->button->options();
}

void QOpenFileLineEdit::setOptions(QFileDialog::Options options)
{
    d->button->setOptions(options);
}

void QOpenFileLineEdit::resetFilePath()
{
    QMetaObject::invokeMethod(d->button, "resetFilePath");
}

void QOpenFileLineEdit::resetCaption()
{
    QMetaObject::invokeMethod(d->button, "resetCaption");
}

void QOpenFileLineEdit::resetDirectory()
{
    QMetaObject::invokeMethod(d->button, "resetDirectory");
}

void QOpenFileLineEdit::resetFilter()
{
    QMetaObject::invokeMethod(d->button, "resetFilter");
}

void QOpenFileLineEdit::resetOptions()
{
    QMetaObject::invokeMethod(d->button, "resetOptions");
}

#include "QOpenFileLineEdit.moc"
