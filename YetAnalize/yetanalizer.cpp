#include "yetanalizer.h"
#include <QMap>
#include <cassert>
#include <QRegExp>

namespace {
const QString MSG_NO_INPUT = "Пустой ввод";
const QString MSG_NO_TYPES = "Не найден ни один тип УЕТ";
const QString MSG_TYPE_FOUND = "Найден тип УЕТ: ";
const QString MSG_UNKNOWN_VALUES = " | Неизвестные значения: ";

const QList<QString> knownTypes = {"СТО", "СТТ"};

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
    rx.setPattern(typeName + "[\\d\\s\\W]*");

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
    rx.setPattern("(\\d+\\s*\\*\\s*\\d+|\\d+)");
    QStringList res;
    int pos = 0;

    while ((pos = rx.indexIn(input, pos)) != -1) {
        res << rx.cap(1).remove(QRegExp("\\s"));
        pos += rx.matchedLength();
    }
    return res;
}




void YetAnalizer::parseTypeTuples(QString typeName, QStringList typeTuples, QString &types)
{
    types += types.isEmpty() ? "" : ", ";
    types += typeName;

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

            if (yetMap.contains(key))
            {
                lastSumValue += yetMap[key] * vt_pair.second;
                types += " " + nextValue;
            }
            else
            {
                unknownValues.append(key.first + " " + QString::number(key.second));
                bool isPrintUnknownValues = ! isAnsUnknownValues;
                if (isPrintUnknownValues)
                {
                    types += " " + nextValue;
                }
            }
        }
    }
}

void YetAnalizer::appendUnknownValuesToAnswer(QString &ans)
{
    if (isAnsUnknownValues)
    {
        if (! unknownValues.isEmpty())
        {
            QString unknownValuesStr;
            foreach (const QString &s, unknownValues)
            {
                unknownValuesStr += unknownValuesStr.isEmpty() ? "" : ", ";
                unknownValuesStr += s;
            }
            ans += MSG_UNKNOWN_VALUES + unknownValuesStr;
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

        appendUnknownValuesToAnswer(ans);
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

void YetAnalizer::setIsAnsUnknownValues(bool value)
{
    isAnsUnknownValues = value;
}


