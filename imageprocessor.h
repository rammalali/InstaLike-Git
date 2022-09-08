#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "qdir.h"
#include "qthread.h"
#include <QObject>
#include <QImage>
#include <string>
#include <vector>
using namespace std;

class ImageProcessor : public QThread
{
    Q_OBJECT
    Q_PROPERTY(QString processImage READ processImage CONSTANT)
    Q_PROPERTY(QStringList fileNames READ fileNames CONSTANT)
    Q_PROPERTY(float progress READ progress WRITE setProgress NOTIFY progressChanged)



public:
    explicit ImageProcessor(QObject *parent = 0);
    const QString &processImage();


    const QStringList &fileNames() const;

    float progress() const;
    Q_INVOKABLE void setProgress(float newProgress);

protected:
    void run() override;


public slots:
    Q_INVOKABLE void setProcessImage( const QString& path);
    Q_INVOKABLE void setFilterType( QString filterType);
    Q_INVOKABLE void setFilterValue( float NewValue);
    Q_INVOKABLE void qImageSave(QString path, QString id);
    Q_INVOKABLE void setFolderPath(QString path);

    Q_INVOKABLE void applyToall( QString saveDirectory);





signals:


    void progressChanged();

private:
    QImage m_processImage;
    QString m_Image;

    QString m_filterType;

    QString m_saveDirectory;

    int m_value = 1;

    QDir m_folderPath;
    QStringList m_fileNames;
    float m_progress;
};

#endif // IMAGEPROCESSOR_H
