#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVariant>
#include <QList>

#include "cpair.h"

#include <map>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    const QStringList &name() const;
    void setName(const QStringList &newName);

    void add(const QString& name);

    const QVariantList &count() const;
    void setCount(const QVariantList &newCount);

    const QVariantMap &value() const;
    void setValue(const QVariantMap &newValue);

    const QList<CPair *> &getCpair() const;
    void setCpair(const QList<CPair *> &newCpair);

    Q_INVOKABLE int maxWord() const;

    Q_INVOKABLE int size() const;

private:

    QList<CPair*> cpair;

    int m_max;

    std::map<QString, int> m_data;

    QStringList m_name;
    QVariantList m_count;

    Q_PROPERTY(QStringList name READ name WRITE setName NOTIFY nameChanged)

    Q_PROPERTY(QVariantList count READ count WRITE setCount NOTIFY countChanged)

    QVariantMap m_value;

    Q_PROPERTY(QVariantMap value READ value WRITE setValue NOTIFY valueChanged)

    Q_PROPERTY(QList<CPair *> cpair READ getCpair WRITE setCpair NOTIFY cpairChanged)

signals:

    void nameChanged();
    void countChanged();
    void valueChanged();
    void cpairChanged();
};

#endif // MODEL_H
