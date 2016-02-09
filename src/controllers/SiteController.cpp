/*
 * SiteController.cpp
 *
 *  Created on: Oct 21, 2013
 *      Author: djvibegga
 */

#include "controllers/SiteController.h"
#include <boost/assign.hpp>
#include <base/Cws.h>
#include <base/CSecurityManager.h>
#include <web/CAssetManager.h>
#include <web/CClientScript.h>
#include <web/CUrlManager.h>
#include <web/CWebUser.h>

#include "MainLayout.h"
#include "MyUserIdentity.h"

SiteController::SiteController(CModule * parent)
: CController("site", parent)
{
	setDefaultLayout(TViewPtr(new MainLayout(this)));
}

SiteController::~SiteController()
{
}

void SiteController::init()
{
    CController::init();
	registerAction("index", ACTION(&SiteController::actionIndex));
	registerAction("am", ACTION(&SiteController::actionAssetManager));
	registerAction("session", ACTION(&SiteController::actionSession));
	registerAction("cookies", ACTION(&SiteController::actionCookies));
	registerAction("login", ACTION(&SiteController::actionLogin));
	registerAction("logout", ACTION(&SiteController::actionLogout));
	registerAction("security", ACTION(&SiteController::actionSecurity));
	registerAction("translate", ACTION(&SiteController::actionTranslate));
}

void SiteController::actionIndex(CHttpRequest * const request, CHttpResponse * response) throw (CException)
{
	string assetsUrl = dynamic_cast<CAssetManager*>(Cws::app()->getComponent("assetManager"))
		->getPublishedUrl(Cws::getPathOfAlias("application.assets"));

	dynamic_cast<CClientScript*>(Cws::app()->getComponent("clientScript"))
		->registerPackage("page.home");

	CDT viewData;
	viewData["assetsUrl"] = assetsUrl;

	render("index", viewData);
}

void SiteController::actionAssetManager(CHttpRequest * const request, CHttpResponse * response) throw (CException)
{
	CAssetManager * am = dynamic_cast<CAssetManager*>(Cws::app()->getComponent("assetManager"));
	CClientScript * cs = dynamic_cast<CClientScript*>(Cws::app()->getComponent("clientScript"));

	string url = am->publish(
		Cws::getPathOfAlias("application.assets")
	);

	cs->registerMetaTag("7ca4fb0526bc4815", "yandex-verification");
	cs->registerCss("initial", "body #content {padding: 5px; }", "screen");

	cs->registerPackage("test");
	cs->registerPackage("subtest");

	cs->registerScript("test", "alert('yes');", CClientScript::POS_READY);

	CDT viewData;
	render("am", viewData);
}

void SiteController::actionSession(CHttpRequest * const request, CHttpResponse * response) throw (CException)
{
	CDT viewData;
	CHttpSession * session = dynamic_cast<CHttpSession*>(Cws::app()->getComponent("session"));
	TSessionDataMap & sessionData = session->getData();
	if (sessionData.find("key") == sessionData.end()) {
		(*session)["key"] = _("привет");
		viewData["sessionKey"] = "unknown";
	} else {
		viewData["sessionKey"] = _to_utf8(sessionData["key"]);
	}

	viewData["sessionId"] = session->getSessionId();
	render("session", viewData);
}

void SiteController::actionCookies(CHttpRequest * const request, CHttpResponse * response) throw (CException)
{
	CHttpSession * session = dynamic_cast<CHttpSession*>(Cws::app()->getComponent("session"));
	CCookieCollection & cookies = request->getCookies();

	CDT viewData;
	if (cookies.find("sessid") != cookies.end()) {
		viewData["sessid"] = cookies["sessid"].value;
	}

	cookies.add(CHttpCookie("sessid", session->getSessionId(), "", "/", time(0) + 100));
	cookies.remove("lang");

	render("cookies", viewData);
}

void SiteController::actionSecurity(CHttpRequest * const request, CHttpResponse * response) throw (CException)
{
	CSecurityManager * manager = dynamic_cast<CSecurityManager*>(Cws::app()->getComponent("securityManager"));
	string source = "test string to check security manager";
	string encrypted = manager->encrypt(source);
	string decrypted = manager->decrypt(encrypted);
	*response << "source: " << source << "<br>" << "encrypted: " << encrypted << "<br>"
		<< "decrypted: " << decrypted << "<br>";

	string hmac = manager->hashData(source);
	string validated = manager->validateData(hmac);

	*response << "source: " << source << "<br>" << "hmac: " << hmac << "<br>"
			<< "validated: " << validated << "<br>";
}

void SiteController::actionLogin(CHttpRequest * const request, CHttpResponse * response) throw (CException)
{
	CWebUser * user = dynamic_cast<CWebUser*>(Cws::app()->getComponent("user"));
	CUrlManager * urlManager = dynamic_cast<CUrlManager*>(Cws::app()->getComponent("urlManager"));

	if (!user->getIsGuest()) {
		*response << _t("user is already logged...<br>")
				  << _("<a href=\"") << urlManager->createUrl("site/logout") << _("\">")
				  << _t("Logout")
				  << _("</a>");
		return;
	}

	MyUserIdentity identity("admin", "admin");
	if (!identity.authenticate()) {
		*response << _t("failure auth");
		return;
	}
	if (!user->login(identity, 1220)) {
		*response << _t("failure login");
		return;
	}

	CDT viewData;
	viewData["username"] = _to_utf8(user->getName());
	render("login", viewData);
}

void SiteController::actionLogout(CHttpRequest * const request, CHttpResponse * response) throw (CException)
{
	CWebUser * user = dynamic_cast<CWebUser*>(Cws::app()->getComponent("user"));
	user->logout();
	response->redirect("/");
}

void SiteController::actionTranslate(CHttpRequest * const request, CHttpResponse * response) throw (CException)
{
	_string message = (_f(_t("test {1}")) % 15).str();

	*response << _to_utf8(message);
}
