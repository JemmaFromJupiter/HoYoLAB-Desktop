#pragma once

#include <QDialog>
#include <QFileDialog>
#include <QSettings>
#include "settingsmanager.h"
#include "ui_settings.h"

class Settings : public QDialog, public Ui::SettingsClass
{
	Q_OBJECT

public:
	Settings(QWidget *parent = nullptr, SettingsManager* settings = nullptr);
	~Settings();

private slots:
	void on_browseGenshin_clicked();
	void on_browseStarrail_clicked();
	void on_browseHonkai_clicked();
	void on_browseZenless_clicked();

private:
	void browseExe(QLineEdit* entry);
	
};
