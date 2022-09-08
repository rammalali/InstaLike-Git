#ifndef JSONATES_H
#define JSONATES_H

#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include <QObject>
#include <QDir>
#include <QRandomGenerator>
class JSONates : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QJsonObject json READ json WRITE setJson NOTIFY jsonChanged)

    Q_PROPERTY(QString imgTitle READ imgTitle WRITE setImgTitle NOTIFY imgTitleChanged)
    Q_PROPERTY(QString imgCaption READ imgCaption WRITE setImgCaption NOTIFY imgCaptionChanged)
    Q_PROPERTY(QString captureDate READ captureDate WRITE setCaptureDate NOTIFY captureDateChanged)
    Q_PROPERTY(bool favorite READ favorite WRITE setFavorite NOTIFY favoriteChanged)
    Q_PROPERTY(QString imgPath READ imgPath WRITE setImgPath NOTIFY imgPathChanged)

public:
    explicit JSONates(QObject *parent = nullptr);

    const QJsonObject &json() const;
    Q_INVOKABLE void setJson(int my_id);
    Q_INVOKABLE void setSavefile(QString path);

    QJsonObject readJson(QString filePath);

    QString &imgTitle() ;
    Q_INVOKABLE void setImgTitle(const QString &newImgTitle);

    QString &imgCaption();
    Q_INVOKABLE void setImgCaption(const QString &newImgCaption);

    QString &captureDate() ;
    Q_INVOKABLE void setCaptureDate(const QString &newCaptureDate);

    bool favorite() const;
    Q_INVOKABLE void setFavorite(bool newFavorite);

    Q_INVOKABLE int getId()const;
    void setId();

    const QString &imgPath() const;
    Q_INVOKABLE void setImgPath(const QString &newImgPath);

    void checkImgInfo();


signals:

    void jsonChanged();
    void imgTitleChanged();

    void imgCaptionChanged();

    void captureDateChanged();

    void favoriteChanged();

    void imgPathChanged();

private:
    QJsonObject m_json;
    QString m_savePath;
//    int generator = QRandomGenerator::global()->generate() ;
    QString m_title = "InstaLike";
    QJsonDocument m_jsonDoc;
    QString val;
    QString m_imgTitle;
    QString m_imgCaption;
    QString m_captureDate;
    bool m_favorite;
    QJsonArray jsonArray;
    int id;
    QString m_imgPath;
    QString m_imgid;
};

#endif // JSONATES_H
