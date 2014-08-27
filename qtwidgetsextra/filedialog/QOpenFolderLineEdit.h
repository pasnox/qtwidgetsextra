#ifndef QOPENFOLDERLINEEDIT_H
#define QOPENFOLDERLINEEDIT_H

#include "QAbstractButtonLineEdit.h"

#include <QFileDialog>

class QOpenFolderLineEdit : public QAbstractButtonLineEdit
{
    Q_OBJECT
    class QOpenFolderLineEditPrivate* d;

    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath USER true NOTIFY filePathChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption)
    Q_PROPERTY(QString directory READ directory WRITE setDirectory)
    Q_PROPERTY(QFileDialog::Options options READ options WRITE setOptions)

public:
    QOpenFolderLineEdit(QWidget *parent = 0);

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

#endif // QOPENFOLDERLINEEDIT_H
