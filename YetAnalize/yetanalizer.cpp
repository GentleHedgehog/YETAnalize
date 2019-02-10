#include "yetanalizer.h"
#include <QMap>
#include <cassert>
#include <QRegExp>

namespace {
const QString MSG_NO_INPUT = "Пустой ввод";
const QString MSG_NO_TYPES = "Не найден ни один тип УЕТ";
const QString MSG_TYPE_FOUND = "Найден тип УЕТ: ";

const QList<QString> knownTypes = {"СТО", "СТТ"};

double lastSumValue = 0;
QMap<QPair<QString, int>, double> yetMap;
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
    rx.setPattern("(\\d+\\*\\d+|\\d+)");
    QStringList res;
    int pos = 0;

    while ((pos = rx.indexIn(input, pos)) != -1) {
        res << rx.cap(1);
        pos += rx.matchedLength();
    }
    return res;
}

QPair<QString, int> extractMultiplier(const QString &input)
{
    QPair<QString, int> res;
    res.first = "";
    res.second = 1;

    bool isMulFound = false;
    QString multValue;
    foreach (QChar c, input) {
        if (isMulFound)
        {
            multValue.append(c);
        }
        else
        {
            if (c == '*')
            {
                isMulFound = true;
            }
            else
            {
                res.first.append(c);
            }
        }
    }

    if (! multValue.isEmpty())
    {
        res.second = multValue.toInt();
    }
    return res;
}


bool YetAnalizer::analize(const QString &input, QString &ans)
{
    lastSumValue = 0;

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
            QStringList l = searchTypeTuples(knownTypes.at(i), input);

            if (l.size())
            {
                ok = true;
                types += types.isEmpty() ? "" : ", ";
                types += knownTypes.at(i);

                QPair<QString, int> key;
                key.first = knownTypes.at(i);

                for (int tupleIndex = 0; tupleIndex < l.size(); ++tupleIndex)
                {
                    QStringList vt = searchValueTuples(l.at(tupleIndex));

                    for (int valueTupleIndex = 0; valueTupleIndex < vt.size(); ++valueTupleIndex)
                    {
                        types += " " + vt.at(valueTupleIndex);
                        QPair<QString, int> vt_pair = extractMultiplier(vt.at(valueTupleIndex));

                        bool ok = false;
                        int number = vt_pair.first.toInt(&ok);
                        assert(ok);
                        key.second = number;

                        lastSumValue += yetMap[key] * vt_pair.second;
                    }
                }
            }
        }

        ans = ok ? ans + types : MSG_NO_TYPES;
    }
    return ok;
}

void YetAnalizer::appendValue(QString yetType, QString yetNumber, double yetValue)
{
    bool ok = false;
    int number = yetNumber.toInt(&ok);
    assert(ok);
    yetMap.insert(qMakePair(yetType, number), yetValue);
}

double YetAnalizer::lastSum()
{
    return lastSumValue;
}


