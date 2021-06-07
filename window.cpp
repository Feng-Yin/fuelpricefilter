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

#include <QtWidgets>

#include "window.h"

Window::Window()
{
    proxyModel = new QSortFilterProxyModel;

    sourceView = new QTreeView;
    sourceView->setRootIsDecorated(false);
    sourceView->setAlternatingRowColors(true);

    proxyView = new QTreeView;
    proxyView->setRootIsDecorated(false);
    proxyView->setAlternatingRowColors(true);
    proxyView->setModel(proxyModel);
    proxyView->setSortingEnabled(true);

    filterStateColumnComboBox = new QComboBox;
    filterStateColumnComboBox->addItem(tr("All"));
    filterStateColumnComboBox->addItem(tr("ACT"));
    filterStateColumnComboBox->addItem(tr("NSW"));
    filterStateColumnComboBox->addItem(tr("QLD"));
    filterStateColumnComboBox->addItem(tr("VIC"));
    filterStateColumnComboBox->addItem(tr("WA"));
    filterStateColumnLabel = new QLabel(tr("State Filter:"));
    filterStateColumnLabel->setBuddy(filterStateColumnComboBox);

    filterFuelColumnComboBox = new QComboBox;
    filterFuelColumnComboBox->addItem(tr("All"));
    filterFuelColumnComboBox->addItem(tr("Diesel"));
    filterFuelColumnComboBox->addItem(tr("E10"));
    filterFuelColumnComboBox->addItem(tr("LPG"));
    filterFuelColumnComboBox->addItem(tr("U91"));
    filterFuelColumnComboBox->addItem(tr("U95"));
    filterFuelColumnComboBox->addItem(tr("U98"));
    filterFuelColumnLabel = new QLabel(tr("Fuel Filter:"));
    filterFuelColumnLabel->setBuddy(filterFuelColumnComboBox);

    hidePostcodeComboBox = new QComboBox;
    hidePostcodeComboBox->addItem(tr("True"));
    hidePostcodeComboBox->addItem(tr("False"));
    hidePostcodeLabel = new QLabel(tr("Hide Postcode:"));
    hidePostcodeLabel->setBuddy(hidePostcodeComboBox);
    connect(hidePostcodeComboBox, &QComboBox::currentIndexChanged, [=]() { columnStateChanged(); });

    hideNameComboBox = new QComboBox;
    hideNameComboBox->addItem(tr("True"));
    hideNameComboBox->addItem(tr("False"));
    hideNameLabel = new QLabel(tr("Hide Name:"));
    hideNameLabel->setBuddy(hideNameComboBox);
    connect(hideNameComboBox, &QComboBox::currentIndexChanged, [=]() { columnStateChanged(); });

    hideSuburbComboBox = new QComboBox;
    hideSuburbComboBox->addItem(tr("True"));
    hideSuburbComboBox->addItem(tr("False"));
    hideSuburbLabel = new QLabel(tr("Hide Suburb:"));
    hideSuburbLabel->setBuddy(hideSuburbComboBox);
    connect(hideSuburbComboBox, &QComboBox::currentIndexChanged, [=]() { columnStateChanged(); });

    sourceGroupBox = new QGroupBox(tr("Original Model"));
    proxyGroupBox = new QGroupBox(tr("Seven-11 Fuel"));

    QHBoxLayout *sourceLayout = new QHBoxLayout;
    sourceLayout->addWidget(sourceView);
    sourceGroupBox->setLayout(sourceLayout);

    QGridLayout *proxyLayout = new QGridLayout;
    proxyLayout->addWidget(proxyView, 0, 0, 1, 3);
    proxyLayout->addWidget(filterFuelColumnLabel, 1, 0);
    proxyLayout->addWidget(filterFuelColumnComboBox, 1, 1, 1, 2);
    proxyLayout->addWidget(filterStateColumnLabel, 2, 0);
    proxyLayout->addWidget(filterStateColumnComboBox, 2, 1, 1, 2);
    proxyLayout->addWidget(hidePostcodeLabel, 3, 0);
    proxyLayout->addWidget(hidePostcodeComboBox, 3, 1, 1, 2);
    proxyLayout->addWidget(hideNameLabel, 4, 0);
    proxyLayout->addWidget(hideNameComboBox, 4, 1, 1, 2);
    proxyLayout->addWidget(hideSuburbLabel, 5, 0);
    proxyLayout->addWidget(hideSuburbComboBox, 5, 1, 1, 2);
    proxyGroupBox->setLayout(proxyLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    //mainLayout->addWidget(sourceGroupBox);
    mainLayout->addWidget(proxyGroupBox);

    setLayout(mainLayout);

    setWindowTitle(tr("Basic Sort/Filter Model"));
    resize(500, 450);

    proxyView->sortByColumn(2, Qt::AscendingOrder);
    filterFuelColumnComboBox->setCurrentIndex(2);
    QScroller::grabGesture(proxyView, QScroller::LeftMouseButtonGesture);

    connect(filterStateColumnComboBox, &QComboBox::currentIndexChanged,
            [=](){ this->filterColumnChanged(); });
    connect(filterFuelColumnComboBox, &QComboBox::currentIndexChanged,
            [=](){ this->filterColumnChanged(); });

    hidePostcodeComboBox->setCurrentIndex(0);
    hideNameComboBox->setCurrentIndex(0);
    hideSuburbComboBox->setCurrentIndex(0);
}

void Window::setSourceModel(QAbstractItemModel *model)
{
    sourceModel = model;
    connect(sourceModel,&QAbstractItemModel::dataChanged, [=](){ this->filterColumnChanged(); });
    proxyModel->setSourceModel(model);
    sourceView->setModel(model);

    proxyView->hideColumn(3);
    proxyView->hideColumn(4);
    proxyView->hideColumn(5);
}

void Window::filterColumnChanged()
{
    if (!sourceModel)
    {
        return;
    }
    if (!intermediaModel)
    {
        intermediaModel = new QSortFilterProxyModel;
    }
    intermediaModel->setSourceModel(sourceModel);
    intermediaModel->setFilterKeyColumn(0);
    if (filterFuelColumnComboBox->currentIndex() != 0)
    {
        intermediaModel->setFilterRegularExpression(filterFuelColumnComboBox->currentText());
    }
    else
    {
        intermediaModel->setFilterRegularExpression(QRegularExpression::wildcardToRegularExpression("*"));
    }
    intermediaModel->setFilterKeyColumn(1);
    if (filterStateColumnComboBox->currentIndex() != 0)
    {
        proxyModel->setFilterRegularExpression(filterStateColumnComboBox->currentText());
    }
    else
    {
        proxyModel->setFilterRegularExpression(QRegularExpression::wildcardToRegularExpression("*"));
    }

    proxyModel->setSourceModel(intermediaModel);
    columnStateChanged();
    resizeColumnToContents();
}

void Window::resizeColumnToContents()
{
    for(int i = 0; i < proxyModel->columnCount(); i++)
    {
        proxyView->resizeColumnToContents(i);
    }
}

void Window::columnStateChanged()
{
    if (hidePostcodeComboBox->currentIndex() == 0)
    {
        proxyView->hideColumn(3);
    }
    else
    {
        proxyView->showColumn(3);
    }
    if (hideNameComboBox->currentIndex() == 0)
    {
        proxyView->hideColumn(4);
    }
    else
    {
        proxyView->showColumn(4);
    }
    if (hideSuburbComboBox->currentIndex() == 0)
    {

        proxyView->hideColumn(5);
    }
    else
    {
        proxyView->showColumn(5);

    }
}

