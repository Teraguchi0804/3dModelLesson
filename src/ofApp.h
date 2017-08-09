#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
//#include "ofxEasingFunc.h"

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
    ofxAssimpModelLoader charactor;
    ofxAssimpModelLoader stage;
    
    bool bAnimate;
    bool bAnimateStage;
    float animationPosition;
    
    ofxPanel gui;
    ofxFloatSlider camPosX;
    ofxFloatSlider camPosY;
    ofxFloatSlider camPosZ;
    ofxFloatSlider lightPosX;
    ofxFloatSlider lightPosY;
    ofxFloatSlider lightPosZ;
    ofxFloatSlider lookAtX;
    ofxFloatSlider lookAtY;
    ofxFloatSlider lookAtZ;
    ofxFloatSlider Camfov;
    ofxFloatSlider CamNear;
    ofxFloatSlider modelY;
    ofxFloatSlider stageY;
    
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

namespace ofxEasingFunc
{
    struct Cubic
    {
        inline static float easeIn(const float t)
        {
            return t * t * t;
        }
        
        inline static float easeInOut(const float t)
        {
            return (t < 0.5) ? easeIn(t * 2.0) * 0.5 : 1 - easeIn(2.0 - t * 2.0) * 0.5;
        }
    };
}


#endif
