#ifndef QFT_ENUM_H
#define QFT_ENUM_H

#include <QJsonObject>
#include <QVector>
#include <QHash>
#include <optional>

template<typename T, typename B>
class qft_enum
{
public:

    QVector<QString> getEnumStrings()
    {
        return static_cast<T*>(this)->impl_getEnumStrings();
    }

    // this is the constructor used to load from  json
    qft_enum(const QString in)
    {
        val = static_cast<T*>(this)->impl_string_to_enum(in);
    }

    qft_enum(const B set) : val(set)
    {
    }

    qft_enum() : val(std::nullopt)
    {

    }   

    bool hasVal() const
    {
        if (val)
            return true;
        else
            return false;
    }

    B getVal() const
    {
        if (val)
            return *val;
        else
            qFatal("Opened empty enum instance");
    }

    QString toString() const
    {
        if (val)
            {
                return static_cast<const T*>(this)->impl_enum_to_string(*val);
            }
        else
            return "{empty}";
    }

protected:

    std::optional<B> val;

    QVector<QString> impl_getEnumStrings()
    {
        qFatal("enum skeleton call to string impl");
        return {};
    }

    B impl_string_to_enum(const QString)
    {
        qFatal("enum skeleton call to s2e");
    }

    QString impl_string_to_enum(const B)
    {
        qFatal("enum skeleton call to s2e");
    }


};

#endif // QFT_ENUM_H
