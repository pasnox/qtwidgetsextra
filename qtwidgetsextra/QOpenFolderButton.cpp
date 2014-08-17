#include "QOpenFolderButton.h"
#include "QEmbedableButton_p.h"

#include <QStyle>

class QOpenFolderButtonPrivate : public QObject
{
    Q_OBJECT

public:
    QOpenFolderButtonPrivate(QOpenFolderButton *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , options(QFileDialog::ShowDirsOnly)
    {
        Q_ASSERT(widget);

        widget->setIcon(widget->style()->standardIcon(QStyle::SP_DirIcon, 0, widget));

        resetCaption();
        resetDirectory();
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

    void resetOptions() {
        options = QFileDialog::ShowDirsOnly;
    }

public slots:
    void clicked() {
        QString dir = directory;

        if (!filePath.isEmpty()) {
            dir = filePath;
        }

        const QString fn = QFileDialog::getExistingDirectory(widget->window(), caption, dir, options);

        if (!fn.isNull()) {
            widget->setFilePath(fn);
        }
    }

public:
    QOpenFolderButton* widget;
    QString filePath;
    QString caption;
    QString directory;
    QFileDialog::Options options;
};

QOpenFolderButton::QOpenFolderButton(QWidget *parent)
    : QEmbedableButton(parent)
    , d(new QOpenFolderButtonPrivate(this))
{
}

QString QOpenFolderButton::filePath() const
{
    return d->filePath;
}

void QOpenFolderButton::setFilePath(const QString &filePath)
{
    if (d->filePath == filePath) {
        return;
    }

    d->filePath = filePath;
    setToolTip(d->filePath);
    emit filePathChanged(filePath);
}

QString QOpenFolderButton::caption() const
{
    return d->caption;
}

void QOpenFolderButton::setCaption(const QString &caption)
{
    d->caption = caption;
}

QString QOpenFolderButton::directory() const
{
    return d->directory;
}

void QOpenFolderButton::setDirectory(const QString &directory)
{
    d->directory = directory;
}

QFileDialog::Options QOpenFolderButton::options() const
{
    return d->options;
}

void QOpenFolderButton::setOptions(QFileDialog::Options options)
{
    d->options = options;
}

void QOpenFolderButton::resetFilePath()
{
    d->resetFilePath();
}

void QOpenFolderButton::resetCaption()
{
    d->resetCaption();
}

void QOpenFolderButton::resetDirectory()
{
    d->resetDirectory();
}

void QOpenFolderButton::resetOptions()
{
    d->resetOptions();
}

#include "QOpenFolderButton.moc"
