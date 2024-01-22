#include "cpair.h"

CPair::CPair(QObject *parent)
    : QObject{parent}
{

}

CPair::CPair(QVariant _first, QVariant _second, QObject *parent)
    : QObject(parent)
    , first(_first)
    , second(_second)
{

}

const QVariant &CPair::getSecond() const
{
    return second;
}

void CPair::setSecond(const QVariant &newSecond)
{
    if (second == newSecond)
        return;
    second = newSecond;
    emit secondChanged();
}

const QVariant &CPair::getFirst() const
{
    return first;
}

void CPair::setFirst(const QVariant &newFirst)
{
    if (first == newFirst)
        return;
    first = newFirst;
    emit firstChanged();
}
