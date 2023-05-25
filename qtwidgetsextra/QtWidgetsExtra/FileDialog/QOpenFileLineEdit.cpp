#include "QOpenFileLineEdit.h"
#include "QtWidgetsExtra/FileDialog/QFileAction.h"

class QOpenFileLineEditPrivate : public QObject
{
    Q_OBJECT

public:
    QOpenFileLineEditPrivate(QOpenFileLineEdit *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , action(new QFileAction(this))
    {
        Q_ASSERT(widget);

        action->setType(QFileAction::OpenFile);
        widget->addAction(action, QLineEdit::ActionPosition::LeadingPosition);

        connect(widget, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
        connect(action, SIGNAL(filePathChanged(QString)), this, SLOT(filePathChanged(QString)));
        connect(action, SIGNAL(filePathChanged(QString)), widget, SIGNAL(filePathChanged(QString)));
    }

public slots:
    void textChanged(const QString &text) {
        action->setFilePath(text);
    }

    void filePathChanged(const QString &text) {
        if (widget->text() != text) {
            widget->setText(text);
        }
    }

public:
    QOpenFileLineEdit *widget;
    QFileAction *action;
};

QOpenFileLineEdit::QOpenFileLineEdit(QWidget *parent)
    : QAbstractButtonLineEdit(parent)
    , d(new QOpenFileLineEditPrivate(this))
{
}

QString QOpenFileLineEdit::filePath() const
{
    return d->action->filePath();
}

void QOpenFileLineEdit::setFilePath(const QString &filePath)
{
    d->action->setFilePath(filePath);
}

QString QOpenFileLineEdit::caption() const
{
    return d->action->caption();
}

void QOpenFileLineEdit::setCaption(const QString &caption)
{
    d->action->setCaption(caption);
}

QString QOpenFileLineEdit::directory() const
{
    return d->action->directory();
}

void QOpenFileLineEdit::setDirectory(const QString &directory)
{
    d->action->setDirectory(directory);
}

QStringList QOpenFileLineEdit::filter() const
{
    return d->action->filter();
}

void QOpenFileLineEdit::setFilter(const QStringList &filter)
{
    d->action->setFilter(filter);
}

QFileDialog::Options QOpenFileLineEdit::options() const
{
    return d->action->options();
}

void QOpenFileLineEdit::setOptions(QFileDialog::Options options)
{
    d->action->setOptions(options);
}

#include "QOpenFileLineEdit.moc"
