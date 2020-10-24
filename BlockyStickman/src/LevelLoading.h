/*
 * LevelLoading.h -- header file for level builder functions
 * Lucas Campbell and Natalie Dorshimer
 */

#pragma once
#include <memory>
#include "Scene.h"
#include <string>
#include "SFML/Graphics.hpp"

namespace Blocky {
	 
	// Static sprite, aka used for blocks/platforms. Does not include a collider component, needs to be added manually
	Entity addStaticSprite(std::shared_ptr<Scene> scene, std::string filepath, int posX=0, int posY=0, double xscale = 1.0, double yScale = 1.0,  double startX=-1, double starty=-1, double xSize=-1, double ySize=-1);
	// Enemies
	Entity addEnemy(std::shared_ptr<Scene> scene, std::string filepath, int posX = 0, int posY = 0, double xscale = 1.0, double yScale = 1.0, double startx=-1, double starty=-1, double xSize=-1, double ySize=-1);
	// Player, has a camera attached to it
	// NOTE: You should only ever create one of these per Scene, for now.
	Entity addPlayer(std::shared_ptr<Scene> scene, std::string filepath, int posX = 0, int posY = 0, double xscale = 1.0, double yScale = 1.0, double startx=-1, double starty=-1, double xSize=-1, double ySize=-1);
	// Text Box
	Entity addText(std::shared_ptr<Scene> scene, std::string msg, std::string filepath, int startX, int startY, int characterSize = 30, sf::Text::Style style = sf::Text::Style::Regular, sf::Color color = sf::Color::Black);
	// static sprite with added camera component
	Entity addBackground(std::shared_ptr<Scene> scene, std::string filepath, int xPos = 0, int yPos = 0, double xscale = 1.0, double yScale = 1.0,  int startX=-1, int starty=-1, int xSize=-1, int ySize=-1);
}
