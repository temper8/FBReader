/**
 * Name        : B2App
 * Version     : 
 * Vendor      : 
 * Description : 
 */


#include "badaApp.h"
#include "badaForm.h"
#include "../library/ZLBadaLibraryImplementation.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

badaApp::badaApp()
{
}

badaApp::~badaApp()
{
}
void badaApp::TestTest(){
	AppLog("B2App::TestTest");
}

Application* badaApp::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new badaApp();
}

bool
badaApp::OnAppInitializing(AppRegistry& appRegistry)
{
	// TODO:
	// Initialize UI resources and application specific data.
	// The application's permanent data and context can be obtained from the appRegistry.
	//
	// If this method is successful, return true; otherwise, return false.
	// If this method returns false, the application will be terminated.

	// Uncomment the following statement to listen to the screen on/off events.
	//PowerManager::SetScreenEventListener(*this);


	ZLbadaLibraryImplementation::SetBada2App(this);
	AppLog("B2App::OnAppInitializing");
	ZLbadaLibraryImplementation::createApplicationWindow();
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

bool
badaApp::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this application for termination.
	// The application's permanent data and context can be saved via appRegistry.
	return true;
}

void
badaApp::OnForeground(void)
{
	// TODO:
	// Start or resume drawing when the application is moved to the foreground.
}

void
badaApp::OnBackground(void)
{
	// TODO:
	// Stop drawing when the application is moved to the background.
}

void
badaApp::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the application.
}

void
badaApp::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void
badaApp::OnScreenOn (void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void
badaApp::OnScreenOff (void)
{
	// TODO:
	//  Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}
