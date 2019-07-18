#include "ofApp.h"

#define BALL_RADIUS 10
#define BALL_SPEED 10
#define BRICK_COL 16
#define BRICK_ROW 6
#define BRICK_WIDTH 64
#define BRICK_HEIGHT 40
#define BAR_Y_POS 40
#define BAR_WIDTH 150
#define BAR_HEIGHT 10
#define BULLET_NUM 300
#define BULLET_SPEED 10

int bricks[BRICK_ROW][BRICK_COL];
int ball_X, ball_Y;
int dir_X, dir_Y;
int bar_X;

struct bulletType {
	int x;
	int y;
	int visible;
};
struct bulletType bullet[BULLET_NUM];

void updateBullet();

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("Arkanoid");
	ofSetWindowShape(1024, 768);
	ofSetFrameRate(60);
	ofBackground(ofColor::white);
	ofSetColor(ofColor::black);
	ofSetLineWidth(1.0);
	ofFill();

	ball_X = ofGetWidth() / 2;
	ball_Y = ofGetHeight() - BAR_HEIGHT;
	dir_X = dir_Y = -BALL_SPEED;

	bar_X = ofGetWidth() / 2;

	// initialize bricks by 1
	for (int i = 0; i < BRICK_ROW; i++) {
		for (int j = 0; j < BRICK_COL; j++) {
			bricks[i][j] = 1;
		}
	}

	// initialize bullets by 0
	for (int i = 0; i < BULLET_NUM; i++) {
		bullet[i].x = 0;
		bullet[i].y = 0;
		bullet[i].visible = 0;
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ball_X += dir_X;
	ball_Y += dir_Y;

	bar_X = ofGetMouseX();

	// collision check between ball and brick
	if (ball_Y < (BRICK_HEIGHT*BRICK_ROW + BALL_RADIUS) &&
		bricks[ball_Y / BRICK_HEIGHT][ball_X / BRICK_WIDTH] == 1) {
		bricks[ball_Y / BRICK_HEIGHT][ball_X / BRICK_WIDTH] = 0;
		dir_Y *= -1;
	}

	// collision check between ball and wall
	if (ball_X < BALL_RADIUS || ball_X > ofGetWidth() - BALL_RADIUS) {
		dir_X *= -1;
	}
	if (ball_Y < BALL_RADIUS) {
		dir_Y *= -1;
	}
	// collision check between ball and bar
	if (ball_Y > ofGetHeight() - BAR_Y_POS - BALL_RADIUS) {
		if (ball_X >= bar_X - (BAR_WIDTH / 2) && ball_X <= bar_X + (BAR_WIDTH / 2)) {
			dir_Y *= -1;
		}
		else if (ball_Y > ofGetHeight() - BALL_RADIUS) {
			dir_X = dir_Y = 0;
		}
	}

	updateBullet();
}

//--------------------------------------------------------------
void ofApp::draw() {

	// draw bricks
	for (int i = 0; i < BRICK_ROW; i++) {
		for (int j = 0; j < BRICK_COL; j++) {
			if (bricks[i][j] == 1) {
				switch (i) {
				case 0: ofSetColor(ofColor::red); break;
				case 1: ofSetColor(ofColor::orange); break;
				case 2: ofSetColor(ofColor::yellow); break;
				case 3: ofSetColor(ofColor::green); break;
				case 4: ofSetColor(ofColor::blue); break;
				case 5: ofSetColor(ofColor::purple); break;
				default: ofSetColor(ofColor::black); break;
				}
			}
			else {
				ofSetColor(ofColor::white);
			}
			ofRect(j*BRICK_WIDTH, i*BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT);
		}
	}
	ofSetColor(ofColor::black);

	// draw ball
	ofCircle(ball_X, ball_Y, BALL_RADIUS);
	// draw bar
	ofRect(bar_X - (BAR_WIDTH / 2), ofGetHeight() - BAR_Y_POS, BAR_WIDTH, BAR_HEIGHT);
	// draw bullet
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet[i].visible) {
			ofCircle(bullet[i].x, bullet[i].y, 3);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	// fire the bullets when key is pressed
	for (int i = 0; i < BULLET_NUM; i++) {
		if (bullet[i].visible == 0) {
			bullet[i].x = bar_X;
			bullet[i].y = ofGetHeight() - BAR_Y_POS;
			bullet[i].visible = 1;
			break;
		}
	}
}

//--------------------------------------------------------------
void updateBullet() {
	int i, x, y;

	for (i = 0; i < BULLET_NUM; i++) {
		if (bullet[i].visible == 1) {
			bullet[i].y -= BULLET_SPEED;
			x = bullet[i].x;
			y = bullet[i].y;
			if (bricks[y / BRICK_HEIGHT][x / BRICK_WIDTH] == 1) {
				bricks[y / BRICK_HEIGHT][x / BRICK_WIDTH] = 0;
				bullet[i].visible = 0;
			}
			if (bullet[i].y < 0) {
				bullet[i].visible = 0;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mousePressed(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) { }