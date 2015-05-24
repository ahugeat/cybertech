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

Platforms::Platforms(b2World &b2_world, ResourceManager &resources) 
: m_textureBackground(nullptr) {
	// Load texture
	m_textureBackground = resources.getTexture("background.png");
	assert(m_textureBackground != nullptr);

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
	b2_bodyDef.position.Set(8 * TILE_SIZE * BOX2D_SCALE, 8 * TILE_SIZE * BOX2D_SCALE);
	b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
	b2_staticBody->CreateFixture(&b2_fixture);
	m_platformsPosition.push_back(b2_staticBody);


	// Setup physic
	/*b2BodyDef b2_bodyDef;
	b2_bodyDef.type = b2_staticBody;
	b2_bodyDef.angle = 0;

	b2PolygonShape b2_boxShape;
	b2_boxShape.SetAsBox(TILE_SIZE * BOX2D_SCALE * 0.5f, TILE_SIZE * BOX2D_SCALE * 0.5f);

	b2FixtureDef b2_fixture;
	b2_fixture.shape = &b2_boxShape;
	b2_fixture.density = 1.0f;
	b2_fixture.friction = 0.3f;*/
	//b2_fixture.density = 1;

	/*for (unsigned int i = 0; i < TILES_WIDTH; ++i) {
		for (unsigned int j = 0; j < TILES_HEIGTH - 1; ++j)
		{
			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * TILES_WIDTH) * 4];*/


			// define its 4 corners
			/*quad[0].position = sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
			quad[1].position = sf::Vector2f((i + 1) * TILE_SIZE, j * TILE_SIZE);
			quad[2].position = sf::Vector2f((i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
			quad[3].position = sf::Vector2f(i * TILE_SIZE, (j + 1) * TILE_SIZE);*/

			/*if (i == 5 && j == TILES_HEIGTH - 3) {
				quad[0].color = sf::Color::Green;
				quad[1].color = sf::Color::Green;
				quad[2].color = sf::Color::Green;
				quad[3].color = sf::Color::Red;

				m_matrixCollision[i + j * TILES_WIDTH] = true;

				b2_bodyDef.position.Set((i * TILE_SIZE) * BOX2D_SCALE, (j * TILE_SIZE) * BOX2D_SCALE);

				quad[0].position = sf::Vector2f(b2_bodyDef.position.x / BOX2D_SCALE, b2_bodyDef.position.y / BOX2D_SCALE);
				quad[1].position = sf::Vector2f(b2_bodyDef.position.x / BOX2D_SCALE + TILE_SIZE, b2_bodyDef.position.y / BOX2D_SCALE);
				quad[2].position = sf::Vector2f(b2_bodyDef.position.x / BOX2D_SCALE + TILE_SIZE, b2_bodyDef.position.y / BOX2D_SCALE + TILE_SIZE);
				quad[3].position = sf::Vector2f(b2_bodyDef.position.x / BOX2D_SCALE, b2_bodyDef.position.y / BOX2D_SCALE + TILE_SIZE);

				b2Body* b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
				b2_staticBody->CreateFixture(&b2_fixture);
			}
			else {*/
				/*// define its 4 color
				quad[0].color = sf::Color::White;
				quad[1].color = sf::Color::White;
				quad[2].color = sf::Color::White;
				quad[3].color = sf::Color::White;*/

				/*m_matrixCollision[i + j * TILES_WIDTH] = false;
			}
		}
	}*/

	// Define last line
	/*for (unsigned int i = 0; i < TILES_WIDTH; ++i) {
		unsigned int j = TILES_HEIGTH - 1;
		// get a pointer to the current tile's quad
		sf::Vertex* quad = &m_vertices[(i + j * TILES_WIDTH) * 4];

		// define its 4 corners
		quad[0].position = sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
		quad[1].position = sf::Vector2f((i + 1) * TILE_SIZE, j * TILE_SIZE);
		quad[2].position = sf::Vector2f((i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
		quad[3].position = sf::Vector2f(i * TILE_SIZE, (j + 1) * TILE_SIZE);

		quad[0].color = sf::Color::Green;
		quad[1].color = sf::Color::Green;
		quad[2].color = sf::Color::Green;
		quad[3].color = sf::Color::Red;

		m_matrixCollision[i + j * TILES_WIDTH] = true;

		b2_bodyDef.position.Set((i * TILE_SIZE) * BOX2D_SCALE, (j * TILE_SIZE) * BOX2D_SCALE);

		b2Body* b2_staticBody = b2_world.CreateBody(&b2_bodyDef);
		b2_staticBody->CreateFixture(&b2_fixture);
	}*/
}

void Platforms::render(sf::RenderWindow& window) {
	sf::RectangleShape shape;
	// Draw background
	shape.setSize({ TILE_SIZE * TILES_WIDTH, TILE_SIZE * TILES_HEIGTH });
	shape.setPosition(0, 0);
	shape.setTexture(m_textureBackground);
	window.draw(shape);

	// Draw ground
	shape.setSize({ TILE_SIZE * TILES_WIDTH, PLATFORM_HEIGHT * 2.0f });
	shape.setPosition({ 0.0f, TILE_SIZE * TILES_HEIGTH - PLATFORM_HEIGHT * 2.0f });
	shape.setFillColor(sf::Color(244, 164, 96));
	shape.setTexture(nullptr);
	window.draw(shape);

	// Draw platforms
	shape.setSize({ PLATFORM_WIDTH, PLATFORM_HEIGHT });
	shape.setFillColor(sf::Color::Green);
	for (auto position : m_platformsPosition) {
		shape.setOrigin(PLATFORM_WIDTH * 0.5f, PLATFORM_HEIGHT * 0.5f);
		shape.setPosition(position->GetPosition().x / BOX2D_SCALE, position->GetPosition().y / BOX2D_SCALE);
		window.draw(shape);
	}
}
