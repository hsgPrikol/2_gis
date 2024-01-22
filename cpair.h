#ifndef CPAIR_H
#define CPAIR_H

#include <QObject>
#include <QVariant>

class CPair : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant first READ getFirst WRITE setFirst NOTIFY firstChanged)

    Q_PROPERTY(QVariant second READ getSecond WRITE setSecond NOTIFY secondChanged)

public:
    explicit CPair(QObject *parent = nullptr);

    CPair(QVariant _first, QVariant _second, QObject *parent = nullptr);

    QVariant first;
    QVariant second;

    const QVariant &getFirst() const;
    void setFirst(const QVariant &newFirst);

    const QVariant &getSecond() const;
    void setSecond(const QVariant &newSecond);

signals:

    void firstChanged();
    void secondChanged();
};

#endif // CPAIR_H
