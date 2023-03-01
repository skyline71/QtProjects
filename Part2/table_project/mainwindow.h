#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_Save_TXT_clicked();

    void on_pushButton_Open_TXT_clicked();

    void on_pushButton_Save_BIN_clicked();

    void on_pushButton_Open_BIN_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
