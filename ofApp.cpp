#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
	
	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

	for (int i = 0; i < 300; i++) {

		auto location = glm::vec3(
			ofMap(ofNoise(noise_seed.x, (i + ofGetFrameNum()) * 0.01), 0, 1, -500, 500),
			ofMap(ofNoise(noise_seed.y, (i + ofGetFrameNum()) * 0.01), 0, 1, -500, 500),
			ofMap(ofNoise(noise_seed.z, (i + ofGetFrameNum()) * 0.01), 0, 1, -500, 500));

		vector<glm::vec3> vertices;
		vertices.push_back(location + glm::vec3(-20, -20, 0));
		vertices.push_back(location + glm::vec3( 20, -20, 0));
		vertices.push_back(location + glm::vec3( 20,  20, 0));
		vertices.push_back(location + glm::vec3(-20,  20, 0));

		int face_index = this->face.getNumVertices() - vertices.size();
		int frame_index = this->frame.getNumVertices() - vertices.size();

		this->face.addVertices(vertices);		
		if (face_index >= 0) {

			this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 1); this->face.addIndex(face_index + 5);
			this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 5); this->face.addIndex(face_index + 4);

			this->face.addIndex(face_index + 3); this->face.addIndex(face_index + 2); this->face.addIndex(face_index + 6);
			this->face.addIndex(face_index + 3); this->face.addIndex(face_index + 6); this->face.addIndex(face_index + 7);

			this->face.addIndex(face_index + 1); this->face.addIndex(face_index + 2); this->face.addIndex(face_index + 6);
			this->face.addIndex(face_index + 1); this->face.addIndex(face_index + 6); this->face.addIndex(face_index + 5);

			this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 3); this->face.addIndex(face_index + 7);
			this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 7); this->face.addIndex(face_index + 4);
		}

		this->frame.addVertices(vertices);
		if (frame_index > 0) {

			this->frame.addIndex(frame_index + 0); this->frame.addIndex(frame_index + 4);
			this->frame.addIndex(frame_index + 1); this->frame.addIndex(frame_index + 5);
			this->frame.addIndex(frame_index + 2); this->frame.addIndex(frame_index + 6);
			this->frame.addIndex(frame_index + 3); this->frame.addIndex(frame_index + 7);
		}
	}

	this->face.addIndex(0); this->face.addIndex(1); this->face.addIndex(2);
	this->face.addIndex(0); this->face.addIndex(2); this->face.addIndex(3);

	this->frame.addIndex(0); this->frame.addIndex(1);
	this->frame.addIndex(1); this->frame.addIndex(2);
	this->frame.addIndex(2); this->frame.addIndex(3);
	this->frame.addIndex(3); this->frame.addIndex(0);

	int face_index = this->face.getNumVertices() - 4;
	int frame_index = this->frame.getNumVertices() - 4;

	this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 1); this->face.addIndex(face_index + 2);
	this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 2); this->face.addIndex(face_index + 3);

	this->frame.addIndex(frame_index + 0); this->frame.addIndex(frame_index + 1);
	this->frame.addIndex(frame_index + 1); this->frame.addIndex(frame_index + 2);
	this->frame.addIndex(frame_index + 2); this->frame.addIndex(frame_index + 3);
	this->frame.addIndex(frame_index + 3); this->frame.addIndex(frame_index + 0);
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	auto target = this->face.getVertex(this->face.getNumVertices() - 1);
	auto camera_location = this->face.getVertex(0) + glm::vec3(0, 0, 660);

	this->cam.setPosition(camera_location);
	this->cam.setTarget(target);
	this->cam.lookAt(target);

	this->cam.begin();

	ofSetColor(39);
	this->face.drawFaces();

	ofSetColor(255);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}