#ifndef QOPENFILELINEEDIT_H
#define QOPENFILELINEEDIT_H

#include <QLineEdit>
#include <QFileDialog>

class QOpenFileLineEdit : public QLineEdit
{
    Q_OBJECT
    class QOpenFileLineEditPrivate* d;

    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath RESET resetFilePath USER true NOTIFY filePathChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption RESET resetCaption)
    Q_PROPERTY(QString directory READ directory WRITE setDirectory RESET resetDirectory)
    Q_PROPERTY(QStringList filter READ filter WRITE setFilter RESET resetFilter)
    Q_PROPERTY(QFileDialog::Options options READ options WRITE setOptions RESET resetOptions)

public:
    QOpenFileLineEdit(QWidget *parent = 0);

    QString filePath() const;
    void setFilePath(const QString &filePath);

    QString caption() const;
    void setCaption(const QString &caption);

    QString directory() const;
    void setDirectory(const QString &directory);

    QStringList filter() const;
    void setFilter(const QStringList &filter);

    QFileDialog::Options options() const;
    void setOptions(QFileDialog::Options options);

private:
    void resetFilePath();
    void resetCaption();
    void resetDirectory();
    void resetFilter();
    void resetOptions();

signals:
    void filePathChanged(const QString &filePath);
};

#endif
