#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofNoFill();

	this->radius = 320;
	ofColor color;
	for (int i = 0; i < 15; i++) {

		for (int deg = 0; deg < 360; deg += 1) {

			auto location = glm::vec2(this->radius * cos(deg * DEG_TO_RAD), this->radius * sin(deg * DEG_TO_RAD));
			this->base_location_list.push_back(location);

			color.setHsb(ofMap(i, 0, 15, 0, 255), 255, 255, 100);
			this->color_list.push_back(color);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->log_list.clear();

	for (int i = 0; i < this->base_location_list.size(); i++) {

		vector<glm::vec2> log;
		log.push_back(this->base_location_list[i]);
		this->log_list.push_back(log);
	}

	int step = 5;
	for (int i = 0; i < this->log_list.size(); i++) {

		int k = 0;
		while (true) {

			auto deg = ofMap(ofNoise(glm::vec4(this->color_list[i].getHue() * 0.005, this->log_list[i].back() * 0.0005, ofGetFrameNum() * 0.01 + k * 0.003)), 0, 1, -90, 90);
			auto next = this->log_list[i].back() + glm::vec2(step * cos(deg * DEG_TO_RAD), step * sin(deg * DEG_TO_RAD));

			if (glm::distance(glm::vec2(0, 0), next) < this->radius) {

				this->log_list[i].push_back(next);
			}
			else {

				break;
			}

			k++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (int i = 0; i < this->log_list.size(); i++) {

		ofRotate(2);

		if (glm::distance(this->log_list[i][0], this->log_list[i][this->log_list[i].size() - 1]) > this->radius * 1.25) {

			continue;
		}

		ofSetColor(this->color_list[i]);

		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();
	}

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}