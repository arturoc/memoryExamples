#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	initAddress = 0;
	posSize = 10;
	totalPosInScreen = (ofGetWidth()-80)/posSize*(ofGetHeight()-80)/posSize;
	totalPosInRow = (ofGetWidth()-80)/posSize;
	ofBackground(255,255,255);

	capacityShown=false;
	eraseFromBeginShown=false;
}

//--------------------------------------------------------------
void testApp::update(){
	if(theVector.capacity()==theVector.size() && theVector.size()==4 && !capacityShown){
		ofSystemAlertDialog("the capacity of the vector is now the same as it's size\n"
				"the next time you add an element it will grow\n"
				"the memory in the vector is always consecutive so making it grow\n"
				"usually means copying it to another location with more free space\n"
				"which is slow, that's why instead of growing by one it will grow more\n"
				"so next time you add an element it doesn't need to reallocate");
		capacityShown = true;
	}
}

long int testApp::getIntRelAddress(char * currAddress){
	return currAddress - initAddress;
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(0,0,0);
	ofLine(0,80,ofGetWidth(),80);
	ofDrawBitmapString("this is a demo of how a vector allocates memory. press 'p' to push_back new elements in the vector. 'c' to clear the vector",20,20);
	ofDrawBitmapString("press 'e' to erase elements at the end of the vector. 'b' from the beginning.",412,35);
	ofDrawBitmapString("filled squares are used memory in the vector = size().",412,50);
	ofDrawBitmapString("empty squares are reserved memory in the vector = capacity().",412,65);

	ofNoFill();

	if(theVector.capacity()==0) return;

	// some tricks to make the position of the vector in the screen
	// move when it moves in memory
	int offset= totalPosInScreen/2;
	long int firstRelAddress = getIntRelAddress(&theVector[0]);
	long int lastRelAddress = getIntRelAddress(&theVector[theVector.capacity()-1]);
	if(theVector.size() && firstRelAddress + totalPosInScreen/2<0){
		offset = -firstRelAddress;
	}
	if(theVector.size() && lastRelAddress + totalPosInScreen/2>totalPosInScreen){
		offset += -firstRelAddress;
	}

	// get the first address in memory of the first position of the vector
	int  zeroAddress = ((long int)&theVector[0])-offset;

	// and draw the memory positions having zero at the center of the screen
	ofLine(80,80,80,ofGetHeight());
	for(int i=0;i<(ofGetHeight()-80)/posSize;i+=2){
		ofSetColor(0,0,0);
		ofDrawBitmapString(ofToHex((int)(zeroAddress+totalPosInRow*i)),3,i*posSize+80+10);
		ofSetColor(200,200,200);
		ofLine(80,80+posSize*i,ofGetWidth(),80+posSize*i);
		ofLine(80,80+posSize*(i+1),ofGetWidth(),80+posSize*(i+1));
	}

	// the capacity of the vector is how much memory it has allocated
	// even if not all of it is used
	for(int i=0;i<theVector.capacity();i++){
		// use the offsets calculated before to make the vector move in the screen
		// according to it's position in memory
		long int intAddress = getIntRelAddress(&theVector[i]);
		int x = (((intAddress+offset)*posSize)%(ofGetWidth()-80))+80;
		int y = posSize*float(((intAddress+offset)*posSize)/(ofGetWidth()-80))+80;

		// the size of the vector is how much memory is actually used
		// lets draw them as filled squares
		if(i<theVector.size()){
			ofFill();
			ofSetColor(100,100,100);
			ofRect(x,y,posSize,posSize);
		}

		// the rest is memory that is not used yet
		// lets draw it as empty squares
		ofNoFill();
		ofSetColor(0,0,0);
		ofRect(x,y,posSize,posSize);
	}

	ofDrawBitmapString("init address: " + ofToHex((long int)&theVector[0]),20,40);
	ofDrawBitmapString("end address: " + ofToHex((long int)&theVector[theVector.capacity()-1]),20,60);




}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch(key){
	case 'p':
		theVector.push_back(ofRandom(0,10));
		if(theVector.size()==1) initAddress = &theVector[0];
		break;
	case 'e':
		theVector.erase(theVector.end()-1);
		break;
	case 'b':
		theVector.erase(theVector.begin());
		if(!eraseFromBeginShown){
			ofSystemAlertDialog("as you will see erasing from the beginning seems to erase actually from the end\n"
					"the vector is actually erasing from the beginning but moving everything to the first position\n"
					"which is slow. with vectors you should add and remove elements only at the end.\n"
					"if you need to do it also from the beginning use some other structure like a deque");
			eraseFromBeginShown=true;
		}
		break;
	case 'c':
		theVector.clear();
	}

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

