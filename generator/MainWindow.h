#pragma once

#include "Generator.h"

#include <QMainWindow>

#include <memory>

class Ui_MainWindow;

class QTreeWidgetItem;
class QAbstractButton;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private Q_SLOTS:
    void on_tbAdd_clicked();
    void on_tbRemove_clicked();
    void on_tbUp_clicked();
    void on_tbDown_clicked();
    void on_dbbButtons_clicked(QAbstractButton *button);

private:
    std::unique_ptr<Ui_MainWindow> m_ui;
    Generator m_generator;

    bool saveFile(const QString &content, const QString &filePath) const;

    void apply();
    void save();
};
