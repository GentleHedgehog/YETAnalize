#include "yetanalizer.h"

namespace {
const QString MSG_NO_INPUT = "Пустой ввод";
const QString MSG_NO_TYPES = "Не найден ни один тип УЕТ";
const QString MSG_TYPE_FOUND = "Найден тип УЕТ: ";

const QList<QString> knownTypes = {"СТО", "СТТ"};
}

YetAnalizer::YetAnalizer(QObject *parent) : QObject(parent)
{

}

bool YetAnalizer::analize(const QString &input, QString &ans)
{
    bool ok = false;
    if (input.isEmpty())
    {
        ans = MSG_NO_INPUT;
    }
    else
    {
        ans = MSG_NO_TYPES;
        for (int i = 0; i < knownTypes.size(); ++i)
        {
            if (input.toUpper() == knownTypes.at(i))
            {
                ok = true;
                ans = MSG_TYPE_FOUND + knownTypes.at(i);
            }
        }
    }
    return ok;
}

//"Найден тип УЕТ: СТО"
