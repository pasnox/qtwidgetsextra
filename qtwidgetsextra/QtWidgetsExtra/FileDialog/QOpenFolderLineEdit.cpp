#include "QOpenFolderLineEdit.h"
#include "QtWidgetsExtra/FileDialog/QFileAction.h"

class QOpenFolderLineEditPrivate : public QObject
{
    Q_OBJECT

public:
    QOpenFolderLineEditPrivate(QOpenFolderLineEdit *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , action(new QFileAction(this))
    {
        Q_ASSERT(widget);

        action->setType(QFileAction::OpenFolder);
        widget->addAction(action, QLineEdit::ActionPosition::LeadingPosition);

        connect(widget, &QLineEdit::textChanged, this, &QOpenFolderLineEditPrivate::textChanged);
        connect(action, &QFileAction::filePathChanged, this, &QOpenFolderLineEditPrivate::filePathChanged);
        connect(action, &QFileAction::filePathChanged, widget, &QOpenFolderLineEdit::filePathChanged);
    }

public Q_SLOTS:
    void textChanged(const QString &text) {
        action->setFilePath(text);
    }

    void filePathChanged(const QString &text) {
        if (widget->text() != text) {
            widget->setText(text);
        }
    }

public:
    QOpenFolderLineEdit *widget;
    QFileAction *action;
};

QOpenFolderLineEdit::QOpenFolderLineEdit(QWidget *parent)
    : QAbstractButtonLineEdit(parent)
    , d(new QOpenFolderLineEditPrivate(this))
{
}

QString QOpenFolderLineEdit::filePath() const
{
    return d->action->filePath();
}

void QOpenFolderLineEdit::setFilePath(const QString &filePath)
{
    d->action->setFilePath(filePath);
}

QString QOpenFolderLineEdit::caption() const
{
    return d->action->caption();
}

void QOpenFolderLineEdit::setCaption(const QString &caption)
{
    d->action->setCaption(caption);
}

QString QOpenFolderLineEdit::directory() const
{
    return d->action->directory();
}

void QOpenFolderLineEdit::setDirectory(const QString &directory)
{
    d->action->setDirectory(directory);
}

QFileDialog::Options QOpenFolderLineEdit::options() const
{
    return d->action->options();
}

void QOpenFolderLineEdit::setOptions(QFileDialog::Options options)
{
    d->action->setOptions(options);
}

#include "QOpenFolderLineEdit.moc"
