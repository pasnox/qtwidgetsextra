#pragma once

#include <QtWidgetsExtraLibExport.h>

#include <QComboBox>
#include <QDir>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QFileSystemComboBox : public QComboBox {
    Q_OBJECT
    class QFileSystemComboBoxPrivate *d;

    Q_PROPERTY(bool nameFilterDisables READ nameFilterDisables WRITE setNameFilterDisables)
    Q_PROPERTY(bool resolveSymlinks READ resolveSymlinks WRITE setResolveSymlinks)
    Q_PROPERTY(QDir::Filters filters READ filters WRITE setFilters)
    Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters)
    Q_PROPERTY(QFileSystemComboBox::Section visibleSection READ visibleSection WRITE setVisibleSection)
    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath NOTIFY rootPathChanged)
    Q_PROPERTY(QString currentFileName READ currentFileName WRITE setCurrentFileName NOTIFY currentFileNameChanged)
    Q_PROPERTY(QString currentFilePath READ currentFilePath WRITE setCurrentFilePath NOTIFY currentFilePathChanged)

public:
    enum class Column {
        Name,
        Size,
        Type,
        LastModification
    };
    Q_ENUM(Column)

    enum class Section {
        All = 0,
        Name = 0x1,
        Size = 0x2,
        Type = 0x4,
        LastModification = 0x8
    };
    Q_ENUM(Section)

    explicit QFileSystemComboBox(QWidget *parent = nullptr);

    bool nameFilterDisables() const;
    void setNameFilterDisables(bool nameFilterDisables);

    bool resolveSymlinks() const;
    void setResolveSymlinks(bool resolveSymlinks);

    QDir::Filters filters() const;
    void setFilters(QDir::Filters filters);

    QStringList nameFilters() const;
    void setNameFilters(const QStringList &nameFilters);

    QFileSystemComboBox::Section visibleSection() const;
    void setVisibleSection(QFileSystemComboBox::Section section);

    QString rootPath() const;
    void setRootPath(const QString &rootPath);

    QString currentFileName() const;
    void setCurrentFileName(const QString &fileName);

    QString currentFilePath() const;
    void setCurrentFilePath(const QString &filePath);

    QString fileName(int index) const;
    QString filePath(int index) const;

    int	findFileName(const QString &fileName, Qt::MatchFlags flags = Qt::MatchCaseSensitive) const;

Q_SIGNALS:
    void directoryLoaded(const QString &path);
    void rootPathChanged(const QString &newPath);
    QString currentFileNameChanged(const QString &fileName);
    QString currentFilePathChanged(const QString &filePath);

private:
    using QComboBox::clear;
    using QComboBox::currentText;
    using QComboBox::setCurrentText;
    using QComboBox::findText;
    using QComboBox::isEditable;
    using QComboBox::setEditable;
    using QComboBox::clearEditText;
    using QComboBox::setEditText;
    using QComboBox::model;
    using QComboBox::setModel;
    using QComboBox::modelColumn;
    using QComboBox::setModelColumn;
    using QComboBox::rootModelIndex;
    using QComboBox::setRootModelIndex;
    using QComboBox::view;
    using QComboBox::setView;
    using QComboBox::addItem;
    using QComboBox::addItems;
    using QComboBox::insertItem;
    using QComboBox::insertItems;
    using QComboBox::insertSeparator;
    using QComboBox::removeItem;
};
