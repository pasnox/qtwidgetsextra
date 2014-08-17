#include "QOpenFolderLineEdit.h"
#include "QOpenFolderButton.h"

#include <QHBoxLayout>
#include <QStyle>

class QOpenFolderLineEditPrivate : public QObject
{
    Q_OBJECT

public:
    QOpenFolderLineEditPrivate(QOpenFolderLineEdit *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , button(new QOpenFolderButton(widget))
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
    QOpenFolderLineEdit* widget;
    QOpenFolderButton* button;
};

QOpenFolderLineEdit::QOpenFolderLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , d(new QOpenFolderLineEditPrivate(this))
{
}

QString QOpenFolderLineEdit::filePath() const
{
    return d->button->filePath();
}

void QOpenFolderLineEdit::setFilePath(const QString &filePath)
{
    d->button->setFilePath(filePath);
}

QString QOpenFolderLineEdit::caption() const
{
    return d->button->caption();
}

void QOpenFolderLineEdit::setCaption(const QString &caption)
{
    d->button->setCaption(caption);
}

QString QOpenFolderLineEdit::directory() const
{
    return d->button->directory();
}

void QOpenFolderLineEdit::setDirectory(const QString &directory)
{
    d->button->setDirectory(directory);
}

QFileDialog::Options QOpenFolderLineEdit::options() const
{
    return d->button->options();
}

void QOpenFolderLineEdit::setOptions(QFileDialog::Options options)
{
    d->button->setOptions(options);
}

void QOpenFolderLineEdit::resetFilePath()
{
    QMetaObject::invokeMethod(d->button, "resetFilePath");
}

void QOpenFolderLineEdit::resetCaption()
{
    QMetaObject::invokeMethod(d->button, "resetCaption");
}

void QOpenFolderLineEdit::resetDirectory()
{
    QMetaObject::invokeMethod(d->button, "resetDirectory");
}

void QOpenFolderLineEdit::resetOptions()
{
    QMetaObject::invokeMethod(d->button, "resetOptions");
}

#include "QOpenFolderLineEdit.moc"
