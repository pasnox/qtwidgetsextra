#include "QOpenFolderLineEdit.h"
#include "QFileAction.h"

class QOpenFolderLineEditPrivate : public QObject {
    Q_OBJECT

public:
    explicit QOpenFolderLineEditPrivate(QOpenFolderLineEdit *widgetP)
        : QObject(widgetP)
        , widget(widgetP)
        , action(new QFileAction(this)) {
        Q_ASSERT(widget);

        action->setType(QFileAction::Type::OpenFolder);
        widget->addAction(action, position);

        connect(widget, &QLineEdit::textChanged, this, &QOpenFolderLineEditPrivate::textChanged);
        connect(action, &QFileAction::filePathChanged, this, &QOpenFolderLineEditPrivate::filePathChanged);
        connect(action, &QFileAction::filePathChanged, widget, &QOpenFolderLineEdit::filePathChanged);
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
    QOpenFolderLineEdit *widget;
    QLineEdit::ActionPosition position = QLineEdit::ActionPosition::LeadingPosition;
    QFileAction *action;
};

QOpenFolderLineEdit::QOpenFolderLineEdit(QWidget *parent)
    : QAbstractButtonLineEdit(parent)
    , d(new QOpenFolderLineEditPrivate(this)) {
}

QLineEdit::ActionPosition QOpenFolderLineEdit::embededActionPosition() const {
    return d->position;
}

void QOpenFolderLineEdit::setEmbededActionPosition(ActionPosition position) {
    if (d->position != position) {
        d->position = position;
        addAction(d->action, d->position);
        Q_EMIT embededActionPositionChanged(d->position);
    }
}

QString QOpenFolderLineEdit::filePath() const {
    return d->action->filePath();
}

void QOpenFolderLineEdit::setFilePath(const QString &filePath) {
    d->action->setFilePath(filePath);
}

QString QOpenFolderLineEdit::caption() const {
    return d->action->caption();
}

void QOpenFolderLineEdit::setCaption(const QString &caption) {
    d->action->setCaption(caption);
}

QString QOpenFolderLineEdit::directory() const {
    return d->action->directory();
}

void QOpenFolderLineEdit::setDirectory(const QString &directory) {
    d->action->setDirectory(directory);
}

QFileDialog::Options QOpenFolderLineEdit::options() const {
    return d->action->options();
}

void QOpenFolderLineEdit::setOptions(QFileDialog::Options options) {
    d->action->setOptions(options);
}

#include "QOpenFolderLineEdit.moc"
