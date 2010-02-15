/*
 * Copyright (C) 2009-2010 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef __NETWORKITEMS_H__
#define __NETWORKITEMS_H__

#include <string>
#include <vector>
#include <map>

#include <shared_ptr.h>

#include <ZLTypeId.h>

class NetworkAuthenticationManager;
class NetworkLink;

class NetworkItem : public ZLObjectWithRTTI {

public:
	typedef std::vector<shared_ptr<NetworkItem> > List;

	enum URLType {
		URL_NONE,
		URL_CATALOG,
		URL_BOOK_EPUB,
		URL_BOOK_MOBIPOCKET,
		URL_BOOK_FB2_ZIP,
		URL_BOOK_PDF,
		URL_BOOK_DEMO_FB2_ZIP,
		URL_HTML_PAGE,
		URL_COVER
	};

protected:
	static const ZLTypeId TYPE_ID;

protected:
	NetworkItem(
		const std::string &title,
		const std::string &summary,
		const std::map<URLType,std::string> &urlByType
	);

public:
	virtual ~NetworkItem();

	virtual const ZLTypeId &typeId() const = 0;

public:
	const std::string Title;
	const std::string Summary;
	/*const*/ std::map<URLType,std::string> URLByType;

private: // disable copying
	NetworkItem(const NetworkItem &item);
	const NetworkItem &operator = (const NetworkItem &);
};

class NetworkCatalogItem : public NetworkItem {

public:
	static const ZLTypeId TYPE_ID;

	enum CatalogType {
		OTHER,
		BY_AUTHORS,
	};

	enum VisibilityType {
		Always,
		Never,
		LoggedUsers
	};

public:
	NetworkCatalogItem(
		const NetworkLink &link,
		const std::string &title,
		const std::string &summary,
		const std::map<URLType,std::string> &urlByType,
		VisibilityType visibility = Always
	);

	const ZLTypeId &typeId() const;

	// method is called each time the View Node is created for the Item.
	virtual void onDisplayItem();
	// returns error message
	virtual std::string loadChildren(List &children) = 0;

	virtual CatalogType catalogType() const;

public:
	const NetworkLink &Link;
	const VisibilityType Visibility;
};

class NetworkBookItem : public NetworkItem {

public:
	struct AuthorData {
		std::string DisplayName;
		std::string SortKey;

		bool operator < (const AuthorData &data) const;
	};

public:
	static const ZLTypeId TYPE_ID;

public:
	NetworkBookItem(
		const std::string &id,
		unsigned int index,
		const std::string &title,
		const std::string &summary,
		const std::string &language,
		const std::vector<AuthorData> &authors,
		const std::vector<std::string> &tags,
		const std::map<URLType,std::string> &urlByType
	);
	explicit NetworkBookItem(const NetworkBookItem &book);

	const ZLTypeId &typeId() const;

public:
	unsigned int index() const;
	void setIndex(unsigned int index);

	const std::string &language() const;
	const std::string &date() const;
	const std::string &seriesTitle() const;
	int indexInSeries() const;
	const std::string &price() const;

	void setLanguage(const std::string &language);
	void setDate(const std::string &date);
	void setPrice(const std::string &price);
	void setSeries(const std::string &name, int index);

	shared_ptr<NetworkAuthenticationManager> authenticationManager() const;
	void setAuthenticationManager(shared_ptr<NetworkAuthenticationManager> manager);

	URLType bestBookFormat() const;
	URLType bestDemoFormat() const;

private:
	unsigned int myIndex;

public:
	const std::string Id;

private:
	std::string myLanguage;
	std::string myDate;
	std::string mySeriesTitle;
	int myIndexInSeries;
	std::string myPrice; // number with curency code (see http://en.wikipedia.org/wiki/List_of_circulating_currencies for example)

public:
	const std::vector<AuthorData> Authors;
	const std::vector<std::string> Tags;

	shared_ptr<NetworkAuthenticationManager> myAuthenticationManager;
};

inline unsigned int NetworkBookItem::index() const { return myIndex; }
inline void NetworkBookItem::setIndex(unsigned int index) { myIndex = index; }

inline const std::string &NetworkBookItem::language() const { return myLanguage; }
inline const std::string &NetworkBookItem::date() const { return myDate; }
inline const std::string &NetworkBookItem::seriesTitle() const { return mySeriesTitle; }
inline int NetworkBookItem::indexInSeries() const { return myIndexInSeries; }
inline const std::string &NetworkBookItem::price() const { return myPrice; }

#endif /* __NETWORKITEMS_H__ */