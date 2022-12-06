/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_TRAFFICGRAPHWIDGET_H
#define DYNAMIC_QT_TRAFFICGRAPHWIDGET_H

#include "trafficgraphdata.h"

#include <boost/function.hpp>

#include <QQueue>
#include <QWidget>

class ClientModel;

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QTimer;
QT_END_NAMESPACE

class TrafficGraphWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrafficGraphWidget(QWidget* parent = 0);
    void setClientModel(ClientModel* model);
    int getGraphRangeMins() const;

protected:
    void paintEvent(QPaintEvent*);

public Q_SLOTS:
    void updateRates();
    void setGraphRangeMins(int value);
    void clear();

private:
    typedef boost::function<float(const TrafficSample&)> SampleChooser;
    void paintPath(QPainterPath& path, const TrafficGraphData::SampleQueue& queue, SampleChooser chooser);

    QTimer* timer;
    float fMax;
    int nMins;
    ClientModel* clientModel;
    TrafficGraphData trafficGraphData;
};

#endif // DYNAMIC_QT_TRAFFICGRAPHWIDGET_H