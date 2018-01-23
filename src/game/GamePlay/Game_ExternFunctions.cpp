#include "pch.h"
#include "../GameCore/CGame.h"
#if defined(_WINDOWS)
extern "C" void OS_AdBoxDownloadFile() {}
extern "C" void OS_DeviceClearAllPushNotify() {}
extern "C" void OS_DeviceAskPushNotify() {}
extern "C" void OS_DevicePushNotify() {}
extern "C" bool		OS_IsDocumentFileExist(const char* filename) { return false; }
extern "C" bool  OS_IsIpadDevice() { return false; }
extern "C" void OpenAppStore(INT64 appleID) {}
#endif

#if defined(_WINDOWS_PHONE8)
extern "C" void OS_AdBoxDownloadFile() {}
#endif