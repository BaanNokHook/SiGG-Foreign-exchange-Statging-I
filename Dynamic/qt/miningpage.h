/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MININGPAGE_H
#define MININGPAGE_H

#include "platformstyle.h"

#include "walletmodel.h"

#include <QPushButton>
#include <QWidget>

#include <memory>

namespace Ui
{
class MiningPage;
}

class MiningPage : public QWidget
{
    Q_OBJECT

public:
    explicit MiningPage(const PlatformStyle* platformStyle, QWidget* parent = 0);
    ~MiningPage();

    void setModel(WalletModel* model);

private:
    Ui::MiningPage* ui;
    WalletModel* model;
    std::unique_ptr<WalletModel::UnlockContext> unlockContext;
    bool hasMiningprivkey;
    bool fGPUMinerOn;
    bool fCPUMinerOn;
    void timerEvent(QTimerEvent* event);
    void updateUI();
    void StartCPUMiner();
    void StopCPUMiner();
    void showCPUHashMeterControls(bool show);
    void updateCPUPushSwitch();
#ifdef ENABLE_GPU
    void StartGPUMiner();
    void StopGPUMiner();
    void showGPUHashMeterControls(bool show);
    void updateGPUPushSwitch();
#endif

    void updatePushSwitch(QPushButton* pushSwitch, bool minerOn);

    bool isMinerOn();

private Q_SLOTS:

    void changeNumberOfCPUThreads(int i, bool shutdown = false);
    void switchCPUMining();
    void showCPUHashRate(int i);
    void changeCPUSampleTime(int i);
    void clearCPUHashRateData();


#ifdef ENABLE_GPU
    void changeNumberOfGPUThreads(int i, bool shutdown = false);
    void switchGPUMining();
    void showGPUHashRate(int i);
    void changeGPUSampleTime(int i);
    void clearGPUHashRateData();
#endif
};

#endif // MININGPAGE_H
