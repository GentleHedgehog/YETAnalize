#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef LANG_EN
    QTranslator translator;
    translator.load(QString(":/QtLanguage_ru.qm"));
    a.installTranslator(&translator);
#endif

    MainWindow w;
    w.show();

    return a.exec();
}
