#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

/*
Funcionamiento alto nivel del proyecto.
1. Hardware
Un arduino que tiene conectado a dos de sus pines analogos dos sensores
permitiran modificar dos variables que mediante un protocolo firmata
se enviaran a la aplicacion openframeworks

2. OpenFramework App
Un fragment shader que dibuja unas metabolas.

El framgent shader recibe información mediante uniforms y dos de dichos uniforms
seran los valores leidos por los pines analogos del arduino.

Estos uniformas modificaran el tamañao de las metabolas y la rotación en
el eje y de la camara del fragment shader.

Los valores analogos leidos por el arduino tambien se enviaran mediante
protocolo OSC a pure data a un sintetizador FM y controlaran a. la frecuencia base y
b. por definir


3. PureData App
Recibira mediante protocolo OSC los valores analogos leidos por el Arduino
y los enviara a los dos parametros especificados anteriormente de un sinte
tizador FM, PureData se encargara de producir el sonido.


*/

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// custom attributes
		ofShader metaballs;

		bool bSetupArduino;			// flag variable for setting up arduino once

		int potValue; // Potenciometer value

		int photoValue; // foto resistor


		ofArduino arduino; // Comunicacion con arduino mediante protocolo firmata
		// ofSerial serial;

		ofxOscSender sender;

		void setupArduino(const int& version);
		void analogPinChanged(const int& pinNum);

};
