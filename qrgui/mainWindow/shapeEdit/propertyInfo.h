#pragma once

#include <QtCore/QStringList>

struct PropertyInfo
{
    enum Type { Enum, Int, Bool, String };

    Type type;
    QStringList values;

    PropertyInfo() {}
    PropertyInfo(Type t, const QStringList &v)
        : type(t), values(v)
    {}

};
