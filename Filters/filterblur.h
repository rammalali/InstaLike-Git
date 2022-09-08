#ifndef FILTERBLUR_H
#define FILTERBLUR_H

#include <QObject>
#include <Filters/filter.h>
#include <QImage>

class FilterBlur : public Filter
{
public:
    FilterBlur();
    ~FilterBlur();
    QImage process(const QImage& image, int value) override;


};
#endif // FILTERBLUR_H
