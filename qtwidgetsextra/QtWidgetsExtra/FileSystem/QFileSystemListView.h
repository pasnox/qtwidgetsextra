#pragma once

#include <QtWidgetsExtraLibExport.h>

#include <QDir>
#include <QListView>

class QT_WIDGETS_EXTRA_QT_WIDGETS_EXTRA_LIB_EXPORT QFileSystemListView : public QListView {
    Q_OBJECT
    class QFileSystemListViewPrivate *d;

    Q_PROPERTY(bool nameFilterDisables READ nameFilterDisables WRITE setNameFilterDisables)
    Q_PROPERTY(bool readOnly READ readOnly WRITE setReadOnly)
    Q_PROPERTY(bool resolveSymlinks READ resolveSymlinks WRITE setResolveSymlinks)
    Q_PROPERTY(bool browsable READ browsable WRITE setBrowsable)
    Q_PROPERTY(QDir::Filters filters READ filters WRITE setFilters)
    Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters)
    Q_PROPERTY(QFileSystemListView::Section visibleSection READ visibleSection WRITE setVisibleSection)
    Q_PROPERTY(QString rootPath READ rootPath WRITE setRootPath NOTIFY rootPathChanged)

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
    Q_DECLARE_FLAGS(Sections, Section)
    Q_FLAG(Sections)

    explicit QFileSystemListView(QWidget *parent = nullptr);

    void setModel(QAbstractItemModel *model) override;

    bool nameFilterDisables() const;
    void setNameFilterDisables(bool nameFilterDisables);

    bool readOnly() const;
    void setReadOnly(bool readOnly);

    bool resolveSymlinks() const;
    void setResolveSymlinks(bool resolveSymlinks);

    bool browsable() const;
    void setBrowsable(bool browsable);

    QDir::Filters filters() const;
    void setFilters(QDir::Filters filters);

    QStringList nameFilters() const;
    void setNameFilters(const QStringList &nameFilters);

    QFileSystemListView::Section visibleSection() const;
    void setVisibleSection(QFileSystemListView::Section section);

    QString rootPath() const;
    void setRootPath(const QString &rootPath);

    using QListView::setSelection;

    QStringList selection() const;
    void setSelection(const QStringList &selection);
    void addSelection(QStringList &selection);
    void clearSelection();

Q_SIGNALS:
    void directoryLoaded(const QString &path);
    void fileRenamed(const QString &path, const QString &oldName, const QString &newName);
    void rootPathChanged(const QString &newPath);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QFileSystemListView::Sections)
