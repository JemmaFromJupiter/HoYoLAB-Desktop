#pragma once

#include <QObject>
#include <QSettings>

class SettingsManager : public QObject {
	Q_OBJECT

public:
	SettingsManager(QObject* parent = nullptr, QString settingsPath = "");

	QString loadSetting(const QString& key, const QString& defaultValue = "");

	void updateSetting(const QString& key, const QString& value);

	void beginGroup(QAnyStringView prefix);

signals:
	void settingsChanged(const QString& key, const QString& value);


private:
	QSettings settings;

};