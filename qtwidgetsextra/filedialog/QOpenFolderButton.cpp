#include "QOpenFolderButton.h"

class QOpenFolderButtonPrivate : public QObject
{
    Q_OBJECT

public:
    QOpenFolderButtonPrivate(QOpenFolderButton *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , action(new QFileAction(this)) {
        Q_ASSERT(widget);

        action->setType(QFileAction::Folder);
        widget->setDefaultAction(action);

        connect(action, SIGNAL(filePathChanged(QString)), widget, SIGNAL(filePathChanged(QString)));
    }

public:
    QOpenFolderButton* widget;
    QFileAction *action;
};

QOpenFolderButton::QOpenFolderButton(QWidget *parent)
    : QEmbedableButton(parent)
    , d(new QOpenFolderButtonPrivate(this))
{
}

QString QOpenFolderButton::filePath() const
{
    return d->action->filePath();
}

void QOpenFolderButton::setFilePath(const QString &filePath)
{
    d->action->setFilePath(filePath);
}

QString QOpenFolderButton::caption() const
{
    return d->action->caption();
}

void QOpenFolderButton::setCaption(const QString &caption)
{
    d->action->setCaption(caption);
}

QString QOpenFolderButton::directory() const
{
    return d->action->directory();
}

void QOpenFolderButton::setDirectory(const QString &directory)
{
    d->action->setDirectory(directory);
}

QFileDialog::Options QOpenFolderButton::options() const
{
    return d->action->options();
}

void QOpenFolderButton::setOptions(QFileDialog::Options options)
{
    d->action->setOptions(options);
}

#include "QOpenFolderButton.moc"
