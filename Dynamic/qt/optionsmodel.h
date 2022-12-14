/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DYNAMIC_QT_OPTIONSMODEL_H
#define DYNAMIC_QT_OPTIONSMODEL_H

#include "amount.h"

#include <QAbstractListModel>

/** Interface from Qt to configuration data structure for Dynamic client.
   To Qt, the options are presented as a list with the different options
   laid out vertically.
   This can be changed to a tree once the settings become sufficiently
   complex.
 */
class OptionsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit OptionsModel(QObject* parent = 0, bool resetSettings = false);

    enum OptionID {
        StartAtStartup,          // bool
        HideTrayIcon,            // bool
        MinimizeToTray,          // bool
        MapPortUPnP,             // bool
        MinimizeOnClose,         // bool
        ProxyUse,                // bool
        ProxyIP,                 // QString
        ProxyPort,               // int
        ProxyUseTor,             // bool
        ProxyIPTor,              // QString
        ProxyPortTor,            // int
        DisplayUnit,             // DynamicUnits::Unit
        ThirdPartyTxUrls,        // QString
        Digits,                  // QString
        Theme,                   // QString
        Language,                // QString
        CoinControlFeatures,     // bool
        ThreadsScriptVerif,      // int
        DatabaseCache,           // int
        SpendZeroConfChange,     // bool
        HideOrphans,             // bool
        ShowDynodesTab,          // bool
        ShowAdvancedPSUI,        // bool
        ShowPrivateSendPopups,   // bool
        LowKeysWarning,          // bool
        PrivateSendRounds,       // int
        PrivateSendAmount,       // int
        PrivateSendMultiSession, // bool
        Listen,                  // bool
        OptionIDRowCount,
    };

    void Init(bool resetSettings = false);
    void Reset();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    /** Updates current unit in memory, settings and emits displayUnitChanged(newUnit) signal */
    void setDisplayUnit(const QVariant& value);

    /* Explicit getters */
    bool getHideTrayIcon() { return fHideTrayIcon; }
    bool getMinimizeToTray() { return fMinimizeToTray; }
    bool getMinimizeOnClose() { return fMinimizeOnClose; }
    int getDisplayUnit() { return nDisplayUnit; }
    QString getThirdPartyTxUrls() { return strThirdPartyTxUrls; }
    bool getCoinControlFeatures() { return fCoinControlFeatures; }
    bool getShowAdvancedPSUI() { return fShowAdvancedPSUI; }
    const QString& getOverriddenByCommandLine() { return strOverriddenByCommandLine; }

    /* Restart flag helper */
    void setRestartRequired(bool fRequired);
    bool isRestartRequired();
    bool resetSettings;

private:
    /* Qt-only settings */
    bool fHideTrayIcon;
    bool fMinimizeToTray;
    bool fMinimizeOnClose;
    QString language;
    int nDisplayUnit;
    QString strThirdPartyTxUrls;
    bool fCoinControlFeatures;
    bool fHideOrphans;
    bool fShowAdvancedPSUI;
    /* settings that were overriden by command-line */
    QString strOverriddenByCommandLine;

    // Add option to list of GUI options overridden through command line/config file
    void addOverriddenOption(const std::string& option);

    // Check settings version and upgrade default values if required
    void checkAndMigrate();
Q_SIGNALS:
    void displayUnitChanged(int unit);
    void privateSendRoundsChanged();
    void privateSentAmountChanged();
    void advancedPSUIChanged(bool);
    void coinControlFeaturesChanged(bool);
    void hideOrphansChanged(bool);
    void hideTrayIconChanged(bool);
};

#endif // DYNAMIC_QT_OPTIONSMODEL_H
