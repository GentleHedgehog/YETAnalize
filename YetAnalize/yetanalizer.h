#ifndef YETANALIZER_H
#define YETANALIZER_H

#include <QObject>

class YetAnalizer : public QObject
{
    Q_OBJECT
    
    QStringList searchTypeTuples(QString typeName, const QString &input);
    QStringList searchValueTuples(const QString &input);
    void parseTypeTuples(QString typeName, QStringList typeTuples, QString &types);

public:
    explicit YetAnalizer(QObject *parent = nullptr);

    bool analize(const QString &input,
                 QString &ans);

    void appendValue(QString yetType, QString yetNumber, double yetValue);
    double lastSum();

    void setIsAnsUnknownValues(bool value);

signals:

public slots:

private:
    bool isAnsUnknownValues = false;
    QStringList unknownValues;
};

#endif // YETANALIZER_H
