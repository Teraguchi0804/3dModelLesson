#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "ofxEasingFunc.h"

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
    bool bAnimateStage;
    float animationPosition;
    
    float speed_x;
    float speed_y;
    
    float width;
    float height;
    
    bool Walk;
    float aac = 0;
    
    ofMesh mesh;
    ofLight	light;
    ofCamera camera;
};

#endif
