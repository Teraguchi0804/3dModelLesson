#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"

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
    
    ofVec3f pos;
    
    ofxAssimpModelLoader charactor; //Addonの初期化
    ofxAssimpModelLoader stage; //Addonの初期化
    
    bool bAnimate;
    bool bAnimateMouse;
    float animationPosition;
    
    ofMesh mesh;
    ofLight	light;
    ofCamera camera;
    ofxPanel gui;
    
    ofxFloatSlider objPosX;
    ofxFloatSlider objPosY;
    ofxFloatSlider objPosZ;
    
    ofxFloatSlider camPosX;
    ofxFloatSlider camPosY;
    ofxFloatSlider camPosZ;
    
    ofxFloatSlider modelX;
    ofxFloatSlider modelY;
//    ofxFloatSlider modelZ;
};

#endif
