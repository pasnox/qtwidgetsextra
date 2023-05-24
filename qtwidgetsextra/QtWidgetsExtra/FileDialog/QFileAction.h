#ifndef QFILEACTION_H
#define QFILEACTION_H

#include <QAction>
#include <QFileDialog>

class QFileAction : public QAction
{
    Q_OBJECT
    class QFileActionPrivate *d;

    Q_ENUMS(Type)

public:
    enum Type {
        OpenFile,
        SaveFile,
        OpenFolder
    };

    explicit QFileAction(QObject *parent = 0);

    QFileAction::Type type() const;
    void setType(QFileAction::Type type);

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

signals:
    void filePathChanged(const QString &filePath);
};

#endif // QFILEACTION_H
