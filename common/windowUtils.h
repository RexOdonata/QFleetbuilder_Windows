#ifndef WINDOWUTILS_H
#define WINDOWUTILS_H

#include "qjsonobject.h"
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVector>
#include <QStringListModel>
#include <QListView>

#include <exception>

#include "fileTypes.h"

#include "../compression/decompressor.h"
#include "../compression/compressor.h"

namespace
{
    template<typename T>
    void loadVectorFromJsonFile(QWidget * parentWindow, QVector<T>& vec, const QString fileType)
    {
        vec.clear();

        QString filename = QFileDialog::getOpenFileName(parentWindow, "open content", QDir::currentPath(), getExtensionFilter(fileType));

        QByteArray data;

        if (decompressor::readCompressedFile(data,filename))
        {
            QJsonParseError err;

            QJsonDocument jsonData = QJsonDocument::fromJson(data, &err);

            QJsonObject wrapperObj = jsonData.object();

            if (wrapperObj.contains(fileType))
            {
                QJsonArray objects = wrapperObj[fileType].toArray();

                for (auto object : objects)
                {
                    T obj(object.toObject());
                    vec.push_back(obj);
                }
            }
            else
            {
                throw std::invalid_argument("Invalid File Type");
            }

        }
    }

    template<typename T>
    void loadMapFromJsonFile(QWidget * parentWindow, QMap<QString, T>& data,const QString fileType)
    {
        data.clear();

        QString filename = QFileDialog::getOpenFileName(parentWindow, "open content", QDir::currentPath(), getExtensionFilter(fileType));

        QByteArray bytes;

        if (decompressor::readCompressedFile(bytes, filename))
        {

            QJsonParseError err;

            QJsonDocument jsonData = QJsonDocument::fromJson(bytes, &err);

            QJsonObject wrapperObj = jsonData.object();

            if (wrapperObj.contains(fileType))
            {
                QJsonArray objects = wrapperObj[fileType].toArray();

                for (auto object : objects)
                {                    
                    T newObj(object.toObject());
                    data.insert(newObj.getName(), newObj);
                }
            }
            else
            {
                throw std::invalid_argument("Invalid File Type");
            }

        }
    }

    template<typename T>
    void saveVectorToJsonFile(QWidget * parentWindow, QVector<T>& vec, const QString fileType)
    {
        QString filename = QFileDialog::getSaveFileName(parentWindow, "save content", QDir::currentPath(), getExtensionFilter(fileType));

        QJsonArray jsonData;

        for (auto& element : vec)
        {
            jsonData.append(QJsonValue(element.toJson()));

        }

        QJsonObject wrapperObj;

        wrapperObj.insert(fileType, jsonData);

        QJsonDocument json(wrapperObj);

        QByteArray bytes = json.toJson(QJsonDocument::Indented);

        compressor::writeCompressedFile(bytes,filename);
    }


    template<typename T>
    void saveObjectToJsonFile(QWidget * parentWindow, T& obj, const QString fileType)
    {
        QString filename = QFileDialog::getSaveFileName(parentWindow, "save content", QDir::currentPath(), getExtensionFilter(fileType));

        QJsonObject wrapperObj;

        wrapperObj.insert(fileType, obj.toJson());

        QJsonDocument json(wrapperObj);

        QByteArray bytes = json.toJson(QJsonDocument::Indented);

        compressor::writeCompressedFile(bytes,filename);

    }

    template<typename T>
    void loadObjectFromJsonFile(QWidget * parentWindow, T& obj, const QString fileType)
    {
        QString filename = QFileDialog::getOpenFileName(parentWindow, "open content", QDir::currentPath(), getExtensionFilter(fileType));

        QByteArray data;

        if (decompressor::readCompressedFile(data,filename))
        {

            QJsonParseError err;

            QJsonDocument jsonData = QJsonDocument::fromJson(data, &err);

            QJsonObject wrapperObj = jsonData.object();

            if (wrapperObj.contains(fileType))
            {
                    QJsonObject object = wrapperObj[fileType].toObject();

                    obj = T(object);
            }
            else
            {
                    throw std::invalid_argument("Invalid File Type");
            }

        }

    }

}
#endif // WINDOWUTILS_H
