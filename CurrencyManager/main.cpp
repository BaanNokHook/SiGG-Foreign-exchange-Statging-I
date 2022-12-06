/**
 * @file main.cpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>

#include "account_handler.hpp"
#include "purchase_object.hpp"

#include "sortfilterproxymodel.hpp"
#include "purchase_tablemodel.hpp"
#include "balancedatamodel.hpp"

#include "currexcdata_object.hpp"
#include "currexcdata_object_model.hpp"
#include "balancedataobject.hpp"



int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    try
    {
        QGuiApplication app(argc, argv);

        QQmlApplicationEngine engine;
        const QUrl url(QStringLiteral("qrc:/appwindow.qml"));
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);


        AccountHandler acc;
        engine.rootContext()->setContextProperty("Account", &acc);

        //история баланса
        BalanceDataModel bmodel;
        std::vector<BalanceData> data{acc.getBalanceHistory()};
        for(const auto& dt : data)
        {
            bmodel.addBalanceHistoryObject(BalanceDataObject(dt));
        }
        engine.rootContext()->setContextProperty("bmodel", &bmodel);

        //список курсов валют
        CurrExcDataObjectModel cmodel;
        std::vector<CurrencyExchangeData> currencies { acc.getExcangeRates() };
        for(const auto& rate : currencies)
        {
            cmodel.addCurrExcDataObject(CurrExcDataObject(rate));
        }
        engine.rootContext()->setContextProperty("cmodel", &cmodel);


        //таблица истории операций
        PurchaseTableModel ptmodel;
        std::vector<Purchase> lots{ acc.getActiveLots() };
        for(const auto& lot : lots)
        {
            ptmodel.addPurchase(PurchaseObject(lot));
        }
        engine.rootContext()->setContextProperty("ptmodel", &ptmodel);

        //фильтр/поиск по истории
        qmlRegisterType<SortFilterProxyModel>("SortFilterProxyModel", 0, 1, "SortFilterProxyModel");


        engine.load(url);
        return app.exec();

    }
    catch (sql::SQLException &e)
    {
        qDebug() << "# ERR: SQLException in " << __FILE__;
        qDebug() << "(" << __FUNCTION__ << ") on line "<< __LINE__ << Qt::endl;
        qDebug() << "# ERR: " << e.what();
        qDebug() << " (MySQL error code: " <<e.getErrorCode();
        qDebug() << ", SQLState: " << e.getSQLState().c_str() <<" )" << Qt::endl;
    }
    catch (std::exception& ex)
    {
        qDebug()<<ex.what()<<"\n";
    }


}
