#pragma once

#include "macros_inc.h"
#include "test_qt_signals.h"

#include "../YetAnalize/yetanalizer.h"
#include "../YetAnalize/yetfiller.h"

class TestFixtureYetAnalize : public ::testing::Test
{
public:
    void SetUp()
    {
//        fillAnalizerWithYetInfo(yetAnalizer);
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

// TODO show unknown types and values
// TODO replace other symbols to * (-, x (eng), х (rus))

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

TEST_F(TestFixtureYetAnalize, errorIfTypoInTypeName)
{
    input = "Стг";
    ASSERT_FALSE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Не найден ни один тип УЕТ");
}

TEST_F(TestFixtureYetAnalize, returnTypeSTO)
{
    input = "сто";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО");
}

TEST_F(TestFixtureYetAnalize, returnTypeSTT)
{
    input = "стТ";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТТ");
}

TEST_F(TestFixtureYetAnalize, returnSeveralTypes)
{
    input = "стТ,Сто";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО, СТТ");
}

TEST_F(TestFixtureYetAnalize, returnSeveralTypesWithoutUnknown)
{
    input = "стТ,сте,Сто";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО, СТТ");
}

TEST_F(TestFixtureYetAnalize, returnTypeWithValue)
{
    input = "Сто 005";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО 005");
}

TEST_F(TestFixtureYetAnalize, returnTypeWithValueWithoutSpace)
{
    input = "Стт041";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТТ 041");
}

TEST_F(TestFixtureYetAnalize, returnTypeWithTwoValues)
{
    input = "Сто 005, 006";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО 005 006");
}

TEST_F(TestFixtureYetAnalize, returnTypeWithTwoValuesWithoutSpace)
{
    input = "Стт041,005";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТТ 041 005");
}

TEST_F(TestFixtureYetAnalize, returnTypeWithTwoValuesWithUnknownValues)
{
    yetAnalizer.registerTypeWithValue("СТТ", "041", 0.1);
    yetAnalizer.registerTypeWithValue("СТТ", "002", 0.1);
    input = "Стт 041, 111, 222, 002";
    yetAnalizer.setIsCollectUnknownValues(true);
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТТ 041 002");
    ASSERT_STREQ_QT(yetAnalizer.getUnknownString(), "Неизвестные значения: СТТ 111, СТТ 222");
}

TEST_F(TestFixtureYetAnalize, returnNoUnknownValsWithoutUnknownValues)
{
    yetAnalizer.registerTypeWithValue("СТТ", "041", 0.1);
    yetAnalizer.registerTypeWithValue("СТТ", "002", 0.1);
    input = "Стт 041, 002";
    yetAnalizer.setIsCollectUnknownValues(true);
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТТ 041 002");
    ASSERT_STREQ_QT(yetAnalizer.getUnknownString(), "Неизвестные значения: ");
}

TEST_F(TestFixtureYetAnalize, returnTwoTypesWithOneValue)
{    
    input = "Сто041стт245";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО 041, СТТ 245");
}

TEST_F(TestFixtureYetAnalize, returnTwoTypesWithSeveralValues)
{
    input = "Сто041,001,002   стт 245, 12, 23";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО 041 001 002, СТТ 245 12 23");
}

TEST_F(TestFixtureYetAnalize, returnTwoTypesWithSeveralValuesWithoutUnknown)
{
    input = "Сто041,001,002сту 001, 003   стт 245, 12, 23";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО 041 001 002, СТТ 245 12 23");
}

TEST_F(TestFixtureYetAnalize, returnTypeWithValueMultiplier)
{
    input = "Сто 041*2";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО 041*2");
}

TEST_F(TestFixtureYetAnalize, returnTypeWithValueIfValueMultiplierWithSpaces)
{
    input = "Сто 041 * 2";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО 041*2");
}

TEST_F(TestFixtureYetAnalize, returnTypeWithTwoValuesMultipliers)
{
    input = "Сто 041*2, 002*4";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО 041*2 002*4");
}

TEST_F(TestFixtureYetAnalize, returnTypeWithTwoValuesMultipliersWithSpaces)
{
    input = "Сто 041 *2, 002*  4";
    ASSERT_TRUE(yetAnalizer.analize(input, ans));
    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО 041*2 002*4");
}

TEST_F(TestFixtureYetAnalize, getLastSumWithMultipliers)
{
    yetAnalizer.registerTypeWithValue("СТО", "001", 0.31);
    yetAnalizer.registerTypeWithValue("СТО", "002", 0.5);
    input = "Сто 001*2, 002*4";

    ASSERT_TRUE(yetAnalizer.analize(input, ans));


    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО 001*2 002*4");
    ASSERT_DOUBLE_EQ(yetAnalizer.lastSum(), 0.31*2 + 0.5*4);
}

TEST_F(TestFixtureYetAnalize, getLastSumWithMultipliersForTwoTypes)
{
    yetAnalizer.registerTypeWithValue("СТО", "001", 0.31);
    yetAnalizer.registerTypeWithValue("СТО", "002", 0.5);

    yetAnalizer.registerTypeWithValue("СТТ", "005", 1.68);
    yetAnalizer.registerTypeWithValue("СТТ", "006", 1.18);
    input = "Сто 001*2, 002*4 Стт 005, 006*3";

    ASSERT_TRUE(yetAnalizer.analize(input, ans));


    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО 001*2 002*4, СТТ 005 006*3");
    ASSERT_DOUBLE_EQ(yetAnalizer.lastSum(), 0.31*2 + 0.5*4 + 1.68 + 1.18*3);
}

TEST_F(TestFixtureYetAnalize, getLastSumWithMultipliersForTwoTypesWithUnknownValues)
{
    yetAnalizer.registerTypeWithValue("СТО", "001", 0.31);
    yetAnalizer.registerTypeWithValue("СТО", "002", 0.5);

    yetAnalizer.registerTypeWithValue("СТТ", "005", 1.68);
    yetAnalizer.registerTypeWithValue("СТТ", "006", 1.18);
    input = "Сто 001*2, 111*4, 002*4 Стт 005, 006*3";
    yetAnalizer.setIsCollectUnknownValues(true);

    ASSERT_TRUE(yetAnalizer.analize(input, ans));


    ASSERT_STREQ_QT(ans, "Найден тип УЕТ: СТО 001*2 002*4, СТТ 005 006*3");
    ASSERT_STREQ_QT(yetAnalizer.getUnknownString(),
                    "Неизвестные значения: СТО 111");

    ASSERT_DOUBLE_EQ(yetAnalizer.lastSum(), 0.31*2 + 0.5*4 + 1.68 + 1.18*3);
}
