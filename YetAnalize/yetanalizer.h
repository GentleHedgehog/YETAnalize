#ifndef YETANALIZER_H
#define YETANALIZER_H

#include <QObject>
#include <QMap>

class YetAnalizer : public QObject
{
    Q_OBJECT
    
    QStringList searchTypeTuples(QString typeName, const QString &input);
    QStringList searchValueTuples(const QString &input);
    void parseTypeTuples(QString typeName, QStringList typeTuples, QString &answer);

public:
    explicit YetAnalizer(QObject *parent = nullptr);

    bool analize(const QString &input,
                 QString &ans);

    void registerTypeWithValue(QString yetType, QString yetNumber, double yetValue);
    double lastSum();

    QString getUnknownString();

    void setIsCollectUnknownValues(bool value);
signals:

public slots:

private:

    const QString MSG_NO_INPUT      ;
    const QString MSG_NO_TYPES      ;
    const QString MSG_TYPE_FOUND    ;
    const QString MSG_UNKNOWN_VALUES;


    double lastSumValue = 0;
    QMap<QPair<QString, int>, double> yetMap;

    bool isCollectUnknownValues = false;
    QStringList unknownValues;
    QString unknownString;
    void yetCalculationByKey(QPair<QString, int> key, int multiplier);
    void printYetValueToAnswer(QString &answer, QPair<QString, int> key, QString nextValue);
};

#endif // YETANALIZER_H
