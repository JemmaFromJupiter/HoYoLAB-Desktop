#include "hoyolabdesktop.h"
#include <iostream>

HoYoLABDesktop::HoYoLABDesktop(QWidget *parent)
	: QMainWindow(parent)
{
	QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
	QDir appDataDir(appDataPath);
	QDir appDataCacheDir(appDataPath + "/cache/webcache");
	
	if (!appDataDir.exists())
		appDataDir.mkdir(".");

	if (!appDataCacheDir.exists())
		appDataCacheDir.mkdir(".");

	cache_path = appDataCacheDir.path();
	settings_path = appDataDir.filePath("settings.ini");
	settings = new SettingsManager(this, settings_path);
	setupUi();
}

HoYoLABDesktop::~HoYoLABDesktop()
{}

void HoYoLABDesktop::on_actionHome_triggered() { toHomePage(); }

void HoYoLABDesktop::on_actionReload_triggered() { ui.hoyoWebView->reload(); }

void HoYoLABDesktop::on_actionBack_triggered() { ui.hoyoWebView->back(); }

void HoYoLABDesktop::on_actionForward_triggered() { ui.hoyoWebView->forward(); }

void HoYoLABDesktop::on_actionFullscreen_triggered() { isFullScreen() ? showNormal() : showFullScreen(); }

void HoYoLABDesktop::on_actionExit_triggered() { close(); }

void HoYoLABDesktop::closeEvent(QCloseEvent* event) {
	settings->syncSettings();

	delete settings;
	profile->deleteLater();
	page->deleteLater();

	QMainWindow::closeEvent(event);
}

void HoYoLABDesktop::on_actionGenshinRun_triggered() {
	QString value = settings->loadSetting("executables/genshin_executable_path");
	if (!value.isEmpty())
		QProcess::startDetached(value);
}

void HoYoLABDesktop::on_actionStarrailRun_triggered() {
	QString value = settings->loadSetting("executables/starrail_executable_path");
	if (!value.isEmpty())
		QProcess::startDetached(value);
}

void HoYoLABDesktop::on_actionHonkaiRun_triggered() {
	QString value = settings->loadSetting("executables/honkai_executable_path");
	if (!value.isEmpty())
		QProcess::startDetached(value);
}

void HoYoLABDesktop::on_actionZenlessRun_triggered() {
	QString value = settings->loadSetting("executables/zenless_executable_path");
	if (!value.isEmpty())
		QProcess::startDetached(value);
}

void HoYoLABDesktop::handleDownloadRequested(QWebEngineDownloadRequest* download) {
	QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/" + download->downloadFileName();
	QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), defaultPath);

	if (!filePath.isEmpty()) {
		download->setDownloadFileName(filePath);
		download->accept();
	}
}

void HoYoLABDesktop::on_actionOpenSettings_triggered() {
	Settings settingsWindow(this, settings);
	if (settingsWindow.exec()) {
		settings->beginGroup("executables");
		QMessageBox messageBox;
		QString g_entry = settingsWindow.entryGenshin->text(), s_entry = settingsWindow.entryStarrail->text(), h_entry = settingsWindow.entryHonkai->text(), z_entry = settingsWindow.entryZenless->text();
		if (g_entry.contains("GenshinImpact.exe") || g_entry.isEmpty())
			settings->updateSetting("genshin_executable_path", g_entry);
		else
			messageBox.critical(this, "Invalid File", "Invalid Executable: Does Not Match Required 'GenshinImpact.exe'");
		if (s_entry.contains("StarRail.exe") || s_entry.isEmpty())
			settings->updateSetting("starrail_executable_path", s_entry);
		else
			messageBox.critical(this, "Invalid File", "Invalid Executable: Does Not Match Required 'StarRail.exe'");
		if (h_entry.contains("BH3.exe") || h_entry.isEmpty())
			settings->updateSetting("honkai_executable_path", h_entry);
		else
			messageBox.critical(this, "Invalid File", "Invalid Executable: Does Not Match Required 'BH3.exe'");
		if (z_entry.contains("ZenlessZoneZero.exe") || z_entry.isEmpty())
			settings->updateSetting("zenless_executable_path", z_entry);
		else
			messageBox.critical(this, "Invalid File", "Invalid Executable: Does Not Match Required 'ZenlessZoneZero.exe'");
		settings = new SettingsManager(this, settings_path);
	}
	else {
		std::cerr << "Could Not Open Settings Window..." << std::endl;
	}
}

void HoYoLABDesktop::on_hoyoWebView_loadFinished() {
	checkRedirects();
}

void HoYoLABDesktop::setupUi() {
	ui.setupUi(this);

	setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	profile = new QWebEngineProfile("webview_profile");

	profile->setCachePath(cache_path);
	profile->setPersistentStoragePath(cache_path);
	profile->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
	profile->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);
	profile->setHttpCacheMaximumSize(20 * 1024 * 1024);

	connect(profile, &QWebEngineProfile::downloadRequested, this, &HoYoLABDesktop::handleDownloadRequested);
	

	page = new WebPage(profile, ui.hoyoWebView);
	page->setUrl(defaultUrl);
	ui.hoyoWebView->setPage(page);
	QWebEngineSettings* settings = ui.hoyoWebView->settings();
	settings->setAttribute(QWebEngineSettings::PluginsEnabled, 1);
	settings->setAttribute(QWebEngineSettings::JavascriptEnabled, 1);
	settings->setAttribute(QWebEngineSettings::LocalStorageEnabled, 1);
	settings->setAttribute(QWebEngineSettings::XSSAuditingEnabled, 1);

	setCentralWidget(ui.hoyoWebView);
}

void HoYoLABDesktop::toHomePage() {
	ui.hoyoWebView->setUrl(defaultUrl);
}

void HoYoLABDesktop::checkRedirects() {
	QString curUrl = ui.hoyoWebView->url().toString();
	if (invalidUrls.contains(curUrl)) {
		toHomePage();
	}
}