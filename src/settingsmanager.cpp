#include "settingsmanager.h"

SettingsManager::SettingsManager(QObject* parent, QString settingsPath)
	: QObject(parent), settings(settingsPath, QSettings::IniFormat) {};

QString SettingsManager::loadSetting(const QString& key, const QString& defaultValue) {
	return settings.value(key, defaultValue).toString();
}

void SettingsManager::updateSetting(const QString& key, const QString& value) {
	settings.setValue(key, value);
	settings.sync();
	emit settingsChanged(key, value);
}

void SettingsManager::beginGroup(QAnyStringView prefix) {
	settings.beginGroup(prefix);
}