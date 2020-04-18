#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "yetfiller.h"
#include <QClipboard>

namespace {

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fillAnalizerWithYetInfo(analizer);

    setWindowTitle(tr("Подсчет УЕТ"));
    analizer.setIsCollectUnknownValues(true);

    ui->pb_paste->setIcon(QIcon(":/icons/paste.png"));
    ui->pb_clear->setIcon(QIcon(":/icons/clear.png"));
    ui->pb_Calc->setIcon(QIcon(":/icons/sync.png"));
    ui->pb_copy->setIcon(QIcon(":/icons/copy.png"));
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
    ui->te_unknown_values->setText(analizer.getUnknownString());
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

void MainWindow::on_pb_paste_clicked()
{
    ui->le_input->setText(QApplication::clipboard()->text());
}

void MainWindow::on_pb_clear_clicked()
{
    ui->le_input->clear();
}

void MainWindow::on_pb_copy_clicked()
{
    QApplication::clipboard()->setText(ui->le_input->text());
}
