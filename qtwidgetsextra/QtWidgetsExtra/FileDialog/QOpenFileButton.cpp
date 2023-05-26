#include "QOpenFileButton.h"

class QOpenFileButtonPrivate : public QObject
{
    Q_OBJECT

public:
    QOpenFileButtonPrivate(QOpenFileButton *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , action(new QFileAction(this)) {
        Q_ASSERT(widget);

        action->setType(QFileAction::OpenFile);
        widget->setDefaultAction(action);

        connect(action, &QFileAction::filePathChanged, widget, &QOpenFileButton::filePathChanged);
    }

public:
    QOpenFileButton* widget;
    QFileAction *action;
};

QOpenFileButton::QOpenFileButton(QWidget *parent)
    : QEmbedableButton(parent)
    , d(new QOpenFileButtonPrivate(this))
{
}

QString QOpenFileButton::filePath() const
{
    return d->action->filePath();
}

void QOpenFileButton::setFilePath(const QString &filePath)
{
    d->action->setFilePath(filePath);
}

QString QOpenFileButton::caption() const
{
    return d->action->caption();
}

void QOpenFileButton::setCaption(const QString &caption)
{
    d->action->setCaption(caption);
}

QString QOpenFileButton::directory() const
{
    return d->action->directory();
}

void QOpenFileButton::setDirectory(const QString &directory)
{
    d->action->setDirectory(directory);
}

QStringList QOpenFileButton::filter() const
{
    return d->action->filter();
}

void QOpenFileButton::setFilter(const QStringList &filter)
{
    d->action->setFilter(filter);
}

QFileDialog::Options QOpenFileButton::options() const
{
    return d->action->options();
}

void QOpenFileButton::setOptions(QFileDialog::Options options)
{
    d->action->setOptions(options);
}

#include "QOpenFileButton.moc"
