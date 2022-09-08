#ifndef FILTER_H
#define FILTER_H

#include <QObject>
//Filter.h
class Filter{
public:
    Filter();
    virtual ~Filter();
    virtual QImage process(const QImage& image, int value = 1) = 0;
};


#endif // FILTER_H
