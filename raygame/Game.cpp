#include "Game.h"
#include "Maze.h"
#include "raylib.h"

Game* Game::m_instance;

Game::Game()
{
	m_instance = this;
	m_camera = new Camera2D();
}

Scene* Game::getScene(int index)
{
	if (index < 0 || index >= m_scenes.size())
		return nullptr;

	return m_scenes[index];
}

Scene* Game::getCurrentScene()
{
	return m_scenes[m_currentSceneIndex];
}

int Game::getCurrentSceneIndex()
{
	return m_currentSceneIndex;
}

int Game::addScene(Scene* scene)
{
	m_scenes.push_back(scene);
	return (int)m_scenes.size() - 1;
}

bool Game::removeScene(Scene* scene)
{
	for (int i = 0; i < m_scenes.size(); i++)
		if (m_scenes[i] = scene) 
		{
			m_scenes.erase(m_scenes.begin() + i);
			return true;
		}

	return false;
}

void Game::setCurrentScene(int index)
{
	//If the index is not within the range of the the array return
	if (index < 0 || index >= m_scenes.size())
		return;

	//Call end for the previous scene before changing to the new one
	if (m_scenes[m_currentSceneIndex]->getStarted())
		m_scenes[m_currentSceneIndex]->end();

	//Update the current scene index
	m_currentSceneIndex = index;
}

bool Game::getKeyDown(int key)
{
	return IsKeyDown((KeyboardKey)key);
}

bool Game::getKeyPressed(int key)
{
	return IsKeyPressed((KeyboardKey)key);
}

void Game::destroy(Actor* actor)
{
	getCurrentScene()->removeActor(actor);
	if (actor->getParent())
		actor->getParent()->removeChild(actor);
	actor->end();
	delete actor;
}

void Game::setGameOver(bool value)
{
	m_gameOver = value;
}

MathLibrary::Matrix3* Game::getWorld()
{
	return getCurrentScene()->getWorld();
}

void Game::run()
{
	start();

	while (!m_gameOver && !WindowShouldClose())
	{
		float deltaTime = GetFrameTime();
		update(deltaTime);
		draw();
	}

	end();
}

void Game::start()
{
	int screenWidth = Maze::WIDTH * Maze::TILE_SIZE;
	int screenHeight = Maze::HEIGHT * Maze::TILE_SIZE;

	InitWindow(screenWidth, screenHeight, "Pac-Like");
	m_camera->offset = { (float)screenWidth / 2, (float)screenHeight / 2 };
	m_camera->target = { (float)screenWidth / 2, (float)screenHeight / 2 };
	m_camera->zoom = 1;

	SetTargetFPS(60);
}

void Game::update(float deltaTime)
{
	getCurrentScene()->update(deltaTime);
}

void Game::draw()
{
	BeginDrawing();
	BeginMode2D(*m_camera);

	ClearBackground(BLACK);

	getCurrentScene()->draw();

	EndMode2D();
	EndDrawing();
}

void Game::end()
{
	CloseWindow();
}