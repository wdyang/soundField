/*  Weidong Yang 2014-04-17
 */


#include "testApp.h"
#include <string>



//-------------------------------------------------------------
testApp::~testApp() {
	
//	delete beat.myData; /*you should probably delete myData for any sample object
//						 that you've created in testApp.h*/
//    delete beat2.myData;
	
}


//--------------------------------------------------------------
void testApp::setup(){
	/* some standard setup stuff*/
	
	ofEnableAlphaBlending();
	ofSetupScreen();
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	
	/* This is stuff you always need.*/
	
	sampleRate 			= 44100; /* Sampling Rate */
	initialBufferSize	= 512;	/* Buffer Size. you have to fill this buffer with sound*/
	
	
	/* Now you can put anything you would normally put in maximilian's 'setup' method in here. */
	
	
//	beat.load(ofToDataPath("beat4.wav"));
    string fnames[numTracks]={"STE-000.wav", "Loop 1 Dramatic Accent.wav",
        "Loop 4 Walkie Talkie.wav", "Clapping.wav", "Loop 7 Morse Code.wav",
        "8 Bubbles.wav", "9 Shutter Cymbal.wav", "beat2.wav"};
    
    for(int i=0; i<numTracks; i++){
        tracks[i].load(ofToDataPath(fnames[i]));
        tracks[i].getLength();
        length[i]=tracks[i].length;
        freq[i]=sampleRate*1.0/length[i];
        volume[i]=1.0;
    }
//    beat.load(ofToDataPath("STE-000.wav"));
//    beat2.load(ofToDataPath("Loop 1 Dramatic Accent.wav"));
//    beat3.load(ofToDataPath("Loop 4 Walkie Talkie.wav"));
//    beat4.load(ofToDataPath("Clapping.wav"));
//    beat5.load(ofToDataPath("Loop 7 Morse Code.wav"));
//    beat.getLength();
//    beat2.getLength();
//    beat3.getLength();
//    beat4.getLength();
//    beat5.getLength();
    
	
//	ofSoundStreamSetup(2,0,this, sampleRate, initialBufferSize, 4);/* Call this last ! */
	ofSoundStreamSetup(8,0,this, sampleRate, initialBufferSize, 16);/* Call this last ! */
}

//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	/* You can use any of the data from audio received and audiorequested to draw stuff here.
	 Importantly, most people just use the input and output arrays defined above.
	 Clever people don't do this. This bit of code shows that by default, each signal is going to flip
	 between -1 and 1. You need to account for this somehow. Get the absolute value for example.
	 */
	
	ofSetColor(255, 255, 255,255);
//	ofRect(600, 300, sample*150, sample*150); /* audio sigs go between -1 and 1. See?*/
    int width=ofGetWindowWidth();
    int step = width/(numTracks + 1);
    for(int i=0; i<numTracks; i++){
        ofRect((i+1)*step, 300, samples[i]*150, samples[i]*150);
    }
//	ofCircle(200, 300, wave*150);
	
}

//--------------------------------------------------------------
void testApp::audioRequested 	(float * output, int bufferSize, int nChannels){
	
	for (int i = 0; i < bufferSize; i++){
		
		/* Stick your maximilian 'play()' code in here ! Declare your objects in testApp.h.
		 
		 For information on how maximilian works, take a look at the example code at
		 
		 http://www.maximilian.strangeloop.co.uk
		 
		 under 'Tutorials'.
		 
		 */
		
		
		
//		sample=beat.play(0.02, 0, beat.length);
        double speedMod =(mouseX - ofGetWindowWidth()/2.0)/200.0;
        for(int j=0; j<numTracks; j++) {
            samples[j] = tracks[j].play(freq[j]*speedMod, 0, tracks[j].length);
        }
//		sample=beat.play(0.02*, 0, beat.length);
//        sample2 = beat2.play(0.02*(mouseX - ofGetWindowWidth()/2)/100, 0, beat.length);
//        sample3 = beat3.play(0.02*(mouseX - ofGetWindowWidth()/2)/100, 0, beat.length);
//        sample4 = beat4.play(0.02*(mouseX - ofGetWindowWidth()/2)/100, 0, beat.length);
//        sample5 = beat5.play(0.02*(mouseX - ofGetWindowWidth()/2)/100, 0, beat.length);
        
//		wave=sine1.sinebuf(abs(mouseX));/* mouse controls sinewave pitch. we get abs value to stop it dropping
										 //										 delow zero and killing the soundcard*/
		
        //		mymix.stereo(sample + wave, outputs, 0.5);
//		mymix.stereo(sample, outputs, 0.5);
//		mymix.stereo(sample2, outputs2, 0.5);
        
		
		
//		output[i*nChannels    ] = outputs[0]; /* You may end up with lots of outputs. add them here */
//		output[i*nChannels + 1] = outputs[1];
//		output[i*nChannels + 2 ] = outputs2[0]; /* You may end up with lots of outputs. add them here */
//		output[i*nChannels + 3] = outputs2[1];

        for(int j=0; j<numTracks; j++){
            output[i*nChannels + j] = samples[j]*volume[j];
        }
//		output[i*nChannels    ] = sample; /* You may end up with lots of outputs. add them here */
//		output[i*nChannels + 1] = sample2;
//		output[i*nChannels + 2 ] = sample3; /* You may end up with lots of outputs. add them here */
//		output[i*nChannels + 3] = sample4;
//		output[i*nChannels + 4] = sample5;
	}
	
}

//--------------------------------------------------------------
void testApp::audioReceived 	(float * input, int bufferSize, int nChannels){	
	
	
	/* You can just grab this input and stick it in a double, then use it above to create output*/
	
	for (int i = 0; i < bufferSize; i++){
		
		/* you can also grab the data out of the arrays*/
		
		
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
	
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}



//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}