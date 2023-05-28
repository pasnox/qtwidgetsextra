#include "QOpenFileLineEdit.h"
#include "QFileAction.h"

class QOpenFileLineEditPrivate : public QObject {
    Q_OBJECT

public:
    explicit QOpenFileLineEditPrivate(QOpenFileLineEdit *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , action(new QFileAction(this)) {
        Q_ASSERT(widget);

        action->setType(QFileAction::Type::OpenFile);
        widget->addAction(action, position);

        connect(widget, &QLineEdit::textChanged, this, &QOpenFileLineEditPrivate::textChanged);
        connect(action, &QFileAction::filePathChanged, this, &QOpenFileLineEditPrivate::filePathChanged);
        connect(action, &QFileAction::filePathChanged, widget, &QOpenFileLineEdit::filePathChanged);
    }

    void textChanged(const QString &text) {
        action->setFilePath(text);
    }

    void filePathChanged(const QString &text) {
        if (widget->text() != text) {
            widget->QAbstractButtonLineEdit::setText(text);
        }
    }

public:
    QOpenFileLineEdit *widget;
    QLineEdit::ActionPosition position = QLineEdit::ActionPosition::LeadingPosition;
    QFileAction *action;
};

QOpenFileLineEdit::QOpenFileLineEdit(QWidget *parent)
    : QAbstractButtonLineEdit(parent)
    , d(new QOpenFileLineEditPrivate(this)) {
}

QLineEdit::ActionPosition QOpenFileLineEdit::embededActionPosition() const {
    return d->position;
}

void QOpenFileLineEdit::setEmbededActionPosition(ActionPosition position) {
    if (d->position != position) {
        d->position = position;
        addAction(d->action, d->position);
        Q_EMIT embededActionPositionChanged(d->position);
    }
}

QString QOpenFileLineEdit::filePath() const {
    return d->action->filePath();
}

void QOpenFileLineEdit::setFilePath(const QString &filePath) {
    d->action->setFilePath(filePath);
}

QString QOpenFileLineEdit::caption() const {
    return d->action->caption();
}

void QOpenFileLineEdit::setCaption(const QString &caption) {
    d->action->setCaption(caption);
}

QString QOpenFileLineEdit::directory() const {
    return d->action->directory();
}

void QOpenFileLineEdit::setDirectory(const QString &directory) {
    d->action->setDirectory(directory);
}

QStringList QOpenFileLineEdit::filter() const {
    return d->action->filter();
}

void QOpenFileLineEdit::setFilter(const QStringList &filter) {
    d->action->setFilter(filter);
}

QFileDialog::Options QOpenFileLineEdit::options() const {
    return d->action->options();
}

void QOpenFileLineEdit::setOptions(QFileDialog::Options options) {
    d->action->setOptions(options);
}

#include "QOpenFileLineEdit.moc"
