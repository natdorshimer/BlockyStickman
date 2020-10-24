#pragma once

#include "blocky-pch.h"
#include "Core.h"


namespace Blocky
{
	#define BIT(x) (1 << x)
	#define CreateSharedPtrName(name) using name##Ptr = std::shared_ptr<name>;

	#define ComponentCreator(ClassName)  \
		template<typename... Args> \
		static std::shared_ptr<ClassName> Create(Args&&... args) \
		{ \
			return std::make_shared<ClassName>(std::forward<Args>(args)...); \
		} 

	struct RotationComponent
	{
		ComponentCreator(RotationComponent)

	}; CreateSharedPtrName(RotationComponent);

	struct NameComponent 
	{ 
		std::string name; 

		ComponentCreator(NameComponent)
	}; CreateSharedPtrName(NameComponent);

	struct TextureComponent
	{
		sf::Texture texture;

		ComponentCreator(TextureComponent)

	}; CreateSharedPtrName(TextureComponent);

	struct CameraComponent
	{
		sf::View view;

		ComponentCreator(CameraComponent)

	}; CreateSharedPtrName(CameraComponent);

	struct TransformComponent 
	{
		sf::Transformable trans;

		ComponentCreator(TransformComponent)

	}; CreateSharedPtrName(TransformComponent);

	//Holds position, texture, and vertices 
	struct SpriteComponent
	{
		sf::Sprite sprite;

		ComponentCreator(SpriteComponent)

	}; CreateSharedPtrName(SpriteComponent);

	struct TextComponent
	{
		sf::Text text;

		ComponentCreator(TextComponent)

	}; CreateSharedPtrName(TextComponent);

	struct FontComponent
	{
		sf::Font font;

		ComponentCreator(FontComponent)

	}; CreateSharedPtrName(FontComponent);

	struct BackgroundComponent
	{
		// this is an empty struct, just an indicator of which sprite is the background
		ComponentCreator(BackgroundComponent)

	}; CreateSharedPtrName(BackgroundComponent);



	//Layers are used for ordering how things are rendered
	//Everything requires a layer to be rendered
	struct BottomLayer
	{
		ComponentCreator(BottomLayer)

	}; CreateSharedPtrName(BottomLayer)

	struct MiddleLayer
	{
		ComponentCreator(MiddleLayer)

	}; CreateSharedPtrName(MiddleLayer)

	struct TopLayer
	{
		ComponentCreator(TopLayer)

	}; CreateSharedPtrName(TopLayer)


	//Used for handling interactions and state changes for entities, typically the player
	struct ObjectState
	{
		enum ObjStates
		{
			Airborne = BIT(0),
			Walking = BIT(1),
			Running = BIT(2),
			Invulnerable = BIT(3),
			Standing = BIT(4)
		};

		using ObjectStates = uint32_t;

		ObjectStates GetStates();

		std::string To_String();

		void SetState(ObjStates s);

		void RemoveState(ObjStates s);

		void RemoveState();

		bool HasState(ObjStates state);

		bool HasStates(ObjectStates states);

		ComponentCreator(ObjectState)

	private:

		ObjStates GetHighestState();

		ObjectStates States = ObjectState::Airborne;

		static std::string To_String(ObjStates);

	}; CreateSharedPtrName(ObjectState);


	struct Player
	{

	}; CreateSharedPtrName(Player);

	//Used for players and enemies to determine stats for their interactions
	struct StatusComponent
	{
		int Health = 1;
		int MaxHealth = 1;

		int AttackPower = 1;
		int Speed = 150;

		int JumpSpeed = -300;

		ComponentCreator(StatusComponent)

	}; CreateSharedPtrName(StatusComponent);

	//Used for storing states about the world
	struct WorldStateComponent
	{
		float gravity = 700;

		ComponentCreator(WorldStateComponent)

	}; CreateSharedPtrName(WorldStateComponent);


	//Automated controller for moving entities. This runs on a simple loop
	struct AIController : public Player
	{
		Timestep timeUntilReverse = 2.0f; //two seconds until it reverses direction
		static inline const Timestep loopLength = 2;
		int speed = 30;

		void resetTime();

		ComponentCreator(AIController)

	}; CreateSharedPtrName(AIController);


	//Used to grab the player that the user controls with input
	struct PlayerController : public Player
	{
		// tells systems which entity is the player
		ComponentCreator(PlayerController)

	}; CreateSharedPtrName(PlayerController);


	//Fundamental structure for the translation system
	struct VelocityComponent
	{
		VelocityComponent() { velocity = sf::Vector2f(0, 0); }

		VelocityComponent(const sf::Vector2f velocity) :
			velocity(velocity) {}

		sf::Vector2f velocity;

		ComponentCreator(VelocityComponent)

	}; CreateSharedPtrName(VelocityComponent);


	//Used for assigning win conditions to other entities
	struct WinConditionComponent
	{

		ComponentCreator(WinConditionComponent)

	};  CreateSharedPtrName(WinConditionComponent);


	//This checks for collisions and determines priority for collisions
	struct ColliderComponent
	{
		enum Priority
		{
			Lowest = 0,
			Medium,
			Highest
		};

		//To register a normal against a specific entity
		std::map<entt::entity, sf::Vector2f> normals;

		//Used for determining if it's actually colliding with anything
		bool hasNormals();

		//Default priority for the player is the lowest : they get moved
		Priority priority = Lowest;

		ComponentCreator(ColliderComponent)

	}; CreateSharedPtrName(ColliderComponent);



	//Keeps track of time in seconds, needs to be managed by a timer system
	struct TimerComponent
	{
		float seconds_elapsed = 0;
		ComponentCreator(TimerComponent)

	}; CreateSharedPtrName(TimerComponent);

}