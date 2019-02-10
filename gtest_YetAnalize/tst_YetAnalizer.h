#pragma once

#include "macros_inc.h"
#include "test_qt_signals.h"

#include "../YetAnalize/yetanalizer.h"

class TestFixtureYetAnalize : public ::testing::Test
{
public:
    void SetUp()
    {

    }
protected:
    YetAnalizer yetAnalizer;
    QString input;
    QString ans;

    /*
     * на вход подается строка
     * в которой указывается сначала тип ует, а за ним идут числа, разделенные запятой
     * нужно проверить что посл-ть начинается с типа
     * сто стт
     * после него идут числа, разделенные запятой
     *
     * если тип не распознан - ошибка
     * если число не распознано - ошибка
     *
     * потом считается сумма
     *
     *
     */
};

TEST_F(TestFixtureYetAnalize, errorIfEmptyInput)
{
    ASSERT_FALSE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Пустой ввод");
}

TEST_F(TestFixtureYetAnalize, errorIfNothingFound)
{
    input = "123abc456,23,gdp";
    ASSERT_FALSE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Не найден ни один тип УЕТ");
}

TEST_F(TestFixtureYetAnalize, returnTypeIfFound)
{
    input = "сто";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО");
}