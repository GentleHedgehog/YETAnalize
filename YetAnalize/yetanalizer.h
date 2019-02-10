#ifndef YETANALIZER_H
#define YETANALIZER_H

#include <QObject>

class YetAnalizer : public QObject
{
    Q_OBJECT
    bool searchNextTypePos(QString typeName, const QString &input, int &pos);
    
public:
    explicit YetAnalizer(QObject *parent = nullptr);

    bool analize(const QString &input, QString &ans);
signals:

public slots:
};

#endif // YETANALIZER_H
