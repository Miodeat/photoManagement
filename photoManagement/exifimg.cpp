#include "exifimg.h"

ExifImg::ExifImg()
{
    slotFinish = false;
}

QString ExifImg::getFormattedAddress()
{
    return formattedAdd;
}

void ExifImg::test()
{
    AntiGeoCode* antiGeo = new AntiGeoCode;
    connect(antiGeo, &AntiGeoCode::formattedAddReturn, this, &ExifImg::getFormattedAdd);
    antiGeo->callAntiGeoCodeAPI("38°11'11\"","116°43'11\"");

}

void ExifImg::getFormattedAdd(QString forAdd)
{
    this->formattedAdd = forAdd;
    qDebug() << formattedAdd;
}
