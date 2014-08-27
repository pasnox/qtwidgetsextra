#include "QSaveFileButton.h"
#include "QEmbedableButton_p.h"

#include <QStyle>

class QSaveFileButtonPrivate : public QObject
{
    Q_OBJECT

public:
    QSaveFileButtonPrivate(QSaveFileButton *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
    {
        Q_ASSERT(widget);

        widget->setIcon(widget->style()->standardIcon(QStyle::SP_DialogSaveButton, 0, widget));

        resetCaption();
        resetDirectory();
        resetFilter();
        resetOptions();

        connect(widget, SIGNAL(clicked()), this, SLOT(clicked()));
    }

    void resetFilePath() {
        widget->setFilePath(QString::null);
    }

    void resetCaption() {
        caption.clear();
    }

    void resetDirectory() {
        directory.clear();
    }

    void resetFilter() {
        filter.clear();
    }

    void resetOptions() {
        options = 0;
    }

public slots:
    void clicked() {
        QString dir = directory;

        if (!filePath.isEmpty()) {
            dir = filePath;
        }

        const QString fn = QFileDialog::getSaveFileName(widget->window(), caption, dir, filter.join(QLatin1String(";;")), 0, options);

        if (!fn.isNull()) {
            widget->setFilePath(fn);
        }
    }

public:
    QSaveFileButton* widget;
    QString filePath;
    QString caption;
    QString directory;
    QStringList filter;
    QFileDialog::Options options;
};

QSaveFileButton::QSaveFileButton(QWidget *parent)
    : QEmbedableButton(parent)
    , d(new QSaveFileButtonPrivate(this))
{
}

QString QSaveFileButton::filePath() const
{
    return d->filePath;
}

void QSaveFileButton::setFilePath(const QString &filePath)
{
    if (d->filePath == filePath) {
        return;
    }

    d->filePath = filePath;
    setToolTip(d->filePath);
    emit filePathChanged(filePath);
}

QString QSaveFileButton::caption() const
{
    return d->caption;
}

void QSaveFileButton::setCaption(const QString &caption)
{
    d->caption = caption;
}

QString QSaveFileButton::directory() const
{
    return d->directory;
}

void QSaveFileButton::setDirectory(const QString &directory)
{
    d->directory = directory;
}

QStringList QSaveFileButton::filter() const
{
    return d->filter;
}

void QSaveFileButton::setFilter(const QStringList &filter)
{
    d->filter = filter;
}

QFileDialog::Options QSaveFileButton::options() const
{
    return d->options;
}

void QSaveFileButton::setOptions(QFileDialog::Options options)
{
    d->options = options;
}

void QSaveFileButton::resetFilePath()
{
    d->resetFilePath();
}

void QSaveFileButton::resetCaption()
{
    d->resetCaption();
}

void QSaveFileButton::resetDirectory()
{
    d->resetDirectory();
}

void QSaveFileButton::resetFilter()
{
    d->resetFilter();
}

void QSaveFileButton::resetOptions()
{
    d->resetOptions();
}

#include "QSaveFileButton.moc"
