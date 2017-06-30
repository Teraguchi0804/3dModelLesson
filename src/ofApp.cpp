#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    
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
    
    bAnimate = false;
    bAnimateStage = true;
    animationPosition = 0;
    
    charactor.setScale(0.2, 0.2, 0.2);
    charactor.loadModel("anima01.dae", false); //モデルデータの読み込み、第2匹数はモデルを最適化(optimize)するかどうか
    charactor.setPosition(pos.x, pos.y+200, 0);
    charactor.setRotation(0, -90, 0, 1, 0);
    
    
    charactor.setLoopStateForAllAnimations(OF_LOOP_NORMAL); //modelのアニメーションフレームをループ
    charactor.playAllAnimations(); //modelのアニメーション開始
    
    stage.setScale(4.5, 4.5, 4.5);
    stage.loadModel("stage03.dae", false); //モデルデータの読み込み、第2匹数はモデルを最適化(optimize)するかどうか
    stage.setPosition(pos.x, pos.y+500, 0);
    
    stage.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    stage.playAllAnimations();
    
    if(!bAnimate) {
        charactor.setPausedForAllAnimations(false); //modelのアニメーションの一時停止(true or false)
    }
    
    if(bAnimateStage){
        stage.setPausedForAllAnimations(false);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(Walk){
        pos.x = pos.x + speed_x;
    }
    
    //右端で跳ね返る
    if(pos.x <= -700){
        Walk = false;
        if(!Walk){
            aac += 0.05;
            float t = ofClamp(aac, 0, 1);
            float v = ofxEasingFunc::Cubic::easeInOut(t); // all functions take input 0. ~ 1., and outputs 0. ~ 1.
            charactor.setRotation(0, -90 * v, 0, 1, 0);
            if(v >= 1){
                aac = 0;
                Walk = true;
                speed_x = speed_x * -1;
            }
        }
    }
    
    //左端で跳ね返る
    if(pos.x >= 500){
        Walk = false;
        if(!Walk){
            aac += 0.05;
            float t = ofClamp(aac, 0, 1);
            float v = ofxEasingFunc::Cubic::easeInOut(t); // all functions take input 0. ~ 1., and outputs 0. ~ 1.
            charactor.setRotation(0, 90 * v, 0, 1, 0);
            if(v >= 1){
                aac = 0;
                Walk = true;
                speed_x = speed_x * -1;
            };
        }
    }
    
    
    charactor.update(); //modelをアップデート
    stage.update();

    light.setPosition(2285.25, 2361, -2148.75);
    
    camera.setupPerspective(false, 19, 2.0, 10000.0);
    camera.setPosition(2665.25, 2533.25, -2947.5);
    camera.lookAt(ofVec3f(231.5, -414, -423.75));
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    
   

    ofSetColor(255); //塗りの色を設定
    ofEnableBlendMode(OF_BLENDMODE_ALPHA); //ブレンドモードの定義
    ofEnableDepthTest(); //深度テストを有効にする関数
    charactor.setPosition(pos.z, pos.y+385, pos.x);
    
    
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

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofPoint modelPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75);
    switch (key) {
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
    
    mesh = stage.getMesh(0);
    stage.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    stage.playAllAnimations();
   
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
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
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

