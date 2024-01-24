#include "progressbarprocess.h"

ProgressBarProcess::ProgressBarProcess(QObject *parent)
    : QObject{parent}
    , m_value(0)
{

}

int ProgressBarProcess::value() const
{
    return m_value;
}

void ProgressBarProcess::setValue(int newValue)
{
    if (m_value == newValue)
        return;
    m_value = newValue;
    emit valueChanged();
}
