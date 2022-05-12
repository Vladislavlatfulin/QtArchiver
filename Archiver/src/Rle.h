#ifndef RLE_H
#define RLE_H
#include <QString>


class CompressorRLE
{
public:
    void compressRLE(QString &compressFileName, QString &rleFileName);
    void decompressRLE(QString &compressedRLE, QString &decompressedFileName);
};

#endif // RLE_H
