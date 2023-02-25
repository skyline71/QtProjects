#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QInputDialog>
#include <QStandardPaths>
#include <QFontDialog>
#include <QTextCursor>
#include <QDateTime>
#include <QColorDialog>
#include <QDesktopServices>
#include <QUrl>

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
    void on_action_create_triggered();

    void on_action_open_triggered();

    void on_action_save_triggered();

    void on_action_saveas_triggered();

    void on_action_quit_triggered();

    void on_plainTextEdit_textChanged();

    void on_plainTextEdit_selectionChanged();

    void on_action_font_triggered();

    void on_action_increment_scale_triggered();

    void on_action_decrement_scale_triggered();

    void on_action_information_triggered();

    void on_action_select_triggered();

    void on_action_delete_triggered();

    void on_action_copy_triggered();

    void on_action_cut_triggered();

    void on_action_paste_triggered();

    void on_action_date_triggered();

    void on_action_undo_triggered();

    void on_action_find_triggered();

    void on_action_replace_triggered();

    void on_action_reset_scale_triggered();

    void on_action_status_line_triggered();

    void on_action_light_theme_triggered();

    void on_action_dark_theme_triggered();

    void on_action_browser_triggered();

private:
    Ui::MainWindow *ui;
    QString path;
    bool saved = false;
    QString title;
    QString file_title;
    QString get_file_title(QString path);
    bool edited = false;
    void text_info();
    int rows = 1;
    int columns = 0;
    int size;
    QString file_text = "";
    QTextCursor cursor;
    int scale;
    bool status_line_hided = false;
    bool issue = false;
    QFont font;


protected:
     void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
