#include "QFileAction.h"

#include <QApplication>
#include <QStyle>

class QFileActionPrivate : public QObject {
    Q_OBJECT

public:
    QFileActionPrivate(QFileAction *actionP)
        : QObject(actionP)
        , action(actionP)
        , type(QFileAction::Open)
        , options(0) {
        Q_ASSERT(action);

        updateIcon();

        connect(action, SIGNAL(triggered()), this, SLOT(triggered()));
    }

    void updateIcon() {
        switch (type) {
            case QFileAction::Open:
                action->setIcon(qApp->style()->standardIcon(QStyle::SP_DialogOpenButton));
                break;
            case QFileAction::Save:
                action->setIcon(qApp->style()->standardIcon(QStyle::SP_DialogSaveButton));
                break;
            case QFileAction::Folder:
                action->setIcon(qApp->style()->standardIcon(QStyle::SP_DirIcon));
                break;
        }
    }

public slots:
    void triggered() {
        QString dir = directory;
        QString fn;

        if (!filePath.isEmpty()) {
            dir = filePath;
        }

        switch (type) {
            case QFileAction::Open:
                fn = QFileDialog::getOpenFileName(0, caption, dir, filter.join(QLatin1String(";;")), 0, options);
                break;
            case QFileAction::Save:
                fn = QFileDialog::getSaveFileName(0, caption, dir, filter.join(QLatin1String(";;")), 0, options);
                break;
            case QFileAction::Folder:
                fn = QFileDialog::getExistingDirectory(0, caption, dir, options);
                break;
        }

        if (!fn.isNull()) {
            action->setFilePath(fn);
        }
    }

public:
    QFileAction *action;
    QFileAction::Type type;
    QString filePath;
    QString caption;
    QString directory;
    QStringList filter;
    QFileDialog::Options options;
};

QFileAction::QFileAction(QObject *parent)
    : QAction(parent)
    , d(new QFileActionPrivate(this))
{
}

QFileAction::Type QFileAction::type() const
{
    return d->type;
}

void QFileAction::setType(QFileAction::Type type)
{
    d->type = type;
    d->updateIcon();
}

QString QFileAction::filePath() const
{
    return d->filePath;
}

void QFileAction::setFilePath(const QString &filePath)
{
    if (d->filePath == filePath) {
        return;
    }

    d->filePath = filePath;
    setToolTip(d->filePath);
    emit filePathChanged(filePath);
}

QString QFileAction::caption() const
{
    return d->caption;
}

void QFileAction::setCaption(const QString &caption)
{
    d->caption = caption;
}

QString QFileAction::directory() const
{
    return d->directory;
}

void QFileAction::setDirectory(const QString &directory)
{
    d->directory = directory;
}

QStringList QFileAction::filter() const
{
    return d->filter;
}

void QFileAction::setFilter(const QStringList &filter)
{
    d->filter = filter;
}

QFileDialog::Options QFileAction::options() const
{
    return d->options;
}

void QFileAction::setOptions(QFileDialog::Options options)
{
    d->options = options;
}

#include "QFileAction.moc"
