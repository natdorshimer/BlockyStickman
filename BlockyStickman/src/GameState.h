#pragma once
#include <map>
#include "Scene.h"
#include <memory>
#include "Core.h"
#include "State.h"

namespace Blocky
{
	 

	using ScenePtr = std::shared_ptr<Scene>;
	//This is the main game state
	//This is where the magic happens

	//We need to monitor events here 
	//Is a pause button pressed?
		//That has to be handled by the state


	class GameState : public State
	{
	public:

		std::shared_ptr<Scene>& GetScene();

		//Requires a reference to the parent to request state switching
		GameState(StateStack* parentRef);

		//Updates the game every frame
		virtual bool Update(Timestep dt);

		//State switches to a game over screen
		void OnGameOver(Timestep dt);

		//When the user presses P, the state transitions to a pause state
		void PauseChecker(Timestep dt, entt::registry& registry);

		//Checks for win conditions and transitions to a game won state if won
		void WinConditionSystem(Timestep dt, entt::registry& registry);

		//Checks to see if the player's health is zero
		void CheckGameOverCondition(Timestep dt, entt::registry& registry);

	private:

		//Loads entities
		void EntityComponentInit();

		//Loads gameplay systems
		void SystemInit();

		//Loads win condition systems
		void InitWinConditionSystems();

		void BlockNextState();

		void AllowNextState();

		bool ShouldContinue();
		
		ScenePtr m_Scene;

		bool m_IsStatePaused;

		bool m_shouldContinue;
	};
}