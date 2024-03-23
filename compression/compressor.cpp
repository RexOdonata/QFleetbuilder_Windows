#include "compressor.h"
#include "constants.h"

#include <lz4file.h>

#include <QJsonObject>
#include <QJsonDocument>
#include <filesystem>

#include <stdio.h>

#include <exception>

bool compressor::writeCompressedFile(QByteArray& src, const QString fn)
{
    try{

    if (fn.isNull())
        return false;

    FILE * writePtr = NULL;

    // open file for binary write
    std::string sfn = fn.toStdString();

    writePtr = fopen(sfn.c_str(), "wb");
    if (writePtr == NULL)
    {
        qCritical()<<"Write File Open Failed";
        throw std::runtime_error("Write File Open Failed");
    }

    LZ4_writeFile_t * lz4Write;
    LZ4F_errorCode_t r = LZ4F_OK_NoError;

    // get open file ready for LZ4F write
    r = LZ4F_writeOpen(&lz4Write, writePtr, NULL);

    if (LZ4F_isError(r))
    {
        qCritical()<<"LZ4f Write File Open Failed";
        throw std::runtime_error("LZ4F Write Open Error");
    }


    std::vector<char> buffer(CHUNKSIZE,0);

    size_t len;

    QByteArray::Iterator srcItr = src.begin();

    while (true)
    {
        len = readSrcBytes(buffer, srcItr,src);

        if (len > 0)
        {
            r = LZ4F_write(lz4Write, buffer.data(), len);

            if (LZ4F_isError(r))
            {
                qCritical()<<QString("LZ4f write error %1").arg(LZ4F_getErrorName(r));
                throw std::runtime_error("LZ4F Write Error");
            }

        }
        // no data
        else
            break;
    }

    r = LZ4F_writeClose(lz4Write);
    if (LZ4F_isError(r))
    {
        qCritical()<<QString("LZ4f write close error %1").arg(LZ4F_getErrorName(r));
        throw std::runtime_error("LZ4F Write Close Error");
    }

    fclose(writePtr);

    return true;

    }
    catch (std::runtime_error)
    {
        return false;
    }
}

// read a chunk of data at a time into buffer
size_t compressor::readSrcBytes(std::vector<char>& buffer,QByteArray::Iterator& itr, QByteArray& src)
{
    // reset the buffer memory
    memset(buffer.data(), 0, CHUNKSIZE);

    size_t cPos = itr - src.begin();
    size_t nPos = cPos + CHUNKSIZE;

    auto nextItr = itr;

    // past end of data
    if (nPos > src.size())
    {
        nextItr = src.end();
    }
    // normal operation
    else
    {
        nextItr = nextItr + CHUNKSIZE;
    }

    // get the distance from current position to next
    size_t len = nextItr - itr;

    // copy memory from src into buffer
    memcpy(buffer.data(), src.data() + cPos, len);

    // advance the iterator
    itr = nextItr;

    return len;
}

