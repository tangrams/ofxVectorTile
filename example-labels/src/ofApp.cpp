#include "ofApp.h"

#include "ofxGlm.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    
    light.setDiffuseColor(ofFloatColor(0.9));
    light.setPosition(ofPoint(0,0,100));
    
    labels.loadFont("Champagne & Limousines.ttf", 10);
    builder.setLabelManager(&labels);
    
//    tileMesh = builder.get(19299,24631,16);
    
//    tile.load(19299,24631,16);
//    builder.loadTo(19299,24631,16, tile);
    tile = builder.getFromWeb(19299,24631,16);
}

//--------------------------------------------------------------
void ofApp::update(){
//    labels.updateCameraPosition(cam.getPosition());
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    cam.begin();
    light.enable();
    ofEnableLighting();
    
    tile.draw();
//    tileMesh.draw();
//    labels.draw3D();
//    labels.updateProjection();
    
    ofDisableLighting();
    light.disable();
    cam.end();
    
//    labels.draw2D();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
