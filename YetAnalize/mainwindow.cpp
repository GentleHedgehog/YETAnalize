#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "yetanalizer.h"

namespace {
YetAnalizer analizer;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    analizer.appendValue("СТО", "001", 0.31 );
    analizer.appendValue("СТО", "002", 0.5  );
    analizer.appendValue("СТО", "003", 0.96 );
    analizer.appendValue("СТО", "004", 0.35 );
    analizer.appendValue("СТО", "005", 0.61 );
    analizer.appendValue("СТО", "006", 0.76 );
    analizer.appendValue("СТО", "015", 0.5  );
    analizer.appendValue("СТО", "022", 0.87 );


    analizer.appendValue("СТТ", "005",    1.68 );
    analizer.appendValue("СТТ", "006",    1.18 );
    analizer.appendValue("СТТ", "017",	0.42 );
    analizer.appendValue("СТТ", "020",	1    );
    analizer.appendValue("СТТ", "022",	0.7  );
    analizer.appendValue("СТТ", "025",	1    );
    analizer.appendValue("СТТ", "026",	0.53 );
    analizer.appendValue("СТТ", "027",	0.95 );
    analizer.appendValue("СТТ", "028",	1.35 );
    analizer.appendValue("СТТ", "029",	0.5  );
    analizer.appendValue("СТТ", "030",	1.15 );
    analizer.appendValue("СТТ", "031",	2    );
    analizer.appendValue("СТТ", "033",	1.25 );
    analizer.appendValue("СТТ", "034",	1.25 );
    analizer.appendValue("СТТ", "035",	0.25 );
    analizer.appendValue("СТТ", "036",	0.48 );
    analizer.appendValue("СТТ", "037",	1.16 );
    analizer.appendValue("СТТ", "038",	0.21 );
    analizer.appendValue("СТТ", "039",	0.46 );
    analizer.appendValue("СТТ", "041",	0.32 );
    analizer.appendValue("СТТ", "044",	0.92 );
    analizer.appendValue("СТТ", "045",	1.71 );
    analizer.appendValue("СТТ", "046",	0.5  );
    analizer.appendValue("СТТ", "048",	2    );
    analizer.appendValue("СТТ", "049",	1    );
    analizer.appendValue("СТТ", "051",	2    );
    analizer.appendValue("СТТ", "053",	0.03 );
    analizer.appendValue("СТТ", "061",	1.7  );

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
