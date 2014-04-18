#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"

#define numTracks 8


class testApp : public ofBaseApp{

	public:
		~testApp();/* destructor is very useful */
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		void audioRequested 	(float * input, int bufferSize, int nChannels); /* output method */
		void audioReceived 	(float * input, int bufferSize, int nChannels); /* input method */
	
		int		initialBufferSize; /* buffer size */
		int		sampleRate;
	
	
		/* stick you maximilian stuff below */
	
        double samples[8], volume[8], length[8], freq[8];
//        double wave,sample,outputs[2], sample2, outputs2[2], sample3, sample4, sample5, sample6, sample7, sample8;
		ofxMaxiMix mymix;
		ofxMaxiOsc sine1;
        ofxMaxiSample tracks[8];
//		ofxMaxiSample beats,beat, beat2, beat3, beat4, beat5, beat6, beat7, beat8;
	
		
};
