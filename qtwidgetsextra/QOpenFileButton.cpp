#include "QOpenFileButton.h"
#include "QEmbedableButton_p.h"

#include <QStyle>

class QOpenFileButtonPrivate : public QObject
{
    Q_OBJECT

public:
    QOpenFileButtonPrivate(QOpenFileButton *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
    {
        Q_ASSERT(widget);

        widget->setIcon(widget->style()->standardIcon(QStyle::SP_DialogOpenButton, 0, widget));

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

        if (!filePath.isEmpty() && QFile::exists(filePath)) {
            dir = filePath;
        }

        const QString fn = QFileDialog::getOpenFileName(widget->window(), caption, dir, filter.join(QLatin1String(";;")), 0, options);

        if (!fn.isNull()) {
            widget->setFilePath(fn);
        }
    }

public:
    QOpenFileButton* widget;
    QString filePath;
    QString caption;
    QString directory;
    QStringList filter;
    QFileDialog::Options options;
};

QOpenFileButton::QOpenFileButton(QWidget *parent)
    : QEmbedableButton(parent)
    , d(new QOpenFileButtonPrivate(this))
{
}

QString QOpenFileButton::filePath() const
{
    return d->filePath;
}

void QOpenFileButton::setFilePath(const QString &filePath)
{
    if (d->filePath == filePath) {
        return;
    }

    d->filePath = filePath;
    setToolTip(d->filePath);
    emit filePathChanged(filePath);
}

QString QOpenFileButton::caption() const
{
    return d->caption;
}

void QOpenFileButton::setCaption(const QString &caption)
{
    d->caption = caption;
}

QString QOpenFileButton::directory() const
{
    return d->directory;
}

void QOpenFileButton::setDirectory(const QString &directory)
{
    d->directory = directory;
}

QStringList QOpenFileButton::filter() const
{
    return d->filter;
}

void QOpenFileButton::setFilter(const QStringList &filter)
{
    d->filter = filter;
}

QFileDialog::Options QOpenFileButton::options() const
{
    return d->options;
}

void QOpenFileButton::setOptions(QFileDialog::Options options)
{
    d->options = options;
}

void QOpenFileButton::resetCaption()
{
    d->resetCaption();
}

void QOpenFileButton::resetDirectory()
{
    d->resetDirectory();
}

void QOpenFileButton::resetFilter()
{
    d->resetFilter();
}

void QOpenFileButton::resetOptions()
{
    d->resetOptions();
}

#include "QOpenFileButton.moc"
