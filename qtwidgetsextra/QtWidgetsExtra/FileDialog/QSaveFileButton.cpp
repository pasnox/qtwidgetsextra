#include "QSaveFileButton.h"

class QSaveFileButtonPrivate : public QObject {
    Q_OBJECT

public:
    explicit QSaveFileButtonPrivate(QSaveFileButton *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , action(new QFileAction(this)) {
        Q_ASSERT(widget);

        action->setType(QFileAction::Type::SaveFile);
        widget->setDefaultAction(action);

        connect(action, &QFileAction::filePathChanged, widget, &QSaveFileButton::filePathChanged);
    }

public:
    QSaveFileButton *widget;
    QFileAction *action;
};

QSaveFileButton::QSaveFileButton(QWidget *parent)
    : QEmbedableButton(parent)
    , d(new QSaveFileButtonPrivate(this)) {
}

QString QSaveFileButton::filePath() const {
    return d->action->filePath();
}

void QSaveFileButton::setFilePath(const QString &filePath) {
    d->action->setFilePath(filePath);
}

QString QSaveFileButton::caption() const {
    return d->action->caption();
}

void QSaveFileButton::setCaption(const QString &caption) {
    d->action->setCaption(caption);
}

QString QSaveFileButton::directory() const {
    return d->action->directory();
}

void QSaveFileButton::setDirectory(const QString &directory) {
    d->action->setDirectory(directory);
}

QStringList QSaveFileButton::filter() const {
    return d->action->filter();
}

void QSaveFileButton::setFilter(const QStringList &filter) {
    d->action->setFilter(filter);
}

QFileDialog::Options QSaveFileButton::options() const {
    return d->action->options();
}

void QSaveFileButton::setOptions(QFileDialog::Options options) {
    d->action->setOptions(options);
}

#include "QSaveFileButton.moc"
