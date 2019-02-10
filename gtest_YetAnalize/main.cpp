#include "tst_YetAnalizer.h"

#include <gtest/gtest.h>

#include <QTextCodec>

int main(int argc, char *argv[])
{
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
