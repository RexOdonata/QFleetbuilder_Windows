#include "decompressor.h"

#include "constants.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonParseError>

#include <algorithm>

#include <stdio.h>

#include <lz4file.h>

#include <exception>

bool decompressor::readCompressedFile(QByteArray& dest, const QString fn)
{
    try
    {

    if (fn.isNull())
        return false;

    FILE * readPtr = NULL;

    // open file for binary read
    std::string sfn = fn.toStdString();

    readPtr = fopen(sfn.c_str(), "rb");
    if (readPtr == NULL)
    {
        qCritical()<<"Read File Open Failed";
        throw std::runtime_error("File Open Error");
    }

    LZ4_readFile_t * lz4Read;
    LZ4F_errorCode_t r = LZ4F_OK_NoError;

    r= LZ4F_readOpen(&lz4Read, readPtr);
    if (LZ4F_isError(r))
    {
        qCritical()<<"LZ4f Read File Open Failed";
        throw std::runtime_error("LZ4F Open Error");
    }


    std::vector<char> buffer(CHUNKSIZE,0);
    std::vector<char> outData;
    outData.reserve(CHUNKSIZE);

    while (true)
    {
        r = LZ4F_read(lz4Read, buffer.data(), CHUNKSIZE);

        if (LZ4F_isError(r))
        {
            qCritical()<<QString("LZ4f read error %1").arg(LZ4F_getErrorName(r));
            throw std::runtime_error("LZ4 Read Error");
        }

        if (r == 0)
            break;

        outData.insert(outData.end(), buffer.begin(), buffer.end());

        // fill the buffer with 0s so that chunk N doesn't have spillover from chunk N-1
        // otherwise space that is supposed to be empty will get repeated data
        memset(buffer.data(), 0, CHUNKSIZE);    }



    // get an iterator to the first 0 element at the end of the file in case of overchunking
    auto lItr = std::find_if(outData.rbegin(), outData.rend(),
                             [](const char val)
                             {
                                 return val != 0;
                             });

    // shrink to trim
    outData.resize(lItr.base()-outData.begin());


    r = LZ4F_readClose(lz4Read);
    if (LZ4F_isError(r))
    {
        qCritical()<<QString("LZ4f read close error %1").arg(LZ4F_getErrorName(r));
        throw std::runtime_error("LZ4F Read Close Error");
    }

    fclose(readPtr);

    // copy results back to the ref passed in, I sure hope this is a deep copy
    dest = QByteArray(outData.data(), outData.size());


    return true;
    }
    catch (std::runtime_error)
    {
        return false;
    }
}

