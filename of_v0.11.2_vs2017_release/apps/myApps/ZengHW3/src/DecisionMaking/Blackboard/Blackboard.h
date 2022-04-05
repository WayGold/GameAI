#pragma once
#include <vector>
#include "../../aiService.h"

namespace BlackBoard {
	class Blackboard {
	public:
		std::vector<Boid*> allBoids;
		std::vector<Boid*> allSeekers;
		std::vector<Boid*> allWanderers;
		std::vector<Obstacle*> allObstacles;

		DynamicSeek* dynamicSeek = nullptr;
		DynamicFace* dynamicFace = nullptr;
		DynamicEvade* dynamicEvade = nullptr;
		DynamicWander* dynamicWander = nullptr;
		DynamicPursue* dynamicPursue = nullptr;
		DynamicArrive* dynamicArrive = nullptr;
		DynamicLookWhereYouAreGoing* dynamicLWYG = nullptr;

		TileGraph* tileGraph = nullptr;

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
		const float safeRadius = 70;
		const float decayCoef = 10000;

		Blackboard() {
			// Init Movement Algorithms
			dynamicSeek = new DynamicSeek(nullptr, nullptr, maxAcceleration);
			dynamicFace = new DynamicFace(nullptr, nullptr, maxAngularAcceleration, maxRotation, targetRadius, slowRadius);
			dynamicLWYG = new DynamicLookWhereYouAreGoing(nullptr, maxAngularAcceleration, maxRotation, targetRadiusRot, slowRadiusRot);
			dynamicWander = new DynamicWander(nullptr, maxAngularAcceleration, maxRotation, maxAcceleration, targetRadiusRot,
				slowRadiusRot, wanderOffset, wanderRate, 0.01);
			dynamicArrive = new DynamicArrive(nullptr, nullptr, maxAcceleration, maxSpeed, targetRadius, slowRadius);
			dynamicEvade = new DynamicEvade(nullptr, nullptr, maxPrediction, maxAcceleration + 25, safeRadius, decayCoef);
			dynamicPursue = new DynamicPursue(nullptr, nullptr, maxPrediction, maxAcceleration);
			// Tile Graph
			tileGraph = new TileGraph(64, 48, 1024, 768);
		}

		~Blackboard() {
			delete dynamicSeek;
			delete dynamicFace;
			delete dynamicLWYG;
			delete dynamicWander;
			delete dynamicArrive;
			delete dynamicEvade;
			delete dynamicPursue;
			delete tileGraph;
		}
	};
}