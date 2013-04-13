#pragma once
#include "ofMain.h"
#include "scPhoto.h"
#include "scFont.h"
#include <iostream>
class testApp : public ofBaseApp{

	public:
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
    
    
    ofVec2f mousePressLoc;
    ofVec2f pMousePos;
    
    int randNeg();
    float fontSize;
    ofVec2f translate;
    
    int w;
    int h;
    
    void formLetters();
    void formGrid();
    
    ofDirectory dir;
    vector<ofImage> images;
    vector<scPhoto> scPhotos;
    vector<ofTTFCharacter> stringPoints;
    ofImage     clip;
    
    ofTrueTypeFont dotFont;
    ofTrueTypeFont testFont;
    ofTTFCharacter testChar;
    char letter;
    
    float scale;
    float tScale;
    
    float textScale;  //scaling size of photo dots to cleanly form letters
    
    
    int nodeTot;
    int rX, rY;
    int gridX, gridY;
    

    
    ofVec2f dims;
    //int photoW;
    //int photoH;
    int numPhotos;
    int numDisplay;
    float easeDef;
    
    node n;
    scFont f;

};
