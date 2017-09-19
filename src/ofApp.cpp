#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Shader stuffs
#ifdef TARGET_OPENGLES
	metaballs.load("shadersES2/metaballs");
#else
	if (ofIsGLProgrammableRenderer()) {
		metaballs.load("shadersGL3/metaballs");

		std::cout << ofGetHeight() << endl;
	}
	else {
		metaballs.load("shadersGL2/metaballs");
	}
#endif

	potValue = 0;

	// Firmata/Arduino Stuffs
	arduino.connect("COM9", 57600);
	arduino.sendFirmwareVersionRequest();

	/*if (arduino.isArduinoReady())
	{
	printf("Hola mundo");
	}*/

	ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
	bSetupArduino = false;

	// OSC/PureData stuffs
	sender.setup(HOST, PORT);

}

void ofApp::setupArduino(const int& version) {
	bSetupArduino = true;

	arduino.sendAnalogPinReporting(0, ARD_ANALOG);
	arduino.sendAnalogPinReporting(1, ARD_ANALOG);

	ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

void ofApp::analogPinChanged(const int& pinNum) {
	// Conectar a analog0 el potenciometro
	// Conectar a analog1 el fotoresistor

	if (pinNum == 0) {
		//std::cout << "Potenciometer: " << arduino.getAnalog(pinNum) << endl
		potValue = arduino.getAnalog(pinNum);

		ofxOscMessage mpot;
		mpot.setAddress("/potenciometer/x");
		mpot.addFloatArg(ofMap(potValue, 0, 1023, 300, 3000));
		sender.sendMessage(mpot, false);
	}

	if (pinNum == 1) {
		//std::cout << "Photoresistor: " << arduino.getAnalog(pinNum) << endl;
		photoValue = arduino.getAnalog(pinNum);

		ofxOscMessage mphoto;
		mphoto.setAddress("/photoresistor/x");
		mphoto.addFloatArg(ofMap(photoValue, 0, 1023, 0., 60.));
		sender.sendMessage(mphoto, false);
	}

}

//--------------------------------------------------------------
void ofApp::update(){
	//std::cout << ofGetElapsedTimef() << endl;
	arduino.update();

	if (!bSetupArduino) return;
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (!bSetupArduino) return;

	ofClear(0, 0, 0, 0);
	metaballs.begin();
	// Parece que solo se pueden enviar uniforms al shader en medio del shader.begin() y el shader.end()
	// TO-DO: Hacer que la resolucion solo se envie una vez.
	metaballs.setUniform2f("iResolution", ofGetWidth(), ofGetHeight());
	metaballs.setUniform1f("iTime", ofGetElapsedTimef());
	metaballs.setUniform2f("iMouse", ofGetMouseX(), ofGetMouseY());
	metaballs.setUniform2f("iSensors",
		ofMap(potValue, 0, 1023, 0, ofGetWidth()),
		ofMap(photoValue, 0, 1023, 0, ofGetHeight()));
	// Se mapean de 0 al ofGetWidth y ofGetHeight, debido a que
	// estos valores son referentes en el shader program.


	ofRect(0, 0, ofGetWidth(), ofGetHeight());
	metaballs.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
