/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "window.h"

#include <QApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QStandardItemModel>
#include <QTime>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QUrlQuery>

void addPrice(QAbstractItemModel *model, const QString &state,
             const QString &type, const double &price, const QString &postcode,
              const QString &name, const QString &suburb, const double &lat,
              const double &lng)
{
    model->insertRow(0);
    model->setData(model->index(0, 0), state);
    model->setData(model->index(0, 1), type);
    model->setData(model->index(0, 2), price);
    model->setData(model->index(0, 3), postcode);
    model->setData(model->index(0, 4), QString(name).replace("11-Seven", "Seven-11"));
    model->setData(model->index(0, 5), suburb);
    model->setData(model->index(0, 6), lat);
    model->setData(model->index(0, 7), lng);
}

void OnNetworkReply(QNetworkReply *reply, QAbstractItemModel *model)
{
    const QList<QString> States = {"VIC", "NSW", "QLD", "WA", "ACT"};
    QJsonDocument replyJson(QJsonDocument::fromJson(reply->readAll()));
    QJsonArray regionsData = replyJson["regions"].toArray();
    for(auto regionValue : regionsData)
    {
        QJsonObject regionData = regionValue.toObject();
        if(!States.contains(regionData["region"].toString()))
        {
            continue;
        }
        QJsonArray pricesData = regionData["prices"].toArray();
        for (auto priceValue : pricesData)
        {
            QJsonObject priceData = priceValue.toObject();
            addPrice(model, priceData["state"].toString(), priceData["type"].toString(),
                    priceData["price"].toDouble(), priceData["postcode"].toString(),
                    priceData["name"].toString(), priceData["suburb"].toString(),
                    priceData["lat"].toDouble(), priceData["lng"].toDouble());
        }
    }
}

QAbstractItemModel *createMailModel(QObject *parent)
{
    //https://projectzerothree.info/api.php?format=json
    // state, type, postcode, name, suburb, lat, lng, price
    QStandardItemModel *model = new QStandardItemModel(0, 8, parent);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("State"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Price"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Postcode"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Suburb"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Lat"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Lng"));

    auto manager = new QNetworkAccessManager();
    QObject::connect(manager, &QNetworkAccessManager::finished, [=](QNetworkReply *reply) { OnNetworkReply(reply, model); });

    QNetworkRequest request;
    //https://projectzerothree.info/api.php?format=json
    QUrl url("https://projectzerothree.info/api.php");
    url.setQuery(QUrlQuery("format=json"));
    request.setUrl(url);
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    request.setSslConfiguration(config);
    manager->get(request);

    return model;
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;
    window.setSourceModel(createMailModel(&window));
    window.show();
    return app.exec();
}
