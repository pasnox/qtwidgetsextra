#pragma once

#include <QtWidgetsExtraLibExport.h>

#include <QAction>
#include <QFileDialog>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QFileAction : public QAction {
    Q_OBJECT
    class QFileActionPrivate *d;

public:
    enum Type {
        OpenFile,
        SaveFile,
        OpenFolder
    };
    Q_ENUM(Type)

    explicit QFileAction(QObject *parent = nullptr);

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

Q_SIGNALS:
    void filePathChanged(const QString &filePath);
};
