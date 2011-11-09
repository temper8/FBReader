/*
 * ZLBadaApplicationWindow.h
 *
 *  Created on: 11.10.2011
 *      Author: Alex
 */

#ifndef ZLBADAAPPLICATIONWINDOW_H_
#define ZLBADAAPPLICATIONWINDOW_H_
#include <FBase.h>
#include <FUi.h>
#include "ZLApplicationWindow.h"
#include "../view/badaApp.h"
//#include "B2Form.h"

class ZLbadaApplicationWindow: public ZLApplicationWindow {

public:
	badaApp*  myBadaApp;
	ZLViewWidget *createViewWidget();
	ZLbadaApplicationWindow(ZLApplication *application);
	~ZLbadaApplicationWindow();
};

#endif /* ZLBADAAPPLICATIONWINDOW_H_ */
