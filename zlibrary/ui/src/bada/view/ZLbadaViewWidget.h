/*
 * ZLbadaViewWidget.h
 *
 *  Created on: 12.10.2011
 *      Author: Alex
 */

#ifndef ZLBADAVIEWWIDGET_H_
#define ZLBADAVIEWWIDGET_H_

#include "ZLViewWidget.h"
#include "../application/ZLbadaApplicationWindow.h"
#include "badaForm.h"

class ZLbadaViewWidget: public ZLViewWidget {

private:
    ZLApplication *myApplication;
public:
    badaForm *mybadaForm;
	//void setView(shared_ptr<ZLView> view);
    void repaint();
	ZLbadaViewWidget(ZLView::Angle initialAngle);
	virtual ~ZLbadaViewWidget();
};

#endif /* ZLBADAVIEWWIDGET_H_ */
