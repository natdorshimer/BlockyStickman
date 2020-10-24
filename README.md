## Design
- This is going to an Entity Component System. What this means, is that objects within the world, are entities
- Entities are just IDs. Nothing be beyond that
- Entities can have stuff, Components

How do we structure our world?



Components
	Collidable
		isColliding: bool
		references to things it's colliding with
		A normal to the thing it's colliding with 



This is going to an Entity Component System. What this means, is that objects within the world, are entities
- Entities are just IDs. Nothing be beyond that
- Entities can have Components. Example Components:
  - Actor : important, drawable, transformable, has sprites(animations)?, etc, "states"
  - PlayerController : "Player Name", "iskeyrepeated", "player state info"
  - Velocity
  - Colliders
  - Actions
  - Inventory
  - Health
  - Script
  - Camera could be an entity, or we can have it be singular and just tie to player 


- Systems act on entities
- Hittable system takes <Actor, Health> 
- Translation system takes <Actor, Velocity>
- Collision system take <Actor, collider>
- Script Handlers take \<Script> 


## TODO LIST

1. Systems
    - System for the player controller

    - System for collisions <Actor, collider>, needs reset to a noncolliding state 

    - System Hittable <Actor, Health>

    - Translation System <Actor, Velocity>

2. The system "system" running. We want to be able to assign entities to the registry, give them components, and have them do their thing

3. We want to system to be working properly. 
    - Get the translation system working
    - Entities with generic velocity, does the translation system move them?
    - Test for multiple entities

	- We want to get the PlayerController system working 
    - Can we control the player to any degree we want?
      - Attach to any entity
			- What if we attach to multiple entities?

	* Collision
		* Collision system is <Actor, Collider>
			* We only move the subset <Actor, Collider, Velocity>
				* We give collider data to all <Actor, Colliders>
				* But we only move <Actor, Collider, Velocities>


	* Combat system? Maybe?

3. Level Design, Character Design, Items

4. Good ways to load levels
	Via some kind of format
	Position, size of rectangle/platform, is collidable?
	* LevelTextureMap
  
  * Do the same kind of thing for enemies
    * PlayerTextureMap
    
    
5. We need sprites
	* Consider looking into animations
	* Might need research

6. Ways to load of entities

7. Game states and switching between them
	AKA Scenes in prominent game engines

8. What is the menu?
	1. Start Game
	2. Exit
	3. Pretty background?
	3. Load game?(if we have time) 

9. End game state, what happens after you reach the end?

10. And ya know, maybe more levels

- Want list:
  - Animation system? instead of sprites


## Blocky Stick Man
- silly lil sprite
- final boss is a triangle/ enemies are triangles
- or perhaps 3D??????? / pyramid aka ramiel
  - a diamond!


## Or mayhaps just a simple platformer
* inspiration: hollow knight
* hidden stuff everywhere, not necessarily related to the end goal. Just for personal gain

## Schedule
### Monday
<strike>
* figure out what is needed for a knowledge base
* what do we need to learn by end of day Tuesday?
* also, nice to have: working workflow that is on github
  - aka have a hello world going
* understand how SFML constructs its world
  </strike>

### Tuesday<strike>
* Think about how to structure our world
* How to structure scenes
	* Ex: Entity Component System vs Raw Inheritance
	* Thinking ECS https://github.com/skypjack/entt
		* Raw inheritance won't require me to learn much but won't scale well
	* How do we handle specific interactions between entities?

* Think about how interactions work 
* What resources we'll use 
* Start setting in place the design structure of the world, scenes, and entities within those scenes, and  interaction between entities


### Wednesday
* Start setting in place the design structure of the world, scenes, and entities within those scenes, and  interaction between entities
* Continue working on design structure of world

* End of day goal: Have a scene where the player character can move, jump around, perform actions, attack enemies, maybe interact with environment in some way


### Thursday
- Polish basic features from wednesday. Animation polishing. 
  - Main menu, starting game menu, intro screen
  </strike>
  - Add new features assuming that what we have works properly. I
  - Picking up items, specific skills? This is metroidvania style?
  - More complex movement options? 
    - Interaction with NPCs?

