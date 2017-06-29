#include "ofApp.h"

float speed_x;
float speed_y;

float width;
float height;

bool Walk;

float aac = 0;

//--------------------------------------------------------------
void ofApp::setup(){
//    ofSetLogLevel(OF_LOG_VERBOSE); //ログレベルを取る(表示する)
    ofBackground(50, 0); //背景色設定：(int r, int g, int b, int a=255)
    
    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords. openGLでテクスチャ画像を使用するための準備的なやつ
    
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    light.enable(); //ライティングを有効に
    ofEnableSeparateSpecularLight();
    
    pos.x = 0;
    pos.y = 0;
    speed_x = 4;
    
    Walk = true;
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    gui.setup();
    
    gui.add(camPosX.setup("camPosX", 2665.25, -5000, 5000));
    gui.add(camPosY.setup("camPosY", 2533.25, -5000, 5000));
    gui.add(camPosZ.setup("camPosZ", -2947.5, -5000, 5000));
    
    gui.add(lightPosX.setup("lightPosX", 2285.25, -3000, 3000));
    gui.add(lightPosY.setup("lightPosY", 2361, -3000, 3000));
    gui.add(lightPosZ.setup("lightPosZ", -2148.75, -3000, 3000));
    
    gui.add(lookAtX.setup("lookAtX", 231.5, -3000, 3000));
    gui.add(lookAtY.setup("lookAtY", -414, -3000, 3000));
    gui.add(lookAtZ.setup("lookAtZ", -423.75, -3000, 3000));
    
    gui.add(Camfov.setup("Camfov", 19, 0, 180));
    
    gui.add(modelY.setup("modelY", 385, -3000, 3000));
    
    
    gui.add(stageY.setup("stageY", 500, -3000, 3000));
    
    
    bAnimate = false;
    bAnimateStage = true;
    bAnimateMouse = false;
    animationPosition = 0;
    
    charactor.setScale(0.2, 0.2, 0.2);
    charactor.loadModel("anima01.dae", false); //モデルデータの読み込み、第2匹数はモデルを最適化(optimize)するかどうか
    charactor.setPosition(pos.x, pos.y+200, 0);
    charactor.setRotation(0, -90, 0, 1, 0);
    
    
    charactor.setLoopStateForAllAnimations(OF_LOOP_NORMAL); //modelのアニメーションフレームをループ
    charactor.playAllAnimations(); //modelのアニメーション開始
    
    stage.setScale(4.5, 4.5, 4.5);
    stage.loadModel("stage03.dae", false); //モデルデータの読み込み、第2匹数はモデルを最適化(optimize)するかどうか
    stage.setPosition(pos.x, pos.y+stageY, 0);
//    cout<< "mesh_count:"<< stage.getNumMeshes() <<endl;
    stage.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    stage.playAllAnimations();
    
    if(!bAnimate) {
        charactor.setPausedForAllAnimations(false); //modelのアニメーションの一時停止(true or false)
    }
    
    if(bAnimateStage){
        stage.setPausedForAllAnimations(false);
    }

    timerEnd = false;
//    startTime = ofGetElapsedTimef();
    
}

//--------------------------------------------------------------
void ofApp::update(){

    
//    float t = ofClamp(ofGetElapsedTimef() / 2., 0, 1);
    // all functions take input 0. ~ 1., and outputs 0. ~ 1.
//    float v = ofxEasingFunc::Cubic::easeInOut(t);
    
//    if(Walk){
        pos.x = pos.x + speed_x;
//    }
    
    
    
    //右端で跳ね返る
    if(pos.x == -700){
        Walk = false;
        if(!Walk){
            aac += 0.05;
            float t = ofClamp(aac, 0, 1);
            // all functions take input 0. ~ 1., and outputs 0. ~ 1.
            float v = ofxEasingFunc::Cubic::easeInOut(t);
            
            charactor.setRotation(0, -90 * v, 0, 1, 0);
            if(v >= 1){
                aac = 0;
                Walk = true;
            }
        }
//        speed_x = speed_x * -1;

    }
    
    //左端で跳ね返る
//    if(pos.x > ofGetWidth()){
    if(pos.x == 500){
//        Walk = false;
//        if(!Walk){
            charactor.setRotation(0, 90, 0, 1, 0);
//        }
        speed_x = speed_x * -1;
    }
    
    
    charactor.update(); //modelをアップデート
    stage.update();

    //mesh = charactor.getCurrentAnimatedMesh(0);
    //mesh = stage.getCurrentAnimatedMesh(0);

    
    light.setPosition(lightPosX, lightPosY, lightPosZ);
    
    camera.setupPerspective(false, Camfov, 2.0, 10000.0);
    camera.setPosition(camPosX, camPosY, camPosZ);
    camera.lookAt(ofVec3f(lookAtX, lookAtY, lookAtZ));
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    
   

    ofSetColor(255); //塗りの色を設定
    ofEnableBlendMode(OF_BLENDMODE_ALPHA); //ブレンドモードの定義
    ofEnableDepthTest(); //深度テストを有効にする関数
    
    charactor.setPosition(pos.z+modelX, pos.y+modelY, pos.x);
    
   
    
     //カメラ開始
  camera.begin();

    
        //stageModel描画
    #ifndef TARGET_PROGRAMMABLE_GL
        glShadeModel(GL_SMOOTH); //some model / light stuff
    #endif
        light.enable();
        ofEnableSeparateSpecularLight();
    
        ofPushMatrix();
    
        camera.setVFlip(true);
        ofRotateZ(180);
    
            stage.drawFaces();
        ofPopMatrix();
    
    
        //charactorModel描画
    #ifndef TARGET_PROGRAMMABLE_GL
        glShadeModel(GL_SMOOTH); //some model / light stuff
    #endif
        light.enable();
        ofEnableSeparateSpecularLight();
        ofPushMatrix();
    
            ofScale(1, -1); //右手座標系へ変換
            charactor.drawFaces(); //model描画実行
    
        ofPopMatrix();

        ofDisableDepthTest(); // 深度テストを無効に
        light.disable(); // ライティングを無効に
        ofDisableLighting();
        ofDisableSeparateSpecularLight();
    
        //塗り色を黒に
        ofSetColor(255, 255, 255 );
    

    camera.end(); //カメラ終了
    
    
    //ログの表示
    ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate(), 2), 10, 15);
    ofDrawBitmapString("keys 1-5 load models, spacebar to trigger animation", 10, 30);
    ofDrawBitmapString("drag to control animation with mouseY", 10, 45);
    ofDrawBitmapString("num animations for this model: " + ofToString(charactor.getAnimationCount()), 10, 60);
    ofDrawBitmapString("pos.x: "+ofToString(pos.x), 10, 75);
    ofDrawBitmapString("pos.y: "+ofToString(pos.y), 10, 90);
    
    gui.draw(); //GUIを描画

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofPoint modelPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75);
    switch (key) { //キーにより読み込むmodelをスイッチ
        case '1':
            charactor.loadModel("astroBoy_walk.dae");
            charactor.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            charactor.setRotation(0, -90, 0, 1, 0);
            ofEnableSeparateSpecularLight();
            break;
        case '2':
            charactor.loadModel("TurbochiFromXSI.dae");
            charactor.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            charactor.setRotation(0, -180, 1, 0, 0);
            ofEnableSeparateSpecularLight();
            break;
        case '3':
            charactor.loadModel("dwarf.x");
            charactor.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            ofDisableSeparateSpecularLight();
            break;
        case '4':
            charactor.loadModel("monster-animated-character-X.X");
            charactor.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            charactor.setRotation(0, -90, 0, 0, 1);
            ofDisableSeparateSpecularLight();
            break;
        case '5':
            charactor.loadModel("squirrel/NewSquirrel.3ds");
            charactor.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
            ofDisableSeparateSpecularLight();
            break;
        case 'a':
            bAnimate = !bAnimate;
            break;
        default:
            break;
    }
    
    mesh = charactor.getMesh(0);
    charactor.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    charactor.playAllAnimations();
    if(!bAnimate) {
        charactor.setPausedForAllAnimations(true);
    }
//    if(key == ' '){
//        n++;
//    }
    
    mesh = stage.getMesh(0);
    stage.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    stage.playAllAnimations();
    
//    if(!bAnimate) {
//        stage.setPausedForAllAnimations(true);
//    }
    
   
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case 'a':
            ofBackground(50, 0);
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // scrub through aninations manually.
    animationPosition = y / (float)ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // pause all animations, so we can scrub through them manually.
    charactor.setPausedForAllAnimations(true);
    animationPosition = y / (float)ofGetHeight();
    bAnimateMouse = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    // unpause animations when finished scrubbing.
    if(bAnimate) {
        charactor.setPausedForAllAnimations(false);
    }
    bAnimateMouse = false;
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

