
#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "ResourceManager.h"
#include "GUI.h"
#include "Tile.h"
#include "Selector.h"
#include <fstream>

class LevelEditor
{
public:
	LevelEditor(ResourceManager& t_gameAssets);
	~LevelEditor();
	void clearGUI();
	void update(sf::Time t_deltaTime, MyVector3 mouseClick, int mouseScroll, bool pressed, bool rightPressed, sf::RenderWindow& t_window);
	void render(sf::RenderWindow& t_window);
	void initialize();
	void saveLevel();
	void loadLevel();
	void checkZoom();
	void backgroundUpdate(MyVector3 mouseClick, int nx, int ny);
	void playUpdate(MyVector3 mouseClick, int nx, int ny);
	void rightClickScroll(MyVector3 mouseClick);
	void optionController(std::string st);
	void saveAndLoad();
	void changeScreen();
	void doEditingArea(bool pressed, sf::RenderWindow& t_window, MyVector3 mouseclick, bool rightPressed);
	void doSelectingArea(sf::RenderWindow& t_window, MyVector3 mouseClick, bool pressed);

private:

	sf::Vertex gridXaxisStart;
	sf::Vertex gridXaxisEnd;
	sf::Vertex gridYaxisStart;
	sf::Vertex gridYaxisEnd;
	sf::VertexArray Xaxis;
	sf::VertexArray Yaxis;
	sf::Font m_font;
	float m_clickTimer;
	float m_enemyPlaceTimer;
	bool saveBool;
	float m_saveTimer;
	float keyPlaceTimer;
	int m_count{ 10 };
	sf::Vector2f m_lastclickPos;
	int m_state{ 1 };
	Selector m_selector;
	GUI m_EditorGUI;
	std::string m_currentTextureTag;
	sf::Sprite m_currentSprite;
	int currentTileIndex;
	bool overGrid;
	bool erase = false;
	float m_timeManager{ 0 };
	std::vector<Tile*> m_level;
	std::vector<Tile*> m_bottomLayer;
	Layer m_currentLayer{ Layer::play };

	std::vector<std::string> m_savedLevelNames;

	std::string m_oldSaveName;
	std::string m_saveName;
	std::string m_oldLoadName;
	std::string m_loadName;

	ResourceManager* gameAssets;

	sf::Vector2f m_cameraStartPos = { 960, 640};
	sf::Vector2f m_diffFromStartCamera;
	MyVector3 m_startPanPos;
	bool m_reentry;
	std::vector<sf::Vector2f> widPosArray;

	bool zoomOut = false;
	sf::Vector2f zoomCentre = { 2100, 1280 };
	float zoomcount = 0;
	float rotCount = 0;
	int rotDirection = 0;
	sf::Vector2f lastCentre;
	std::vector<std::pair<MyVector3, MyVector3>> m_xLines;
	std::vector<std::pair<MyVector3, MyVector3>> m_yLines;
	float m_viewValueScale = 356;
	bool placeRoute = false;
	bool doorPlace = false;
	Tile* currentInUseEnemy = nullptr;
	int currentRouteCount{ 0 };
};
