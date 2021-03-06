#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.width = 1024;
	settings.height = 768;
	settings.title = "Volcano Demo - Jose Villalobos - GameBite10";
	settings.windowMode = ofWindowMode::OF_FULLSCREEN;
	ofCreateWindow(settings);
	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
