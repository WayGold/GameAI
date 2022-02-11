#pragma once

#include "ofMain.h"
#include <vector>
#include "aiService.h"
#include <unordered_map>
#include <string>

class ofApp : public ofBaseApp{

	public:
		std::vector<Boid*> allBoids;
		std::vector<Boid*> allSeekers;
		std::vector<Boid*> allArrivers;
		std::vector<Boid*> allPursuers;
		std::vector<Boid*> allWanderers;
		std::vector<Boid*> allFollowers;
		std::vector<Boid*> allLeaders;

		std::vector<RigidBody*> allFollowersRB;
		std::vector<RigidBody*> flockRBs;

		std::vector<std::pair<glm::vec2, ofColor>> allPrevPos;

		std::vector<string> states;
		std::vector<string>::iterator currentState;
		std::vector<Boid*> windowCorners;
		std::vector<Boid*>::iterator currentKinematicTarget;

		bool isdrawBreadcrumb = true;
		bool isdrawLimitedBreadcrumb = true;
		bool playKinematic = false;

		Boid* seekTarget = nullptr;
		Boid* kinematicBoid = nullptr;
		Boid* topLeft = nullptr;
		Boid* topRight = nullptr;
		Boid* bottomLeft = nullptr;
		Boid* bottomRight = nullptr;

		float seekTargetIndex = -1;

		DynamicSeek* dynamicSeek = nullptr;
		DynamicFace* dynamicFace = nullptr;
		DynamicEvade* dynamicEvade = nullptr;
		DynamicWander* dynamicWander = nullptr;
		DynamicPursue* dynamicPursue = nullptr;
		DynamicArrive* dynamicArrive = nullptr;
		DynamicFlocking* dynamicFlock = nullptr;
		DynamicSeperation* dynamicSeperate = nullptr;
		DynamicLookWhereYouAreGoing* dynamicLWYG = nullptr;

		KinematicSeek* kinematicSeek = nullptr;
		
		const float maxSpeed = 40;
		const float maxAcceleration = 50;

		const float slowRadius = 150;
		const float targetRadius = 2;

		const float maxRotation = glm::pi<float>() / 2;
		const float maxAngularAcceleration = glm::pi<float>() * 2;

		const float slowRadiusRot = glm::pi<float>() / 8;
		const float targetRadiusRot = glm::pi<float>() / 1024;

		const float wanderOffset = 5;
		const float wanderRate = glm::pi<float>() * 2;

		const float maxPrediction = 2;
		const float safeRadius = 75;
		const float decayCoef = 1000;
		
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void drawBreadcrumb(glm::vec2 position, ofColor color);
};
