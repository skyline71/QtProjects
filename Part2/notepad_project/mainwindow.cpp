#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Безымянный – Блокнот");
    title = QWidget::windowTitle();
    path = "Безымянный";
    size = 0;
    scale = 100;
    ui->label->setText(tr("Строк ") + QString::number(1) + tr(", Символов ") + QString::number(0)
                       + QString("\t") + tr("Масштаб ") + (QString::number(100) + "%"));
    ui->action_cut->setDisabled(true);
    ui->action_copy->setDisabled(true);
    ui->action_delete->setDisabled(true);
    ui->action_undo->setDisabled(true);
    ui->action_find->setDisabled(true);
    ui->action_replace->setDisabled(true);
    ui->action_browser->setDisabled(true);
    font = QFont("Consolas", 20);
    ui->plainTextEdit->setFont(QFont("Consolas", 20));
    ui->action_status_line->setCheckable(true);
    ui->action_status_line->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_create_triggered() //Кнопка создания нового файла
{
    if(title.contains("*"))
    {
        QMessageBox::StandardButton reply;
        QString question = "Вы хотите сохранить изменения в файле " + QString("\"") + path + QString("\"") + "?";
        QString cute_question = QString("<span style='color:#483D8B;'>%1</span>").arg(question);


        reply = QMessageBox::question(this,"Блокнот", cute_question,
                                      QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(reply == QMessageBox::Yes)
        {
            on_action_save_triggered();
            if(path == "Безымянный")
            {
                return;
            }
            else
            {
                ui->plainTextEdit->clear();
                QWidget::setWindowTitle("Безымянный – Блокнот");
                title = "Безымянный – Блокнот";
                path = "Безымянный";
                edited = false;
                saved = false;
            }
        }
        else if(reply == QMessageBox::No)
        {
            ui->plainTextEdit->clear();
            QWidget::setWindowTitle("Безымянный – Блокнот");
            title = "Безымянный – Блокнот";
            path = "Безымянный";
            edited = false;
            saved = false;
        }
        else if(reply == QMessageBox::Cancel)
        {
            return;
        }
    }
    else
    {
        ui->plainTextEdit->clear();
        QWidget::setWindowTitle("Безымянный – Блокнот");
        title = "Безымянный – Блокнот";
        path = "Безымянный";
        edited = false;
        saved = false;
    }
}

void MainWindow::on_action_open_triggered() //Кнопка открытия файла
{
    if(title.contains("*"))
    {
        QMessageBox::StandardButton reply;
        QString question = "Вы хотите сохранить изменения в файле " + QString("\"") + path + QString("\"") + "?";
        QString cute_question = QString("<span style='color:#483D8B;'>%1</span>").arg(question);

        reply = QMessageBox::question(this,"Блокнот", cute_question,
                                      QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(reply == QMessageBox::Yes)
        {
            //part 1: save
            on_action_save_triggered();
            if(path == "Безымянный")
            {
                return;
            }
            else
            {
                //part 2: open
                QString new_path = QFileDialog::getOpenFileName(this,"Открытие",
                                                    QString(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)),
                                                    "Текстовые документы (*.txt)");

                if(!new_path.isEmpty())
                {
                    QFile file_new(new_path);
                    file_new.open(QIODevice::ReadOnly | QIODevice::Text);
                    file_title = get_file_title(new_path);

                    if(file_new.isOpen())
                    {
                        QByteArray data;
                        data = file_new.readAll();
                        ui->plainTextEdit->setPlainText(QString(data));

                        QWidget::setWindowTitle(file_title + " – Блокнот");
                        path = new_path;
                        title = file_title + " – Блокнот";
                        edited = false;
                        saved = true;
                    }
                    else
                    {
                        QMessageBox::information(this,"Блокнот","Ошибка открытия файла");
                        file_title = get_file_title(path);
                        return;
                    }
                }
                else
                {
                    QMessageBox::information(this,"Блокнот","Ошибка открытия файла");
                    file_title = get_file_title(path);
                    return;
                }
            }
        }
        else if(reply == QMessageBox::No)
        {
            QString new_path = QFileDialog::getOpenFileName(this,"Открытие",
                                                QString(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)),
                                                "Текстовые документы (*.txt)");

            if(!new_path.isEmpty())
            {
                QFile file(new_path);
                file.open(QIODevice::ReadOnly | QIODevice::Text);
                file_title = get_file_title(new_path);

                if(file.isOpen())
                {
                    QByteArray data;
                    data = file.readAll();
                    ui->plainTextEdit->setPlainText(QString(data));

                    QWidget::setWindowTitle(file_title + " – Блокнот");
                    path = new_path;
                    title = file_title + " – Блокнот";
                    edited = false;
                    saved = true;
                }
                else
                {
                    QMessageBox::information(this,"Блокнот","Ошибка открытия файла");
                    file_title = get_file_title(path);
                    return;
                }
            }
            else
            {
                QMessageBox::information(this,"Блокнот","Ошибка открытия файла");
                file_title = get_file_title(path);
                return;
            }
        }
        else if(reply == QMessageBox::Cancel)
        {
            return;
        }
    }
    else
    {
        QString new_path = QFileDialog::getOpenFileName(this,"Открытие",
                                            QString(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)),
                                            "Текстовые документы (*.txt)");

        if(!new_path.isEmpty())
        {
            QFile file(new_path);
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            file_title = get_file_title(new_path);

            if(file.isOpen())
            {
                QByteArray data;
                data = file.readAll();
                ui->plainTextEdit->setPlainText(QString(data));

                QWidget::setWindowTitle(file_title + " – Блокнот");
                title = file_title + " – Блокнот";
                path = new_path;
                edited = false;
                saved = true;
            }
            else
            {
                QMessageBox::information(this,"Блокнот","Ошибка открытия файла");
                file_title = get_file_title(path);
                return;
            }
        }
        else
        {
            QMessageBox::information(this,"Блокнот","Ошибка открытия файла");
            file_title = get_file_title(path);
            return;
        }
    }
}

void MainWindow::on_action_save_triggered() //Кнопка сохранения ранее сохраненного файла
{
    if(saved)
    {
        QString new_path = path;
        if(new_path == "Безымянный")
        {
            return;
        }

        if(!new_path.isEmpty())
        {
            QFile file(new_path);
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            file_title = get_file_title(new_path);

            if(file.isOpen())
            {
                issue = false;
                QTextStream stream(&file);
                stream.setCodec("UTF-8");
                stream << ui->plainTextEdit->toPlainText();
                file.close();
                saved = true;
                QWidget::setWindowTitle(file_title + " – Блокнот");
                path = new_path;
                title = file_title + " – Блокнот";
                edited = false;
            }
            else
            {
                issue = true;
                QMessageBox::information(this,"Блокнот","Ошибка сохранения файла");
                file_title = get_file_title(path);
                return;
            }
        }
        else
        {
            issue = true;
            QMessageBox::information(this,"Блокнот","Ошибка сохранения файла");
            file_title = get_file_title(path);
            return;
        }
    }
    else
    {
        QString new_path = QFileDialog::getSaveFileName(this,"Сохранение",
                                            QString(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)),
                                            "Текстовые документы (*.txt)");

        if(!new_path.isEmpty())
        {
            QFile file(new_path);
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            file_title = get_file_title(new_path);

            if(file.isOpen())
            {
                issue = false;
                QTextStream stream(&file);
                stream.setCodec("UTF-8");
                stream << ui->plainTextEdit->toPlainText();
                file.close();
                saved = true;
                QWidget::setWindowTitle(file_title + " – Блокнот");
                path = new_path;
                title = file_title + " – Блокнот";
                edited = false;
            }
            else
            {
                issue = true;
                QMessageBox::information(this,"Блокнот","Ошибка сохранения файла");
                file_title = get_file_title(path);
                return;
            }
        }
        else
        {
            issue = true;
            QMessageBox::information(this,"Блокнот","Ошибка сохранения файла");
            file_title = get_file_title(path);
            return;
        }
    }
}

void MainWindow::on_action_saveas_triggered() //Кнопка сохранения нового файла
{
    QString new_path = QFileDialog::getSaveFileName(this,"Сохранение",
                                        QString(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)),
                                        "Текстовые документы (*.txt)");

    if(!new_path.isEmpty())
    {
        QFile file(new_path);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file_title = get_file_title(new_path);

        if(file.isOpen())
        {
            QTextStream stream(&file);
            stream.setCodec("UTF-8");
            stream << ui->plainTextEdit->toPlainText();
            file.close();
            saved = true;
            QWidget::setWindowTitle(file_title + " – Блокнот");
            path = new_path;
            title = file_title + " – Блокнот";
            edited = false;
        }
        else
        {
            QMessageBox::information(this,"Блокнот","Ошибка сохранения файла");
            file_title = get_file_title(path);
            return;
        }
    }
    else
    {
        QMessageBox::information(this,"Блокнот","Ошибка сохранения файла");
        file_title = get_file_title(path);
        return;
    }
}

void MainWindow::closeEvent(QCloseEvent *event) //Функция обработки сигнала с закрытием программы
{
    if(title.contains("*"))
    {
        QMessageBox::StandardButton reply;
        QString question = "Вы хотите сохранить изменения в файле " + QString("\"") + path + QString("\"") + "?";
        QString cute_question = QString("<span style='color:#483D8B;'>%1</span>").arg(question);


        reply = QMessageBox::question(this,"Блокнот", cute_question,
                                      QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(reply == QMessageBox::Yes)
        {
            on_action_save_triggered();
            if(issue)
            {
                event->ignore();
            }
            else
            {
                event->accept();
            }
        }
        else if(reply == QMessageBox::No)
        {
            event->accept();
        }
        else if(reply == QMessageBox::Cancel)
        {
            event->ignore();
        }
    }
    else
    {
        event->accept();
    }
}

void MainWindow::on_action_quit_triggered() //Кнопка закрытия программы
{
    close();
}

void MainWindow::text_info() //Функция с информацией в строке состояния
{
    rows = file_text.count("\n") + 1;
    ui->label->setText(tr("Строк ") + QString::number(rows) + tr(", Символов ") + QString::number(size)
                       + QString("\t") + tr("Масштаб ") + (QString::number(scale) + "%"));
}

void MainWindow::on_plainTextEdit_textChanged() //Функция обработки сигнала изменения документа
{
    file_text = ui->plainTextEdit->toPlainText();
    size = file_text.size();
    if(size == 0)
    {
        ui->action_find->setDisabled(true);
        ui->action_replace->setDisabled(true);
    }
    else
    {
        ui->action_find->setEnabled(true);
        ui->action_replace->setEnabled(true);
    }

    if(title == "*Безымянный – Блокнот" and size == 0)
    {
        QWidget::setWindowTitle("Безымянный – Блокнот");
        title = "Безымянный – Блокнот";
        edited = false;
    }
    else
    {
        if(!edited)
        {
            QWidget::setWindowTitle('*' + title);
            title = "*" + title;
            edited = true;
        }
    }
    ui->action_undo->setEnabled(true);

    text_info();
}

void MainWindow::on_plainTextEdit_selectionChanged() //Функция обработки сигнала выделения текста внутри документа
{
    cursor = ui->plainTextEdit->textCursor();

    if(cursor.hasSelection())
    {
        ui->action_cut->setEnabled(true);
        ui->action_copy->setEnabled(true);
        ui->action_delete->setEnabled(true);
        ui->action_browser->setEnabled(true);
    }
    else
    {
        ui->action_cut->setDisabled(true);
        ui->action_copy->setDisabled(true);
        ui->action_delete->setDisabled(true);
        ui->action_browser->setDisabled(true);
    }
}

QString MainWindow::get_file_title(QString path) //Функция с информаицией о названии файла
{

    if(path.contains("/"))
    {
        int len = path.size();
        int pos = path.lastIndexOf("/");
        QString current_file_title = path.right(len - pos - 1);
        return current_file_title;
    }
    else
    {
        return "Безымянный";
    }
}

void MainWindow::on_action_font_triggered() //Функция с выбором шрифта
{
    bool ok;
    font = QFontDialog::getFont(&ok, font, this, "Шрифт");
    if (ok)
    {
        ui->plainTextEdit->setFont(font);
    }
    else
    {
        return;
    }
}

void MainWindow::on_action_increment_scale_triggered() //Кнопка увелечения масштаба на 10%
{
    scale += 10;

    ui->label->setText(tr("Строк ") + QString::number(rows) + tr(", Символов ") + QString::number(size)
                       + QString("\t") + tr("Масштаб ") + (QString::number(scale) + "%"));
    if(scale > 500)
    {
        scale = 500;
        ui->label->setText(tr("Строк ") + QString::number(rows) + tr(", Символов ") + QString::number(size)
                           + QString("\t") + tr("Масштаб ") + (QString::number(scale) + "%"));
        return;
    }
    ui->plainTextEdit->zoomOut(-1);
}

void MainWindow::on_action_decrement_scale_triggered() //Кнопка уменьшения масштаба на 10%
{
    scale -= 10;

    ui->label->setText(tr("Строк ") + QString::number(rows) + tr(", Символов ") + QString::number(size)
                       + QString("\t") + tr("Масштаб ") + (QString::number(scale) + "%"));
    if(scale < 10)
    {
        scale = 10;
        ui->label->setText(tr("Строк ") + QString::number(rows) + tr(", Символов ") + QString::number(size)
                           + QString("\t") + tr("Масштаб ") + (QString::number(scale) + "%"));
        return;
    }
    ui->plainTextEdit->zoomOut(1);
}

void MainWindow::on_action_information_triggered() //Кнопка со справкой
{

    QString information = "Блокнот - текстовый редактор. Версия 1.5.2 Developed by Mozzherin Roman RSBO-02-22 2023(c)";
    QString photo = "<img src=\":/new_prefix/images/photo.png\"";

    QMessageBox about_message;
    about_message.setTextFormat(Qt::RichText);
    about_message.setStyleSheet("QLabel{min-width: 550px;}");
    about_message.setWindowTitle("Блокнот: сведения");
    about_message.setText(information + photo);
    about_message.addButton(QMessageBox::Ok);
    about_message.show();
    about_message.exec();
}

void MainWindow::on_action_select_triggered() //Кнопка выделить все
{
    cursor = ui->plainTextEdit->textCursor();
    cursor.setPosition(0);
    cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, size);
    ui->plainTextEdit->setTextCursor(cursor);
}

void MainWindow::on_action_delete_triggered() //Кнопка удалить
{
    cursor = ui->plainTextEdit->textCursor();
    cursor.removeSelectedText();
    ui->plainTextEdit->setTextCursor(cursor);
}

void MainWindow::on_action_copy_triggered() //Кнопка копировать
{
    ui->plainTextEdit->copy();
}

void MainWindow::on_action_cut_triggered() //Кнопка вырезать
{
    ui->plainTextEdit->copy();
    cursor.removeSelectedText();
    ui->plainTextEdit->setTextCursor(cursor);
}

void MainWindow::on_action_paste_triggered()//Кнопка вставить
{
    ui->plainTextEdit->paste();
}

void MainWindow::on_action_date_triggered()//Кнопка с информацией о дате и времени
{
    QString date = QDateTime::currentDateTime().toString("HH:mm dd.MM.yyyy");
    ui->plainTextEdit->appendPlainText(date);
}

void MainWindow::on_action_undo_triggered()//Кнопка отменить
{
    ui->plainTextEdit->undo();
}

void MainWindow::on_action_find_triggered()//Кнопка найти
{
    QString block = QInputDialog::getText(this, tr("Найти"), tr("Что:"), QLineEdit::Normal);
    if(file_text.contains(block))
    {
        int length = block.size();
        int finded_pos = ui->plainTextEdit->toPlainText().indexOf(block);

        cursor = ui->plainTextEdit->textCursor();
        cursor.setPosition(finded_pos);
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, length);
        ui->plainTextEdit->setTextCursor(cursor);
    }
    else
    {
        QMessageBox::information(this, "Блокнот", "Не удается найти " + QString("\"") + QString(block) + QString("\""));
    }
}

void MainWindow::on_action_replace_triggered()//Кнопка заменить
{
    QString block_find = QInputDialog::getText(this, tr("Заменить"), tr("Что:"), QLineEdit::Normal);

    if(file_text.contains(block_find))
    {
        QString block_replace = QInputDialog::getText(this, tr("Заменить"), tr("Чем:"), QLineEdit::Normal);

        int length = block_find.size();
        int finded_pos = ui->plainTextEdit->toPlainText().indexOf(block_find);

        cursor = ui->plainTextEdit->textCursor();
        cursor.setPosition(finded_pos);
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, length);
        cursor.deleteChar();
        cursor.insertText(block_replace);
        ui->plainTextEdit->setTextCursor(cursor);
    }
    else
    {
        QMessageBox::information(this, "Блокнот", "Не удается найти " + QString("\"") + QString(block_find) + QString("\""));
        return;
    }
}

void MainWindow::on_action_reset_scale_triggered()//Кнопка восстановить масштаб по умолчанию
{
    if(scale > 100)
    {
        while(scale != 100)
        {
            ui->plainTextEdit->zoomOut(1);
            scale -= 10;
        }
    }
    else if(scale < 100)
    {
        while(scale != 100)
        {
            ui->plainTextEdit->zoomIn(1);
            scale += 10;
        }
    }

    ui->label->setText(tr("Строк ") + QString::number(rows) + tr(", Символов ") + QString::number(size)
                       + QString("\t") + (QString::number(scale) + "%"));
}

void MainWindow::on_action_status_line_triggered()//Кнопка с информацией о строке состояния
{
    if(status_line_hided)
    {
        ui->action_status_line->setChecked(true);
        ui->label->show();
        status_line_hided = false;
    }
    else
    {
        ui->action_status_line->setChecked(false);
        ui->label->hide();
        status_line_hided = true;
    }
}

void MainWindow::on_action_light_theme_triggered() //Кнопка со сменой темы на светлую
{
    QPalette palette_textedit = ui->plainTextEdit->palette();
    palette_textedit.setColor(QPalette::Base, Qt::white);
    palette_textedit.setColor(QPalette::Text, Qt::black);
    ui->plainTextEdit->setPalette(palette_textedit);

    QPalette palette_window = MainWindow::palette();
    palette_window.setColor(QPalette::Window, Qt::white);
    MainWindow::setPalette(palette_window);

    ui->label->setStyleSheet("QLabel { color : black }");
}

void MainWindow::on_action_dark_theme_triggered() //Кнопка со сменой темы на темную
{
    QPalette palette_textedit = ui->plainTextEdit->palette();
    palette_textedit.setColor(QPalette::Base, "#2D2832");
    palette_textedit.setColor(QPalette::Text, Qt::white);
    ui->plainTextEdit->setPalette(palette_textedit);

    QPalette palette_window = MainWindow::palette();
    palette_window.setColor(QPalette::Window, "#2D2832");
    MainWindow::setPalette(palette_window);

    ui->label->setStyleSheet("QLabel { color : white }");
}

void MainWindow::on_action_browser_triggered()//Кнопка с открытием браузера
{
    cursor = ui->plainTextEdit->textCursor();
    QString request = cursor.selectedText();
    QString link = "https://www.bing.com/search?q=" + request;
    QDesktopServices::openUrl(QUrl(link));
}
