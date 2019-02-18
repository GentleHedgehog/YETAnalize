#include "yetanalizer.h"
#include <QMap>
#include <cassert>
#include <QRegExp>

namespace {
const QString MSG_NO_INPUT = "Пустой ввод";
const QString MSG_NO_TYPES = "Не найден ни один тип УЕТ";
const QString MSG_TYPE_FOUND = "Найден тип УЕТ: ";
const QString MSG_UNKNOWN_VALUES = "Неизвестные значения: ";

const QList<QString> knownTypes = {"СТО", "СТТ"};
const QList<QChar> knownMultipliers =
{QString("*")[0],
 QString("-")[0],
 QString("x")[0]/*eng*/,
 QString("х")[0]/*rus*/}; // hack with qsting - for proper convertion (UTF8 -> unicode)

double lastSumValue = 0;
QMap<QPair<QString, int>, double> yetMap;

QPair<int, int> extractValueAndMultiplier(const QString &input)
{
    QPair<int, int> res;
    res.first = 0;
    res.second = 1;

    bool isMulFound = false;
    QString multValueStr;
    QString valueStr;
    foreach (QChar c, input) {
        if (isMulFound)
        {
            multValueStr.append(c);
        }
        else
        {
            if (c == '*')
            {
                isMulFound = true;
            }
            else
            {
                valueStr.append(c);
            }
        }
    }

    if (! valueStr.isEmpty())
    {
        bool ok = false;
        int value_number = valueStr.toInt(&ok);
        assert(ok);
        res.first = value_number;
    }

    if (! multValueStr.isEmpty())
    {
        bool ok = false;
        int mult_number = multValueStr.toInt(&ok);
        assert(ok);
        res.second = mult_number;
    }

    return res;
}
}

YetAnalizer::YetAnalizer(QObject *parent) : QObject(parent)
{

}

QStringList YetAnalizer::searchTypeTuples(QString typeName, const QString &input)
{
    QRegExp rx;
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    QString pattern = "[\\d\\s\\W";
    foreach (QChar c, knownMultipliers)
    {
        if (c.isLetter())
            pattern += c;
    }
    pattern += "]*";
    rx.setPattern(typeName + pattern);

    rx.indexIn(input);

    QStringList res = rx.capturedTexts();
    if (res.at(0).isEmpty())
    {
        res.clear();
    }

    return res;
}

QStringList YetAnalizer::searchValueTuples(const QString &input)
{
    QRegExp rx;
    QString pattern_number_with_mult_begin = "\\d+\\s*(";
    QString pattern_number_with_mult_symbol = "";
    foreach (QChar c, knownMultipliers)
    {
        pattern_number_with_mult_symbol +=
                pattern_number_with_mult_symbol.isEmpty() ? "" : "|";
        if (c == QString("*")[0])
        {
            pattern_number_with_mult_symbol += QString("\\");
        }
        pattern_number_with_mult_symbol += c;
    }
    QString pattern_number_with_mult_end = ")\\s*\\d+";
    QString pattern_number_with_mult =
            pattern_number_with_mult_begin +
            pattern_number_with_mult_symbol +
            pattern_number_with_mult_end;

    QString pattern_number = "\\d+";

    QString pattern = "(" + pattern_number_with_mult + "|" + pattern_number + ")";

    rx.setPattern(pattern);
    QStringList res;
    int pos = 0;

    while ((pos = rx.indexIn(input, pos)) != -1) {
        QString foundValue = rx.cap(1);
        foundValue.remove(QRegExp("\\s"));
        foreach (QChar c, knownMultipliers)
        {
            if (foundValue.contains(c))
            {
                foundValue.replace(c, '*');
                break;
            }
        }
        res << foundValue;
        pos += rx.matchedLength();
    }
    return res;
}




void YetAnalizer::yetCalculationByKey(QPair<QString, int> key, int multiplier)
{
    if (yetMap.contains(key))
    {
        lastSumValue += yetMap[key] * multiplier;
    }
}

void YetAnalizer::printYetValueToAnswer(QString &answer, QPair<QString, int> key, QString nextValue)
{
    bool isPrintUnknownValues = ! isCollectUnknownValues;

    if (yetMap.contains(key) || isPrintUnknownValues)
    {
        answer += " " + nextValue;
    }
    else
    {
        unknownValues.append(key.first + " " + QString::number(key.second));
    }
}

void YetAnalizer::parseTypeTuples(QString typeName, QStringList typeTuples, QString &answer)
{
    answer += answer.isEmpty() ? "" : ", ";
    answer += typeName;

    QPair<QString, int> key;
    key.first = typeName;

    for (int tupleIndex = 0; tupleIndex < typeTuples.size(); ++tupleIndex)
    {
        QStringList valueTuples = searchValueTuples(typeTuples.at(tupleIndex));

        for (int valueTupleIndex = 0; valueTupleIndex < valueTuples.size(); ++valueTupleIndex)
        {
            QString nextValue = valueTuples.at(valueTupleIndex);
            QPair<int, int> vt_pair = extractValueAndMultiplier(nextValue);

            key.second = vt_pair.first;

            yetCalculationByKey(key, vt_pair.second);

            printYetValueToAnswer(answer, key, nextValue);
        }
    }
}



bool YetAnalizer::analize(const QString &input, QString &ans)
{
    lastSumValue = 0;
    unknownValues.clear();

    bool ok = false;
    if (input.isEmpty())
    {
        ans = MSG_NO_INPUT;
    }
    else
    {
        ans = MSG_TYPE_FOUND;
        QString types = "";

        for (int i = 0; i < knownTypes.size(); ++i)
        {
            QStringList typeTuples = searchTypeTuples(knownTypes.at(i), input);

            if (typeTuples.size())
            {
                ok = true;
                parseTypeTuples(knownTypes.at(i), typeTuples, types);
            }
        }

        ans = ok ? ans + types : MSG_NO_TYPES;
    }
    return ok;
}

void YetAnalizer::registerTypeWithValue(QString yetType, QString yetNumber, double yetValue)
{
    bool ok = false;
    int number = yetNumber.toInt(&ok);
    assert(ok);
    auto key = qMakePair(yetType, number);
    if (! yetMap.contains(key))
    {
        yetMap.insert(key, yetValue);
    }
}

double YetAnalizer::lastSum()
{
    return lastSumValue;
}

void YetAnalizer::setIsCollectUnknownValues(bool value)
{
    isCollectUnknownValues = value;
}

QString YetAnalizer::getUnknownString()
{
    unknownString = MSG_UNKNOWN_VALUES;
    if (! unknownValues.isEmpty())
    {
        QString unknownValuesStr;
        foreach (const QString &s, unknownValues)
        {
            unknownValuesStr += unknownValuesStr.isEmpty() ? "" : ", ";
            unknownValuesStr += s;
        }
        unknownString += unknownValuesStr;
    }
    return unknownString;
}


