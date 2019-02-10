#ifndef YETANALIZER_H
#define YETANALIZER_H

#include <QObject>

class YetAnalizer : public QObject
{
    Q_OBJECT
public:
    explicit YetAnalizer(QObject *parent = nullptr);

    bool analize(const QString &input, QString &ans);
signals:

public slots:
};

#endif // YETANALIZER_H
