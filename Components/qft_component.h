#ifndef QFT_COMPONENT_H
#define QFT_COMPONENT_H

#include <QJsonObject>
#include <QJsonArray>

#include "qft_enum.h"


template <typename T>
class qft_component
{
public:

    qft_component(const QString set_name) : name(set_name)
    {
        // nothing needs to happen here
    }

    // creates a json object out of this component
    QJsonObject toJson()
    {
        QJsonObject json;
        json.insert(field_name, name);
        static_cast<T*>(this)->impl_toJson(json);
        return json;
    }

    QString name;

    const QString getName() const
    {
        return name;
    }

    // ENCODING and DECODING

    // INT
    static void fieldToJson(QJsonObject& json, const QString field, const unsigned int val)
    {
        json.insert(field, QVariant(val).toJsonValue());
    }

    static void fieldFromJson(QJsonObject& json, const QString field, unsigned int& val)
    {
        if (json.contains(field))
        {
            val = json.value(field).toInt();
        }
        else
        {
            qFatal("No field found");
        }
    }

    // STRINGF
    static void fieldToJson(QJsonObject& json, const QString field, const QString val)
    {
        json.insert(field, val);
    }

    static void fieldFromJson(QJsonObject& json, const QString field, QString& val)
    {
        if (json.contains(field))
        {
            val = json.value(field).toString();
        }
        else
        {
            qFatal("No field found");
        }
    }

    // BOOL
    static void fieldToJson(QJsonObject& json, const QString field, const bool val)
    {
        json.insert(field, val);
    }

    static void fieldFromJson(QJsonObject& json, const QString field, bool& val)
    {
        if (json.contains(field))
        {
            val = json.value(field).toBool();
        }
        else
        {
            qFatal("No field found");
        }
    }

    // STRING VEC
    static void fieldToJson(QJsonObject& json, const QString field, const QVector<QString> vals)
    {
        QJsonArray jsonArr;

        for (auto& element : vals)
        {
            jsonArr.push_back(element);
        }

        json.insert(field, jsonArr);
    }

    static void fieldFromJson(QJsonObject& json, const QString field, QVector<QString>& vals)
    {
        vals.clear();


        if (json.contains(field))
        {
            for (auto element : json.value(field).toArray())
            {
                vals.push_back(element.toString());
            }
        }
        else
        {
            qFatal("No field found");
        }
    }

    // COMPONENT VECTOR
    template <typename O>
    static void fieldFromJson(QJsonObject& json, const QString field, QVector<O>& vals)
    {
        vals.clear();


        if (json.contains(field))
        {
            for (auto element : json.value(field).toArray())
            {
                vals.push_back(O(element.toObject()));
            }
        }
        else
        {
            qFatal("No field found");
        }
    }

    template<typename O>
    static void fieldToJson(QJsonObject& json, const QString field, QVector<O>& vals)
    {
        QJsonArray jsonArr;

        for (auto& element : vals)
        {
            jsonArr.push_back(element.toJson());
        }

        json.insert(field, jsonArr);
    }


    // PTR to COMPONENT VEC
    template<typename O>
    static void fieldToJson(QJsonObject& json, const QString field, std::shared_ptr<QVector<O>> vals)
    {
        QJsonArray jsonArr;

        if (vals)
        {
            for (auto& element : *vals)
            {
                jsonArr.push_back(element.toJson());
            }
        }

        json.insert(field, jsonArr);
    }

    template <typename O>
    static void fieldFromJson(QJsonObject& json, const QString field, std::shared_ptr<QVector<O>> vals)
    {
        vals->clear();


        if (json.contains(field) && vals)
        {
            for (auto element : json.value(field).toArray())
            {
                vals->push_back(O(element.toObject()));
            }
        }
        else
        {
            qFatal("No field found");
        }
    }

    // COMPONENT PTR
    template<typename O>
    static void fieldToJson(QJsonObject& json, const QString field, std::shared_ptr<O> val)
    {
        if (val)
        {
            json.insert(field, val->toJson());
        }
        else
        {
            json.insert(field, QJsonValue::Null);
        }
    }

    template <typename O>
    static void fieldFromJson(QJsonObject& json, const QString field, std::shared_ptr<O> ptr)
    {

        if (json.contains(field) && ptr)
        {
            if (!json.value(field).isNull())
            {
                ptr = std::make_shared<O>(json.value(field).toObject());
            }
            else
            {
                ptr = NULL;
            }

        }
        else
        {
            qFatal("No field found");
        }
    }

    // COMPONENT
    template <typename O>
    static void fieldFromJson(QJsonObject& json, const QString field, O& val)
    {
        if (json.contains(field))
        {
            val = O(json[field].toObject());
        }
        else
        {
            qFatal("No field found");
        }
    }

    template<typename O>
    static void fieldToJson(QJsonObject& json, const QString field, O& val)
    {

        json.insert(field, val.toJson());

    }

    // QFT ENUMS
    template <typename O>
    static void enumFromJson(QJsonObject& json, const QString field, O& val)
    {
        if (json.contains(field))
        {
            val = O(json[field].toString());
        }
        else
        {
            qFatal("No field found");
        }
    }

    template<typename O>
    static void enumToJson(QJsonObject& json, const QString field, O& val)
    {
        json.insert(field, val.toString());
    }

    // QFT ENUM VECTORS
    template <typename O>
    void enumFromJson(QJsonObject& json, const QString field, QVector<O>& vals)
    {
        if (json.contains(field))
        {
            for (auto element : json.value(field).toArray())
            {
                vals.push_back(O(element.toString()));
            }
        }
        else
        {
            qFatal("No field found");
        }
    }

    template<typename O>
    static void enumToJson(QJsonObject& json, const QString field, QVector<O>& vals)
    {
        QJsonArray array;

        for (auto& val : vals)
        {
            array.push_back(val.toString());
        }

        json.insert(field, array);
    }

    // QFT ENUM PTRS
    template <typename O>
    static void enumFromJson(QJsonObject& json, const QString field, std::shared_ptr<O>& val)
    {
        if (json.contains(field))
        {
            *val = std::make_shared<O>(json[field].toString());
        }
        else
        {
            qFatal("No field found");
        }
    }

    template<typename O>
    static void enumToJson(QJsonObject& json, const QString field, std::shared_ptr<O>& val)
    {
        if (val)
            json.insert(field, val->toString());
    }

protected:

    void impl_toJson(QJsonObject& json)
    {
        qFatal("base class impl call");
    }
    // variables


    inline static  const QString field_name="name";

    // Enter the hellscape that is member variable to json helpers
    // these generally come in a few flavors
    // 1. Built in types to/from json
    // 2. vectors of components to/from json
    // 3. componenet ptrs or vectors of component ptrs to/from json



};

#endif // QFT_COMPONENT_H
