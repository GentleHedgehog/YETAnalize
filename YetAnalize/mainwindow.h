#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "yetanalizer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pb_Calc_clicked();

    void on_le_input_editingFinished();

    void on_le_input_textChanged(const QString &arg1);

    void on_pb_paste_clicked();

    void on_pb_clear_clicked();

    void on_pb_copy_clicked();

private:
    Ui::MainWindow *ui;
    YetAnalizer analizer;
};

#endif // MAINWINDOW_H
