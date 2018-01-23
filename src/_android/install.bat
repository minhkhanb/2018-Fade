call config.bat
adb uninstall topebox.game.fade
adb install  build\outputs\apk\debug\fade-debug-v0.0.1.apk
::adb install  build\outputs\apk\fade-release-v0.0.1-unsigned-signed.apk