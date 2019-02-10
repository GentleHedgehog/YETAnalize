#include "yetanalizer.h"

namespace {
const QString NO_INPUT = "Пустой ввод";
const QString NO_TYPES = "Не найден ни один тип УЕТ";

//const QString NO_TYPES =
}

YetAnalizer::YetAnalizer(QObject *parent) : QObject(parent)
{

}

bool YetAnalizer::analize(const QString &input, QString &ans)
{
    bool ok = false;
    ans = input.isEmpty() ? NO_INPUT : NO_TYPES;
    return ok;
}

//"Найден тип УЕТ: СТО"
