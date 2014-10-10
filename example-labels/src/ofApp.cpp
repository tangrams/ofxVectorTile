#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    
    light.setDiffuseColor(ofFloatColor(0.9));
    light.setPosition(ofPoint(0,0,100));
    
    font.loadFont(ofToDataPath("Champagne & Limousines.ttf"), 10);
    labels.setFont(&font);
    builder.setLabelManager(&labels);
    
    builder.setOffset(19299,24631,16);
    glmMesh mesh = builder.getFromWeb(19299,24631,16).getMesh();
    tileMesh = toOf(mesh);
}

//--------------------------------------------------------------
void ofApp::update(){
    labels.updateCameraPosition( toGlm(cam.getPosition()) );
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    cam.begin();
    light.enable();
    ofEnableLighting();
    
    tileMesh.draw();
    labels.draw3D();
    labels.updateProjection();
    
    ofDisableLighting();
    light.disable();
    cam.end();
    
    labels.draw2D();

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
