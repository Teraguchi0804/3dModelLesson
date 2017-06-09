#include "ofApp.h"

float speed_x;
float speed_y;

bool isWalkRight;
bool isWalkLeft;


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE); //ログレベルを取る(表示する)
    ofBackground(50, 0); //背景色設定：(int r, int g, int b, int a=255)
    
    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords. openGLでテクスチャ画像を使用するための準備的なやつ
    
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    isWalkRight = false;
    isWalkLeft = true;
    
    pos.x = ofGetWidth()/2;
    pos.y = ofGetHeight()/2;
    speed_x = 4;
    
    
    gui.setup();

    gui.add(camPosX.setup("camPosX", 0, 0, 3000));
    gui.add(camPosY.setup("camPosY", 375, 0, 3000));
    gui.add(camPosZ.setup("camPosZ", 0, 0, 3000));
    
    gui.add(modelX.setup("modelX", 750, -3000, 3000));
    gui.add(modelY.setup("modelY", -480, -3000, 3000));
//    gui.add(modelZ.setup("modelZ", 0, -3000, 3000));
    
    
    
    
    bAnimate = false;
    bAnimateMouse = false;
    animationPosition = 0;
    
    charactor.setScale(0.5, 0.5, 0.5);
//    charactor.loadModel("astroBoy_walk.dae", false); //モデルデータの読み込み、第2匹数はモデルを最適化(optimize)するかどうか
    charactor.loadModel("charactor.obj", false);
    
    
    charactor.setPosition(pos.x, pos.y, 0);
    
//    charactor.setLoopStateForAllAnimations(OF_LOOP_NORMAL); //modelのアニメーションフレームをループ
//    charactor.playAllAnimations(); //modelのアニメーション開始
//    if(!bAnimate) {
//        charactor.setPausedForAllAnimations(true); //modelのアニメーションの一時停止(true or false)
//    }
//
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    pos.x = pos.x + speed_x;
    
    //左端で跳ね返る
    if(pos.x < 0){
        speed_x = speed_x * -1;
    }
    
    //右端で跳ね返る
    if(pos.x > ofGetWidth()){
        speed_x = speed_x * -1;
    }
    
    
    charactor.update(); //modelをアップデート
    
//    if(bAnimateMouse) {
//        charactor.setPositionForAllAnimations(animationPosition);
//    }
//    
    mesh = charactor.getCurrentAnimatedMesh(0);

    
//    charactor.setPosition(pos.x, pos.y+modelY, 0);
    
    
//    camera.setPosition(100, 100, 100);
//    camera.lookAt(ofVec3f(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0));
    camera.setPosition(camPosX, camPosY, camPosZ);
    camera.lookAt(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0));
    
    
//    camera.setPosition(200*cos(ofGetElapsedTimef()*2), 0, 200*sin(ofGetElapsedTimef()*2)); //タイムを取得して更新

    
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    
        ofSetColor(255); //塗りの色を設定
    
        ofEnableBlendMode(OF_BLENDMODE_ALPHA); //ブレンドモードの定義
    
        ofEnableDepthTest(); //深度テストを有効にする関数
    
    charactor.setPosition(pos.z+modelX, pos.y+modelY, pos.x);
    
//    ofDrawCircle(pos.x, pos.y, 40);
    camera.begin(); //カメラ開始
    
    
        //mdoelの顔部分
    #ifndef TARGET_PROGRAMMABLE_GL
        glShadeModel(GL_SMOOTH); //some model / light stuff
    #endif
        light.enable(); //ライティングを有効に
        ofEnableSeparateSpecularLight();
    
        ofPushMatrix(); //ofPushMatrix〜ofPopMatrixで囲まれた範囲内は外部の座標系に影響しない
    
//            ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
            ofScale(1, -1); //右手座標系へ変換
//            ofTranslate(model.getPosition().x+100, model.getPosition().y, 0);
                ofTranslate(charactor.getPosition().x, charactor.getPosition().y, 0);
//            ofRotate(-mouseX, 0, 1, 0); //マウスのX座標移動により回転
//            ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
    
            charactor.drawFaces(); //modelの顔を描画
    
        ofPopMatrix();
    
    
    
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0); //右手座標系に変換
            ofScale(1, -1, 1); //右手座標系へ変換

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
            ofBackground(0, 0);
            break;
        case 's':
            ofBackground(50, 0);
            break;
        case 'p':
            ofPushMatrix();
            ofTranslate(charactor.getPosition().x+500, charactor.getPosition().y, 0);
            charactor.drawFaces();
            ofPopMatrix();
            break;
//        case 'c':
//            //  何かキーを押したらスタート
//            isStart = true;
//            break;
        case ' ':
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
    
//    mesh_stage = model_stage.getMesh(0);
//    model_stage.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
//    model_stage.playAllAnimations();
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

