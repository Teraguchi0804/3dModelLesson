#include "ofApp.h"

float speed_x;
float speed_y;

float width;
float height;

bool rightWalk;
bool leftWalk;

int n = 0;




//--------------------------------------------------------------
void ofApp::setup(){
//    ofSetLogLevel(OF_LOG_VERBOSE); //ログレベルを取る(表示する)
    ofBackground(50, 0); //背景色設定：(int r, int g, int b, int a=255)
    
    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords. openGLでテクスチャ画像を使用するための準備的なやつ
    
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    light.enable(); //ライティングを有効に
    ofEnableSeparateSpecularLight();
    
//    pos.x = ofGetWidth()/2;
//    pos.y = ofGetHeight()/2;
    
    pos.x = 0;
    pos.y = 0;
    speed_x = 4;
    
    rightWalk = true;
    leftWalk = false;
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    gui.setup();

//    gui.add(camPosX.setup("camPosX", -2010, -3000, 3000));
//    gui.add(camPosY.setup("camPosY", 2070, -3000, 3000));
//    gui.add(camPosZ.setup("camPosZ", 1920, -3000, 3000));
    
    gui.add(camPosX.setup("camPosX", 1560, -3000, 3000));
    gui.add(camPosY.setup("camPosY", 1290, -3000, 3000));
    gui.add(camPosZ.setup("camPosZ", -2520, -3000, 3000));
    
    gui.add(lightPosX.setup("lightPosX", 2220, -3000, 3000));
    gui.add(lightPosY.setup("lightPosY", 2640, -3000, 3000));
    gui.add(lightPosZ.setup("lightPosZ", -1200, -3000, 3000));
    
    gui.add(lookAtX.setup("lookAtX", -224.25, -3000, 3000));
    gui.add(lookAtY.setup("lookAtY", -879, -3000, 3000));
    gui.add(lookAtZ.setup("lookAtZ", -102.75, -3000, 3000));
    
    gui.add(Camfov.setup("Camfov", 31, 0, 180));
    
    gui.add(modelY.setup("modelY", 385, -3000, 3000));
    
    
    gui.add(stageY.setup("stageY", 500, -3000, 3000));
    
    
    bAnimate = false;
    bAnimateMouse = false;
    animationPosition = 0;
    
    charactor.setScale(0.2, 0.2, 0.2);
    charactor.loadModel("anima01.dae", false); //モデルデータの読み込み、第2匹数はモデルを最適化(optimize)するかどうか
    charactor.setPosition(pos.x, pos.y+200, 0);
    charactor.setRotation(0, -90, 0, 1, 0);
    
    
    charactor.setLoopStateForAllAnimations(OF_LOOP_NORMAL); //modelのアニメーションフレームをループ
    charactor.playAllAnimations(); //modelのアニメーション開始
    
    stage.setScale(3.5, 3.5, 3.5);
    stage.loadModel("stage03.dae", false); //モデルデータの読み込み、第2匹数はモデルを最適化(optimize)するかどうか
    stage.setPosition(pos.x, pos.y+stageY, 0);
    cout<< "mesh_count:"<< stage.getNumMeshes() <<endl;
    stage.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    stage.playAllAnimations();
    
    if(!bAnimate) {
        charactor.setPausedForAllAnimations(true); //modelのアニメーションの一時停止(true or false)
        stage.setPausedForAllAnimations(true);
    }

    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    pos.x = pos.x + speed_x;
//    charactor.setRotation(0, -90, 0, 1, 0);
    
    //左端で跳ね返る
    if(pos.x < 0){
        if(!leftWalk){
            charactor.setRotation(0, -90, 0, 1, 0);
            leftWalk = true;
            rightWalk = true;
        }
        speed_x = speed_x * -1;
    }
    
    //右端で跳ね返る
    if(pos.x > ofGetWidth()){
        
        if(rightWalk){
            charactor.setRotation(0, 90, 0, 1, 0);
            rightWalk = false;
            leftWalk = false;
        }
        speed_x = speed_x * -1;
    }
    
    
    charactor.update(); //modelをアップデート
    stage.update();
    
    if(bAnimateMouse) {
        charactor.setPositionForAllAnimations(animationPosition);
        stage.setPositionForAllAnimations(animationPosition);
    }

    //mesh = charactor.getCurrentAnimatedMesh(0);
    //mesh = stage.getCurrentAnimatedMesh(0);

    
    light.setPosition(lightPosX, lightPosY, lightPosZ);
    
//    camera.setFov(30);
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
    
//    camera.setVFlip(true);
    
     //カメラ開始
  camera.begin();
        //stageModel描画
//    #ifndef TARGET_PROGRAMMABLE_GL
//        glShadeModel(GL_SMOOTH); //some model / light stuff
//    #endif
        light.enable();
        ofEnableSeparateSpecularLight();
    
        ofPushMatrix();
    
        camera.setVFlip(true);
//            ofScale(1, -1);
        ofRotateZ(180);
//            ofScale(1, -1, 1);
    
            stage.drawFaces();
        ofPopMatrix();
    
    
        //charactorModel描画
//    #ifndef TARGET_PROGRAMMABLE_GL
//        glShadeModel(GL_SMOOTH); //some model / light stuff
//    #endif
        light.enable();
        ofEnableSeparateSpecularLight();
        ofPushMatrix();
    
            ofScale(1, -1); //右手座標系へ変換
    
//            ofTranslate(charactor.getPosition().x+100, charactor.getPosition().y, 0);
//            ofRotate(-mouseX, 0, 1, 0); //マウスのX座標移動により回転
//            ofTranslate(-charactor.getPosition().x, -charactor.getPosition().y, 0);
    
            charactor.drawFaces(); //model描画実行
    
        ofPopMatrix();
    
    
    
//        ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0); //右手座標系に変換
//        ofScale(1, -1, 1); //右手座標系へ変換

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
    
    if(!bAnimate) {
        stage.setPausedForAllAnimations(true);
    }
    
   
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

