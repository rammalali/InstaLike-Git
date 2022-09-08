#include "jsonates.h"
#include "qjsonobject.h"
#include <QDebug>
#include <QJsonDocument>
#include <qfile.h>
#include <istream>
#include <QDir>
#include <QFileInfo>

JSONates::JSONates(QObject *parent)
    : QObject{parent}
{

}

const QJsonObject &JSONates::json() const
{
    return m_json;
}

QJsonObject JSONates::readJson(QString filePath){

    QFile file(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    m_jsonDoc = QJsonDocument::fromJson(val.toUtf8());
    m_json = m_jsonDoc.object();

    return m_json;
}

void JSONates::setId(){
    id = QRandomGenerator::global()->generate64();
}

void JSONates::setJson(int my_id)
{
    id = my_id;
    if(m_savePath == ""){
        m_savePath = QDir::homePath() + "/Pictures";
        if (QDir(m_savePath + "/Qt").exists()){
            m_savePath = m_savePath + "/Qt";
        }
        else{
            QDir().mkdir(m_savePath + "/Qt");
            m_savePath = m_savePath + "/Qt";
        }

    }
    m_json = readJson(m_savePath + '/'  + "InstaLike.json");

    if(!m_json.isEmpty()){
        jsonArray = m_json["InstaLike"].toArray() ;
    }


    QJsonObject infoJson = {};
    infoJson.insert("id", id);

    infoJson.insert("ImageTitle", m_imgTitle);
    infoJson.insert("ImageCaption", m_imgCaption);
    infoJson.insert("dateOfCapture", m_captureDate);
    infoJson.insert("Favorite", m_favorite);
    jsonArray.push_back(infoJson);

    m_json.insert(QString("InstaLike"), jsonArray);

    m_title = "InstaLike";


    if(m_savePath == ""){
        m_savePath = QDir::homePath() + "/Pictures";
        if (QDir(m_savePath + "/Qt").exists()){
            m_savePath = m_savePath + "/Qt";
        }
        else{
            QDir().mkdir(m_savePath + "/Qt");
            m_savePath = m_savePath + "/Qt";
        }

    }

    QFile file(m_savePath + '/'  + m_title + ".json");
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
      } else {
        qDebug() << m_savePath;
        qDebug() <<"JSON File open!";
      }


    //Use QJsonDocument to set the json object
    m_jsonDoc.setObject(m_json);

    file.write(m_jsonDoc.toJson());
    file.close();

    emit jsonChanged();
}


void JSONates::setSavefile(QString path)
{
    m_title = "InstaLike";
    m_savePath = path;
    m_savePath.remove("file:///");
}

QString &JSONates::imgTitle()
{
    for(int i=0;i<jsonArray.size(); i++){

        if(QString::number(jsonArray[i].toObject()["id"].toInt()) == m_imgid){
            m_imgTitle = jsonArray[i].toObject()["ImageTitle"].toString();
        }
    }
    return m_imgTitle;

}

void JSONates::setImgTitle(const QString &newImgTitle)
{
    if (m_imgTitle == newImgTitle)
        return;
    m_imgTitle = newImgTitle;
    emit imgTitleChanged();
}

QString &JSONates::imgCaption()
{
    for(int i=0;i<jsonArray.size(); i++){

        if(QString::number(jsonArray[i].toObject()["id"].toInt()) == m_imgid){
            m_imgCaption =  jsonArray[i].toObject()["ImageCaption"].toString();
        }
    }

    return m_imgCaption;
}

void JSONates::setImgCaption(const QString &newImgCaption)
{
    if (m_imgCaption == newImgCaption)
        return;
    m_imgCaption = newImgCaption;
    emit imgCaptionChanged();
}

QString &JSONates::captureDate()
{
    for(int i=0;i<jsonArray.size(); i++){

        if(QString::number(jsonArray[i].toObject()["id"].toInt()) == m_imgid){
            m_captureDate =  jsonArray[i].toObject()["dateOfCapture"].toString();
        }
    }
    return m_captureDate;
}

void JSONates::setCaptureDate(const QString &newCaptureDate)
{
    if (m_captureDate == newCaptureDate)
        return;
    m_captureDate = newCaptureDate;
    emit captureDateChanged();
}

bool JSONates::favorite() const
{
    bool result = false;
    for(int i=0;i<jsonArray.size(); i++){
        if(QString::number(jsonArray[i].toObject()["id"].toInt()) == m_imgid){
            result =  jsonArray[i].toObject()["Favorite"].toBool();
        }
    }
    return result;
}

void JSONates::setFavorite(bool newFavorite)
{
    if (m_favorite == newFavorite)
        return;
    m_favorite = newFavorite;
    emit favoriteChanged();
}

int JSONates::getId() const
{
    return id;

}


const QString &JSONates::imgPath() const
{
    return m_imgPath;
}

void JSONates::setImgPath(const QString &newImgPath)
{

    m_imgPath = newImgPath.mid(newImgPath.lastIndexOf("/") + 1);
    QFileInfo f(m_imgPath);
    m_imgid = f.baseName();
    m_json = readJson(m_savePath + '/'  + "InstaLike.json");
    qDebug() << "check";
    if(!m_json.isEmpty()){
        jsonArray = m_json["InstaLike"].toArray() ;
    }
}

void JSONates::checkImgInfo(){
    m_json = readJson(m_savePath + '/'  + "InstaLike.json");
    qDebug() << "check";
    if(!m_json.isEmpty()){
        jsonArray = m_json["InstaLike"].toArray() ;
    }

}
