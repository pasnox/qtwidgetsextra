#include "QSaveFileLineEdit.h"
#include "QFileAction.h"

class QSaveFileLineEditPrivate : public QObject {
    Q_OBJECT

public:
    explicit QSaveFileLineEditPrivate(QSaveFileLineEdit *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , action(new QFileAction(this)) {
        Q_ASSERT(widget);

        action->setType(QFileAction::Type::SaveFile);
        widget->addAction(action, position);

        connect(widget, &QLineEdit::textChanged, this, &QSaveFileLineEditPrivate::textChanged);
        connect(action, &QFileAction::filePathChanged, this, &QSaveFileLineEditPrivate::filePathChanged);
        connect(action, &QFileAction::filePathChanged, widget, &QSaveFileLineEdit::filePathChanged);
    }

    void textChanged(const QString &text) {
        action->setFilePath(text);
    }

    void filePathChanged(const QString &text) {
        if (widget->QAbstractButtonLineEdit::text() != text) {
            widget->QAbstractButtonLineEdit::setText(text);
        }
    }

public:
    QSaveFileLineEdit *widget;
    QLineEdit::ActionPosition position = QLineEdit::ActionPosition::LeadingPosition;
    QFileAction *action;
};

QSaveFileLineEdit::QSaveFileLineEdit(QWidget *parent)
    : QAbstractButtonLineEdit(parent)
    , d(new QSaveFileLineEditPrivate(this)) {
}

QLineEdit::ActionPosition QSaveFileLineEdit::embededActionPosition() const {
    return d->position;
}

void QSaveFileLineEdit::setEmbededActionPosition(ActionPosition position) {
    if (d->position != position) {
        d->position = position;
        addAction(d->action, d->position);
        Q_EMIT embededActionPositionChanged(d->position);
    }
}

QString QSaveFileLineEdit::filePath() const {
    return d->action->filePath();
}

void QSaveFileLineEdit::setFilePath(const QString &filePath) {
    d->action->setFilePath(filePath);
}

QString QSaveFileLineEdit::caption() const {
    return d->action->caption();
}

void QSaveFileLineEdit::setCaption(const QString &caption) {
    d->action->setCaption(caption);
}

QString QSaveFileLineEdit::directory() const {
    return d->action->directory();
}

void QSaveFileLineEdit::setDirectory(const QString &directory) {
    d->action->setDirectory(directory);
}

QStringList QSaveFileLineEdit::filter() const {
    return d->action->filter();
}

void QSaveFileLineEdit::setFilter(const QStringList &filter) {
    d->action->setFilter(filter);
}

QFileDialog::Options QSaveFileLineEdit::options() const {
    return d->action->options();
}

void QSaveFileLineEdit::setOptions(QFileDialog::Options options) {
    d->action->setOptions(options);
}

#include "QSaveFileLineEdit.moc"
