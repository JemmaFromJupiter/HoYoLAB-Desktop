#pragma once

#include <QtWebEngineCore/QWebEnginePage>

class WebPage  : public QWebEnginePage
{
	Q_OBJECT

public:
	WebPage(QObject *parent);
	WebPage(QWebEngineProfile* profile, QObject* parent);
	~WebPage();

private:
	virtual QWebEnginePage* createWindow(QWebEnginePage::WebWindowType _type);
};
