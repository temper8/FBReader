/*
 * Copyright (C) 2004-2006 Nikolay Pultsin <geometer@mawhrin.net>
 * Copyright (C) 2005 Mikhail Sobolev <mss@mawhrin.net>
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

#ifndef __ZLQTOPTIONVIEW_H__
#define __ZLQTOPTIONVIEW_H__

#include <qobject.h>

#include "../../abstract/dialogs/ZLOptionsDialog.h"
#include "../../abstract/dialogs/ZLOptionEntry.h"
#include "../../abstract/dialogs/ZLOptionView.h"

class ZLQtDialogContent;

class QButtonGroup;
class QLabel;
class QSpinBox;
class QCheckBox;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QComboBox;
class QSlider;
class QWidget;

class ZLQtOptionView : public ZLOptionView {

protected:
	ZLQtOptionView(ZLOptionEntry *option, ZLQtDialogContent *tab, int row, int fromColumn, int toColumn) : ZLOptionView(option), myTab(tab), myRow(row), myFromColumn(fromColumn), myToColumn(toColumn), myInitialized(false) {}

public:
	virtual ~ZLQtOptionView() {}
	void setPosition(ZLQtDialogContent *tab, int row, int fromColumn, int toColumn) {
		myTab = tab;
		myRow = row;
		myFromColumn = fromColumn;
		myToColumn = toColumn;
	}

	void setVisible(bool visible) {
		if (visible) {
			if (!myInitialized) _createItem(); myInitialized = true; setActive(myOption->isActive()); _show();
		} else {
			if (myInitialized) _hide();
		}
	}
	void setActive(bool active) {
		if (myInitialized) {
			_setActive(active);
		}
	}
	void onAccept() const { if (myInitialized) _onAccept(); }

protected:
	virtual void _createItem() = 0;
	virtual void _hide() = 0;
	virtual void _show() = 0;
	// TODO: replace by pure virtual method
	virtual void _setActive(bool active) {}
	virtual void _onAccept() const = 0;

protected:
	ZLQtDialogContent *myTab;
	int myRow, myFromColumn, myToColumn;

private:
	bool myInitialized;
};

class ChoiceOptionView : public ZLQtOptionView {

public:
	ChoiceOptionView(ZLChoiceOptionEntry *option, ZLQtDialogContent *tab, int row, int fromColumn, int toColumn) : ZLQtOptionView(option, tab, row, fromColumn, toColumn) {
		myButtons = 0;
	}
	~ChoiceOptionView() { if (myButtons != 0) delete[] myButtons; }

protected:
	void _createItem();
	void _show();
	void _hide();
	void _onAccept() const;

private:
	QButtonGroup *myGroup;
	QRadioButton **myButtons;
};

class BooleanOptionView : public QObject, public ZLQtOptionView {

Q_OBJECT

public:
	BooleanOptionView(ZLBooleanOptionEntry *option, ZLQtDialogContent *tab, int row, int fromColumn, int toColumn) : ZLQtOptionView(option, tab, row, fromColumn, toColumn) {}

protected:
	void _createItem();
	void _show();
	void _hide();
	void _onAccept() const;

private slots:
	void onStateChanged(bool) const;

private:
	QCheckBox *myCheckBox;
};

class StringOptionView : public QObject, public ZLQtOptionView {

Q_OBJECT

public:
	StringOptionView(ZLStringOptionEntry *option, ZLQtDialogContent *tab, int row, int fromColumn, int toColumn) : ZLQtOptionView(option, tab, row, fromColumn, toColumn), myLabel(0), myLineEdit(0) {}

protected:
	void _createItem();
	void _show();
	void _hide();
	void _setActive(bool active);
	void _onAccept() const;
	void reset();

private slots:
	void onValueEdited(const QString &value);

private:
	QLabel *myLabel;
	QLineEdit *myLineEdit;
};

class SpinOptionView : public ZLQtOptionView {

public:
	SpinOptionView(ZLSpinOptionEntry *option, ZLQtDialogContent *tab, int row, int fromColumn, int toColumn) : ZLQtOptionView(option, tab, row, fromColumn, toColumn) {}

protected:
	void _createItem();
	void _show();
	void _hide();
	void _onAccept() const;

private:
	QLabel *myLabel;
	QSpinBox *mySpinBox;
};

class ComboOptionView : public QObject, public ZLQtOptionView {

Q_OBJECT

public:
	ComboOptionView(ZLComboOptionEntry *option, ZLQtDialogContent *tab, int row, int fromColumn, int toColumn) : ZLQtOptionView(option, tab, row, fromColumn, toColumn), myLabel(0), myComboBox(0) {}

protected:
	void _createItem();
	void _show();
	void _hide();
	void _setActive(bool active);
	void _onAccept() const;
	void reset();

private slots:
	void onValueSelected(int index);
	void onValueEdited(const QString &value);
	void onTabResized(const QSize &size);
	
private:
	QLabel *myLabel;
	QComboBox *myComboBox;
};

class KeyOptionView : public QObject, public ZLQtOptionView {

Q_OBJECT

public:
	KeyOptionView(ZLKeyOptionEntry *option, ZLQtDialogContent *tab, int row, int fromColumn, int toColumn) : ZLQtOptionView(option, tab, row, fromColumn, toColumn), myWidget(0), myKeyButton(0), myLabel(0), myComboBox(0) {}

private:
	void _createItem();
	void _show();
	void _hide();
	void _onAccept() const;
	void reset();

private slots:
	void onValueChanged(int);

private:
	QWidget *myWidget;
	QPushButton *myKeyButton;
	QLabel *myLabel;
	QComboBox *myComboBox;
	std::string myCurrentKey;

friend class KeyButton;
};

class ColorOptionView : public QObject, public ZLQtOptionView {

Q_OBJECT

public:
	ColorOptionView(ZLColorOptionEntry *option, ZLQtDialogContent *tab, int row, int fromColumn, int toColumn) : ZLQtOptionView(option, tab, row, fromColumn, toColumn), myWidget(0), myRSlider(0), myGSlider(0), myBSlider(0), myColorBar(0) {}

private:
	void _createItem();
	void _show();
	void _hide();
	void _onAccept() const;
	void reset();

private slots:
	void onSliderMove(int);

private:
	QWidget *myWidget;
	QSlider *myRSlider, *myGSlider, *myBSlider;
	QLabel *myColorBar;
};

#endif /* __ZLQTOPTIONVIEW_H__ */