#pragma once
#include <vector>
#include "../../aiService.h"

namespace BlackBoard {
	class Blackboard {
	public:
		std::vector<Boid*> allBoids;
		std::vector<Obstacle*> allObstacles;
		Boid* DT_Target = nullptr;
		Boid* myChar = nullptr;

		DynamicSeek* dynamicSeek = nullptr;
		DynamicEvade* dynamicEvade = nullptr;
		DynamicWander* dynamicWander = nullptr;
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
			dynamicLWYG = new DynamicLookWhereYouAreGoing(nullptr, maxAngularAcceleration, maxRotation, targetRadiusRot, slowRadiusRot);
			dynamicWander = new DynamicWander(nullptr, maxAngularAcceleration, maxRotation, maxAcceleration, targetRadiusRot,
				slowRadiusRot, wanderOffset, wanderRate, 0.01);
			dynamicEvade = new DynamicEvade(nullptr, nullptr, maxPrediction, maxAcceleration + 25, safeRadius, decayCoef);
		}

		~Blackboard() {
			delete dynamicSeek;
			delete dynamicLWYG;
			delete dynamicWander;
			delete dynamicEvade;
		}

		inline void update(std::vector<Boid*> i_allBoids, std::vector<Obstacle*> i_allObstacles, 
							Boid* i_DT_Target, TileGraph* i_tileGraph, Boid* i_myChar) {
			// Update Abstract Scheme
			allBoids = i_allBoids;
			allObstacles = i_allObstacles;
			DT_Target = i_DT_Target;
			tileGraph = i_tileGraph;
			myChar = i_myChar;
		};
	};
}