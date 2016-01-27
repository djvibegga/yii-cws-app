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
#include <db/CDbDataReader.h>
#include <db/CDbCriteria.h>
#include <db/schema/CDbCommandBuilder.h>
#include <web/CAssetManager.h>
#include <web/CClientScript.h>
#include <web/CWebUser.h>
#include <utils/CMap.h>
#include <boost/assign/list_of.hpp>

#include "MainLayout.h"
#include "MyUserIdentity.h"
#include "models/Page.h"
#include "models/Object.h"

SiteController::SiteController(CModule * parent)
: CController("site", parent)
{
	setLayout(TViewPtr(new MainLayout(this)));
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
	registerAction("db", ACTION(&SiteController::actionDb));
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
	setLayout(TViewPtr(new MainLayout(this, "application.views.layouts.home")));

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
	cs->registerPackage("bbq");
	cs->registerPackage("cookie");

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

	cookies.add(CHttpCookie("lang", "ru", "", "/"));
	cookies.add(CHttpCookie("sessid", session->getSessionId(), "", "/", time(0) + 100));
	cookies.remove("lang");

	render("cookies", viewData);
}

void SiteController::actionSecurity(CHttpRequest * const request, CHttpResponse * response) throw (CException)
{
	CSecurityManager * manager = dynamic_cast<CSecurityManager*>(Cws::app()->getComponent("securityManager"));
	string source = "test stupid lorem ipsum";
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

	if (!user->getIsGuest()) {
		*response << _("user is already logged");
		return;
	}

	MyUserIdentity identity("admin", "admin");
	if (!identity.authenticate()) {
		*response << _("failure auth");
		return;
	}
	if (!user->login(identity, 1220)) {
		*response << _("failure login");
		return;
	}

	*response << _("Welcome, ") << user->getName() << _("!");
}

void SiteController::actionLogout(CHttpRequest * const request, CHttpResponse * response) throw (CException)
{
	CWebUser * user = dynamic_cast<CWebUser*>(Cws::app()->getComponent("user"));
	user->logout();
	*response << _("Bye bye...");
}

void SiteController::actionDb(CHttpRequest * const request, CHttpResponse * response) throw (CException)
{
	CDbCriteria criteria;
	CDT viewData;
//	workCriteria.join = "INNER JOIN article_revision `ar` ON (`ar`.article_id = `t`.id AND `ar`.revision_type = 2)";
//	string categoryParam = request->getParam("category");
//	if (!categoryParam.empty()) {
//		CDbCriteria criteria;
//		criteria.compare("name", categoryParam);
//		ArticleCategory * categoryModel = dynamic_cast<ArticleCategory*>(ArticleCategory::model()->find(criteria).get());
//		if (categoryModel) {
//			workCriteria.join += " INNER JOIN article_revision_article_category `arac` ON (`arac`.article_revision_id = `ar`.id)";
//			workCriteria.compare("`arac`.article_category_id", categoryModel->id);
//		}
//		workCriteria.group = "`t`.id";
//	}
//	string tagParam = request->getParam("tag");
//	if (!tagParam.empty()) {
//		Tag * tagModel = dynamic_cast<Tag*>(Tag::model()->findByName(tagParam).get());
//		if (tagModel) {
//			workCriteria.join += " INNER JOIN article_revision_object_tag `arot` ON (`arot`.article_revision_id = `ar`.id)"
//				" INNER JOIN article_tag `at` ON (`arot`.object_tag_id = `at`.object_id)";
//			workCriteria.compare("`at`.object_id", tagModel->objectId);
//		}
//		workCriteria.group = "`t`.id";
//	}
//
//	workCriteria.select = boost::assign::list_of ("t.*");
//	TActiveRecordList items = Article::model()->findAll(workCriteria);
//
//	CDbCriteria categoryCriteria;
//	categoryCriteria.order = "`index` ASC";
//	TActiveRecordList categories = ArticleCategory::model()->findAll(categoryCriteria);
//
//	TActiveRecordList tags = Tag::model()->findAll();
//
//	CApplication * app = Cws::app();
//
//	CDT work;
//	CUrlManager * urlManager = dynamic_cast<CUrlManager*>(app->getComponent("urlManager"));
//	viewData["items"] = CDT();
//	for (TActiveRecordList::iterator iter = items.begin(); iter != items.end(); ++iter) {
//		Article * item = dynamic_cast<Article*>(iter->get());
//		work["id"] = item->id;
//		work["name"] = item->name;
//		TRouteStruct route("work/view");
//		route.params["name"] = item->name;
//		work["url"] = urlManager->createUrl(route);
//		viewData["items"].PushBack(work);
//	}
//
//	CDT category;
//	for (TActiveRecordList::iterator iter = categories.begin(); iter != categories.end(); ++iter) {
//		ArticleCategory * item = dynamic_cast<ArticleCategory*>(iter->get());
//		category["id"] = item->id;
//		category["name"] = item->name;
//		category["label"] = _to_utf8(item->label);
//		TRouteStruct route("work/index");
//		route.params["category"] = item->name;
//		category["url"] = urlManager->createUrl(route);
//		viewData["categories"].PushBack(category);
//	}
//
//	CDT tag;
//	for (TActiveRecordList::iterator iter = tags.begin(); iter != tags.end(); ++iter) {
//		Tag * item = dynamic_cast<Tag*>(iter->get());
//		tag["id"] = item->id;
//		tag["name"] = item->name;
//		tag["label"] = _to_utf8(item->label);
//		TRouteStruct route("work/index");
//		route.params["tag"] = item->name;
//		tag["url"] = urlManager->createUrl(route);
//		viewData["tags"].PushBack(tag);
//	}

	viewData["assetsUrl"] = dynamic_cast<CAssetManager*>(app->getComponent("assetManager"))
		->getPublishedUrl(Cws::getPathOfAlias("application.assets"));

	render("index", viewData);
}

void SiteController::actionTranslate(CHttpRequest * const request, CHttpResponse * response) throw (CException)
{
	_string message = (_f(_t(_("test {1}"))) % 15).str();

	*response << _to_utf8(message);
}
