#pragma once

#include <QtCore/QDir>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QSettings>
#include <QtWebEngineCore/QWebEngineProfile>
#include <QtWebEngineCore/QWebEngineSettings>
#include <QProcess>
#include <QMessageBox>
#include "webview.h"
#include "settings.h"
#include "settingsmanager.h"
#include "ui_hoyolabdesktop.h"

class HoYoLABDesktop : public QMainWindow
{
	Q_OBJECT

public:
	HoYoLABDesktop(QWidget *parent = nullptr);
	~HoYoLABDesktop();

private:
	QString cache_path = QDir::homePath() + "/.cache/HoYoLAB";
	QString settings_path = QDir(QApplication::applicationDirPath()).filePath("settings.ini");
	Ui::HoYoLABDesktopClass ui;
	QUrl defaultUrl = QUrl("https://www.hoyolab.com/home");
	QString invalidUrls{
		"https://account.hoyolab.com/single-page/cross-login.html?complete=1"
	};
	QWebEngineProfile* profile;
	QWebEnginePage* page;
	SettingsManager* settings;

private slots:
	void on_actionHome_triggered();
	void on_actionReload_triggered();
	void on_actionBack_triggered();
	void on_actionForward_triggered();
	void on_actionFullscreen_triggered();

	void on_actionGenshinRun_triggered();
	void on_actionStarrailRun_triggered();
	void on_actionHonkaiRun_triggered();
	void on_actionZenlessRun_triggered();

	void on_actionOpenSettings_triggered();

	void on_hoyoWebView_loadFinished();

private:
	void setupUi();
	void toHomePage();
	void checkRedirects();

};
