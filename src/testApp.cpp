#include "testApp.h"
//--------------------------------------------------------------
void testApp::setup(){
    
    w = ofGetWidth();
    h = ofGetWidth();
    
    fontSize = h/5;
    cout<<"fontsize = "<<fontSize<<"\n";
    
    
    dotFont.loadFont("LL_DOT__.TTF", fontSize,true,true,true);
    //code for grabbing center points of dots in font
    
    testChar = testFont.getCharacterAsPoints(letter);
    for(int i = 0; i<testChar.getSubPaths().size(); i++){
        ofSubPath sp = testChar.getSubPaths()[i];
        ofPoint p1 = sp.getCommands()[3].cp1;
        ofCircle(p1.x+100, p1.y+200, 3);
        //cout<<"point "<<i<<"="<<p1<<"\n ";
    }
    //dotFont.
    ofSetFrameRate(150);
    int nodeTot = 0;
    int nFiles = dir.listDir("photos");
    numPhotos = dir.numFiles();
    
    cout<<"Num Photos: "<<numPhotos<<"\n";
    dims.x = 427/4;  //define standard size of image
    dims.y = 640/4;
    easeDef = 6;
    scale = 1;
    tScale =scale;
    
    textScale = .25;
    
    translate = ofVec2f(0,0);
    
    ofSetCircleResolution(100);
   gridX = ofGetWidth()/dims.x*4;
    gridY = ofGetHeight()/dims.y*4;
    
   // gridX= 10;
   // gridY=10;
    
    numDisplay = gridX * gridY;
   // cout<<"numDisplay: "<<numDisplay;
    //load photos from directory into photos vector
    if(nFiles) {
        for(int i=0; i<numPhotos; i++) {
            // add the image to the vector
            string filePath = dir.getPath(i);
            images.push_back(ofImage());
            images.back().loadImage(filePath);
        }
        
       // cout<<"images size"<<images.size()<<"\n";
        
        //resize photos
        for(int i=0; i<numPhotos; i++) {
            images[i].resize(dims.x,dims.y);
            
        }
        
        
        //load images into scPhoto objects
        for(int i=0; i <numDisplay; i++){
            ofVec2f v =ofVec2f(0,0);
            scPhoto p;
           scPhotos.push_back(p);
           // cout<<"scPhotos size "<<scPhotos.size()<<"\n";
            
           scPhotos[i].init(images[ofRandom(images.size())], v, dims);
        }
        
        for(int y = 0; y< gridY; y++){
            for(int x = 0; x< gridX; x++){
                int index = y*gridX+x;
                
                scPhotos[index].process();
                
                
            }
        }
      
    }

}

//--------------------------------------------------------------
void testApp::update(){
        
    for(int i = 0; i<numDisplay;i++){
        scPhotos[i].update();
    }
    
    }

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(255, 255, 255);
    
    ofFill();
    ofPushMatrix();
    ofScale(scale,scale);
    ofTranslate(translate.x, translate.y);
    
    
    
    for(int i=0; i<scPhotos.size(); i++){
      scPhotos[i].draw();
        
    }
    
     //ofPopMatrix();
    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key == 'a'){
        int rand = ofRandom(numDisplay);
        scPhotos[rand].fade = !scPhotos[rand].fade;
    }
       
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    if(key == 'g'){
        formGrid();
    }
    
    if(key == 'l'){
    
        formLetters();
    }
    
    
    if(key=='r'){
    for(int i = 0; i<numDisplay; i++){
        //cout<<"t shape = "<<tShape<<", shape = "<<shape<<"\n";
        scPhotos[i].shapeTrans("rect");
       // scPhotos[i].process();
    }
    }
    
    if(key=='c'){
        for(int i = 0; i<numDisplay; i++){
            scPhotos[i].shapeTrans("circ");
           // scPhotos[i].process();
        }
    }
    
    
    if(key=='='){
        scale+= .1;

    }
    if(key=='-'){
        scale-= .1;
        
    }

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    //scale+= (y-pMousePos.y)/100;
    translate.x+=(x-pMousePos.x);
    translate.y+=(y-pMousePos.y);
    
    pMousePos= ofVec2f(x,y);
    
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    pMousePos = ofVec2f(x,y);
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    for(int i = 0; i<numDisplay-1; i++){
        
    }
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


void testApp::formGrid(){

    for(int y = 0; y< gridY; y++){
        for(int x = 0; x< gridX; x++){
            int index = y*gridX+x;
             scPhotos[index].fade = false;
             scPhotos[index].tPos = ofVec2f(x* dims.y,y* dims.y);
             scPhotos[index].shapeTrans("rect");
         }
    }
}


int testApp::randNeg(){
    int mult = ofRandom(-2,2);
    if(mult>0){
        return 1;
    }
    if(mult<=0)
    {        return -1;
    }
}


void testApp::formLetters(){
    stringPoints = dotFont.getStringAsPoints("StoryCorps");
    //loop through the vector of characters form our string
    
    int totalPoints = 0;
       
    for(int i = 0; i<stringPoints.size(); i++){
        //now loop through each chars and get the subpaths
        for(int j = 0; j<stringPoints[i].getSubPaths().size(); j++){
            ofSubPath sp = stringPoints[i].getSubPaths()[j];
            ofPoint p1 = sp.getCommands()[3].cp1;
            //ofCircle(p1.x+100, p1.y+700, 3);
            scPhotos[totalPoints].tPos = ofVec2f(p1.x+w/10,p1.y+fontSize);
            scPhotos[totalPoints].shapeTrans("circ");
            scPhotos[totalPoints].tTextScale = 30/fontSize;
            
            cout<<"tScale= "<< scPhotos[1].tTextScale<<"\n ";
            //scPhotos[totalPoints].tTextScale = .3;
            
            cout<<"totalPoints"<<index<<"\n";
               totalPoints+=1;
        }
    }

   // cout<<"total point: "<<totalPoints<<"\n";
   
    
    for(int p = totalPoints; p<scPhotos.size(); p++){
        
       // scPhotos[p].tPos = ofVec2f(randNeg()*ofRandom(2000,8000),ofRandom(-9000,9000));
      
        scPhotos[p].fade = true;
          
    }
    
    
}