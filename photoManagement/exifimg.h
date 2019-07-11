#ifndef EXIFIMG_H
#define EXIFIMG_H

#include "antigeocode.h"

class ExifImg : public QObject
{
    Q_OBJECT
public:
    ExifImg();
    QString getFormattedAddress();
    void test();

private slots:
    void getFormattedAdd(QString forAdd);

private:
    QString formattedAdd;
    bool slotFinish;
};

#endif // EXIFIMG_H
