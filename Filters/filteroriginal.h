#ifndef FILTERORIGINAL_H
#define FILTERORIGINAL_H

#include <QObject>
#include <Filters/filter.h>
#include <QImage>

class FilterOriginal : public Filter
{
public:
    FilterOriginal();
    ~FilterOriginal();
    QImage process(const QImage& image, int value) override;
};

#endif // FILTERORIGINAL_H
