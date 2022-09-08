#ifndef QQUICKIMAGEPROVIDER_H
#define QQUICKIMAGEPROVIDER_H

#include <QObject>

class QQuickImageProvider : public QObject
{
    Q_OBJECT
public:
    explicit QQuickImageProvider(QObject *parent = nullptr);

signals:

};

#endif // QQUICKIMAGEPROVIDER_H
