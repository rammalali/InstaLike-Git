#ifndef FILTERGRAYSCALE_H
#define FILTERGRAYSCALE_H


#include <QObject>
#include <Filters/filter.h>
#include <QImage>

class FilterGrayscale : public Filter
{
public:
    FilterGrayscale();
    ~FilterGrayscale();
    QImage process(const QImage& image, int value) override;

};

#endif // FILTERGRAYSCALE_H
