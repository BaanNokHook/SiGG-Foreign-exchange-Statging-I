/**
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "winshutdownmonitor.h"

#if defined(Q_OS_WIN) && QT_VERSION >= 0x050000
#include "init.h"
#include "util.h"

#include <windows.h>

#include <openssl/rand.h>

#include <QDebug>

// If we don't want a message to be processed by Qt, return true and set result to
// the value that the window procedure should return. Otherwise return false.
bool WinShutdownMonitor::nativeEventFilter(const QByteArray& eventType, void* pMessage, long* pnResult)
{
    Q_UNUSED(eventType);

    MSG* pMsg = static_cast<MSG*>(pMessage);

    // Seed OpenSSL PRNG with Windows event data (e.g.  mouse movements and other user interactions)
    if (RAND_event(pMsg->message, pMsg->wParam, pMsg->lParam) == 0) {
        // Warn only once as this is performance-critical
        static bool warned = false;
        if (!warned) {
            LogPrintf("%s: OpenSSL RAND_event() failed to seed OpenSSL PRNG with enough data.\n", __func__);
            warned = true;
        }
    }

    switch (pMsg->message) {
    case WM_QUERYENDSESSION: {
        // Initiate a client shutdown after receiving a WM_QUERYENDSESSION and block
        // Windows session end until we have finished client shutdown.
        StartShutdown();
        *pnResult = FALSE;
        return true;
    }

    case WM_ENDSESSION: {
        *pnResult = FALSE;
        return true;
    }
    }

    return false;
}

void WinShutdownMonitor::registerShutdownBlockReason(const QString& strReason, const HWND& mainWinId)
{
    typedef BOOL(WINAPI * PSHUTDOWNBRCREATE)(HWND, LPCWSTR);
    PSHUTDOWNBRCREATE shutdownBRCreate = (PSHUTDOWNBRCREATE)GetProcAddress(GetModuleHandleA("User32.dll"), "ShutdownBlockReasonCreate");
    if (shutdownBRCreate == NULL) {
        qWarning() << "registerShutdownBlockReason: GetProcAddress for ShutdownBlockReasonCreate failed";
        return;
    }

    if (shutdownBRCreate(mainWinId, strReason.toStdWString().c_str()))
        qWarning() << "registerShutdownBlockReason: Successfully registered: " + strReason;
    else
        qWarning() << "registerShutdownBlockReason: Failed to register: " + strReason;
}
#endif
