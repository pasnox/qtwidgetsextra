#ifndef QOPENFOLDERBUTTON_H
#define QOPENFOLDERBUTTON_H

#include "QEmbedableButton_p.h"
#include "QFileAction.h"

class QOpenFolderButton : public QEmbedableButton
{
    Q_OBJECT
    class QOpenFolderButtonPrivate* d;

    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath USER true NOTIFY filePathChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption)
    Q_PROPERTY(QString directory READ directory WRITE setDirectory)
    Q_PROPERTY(QFileDialog::Options options READ options WRITE setOptions)

public:
    explicit QOpenFolderButton(QWidget *parent = 0);

    QString filePath() const;
    void setFilePath(const QString &filePath);

    QString caption() const;
    void setCaption(const QString &caption);

    QString directory() const;
    void setDirectory(const QString &directory);

    QFileDialog::Options options() const;
    void setOptions(QFileDialog::Options options);

signals:
    void filePathChanged(const QString &filePath);
};

#endif // QOPENFOLDERBUTTON_H
