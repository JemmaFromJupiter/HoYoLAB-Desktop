#include "settings.h"

Settings::Settings(QWidget *parent, SettingsManager* settings)
	: QDialog(parent)
{
	setupUi(this);
	entryGenshin->setText(settings->loadSetting("executables/genshin_executable_path"));
	entryStarrail->setText(settings->loadSetting("executables/starrail_executable_path"));
	entryHonkai->setText(settings->loadSetting("executables/honkai_executable_path"));
	entryZenless->setText(settings->loadSetting("executables/zenless_executable_path"));
}

Settings::~Settings()
{}

void Settings::on_browseGenshin_clicked() {
	browseExe(entryGenshin);
}

void Settings::on_browseStarrail_clicked() {
	browseExe(entryStarrail);
}

void Settings::on_browseHonkai_clicked() {
	browseExe(entryHonkai);
}

void Settings::on_browseZenless_clicked() {
	browseExe(entryZenless);
}

void Settings::browseExe(QLineEdit* entry) {
	QString filepath = QFileDialog::getOpenFileName(this, "Select Executable", QString(), QString("Executable Files (*.exe)"));
	if (!filepath.isEmpty())
		entry->setText(filepath);
}