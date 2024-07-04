#include "webview.h"

WebPage::WebPage(QObject *parent)
	: QWebEnginePage(parent)
{}

WebPage::WebPage(QWebEngineProfile* profile, QObject* parent)
	: QWebEnginePage(profile, parent)
{}

WebPage::~WebPage()
{}

QWebEnginePage* WebPage::createWindow(QWebEnginePage::WebWindowType _type) {
	return this;
}