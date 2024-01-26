#ifndef PROGRESSBARPROCESS_H
#define PROGRESSBARPROCESS_H

#include <QObject>

class ProgressBarProcess : public QObject
{
    Q_OBJECT
public:
    explicit ProgressBarProcess(QObject *parent = nullptr);

    int value() const;
    void setValue(int newValue);

private:

    int m_value;

    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)

signals:

    void valueChanged();
};

#endif // PROGRESSBARPROCESS_H
