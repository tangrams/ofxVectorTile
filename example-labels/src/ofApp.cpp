#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    light.setDiffuseColor(ofFloatColor(0.9));
    light.setPosition(ofPoint(0,0,100));
    
    //  Load Label Fonts
    //
    labels.loadFont("Champagne & Limousines.ttf", 10);
    labels.setFontColor(ofFloatColor(1.0), ofFloatColor(0.0));
    
    //  Link the label manager with the builder
    //
    builder.setLabelManager(&labels);
    
    //  Request a new tile to the builder
    //
    tile = builder.getFromWeb(19299,24631,16);
    
    //  Make a VBO from the tile (FASTER)
    //
    tileMesh = tile.getMesh();
    
    fbo.allocate(ofGetWidth(),ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
    labels.updateCameraPosition(cam.getPosition());
    
    //  Update the scene
    //
    fbo.begin();
    ofClear(0,0,0,0);
    cam.begin();
    ofEnableDepthTest();
    
    ofEnableLighting();
    light.enable();
    
    //    tile.draw();
    tileMesh.draw();
    
    light.disable();
    ofDisableLighting();
    
    labels.draw3D();
    labels.updateProjection();
    
    ofDisableDepthTest();
    cam.end();
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::gray,ofColor::black);
    
    ofSetColor(255);
    fbo.draw(0,0);
    
    labels.draw2D();
    
    ofDrawBitmapString(" 'p' : toogle point labels debug", 10,15);
    ofDrawBitmapString(" 'l' : toogle line labels debug", 10,35);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == 'f'){
        ofToggleFullscreen();
    } else if (key == 'p'){
        labels.bDebugPoints = !labels.bDebugPoints;
    } else if (key == 'l'){
        labels.bDebugLines = !labels.bDebugLines;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
void ofApp::windowResized(int w, int h){
    fbo.allocate(w,h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
