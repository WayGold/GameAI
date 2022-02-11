#include "ofApp.h"
#include "ofMain.h"

//--------------------------------------------------------------
void ofApp::setup() {

	// Init States
	states.push_back("SEEKER");
	states.push_back("ARRIVER");
	states.push_back("PURSUER");
	states.push_back("TARGET");
	states.push_back("FOLLOWER");
	states.push_back("WANDERER");
	states.push_back("LEADER");

	// Set Initial State to Seeker
	currentState = states.begin();

	// Init Movement Algorithms
	dynamicSeek = new DynamicSeek(nullptr, nullptr, maxAcceleration);
	dynamicFace = new DynamicFace(nullptr, nullptr, maxAngularAcceleration, maxRotation, targetRadius, slowRadius);
	dynamicLWYG = new DynamicLookWhereYouAreGoing(nullptr, maxAngularAcceleration, maxRotation, targetRadiusRot, slowRadiusRot);
	dynamicWander = new DynamicWander(nullptr, maxAngularAcceleration, maxRotation, maxAcceleration, targetRadiusRot,
		slowRadiusRot, wanderOffset, wanderRate, 0.01);
	dynamicArrive = new DynamicArrive(nullptr, nullptr, maxAcceleration, maxSpeed, targetRadius, slowRadius);
	dynamicFlock = new DynamicFlocking(nullptr, allFollowersRB, maxPrediction, maxAcceleration, safeRadius, decayCoef, maxSpeed, targetRadius, slowRadius);
	dynamicEvade = new DynamicEvade(nullptr, nullptr, maxPrediction, maxAcceleration, safeRadius, decayCoef);
	dynamicSeperate = new DynamicSeperation(nullptr, allFollowersRB, maxPrediction, maxAcceleration, safeRadius, decayCoef);
	dynamicPursue = new DynamicPursue(nullptr, nullptr, maxPrediction, maxAcceleration);
	kinematicSeek = new KinematicSeek(nullptr, nullptr, maxSpeed);

	topLeft = new Boid();
	topRight = new Boid();
	bottomLeft = new Boid();
	bottomRight = new Boid();
	kinematicBoid = new Boid(glm::vec2(0, 0), 20, 10, ofColor(204, 204, 255));

	topLeft->boidRB->position = glm::vec2(20, 20);
	topRight->boidRB->position = glm::vec2(1004, 20);
	bottomLeft->boidRB->position = glm::vec2(20, 748);
	bottomRight->boidRB->position = glm::vec2(1004, 748);
	kinematicBoid->boidRB->position = bottomLeft->boidRB->position;

	windowCorners.push_back(bottomLeft);
	windowCorners.push_back(bottomRight);
	windowCorners.push_back(topRight);
	windowCorners.push_back(topLeft);

	currentKinematicTarget = ++windowCorners.begin();
}

//--------------------------------------------------------------
void ofApp::update() {
	auto deltaTime = ofGetLastFrameTime();

	std::stringstream strm;
	strm << "fps: " << trunc(ofGetFrameRate()) << ", OnClick Create: " << (*currentState);
	ofSetWindowTitle(strm.str());

	if (playKinematic) {
		kinematicSeek->characterRB = kinematicBoid->boidRB;
		kinematicSeek->targetRB = (*currentKinematicTarget)->boidRB;
		auto steeringOutput = kinematicSeek->getSteering();
		kinematicBoid->boidRB->update(steeringOutput, 500, maxRotation, deltaTime);
	}
	else {
		currentKinematicTarget = ++windowCorners.begin();
		kinematicBoid->boidRB->position = bottomLeft->boidRB->position;
	}

	if (allSeekers.size() != 0 && seekTarget) {
		// Get steering and update all
		for (auto it = allSeekers.begin(); it != allSeekers.end(); ++it) {
			// Set up input to algorithms
			dynamicSeek->characterRB = (*it)->boidRB;
			dynamicSeek->targetRB = seekTarget->boidRB;

			/*dynamicFace->characterRB = (*it)->boidRB;
			dynamicFace->targetRB = seekTarget->boidRB;*/
			dynamicLWYG->characterRB = (*it)->boidRB;

			// Get steering - seek + face/LWYG
			auto steeringOutput = dynamicSeek->getSteering();
			//steeringOutput.rotAccel = dynamicFace->getSteering().rotAccel;
			steeringOutput.rotAccel = dynamicLWYG->getSteering().rotAccel;
			(*it)->boidRB->update(steeringOutput, maxSpeed, maxRotation, deltaTime);
		}
	}

	if (allArrivers.size() != 0 && seekTarget) {
		// Get steering and update all
		for (auto it = allArrivers.begin(); it != allArrivers.end(); ++it) {
			// Set up input to algorithms
			dynamicArrive->characterRB = (*it)->boidRB;
			dynamicArrive->targetRB = seekTarget->boidRB;

			/*dynamicFace->characterRB = (*it)->boidRB;
			dynamicFace->targetRB = seekTarget->boidRB;*/
			dynamicLWYG->characterRB = (*it)->boidRB;

			// Get steering - seek + face/LWYG
			auto steeringOutput = dynamicArrive->getSteering();
			//steeringOutput.rotAccel = dynamicFace->getSteering().rotAccel;
			steeringOutput.rotAccel = dynamicLWYG->getSteering().rotAccel;
			(*it)->boidRB->update(steeringOutput, maxSpeed, maxRotation, deltaTime);
		}
	}

	if (allPursuers.size() != 0 && seekTarget) {
		// Get steering and update all
		for (auto it = allPursuers.begin(); it != allPursuers.end(); ++it) {
			// Set up input to algorithms
			dynamicPursue->characterRB = (*it)->boidRB;
			dynamicPursue->targetRB = seekTarget->boidRB;

			/*dynamicFace->characterRB = (*it)->boidRB;
			dynamicFace->targetRB = seekTarget->boidRB;*/
			dynamicLWYG->characterRB = (*it)->boidRB;

			// Get steering - seek + face/LWYG
			auto steeringOutput = dynamicPursue->getSteering();
			//steeringOutput.rotAccel = dynamicFace->getSteering().rotAccel;
			steeringOutput.rotAccel = dynamicLWYG->getSteering().rotAccel;
			(*it)->boidRB->update(steeringOutput, maxSpeed, maxRotation, deltaTime);
		}
	}


	if (allWanderers.size() != 0) {
		for (auto it = allWanderers.begin(); it != allWanderers.end(); ++it) {
			dynamicWander->characterRB = (*it)->boidRB;
			// Switch wander style by passing in true/false
			auto steeringOutput = dynamicWander->getSteering(true);
			(*it)->boidRB->update(steeringOutput, maxSpeed, maxRotation, deltaTime);
		}
	}

	if (allFollowers.size() > 1 && allLeaders.size() == 0) {
		for (auto it = allFollowers.begin(); it != allFollowers.end(); ++it) {
			dynamicSeperate->characterRB = (*it)->boidRB;
			dynamicSeperate->targetRBs = flockRBs;
			dynamicLWYG->characterRB = (*it)->boidRB;
			// Get Acceleration from flock and orientation from LWYG
			auto steeringOutput = dynamicSeperate->getSteering();
			steeringOutput.rotAccel = dynamicLWYG->getSteering().rotAccel;
			// Update Flock
			(*it)->boidRB->update(steeringOutput, maxSpeed, maxRotation, deltaTime);
		}
	}

	if (flockRBs.size() != 0 && allLeaders.size() != 0) {
		// Call Wander for leaders
		for (auto it = allLeaders.begin(); it != allLeaders.end(); ++it) {
			dynamicWander->characterRB = (*it)->boidRB;
			// Switch wander style by passing in true/false
			auto steeringOutput = dynamicWander->getSteering(false);
			(*it)->boidRB->update(steeringOutput, maxSpeed, maxRotation, deltaTime);
		}
		// Call Flocking for all followers
		for (auto it = allFollowers.begin(); it != allFollowers.end(); ++it) {
			dynamicFlock->characterRB = (*it)->boidRB;
			dynamicFlock->flock = flockRBs;
			dynamicLWYG->characterRB = (*it)->boidRB;
			// Get Acceleration from flock and orientation from LWYG
			auto steeringOutput = dynamicFlock->getSteering();
			steeringOutput.rotAccel = dynamicLWYG->getSteering().rotAccel;
			// Update Flock
			(*it)->boidRB->update(steeringOutput, maxSpeed, maxRotation, deltaTime);
		}
	}

	// Target Evade Section
	//if (allArrivers.size() != 0 && seekTarget) {
	//	dynamicEvade->characterRB = seekTarget->boidRB;
	//	dynamicEvade->targetRB = (*(allArrivers.begin() + allArrivers.size() - 1))->boidRB;
	//	dynamicLWYG->characterRB = seekTarget->boidRB;
	//	auto steeringOutput = dynamicEvade->getSteering();
	//	steeringOutput.rotAccel = dynamicLWYG->getSteering().rotAccel;
	//	// Update seekTarget
	//	seekTarget->boidRB->update(steeringOutput, maxSpeed, maxRotation, deltaTime);
	//}

	// Keep Track of all boids position used to draw breadcrumbs
	for (auto it = allBoids.begin(); it != allBoids.end(); ++it) {
		allPrevPos.push_back(std::make_pair((*it)->boidRB->position, (*it)->boidColor));
	}
	allPrevPos.push_back(std::make_pair(kinematicBoid->boidRB->position, kinematicBoid->boidColor));

	if (isdrawLimitedBreadcrumb) {
		if (allPrevPos.size() > 2048)
			allPrevPos.clear();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	for (auto it = allBoids.begin(); it != allBoids.end(); ++it) {
		(*it)->draw();
	}
	ofDrawGrid(102.4, 10, true, false, false, true);
	// Draw Breadcrumbs
	if (isdrawBreadcrumb) {
		for (auto it = allPrevPos.begin(); it != allPrevPos.end(); ++it) {
			drawBreadcrumb((*it).first, (*it).second);
		}
	}
	// Draw Kinematic
	if (playKinematic) {
		kinematicBoid->draw();
	}
}

void ofApp::exit()
{
	if (dynamicSeek)
		delete dynamicSeek;

	if (dynamicFace)
		delete dynamicFace;

	if (dynamicWander)
		delete dynamicWander;

	if (dynamicLWYG)
		delete dynamicLWYG;

	if (dynamicArrive)
		delete dynamicArrive;

	if (dynamicFlock)
		delete dynamicFlock;

	if (dynamicPursue)
		delete dynamicPursue;

	if (kinematicSeek)
		delete kinematicSeek;

	delete topLeft;
	delete topRight;
	delete bottomLeft;
	delete bottomRight;
	delete kinematicBoid;

	if (allBoids.size() != 0) {
		for (auto it = allBoids.begin(); it != allBoids.end(); ++it) {
			delete* it;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == OF_KEY_DOWN) {
		if ((++currentState) != states.end()) {
		}
		else {
			currentState = states.begin();
		}
	}

	if (key == OF_KEY_UP) {
		if ((currentState) == states.begin()) {
			currentState += states.size() - 1;
		}
		else {
			currentState--;
		}
	}

	if (key == 'B' || key == 'b') {
		isdrawBreadcrumb = !isdrawBreadcrumb;
	}

	if (key == 'L' || key == 'l') {
		isdrawLimitedBreadcrumb = !isdrawLimitedBreadcrumb;
	}

	if (key == 'K' || key == 'k') {
		playKinematic = !playKinematic;
	}

	if (key == 'N' || key == 'n') {
		currentKinematicTarget++;
		if (currentKinematicTarget == windowCorners.end()) {
			currentKinematicTarget = windowCorners.begin();
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

	if (*currentState == "SEEKER") {
		allSeekers.push_back(new Boid(glm::vec2(x, y), 20, 10, ofColor(255, 0, 0)));
		allBoids.push_back(allSeekers.back());
	}

	if (*currentState == "ARRIVER") {
		allArrivers.push_back(new Boid(glm::vec2(x, y), 20, 10, ofColor(255, 204, 204)));
		allBoids.push_back(allArrivers.back());
	}

	if (*currentState == "PURSUER") {
		allPursuers.push_back(new Boid(glm::vec2(x, y), 20, 10, ofColor(0, 0, 204)));
		allBoids.push_back(allPursuers.back());
	}

	if (*currentState == "TARGET") {
		if (seekTarget) {
			allBoids.erase(allBoids.begin() + seekTargetIndex);
			seekTargetIndex = -1;
			delete seekTarget;
		}
		seekTarget = new Boid(glm::vec2(x, y), 20, 10, ofColor(0, 255, 255));
		seekTargetIndex = allBoids.size();
		allBoids.push_back(seekTarget);
	}

	if (*currentState == "FOLLOWER") {
		allFollowers.push_back(new Boid(glm::vec2(x, y), 20, 10, ofColor(153, 255, 153)));
		allFollowersRB.push_back(allFollowers.back()->boidRB);
		flockRBs.push_back(allFollowers.back()->boidRB);
		allBoids.push_back(allFollowers.back());
	}

	if (*currentState == "WANDERER") {
		allWanderers.push_back(new Boid(glm::vec2(x, y), 20, 10, ofColor(255, 204, 229)));
		allBoids.push_back(allWanderers.back());
	}

	if (*currentState == "LEADER") {
		allLeaders.push_back(new Boid(glm::vec2(x, y), 20, 10, ofColor(255, 255, 0), 500.0f));
		flockRBs.push_back(allLeaders.back()->boidRB);
		allBoids.push_back(allLeaders.back());
	}

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

void ofApp::drawBreadcrumb(glm::vec2 position, ofColor color)
{
	ofPushMatrix();

	ofTranslate(position.x, position.y);
	ofSetColor(color);

	// Body
	ofDrawCircle(0, 0, 2);
	ofDrawCircle(5, -5, 2);
	ofDrawCircle(5, 5, 2);
	ofDrawCircle(-5, 5, 2);
	ofDrawCircle(-5, -5, 2);

	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}