/*
 * LevelLoading.cpp -- definitions for level builder functions
 * Lucas Campbell and Natalie Dorshimer
 */

#include "LevelLoading.h"
#include "Core.h"
#include "Components.h"
#include "Scene.h"
#include "memory.h"
#include "Renderer.h"

// size of bg image in pixels
#define DEFAULT_VIEW_SIZE sf::Vector2f(384.f, 224.f)

namespace Blocky {

	/* 
	 * Adds a non-moving sprite to the registry system for the given Scene. 
	 * Gets texture for sprite from the given filepath, and scales/positions it in the scene accordingly
	 */
	Entity addStaticSprite(std::shared_ptr<Scene> scene, std::string filepath, int posX, int posY, double xScale, double yScale, double startX, double startY, double xSize, double ySize)
	{
		// sprites have texture (image associated with them), sprite, and are associated with the middle layer for
		// rendering (behind text, in front of background)
		Entity newMapPiece = scene->CreateEntity();
		GiveComponent(newMapPiece, TextureComponent);
		GiveComponent(newMapPiece, SpriteComponent);
		GiveComponent(newMapPiece, MiddleLayer);


		if (!newMapPieceTextureComponent->texture.loadFromFile(filepath)) 
		{
			LOG("Error: Could not load texture from {}", filepath);
		}

		newMapPieceSpriteComponent->sprite.setTexture(newMapPieceTextureComponent->texture);

		// Logic for only getting a part of the provided texture
		if (startX > 0 && startY > 0 && xSize > 0 && ySize > 0)
		{
			newMapPieceSpriteComponent->sprite.setTextureRect(sf::IntRect(startX, startY, xSize, ySize));
		}
		// scale the sprite to the desired shape
		if (xScale != 1.0 || yScale != 1.0) 
		{
			// this scale is from the original image dimensions. For example, if the image was 64x64, sprite.scale(2.0, 0.5) yields a 128x32 image
			newMapPieceSpriteComponent->sprite.scale(xScale, yScale);
		}

		// starting position on the map
		newMapPieceSpriteComponent->sprite.move(posX, posY);

		return newMapPiece;

	}


	/*
	 * Adds an enemy (sprite with movement, collider, velocity, health) to the given scene, with texture from the desired filepath.
	 */
	Entity addEnemy(std::shared_ptr<Scene> scene, std::string filepath, int posX, int posY, double xScale, double yScale, double startX, double startY, double xSize, double ySize)
	{
		Entity enemy = scene->CreateEntity();
		GiveComponent(enemy, TextureComponent);
		GiveComponent(enemy, SpriteComponent);
		GiveComponent(enemy, ColliderComponent);
		GiveComponent(enemy, StatusComponent); // details health, attack power, jump, and speed
		GiveComponent(enemy, AIController); // movement behavior
		GiveComponent(enemy, VelocityComponent);
		GiveComponent(enemy, ObjectState); // way to tell if walking/jumping/etc
		GiveComponent(enemy, MiddleLayer);


		//Enemy collider priority:
		enemyColliderComponent->priority = ColliderComponent::Priority::Medium;

		if (!enemyTextureComponent->texture.loadFromFile(filepath)) 
		{
			LOG("Error: Could not load texture from {}", filepath);
		}

		enemySpriteComponent->sprite.setTexture(enemyTextureComponent->texture);

		// Logic for only getting a part of the provided texture
		if (startX > 0 && startY > 0 && xSize > 0 && ySize > 0) 
		{
			enemySpriteComponent->sprite.setTextureRect(sf::IntRect(startX, startY, xSize, ySize));
		}

		// scale the sprite to the desired shape
		if (xScale != 1.0 || yScale != 1.0) 
		{
			enemySpriteComponent->sprite.scale(xScale, yScale);
		}

		// starting position on the map
		enemySpriteComponent->sprite.move(posX, posY);
		return enemy;
	}

	/*
	 * Adds a player to the scene from provided file path for texture, starting x,y position, etc.
	 * NOTE: Only create one of these per scene, for camera rendering purposes
	 */
	Entity addPlayer(std::shared_ptr<Scene> scene, std::string filepath, int posX, int posY, double xScale, double yScale, double startX, double startY, double xSize, double ySize)
	{
		Entity player = scene->CreateEntity();
		GiveComponent(player, TextureComponent);
		GiveComponent(player, SpriteComponent);
		GiveComponent(player, VelocityComponent);
		GiveComponent(player, ColliderComponent); //crash into things!
		GiveComponent(player, PlayerController); // used by systems in the game to determine which entity is the Player
		GiveComponent(player, CameraComponent); // used for centering the view that the human player sees
		GiveComponent(player, StatusComponent); // details health, attack power, jump, and speed
		GiveComponent(player, ObjectState); // way to tell if walking/jumping/etc
		GiveComponent(player, MiddleLayer);

		playerColliderComponent->priority = playerColliderComponent->Lowest;
		if (!playerTextureComponent->texture.loadFromFile(filepath)) 
		{
			LOG("Error: Could not load texture from {}", filepath);
		}

		playerSpriteComponent->sprite.setTexture(playerTextureComponent->texture);
		if (startX > 0 && startY > 0 && xSize > 0 && ySize > 0) 
		{
			playerSpriteComponent->sprite.setTextureRect(sf::IntRect(startX, startY, xSize, ySize));
		}

		if (xScale != 1.0 || yScale != 1.0) 
		{
			playerSpriteComponent->sprite.scale(xScale, yScale);
		}

		playerCameraComponent->view.setCenter(playerSpriteComponent->sprite.getPosition());
		// This sets the size of what is seen for the whole game, assuming that there is only one player.
		playerCameraComponent->view.setSize(DEFAULT_VIEW_SIZE);

		playerSpriteComponent->sprite.move(posX, posY);

		return player;
	}

	/*
	 * Adds a piece of text to the scene. Parameters adjust text context, font, position, style, and color.
	 */
	Entity addText(std::shared_ptr<Scene> scene, std::string msg, std::string filepath, int startX, int startY, int characterSize, sf::Text::Style style, sf::Color color )
	{
		Entity text = scene->CreateEntity();
		GiveComponent(text, TextComponent);
		GiveComponent(text, FontComponent);
		GiveComponent(text, TopLayer);

		// get font from file and set it
		if (!textFontComponent->font.loadFromFile(filepath)) 
		{
			LOG("Error: Could not load font from {}", filepath);
		}
		textTextComponent->text.setFont(textFontComponent->font);

		// set the message 
		textTextComponent->text.setString(msg);

		// absolute position
		textTextComponent->text.setPosition(startX, startY);

		// text color
		textTextComponent->text.setFillColor(color);

		// text style
		if (style != sf::Text::Style::Regular) 
		{
			textTextComponent->text.setStyle(style);
		}

		// char size, in pixels
		if (characterSize != 30) 
		{
			textTextComponent->text.setCharacterSize(characterSize);
		}

		return text;
	}

	// Adds static sprite with added camera component the exists on the bottom layer for rendering purposes.
	Entity addBackground(std::shared_ptr<Scene> scene, std::string filepath, int xPos, int yPos, double xScale, double yScale, int startX, int startY, int xSize, int ySize)
	{
		Entity bg = addStaticSprite(scene, filepath, xPos, yPos, xScale, yScale, startX, startY, xSize, ySize);
		scene->GetRegistry().remove<MiddleLayerPtr>(bg.GetID()); //don't want background to be middle layer

		GiveComponent(bg, BackgroundComponent);
		GiveComponent(bg, CameraComponent);
		GiveComponent(bg, BottomLayer);

		// Find the newly added sprite in the registry and give it a camera
		auto spritesView = scene->GetRegistry().view<SpriteComponentPtr>();
		for (auto spriteEntity : spritesView) 
		{
			if (spriteEntity == bg.GetID()) 
			{
				auto& bgSprite = spritesView.get<SpriteComponentPtr>(spriteEntity)->sprite;

				//Get background image width and height
				auto h = bgSprite.getGlobalBounds().height;
				auto w = bgSprite.getGlobalBounds().width;

				// set camera to center on the background image
				bgCameraComponent->view.setCenter(w/2, h/2);
				bgCameraComponent->view.setSize(w, h);
				break;
			}
		}

		return bg;
	}

}

