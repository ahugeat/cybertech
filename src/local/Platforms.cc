/*
 * Copyright (c) 2015 OFNI
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Platforms.h"

using namespace local;

Platforms::Platforms(b2World &b2_world, game::ResourceManager &resources) 
: m_textureBackground(nullptr)
, m_textureGrass(nullptr) {
	// Load texture
	m_textureBackground = resources.getTexture("background.png");
	assert(m_textureBackground != nullptr);

	m_textureGrass = resources.getTexture("grass.png");
	assert(m_textureGrass != nullptr);

	// Setup  the border of screen
	b2BodyDef b2_bodyDef;
	b2_bodyDef.type = b2_staticBody;

	b2PolygonShape b2_boxShape;

	b2FixtureDef b2_fixture;
	b2_fixture.shape = &b2_boxShape;

	// Bottom
	b2_boxShape.SetAsBox(TILE_SIZE * TILES_WIDTH * BOX2D_SCALE * 0.5f, PLATFORM_HEIGHT * 2.0f * BOX2D_SCALE);
	b2_bodyDef.position.Set(TILE_SIZE * TILES_WIDTH * BOX2D_SCALE * 0.5f, TILE_SIZE * TILES_HEIGTH * BOX2D_SCALE);
	b2Body* b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);

	// Top
	b2_boxShape.SetAsBox(TILE_SIZE * TILES_WIDTH * BOX2D_SCALE * 0.5f, 5.0f * BOX2D_SCALE);
	b2_bodyDef.position.Set(TILE_SIZE * TILES_WIDTH * BOX2D_SCALE * 0.5f, -5.0f * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);

	// Right 
	b2_boxShape.SetAsBox(5.0f * BOX2D_SCALE, TILE_SIZE * TILES_HEIGTH * BOX2D_SCALE * 0.5f);
	b2_bodyDef.position.Set(-5.0f * BOX2D_SCALE, TILE_SIZE * TILES_HEIGTH * BOX2D_SCALE * 0.5f);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);

	// Left
	b2_bodyDef.position.Set((TILE_SIZE * TILES_WIDTH + 5.0f) * BOX2D_SCALE, TILE_SIZE * TILES_HEIGTH * BOX2D_SCALE * 0.5f);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);

	// Generate the platforms
	b2_boxShape.SetAsBox(PLATFORM_WIDTH * BOX2D_SCALE * 0.5f, PLATFORM_HEIGHT * BOX2D_SCALE * 0.5f);

	// First line
	b2_bodyDef.position.Set(1 * TILE_SIZE * BOX2D_SCALE, 8 * TILE_SIZE * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);
	m_platformsPosition.push_back(b2_staticBody);

	b2_bodyDef.position.Set(2 * TILE_SIZE * BOX2D_SCALE, 8 * TILE_SIZE * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);
	m_platformsPosition.push_back(b2_staticBody);

	b2_bodyDef.position.Set((TILES_WIDTH - 1) * TILE_SIZE * BOX2D_SCALE, 8 * TILE_SIZE * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);
	m_platformsPosition.push_back(b2_staticBody);

	b2_bodyDef.position.Set((TILES_WIDTH - 2) * TILE_SIZE * BOX2D_SCALE, 8 * TILE_SIZE * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);
	m_platformsPosition.push_back(b2_staticBody);

	// Second Line
	b2_bodyDef.position.Set((TILES_WIDTH / 2) * TILE_SIZE * BOX2D_SCALE, 7 * TILE_SIZE * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);
	m_platformsPosition.push_back(b2_staticBody);

	// Third line
	b2_bodyDef.position.Set(0 * TILE_SIZE * BOX2D_SCALE, 6 * TILE_SIZE * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);
	m_platformsPosition.push_back(b2_staticBody);

	b2_bodyDef.position.Set(1 * TILE_SIZE * BOX2D_SCALE, 6 * TILE_SIZE * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);
	m_platformsPosition.push_back(b2_staticBody);

	b2_bodyDef.position.Set(TILES_WIDTH * TILE_SIZE * BOX2D_SCALE, 6 * TILE_SIZE * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);
	m_platformsPosition.push_back(b2_staticBody);

	b2_bodyDef.position.Set((TILES_WIDTH - 1) * TILE_SIZE * BOX2D_SCALE, 6 * TILE_SIZE * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);
	m_platformsPosition.push_back(b2_staticBody);

	// Fourth line
	b2_bodyDef.position.Set((5 * TILE_SIZE + TILE_SIZE / 2) * BOX2D_SCALE, 5 * TILE_SIZE * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);
	m_platformsPosition.push_back(b2_staticBody);

	b2_bodyDef.position.Set((7 * TILE_SIZE - TILE_SIZE / 2) * BOX2D_SCALE, 5 * TILE_SIZE * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);
	m_platformsPosition.push_back(b2_staticBody);

	// Fifth line
	b2_bodyDef.position.Set(2 * TILE_SIZE * BOX2D_SCALE, 3.5 * TILE_SIZE * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);
	m_platformsPosition.push_back(b2_staticBody);

	b2_bodyDef.position.Set((TILES_WIDTH - 2) * TILE_SIZE * BOX2D_SCALE, 3.5 * TILE_SIZE * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);
	m_platformsPosition.push_back(b2_staticBody);

	// Last line
	b2_bodyDef.position.Set((TILES_WIDTH / 2) * TILE_SIZE * BOX2D_SCALE, 2 * TILE_SIZE * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);
	m_platformsPosition.push_back(b2_staticBody);
}

void Platforms::render(sf::RenderWindow& window) {
	sf::RectangleShape shape;
	// Draw background
	shape.setSize({ TILE_SIZE * TILES_WIDTH, TILE_SIZE * TILES_HEIGTH });
	shape.setPosition(0, 0);
	shape.setTexture(m_textureBackground);
	window.draw(shape);

	// Draw ground
	shape.setSize({ 64.0f, 64.0f });
	shape.setTexture(m_textureGrass);
	shape.setTextureRect(sf::IntRect({0, 0}, {64, 48}));

	for (unsigned int i = 0; i < TILES_WIDTH; ++i) {
		shape.setPosition({ i * 64.0f, TILE_SIZE * TILES_HEIGTH - PLATFORM_HEIGHT * 2.0f });
		window.draw(shape);
	}

	// Draw platforms
	shape.setSize({ PLATFORM_WIDTH, PLATFORM_HEIGHT });
	shape.setTexture(m_textureGrass);
	shape.setTextureRect(sf::IntRect({0, 0}, {64, 20}));
	shape.setOrigin(PLATFORM_WIDTH * 0.5f, PLATFORM_HEIGHT * 0.5f);
	for (auto position : m_platformsPosition) {
		shape.setPosition(position->GetPosition().x / BOX2D_SCALE, position->GetPosition().y / BOX2D_SCALE);
		window.draw(shape);
	}
}
