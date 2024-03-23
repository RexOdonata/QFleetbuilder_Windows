#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H


#include <QByteArray>
#include <QString>

#include <vector>

class decompressor
{
public:
    decompressor() = delete;

    static bool readCompressedFile(QByteArray&, const QString);
};

#endif // DECOMPRESSOR_H
