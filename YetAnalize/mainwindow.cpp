#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "yetanalizer.h"
#include "yetfiller.h"

namespace {
YetAnalizer analizer;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fillAnalizerWithYetInfo(analizer);

    setWindowTitle("Подсчет УЕТ");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_Calc_clicked()
{
    QString ans;
    analizer.analize(ui->le_input->text(), ans);
    ui->lbl_answer->setText(ans);
    ui->lbl_lastSum->setText(QString::number(analizer.lastSum()));
}

void MainWindow::on_le_input_editingFinished()
{
    on_pb_Calc_clicked();
}

void MainWindow::on_le_input_textChanged(const QString &arg1)
{
    on_pb_Calc_clicked();
}
