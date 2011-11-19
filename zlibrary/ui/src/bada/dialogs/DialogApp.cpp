/*
 * DialogApp.cpp
 *
 *  Created on: 19.11.2011
 *      Author: Alex
 */

#include "DialogApp.h"
#include <FBase.h>

using namespace Osp::App;
using namespace Osp::Media;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::System;
using namespace Osp::Base;

DialogApp::DialogApp() {
	// TODO Auto-generated constructor stub
	AppLog("DialogApp::DialogApp()");
}

DialogApp::~DialogApp() {
	// TODO Auto-generated destructor stub
}


Application* DialogApp::CreateInstance(void)
{
	// Create the instance through the constructor.
	AppLog("DialogApp::CreateInstance()");
	return new DialogApp();
}



bool DialogApp::OnAppInitializing(AppRegistry& appRegistry)
{
	// TODO:
	// Initialize UI resources and application specific data.
	// The application's permanent data and context can be obtained from the appRegistry.
	//
	// If this method is successful, return true; otherwise, return false.
	// If this method returns false, the application will be terminated.

	// Uncomment the following statement to listen to the screen on/off events.
	//PowerManager::SetScreenEventListener(*this);
	AppLog("DialogApp::OnAppInitializing()");

/* // Create a form
	B2Form *pB2Form = new B2Form();
	pB2Form->Initialize();

	// Add the form to the frame
	Frame *pFrame = GetAppFrame()->GetFrame();
	pFrame->AddControl(*pB2Form);

	// Set the current form
	pFrame->SetCurrentForm(*pB2Form);

	// Draw and Show the form
	pB2Form->Draw();
	pB2Form->Show();
*/
	return true;
}

bool DialogApp::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this application for termination.
	// The application's permanent data and context can be saved via appRegistry.
	return true;
}

void DialogApp::OnForeground(void)
{
	// TODO:
	// Start or resume drawing when the application is moved to the foreground.
}

void DialogApp::OnBackground(void)
{
	// TODO:
	// Stop drawing when the application is moved to the background.
}

void DialogApp::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the application.
}

void DialogApp::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void DialogApp::OnScreenOn (void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void DialogApp::OnScreenOff (void)
{
	// TODO:
	//  Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}
