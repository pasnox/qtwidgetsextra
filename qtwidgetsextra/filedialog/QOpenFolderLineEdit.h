#ifndef QOPENFOLDERLINEEDIT_H
#define QOPENFOLDERLINEEDIT_H

#include <QLineEdit>
#include <QFileDialog>

class QOpenFolderLineEdit : public QLineEdit
{
    Q_OBJECT
    class QOpenFolderLineEditPrivate* d;

    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath RESET resetFilePath USER true NOTIFY filePathChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption RESET resetCaption)
    Q_PROPERTY(QString directory READ directory WRITE setDirectory RESET resetDirectory)
    Q_PROPERTY(QFileDialog::Options options READ options WRITE setOptions RESET resetOptions)

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

private:
    void resetFilePath();
    void resetCaption();
    void resetDirectory();
    void resetOptions();

signals:
    void filePathChanged(const QString &filePath);
};

#endif // QOPENFOLDERLINEEDIT_H
