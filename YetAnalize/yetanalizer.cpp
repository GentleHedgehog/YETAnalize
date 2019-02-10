#include "yetanalizer.h"

#include <QRegExp>

namespace {
const QString MSG_NO_INPUT = "Пустой ввод";
const QString MSG_NO_TYPES = "Не найден ни один тип УЕТ";
const QString MSG_TYPE_FOUND = "Найден тип УЕТ: ";

const QList<QString> knownTypes = {"СТО", "СТТ"};
}

YetAnalizer::YetAnalizer(QObject *parent) : QObject(parent)
{

}

bool YetAnalizer::searchNextTypePos(QString typeName, const QString &input, int &pos)
{
    QRegExp rx;
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    rx.setPattern(typeName);

    bool ok = false;
    pos = rx.indexIn(input, pos);
    ok = pos != -1;
    pos += rx.matchedLength();

    return ok;
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
        ans = MSG_TYPE_FOUND;
        QString types = "";

        for (int i = 0; i < knownTypes.size(); ++i)
        {
            int pos = 0;
            while (searchNextTypePos(knownTypes.at(i), input, pos))
            {
                QRegExp rx;
                rx.setPattern("\\d\\d\\d");
                int numPos = rx.indexIn(input, pos);
                bool isNumberFound = numPos != -1;

                ok = true;
                types += types.isEmpty() ? "" : ", ";
                types += knownTypes.at(i);
                types += isNumberFound ? " " + rx.cap() : "";
            }
        }

        ans = ok ? ans + types : MSG_NO_TYPES;
    }
    return ok;
}


