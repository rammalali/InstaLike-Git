#include <Filters/filteroriginal.h>
#include <QImage>

FilterOriginal::FilterOriginal() :
Filter()
{
}
FilterOriginal::~FilterOriginal()
{
}
QImage FilterOriginal::process(const QImage& image, int value)
{
    return image.copy();
}
