#ifndef COMPRESSOR_H
#define COMPRESSOR_H



#include <QByteArray>
#include <QString>
#include <vector>

class compressor
{
public:

    compressor() = delete;

    static bool writeCompressedFile(QByteArray&, const QString);


private:

    static size_t readSrcBytes(std::vector<char>&,QByteArray::Iterator&, QByteArray&);

};

#endif
