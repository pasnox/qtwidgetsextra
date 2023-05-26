#ifndef QSAVEFILEBUTTON_H
#define QSAVEFILEBUTTON_H

#include <QtWidgetsExtra/QEmbedableButton_p.h>
#include <QtWidgetsExtra/FileDialog/QFileAction.h>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QSaveFileButton : public QEmbedableButton
{
    Q_OBJECT
    class QSaveFileButtonPrivate* d;

    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath USER true NOTIFY filePathChanged)
    Q_PROPERTY(QString caption READ caption WRITE setCaption)
    Q_PROPERTY(QString directory READ directory WRITE setDirectory)
    Q_PROPERTY(QStringList filter READ filter WRITE setFilter)
    Q_PROPERTY(QFileDialog::Options options READ options WRITE setOptions)

public:
    explicit QSaveFileButton(QWidget *parent = 0);

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

Q_SIGNALS:
    void filePathChanged(const QString &filePath);
};

#endif // QSAVEFILEBUTTON_H
