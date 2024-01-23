#include "model.h"

Model::Model(QObject *parent)
    : QObject{parent}
    , m_max(0)
{
    m_data.insert({"aaa", 4});
    m_data.insert({"abb", 30});
    m_data.insert({"abc", 20});
    m_data.insert({"abs", 35});
    m_data.insert({"abq", 60});
    m_data.insert({"aweb", 10});
    m_data.insert({"abasd", 10});
    m_data.insert({"abzxfc", 10});
    m_data.insert({"axcb", 10});
    m_data.insert({"abbx", 10});
    m_data.insert({"abzx", 10});
    m_data.insert({"abxzc", 10});
    m_data.insert({"azvb", 10});
    m_data.insert({"bzx", 100});
    m_data.insert({"abzxd", 10});

    m_data.insert({"we", 15});

//    QList<std::unique_ptr<CPair>> tmp;

//    for (const auto& [name, count] : m_data) {

//        if (m_max < count) {
//            m_max = count;
//        }

//        tmp.push_back(std::make_unique<CPair>(CPair(name, count)));
//    }

//    auto compare_count = [](const auto& lhs, const auto& rhs){
//        return lhs->second > rhs->second;
//    };

//    if (m_data.size() >= SIZE) {
//        std::partial_sort(cpair.begin(), cpair.begin() + SIZE, cpair.end(), compare_count);
//    } else {
//        std::sort(cpair.begin(), cpair.end(), compare_count);
//    }






}
const QStringList &Model::name() const
{
    return m_name;
}

void Model::setName(const QStringList &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

void Model::add(const QString &name)
{

}

int Model::size() const
{
    return cpair.size() >= 15 ? 15 : cpair.size();
}

const QVariantList &Model::count() const
{
    //    return m_value.values();
    return m_count;
}

void Model::setCount(const QVariantList &newCount)
{

}

const QVariantMap &Model::value() const
{
    return m_value;
}

void Model::setValue(const QVariantMap &newValue)
{
    if (m_value == newValue)
        return;
    m_value = newValue;
    emit valueChanged();
}

const QList<CPair *> &Model::getCpair() const
{
    return cpair;
}

void Model::setCpair(const QList<CPair *> &newCpair)
{
    if (cpair == newCpair)
        return;
    cpair = newCpair;
    emit cpairChanged();
}

int Model::maxWord() const
{
    return m_max;
}
