#pragma once

#include <QtWidgetsExtra/QAbstractButtonLineEdit.h>

#include <QFileDialog>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QOpenFolderLineEdit : public QAbstractButtonLineEdit {
    Q_OBJECT
    class QOpenFolderLineEditPrivate *d;

    Q_PROPERTY(QLineEdit::ActionPosition embededActionPosition READ embededActionPosition WRITE setEmbededActionPosition
                   NOTIFY embededActionPositionChanged)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath USER true NOTIFY filePathChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption)
    Q_PROPERTY(QString directory READ directory WRITE setDirectory)
    Q_PROPERTY(QFileDialog::Options options READ options WRITE setOptions)

public:
    QOpenFolderLineEdit(QWidget *parent = nullptr);

    QLineEdit::ActionPosition embededActionPosition() const;
    void setEmbededActionPosition(QLineEdit::ActionPosition position);

    QString filePath() const;
    void setFilePath(const QString &filePath);

    QString caption() const;
    void setCaption(const QString &caption);

    QString directory() const;
    void setDirectory(const QString &directory);

    QFileDialog::Options options() const;
    void setOptions(QFileDialog::Options options);

Q_SIGNALS:
    void embededActionPositionChanged(QLineEdit::ActionPosition position);
    void filePathChanged(const QString &filePath);
};
