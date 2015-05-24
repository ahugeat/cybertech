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

#include "Bones.h"

#include <cassert>
#include <iostream>

#include "Hero.h"
#include "Platforms.h"

static constexpr unsigned int NUMBER_BONES = 5;
static constexpr float BONE_SIZE = 32.0f;
static constexpr float RATIO = BONE_SIZE / 256.0f;
static constexpr float TIME_POP = 4.0f;

using namespace local;

Bones::Bones(game::ResourceManager &resources, game::Random &random) 
: game::Entity(1)
, m_random(random)
, m_texture(nullptr)
, m_timeElapsed(0.0f) {
	// Load texture
	m_texture = resources.getTexture("bone.png");
	assert(m_texture != nullptr);

	// Generate the bones
	for (unsigned int i = 0; i < NUMBER_BONES; ++i) {
		sf::Vector2f position;

		do {
			position.x = random.computeUniformInteger(1, TILES_WIDTH-1) * TILE_SIZE;
			position.y = random.computeUniformInteger(2, TILES_HEIGTH-2) * TILE_SIZE + 16.0f;
		} while(std::find(m_positions.begin(), m_positions.end(), position) != m_positions.end());

		m_positions.push_back(position);
	}

}

bool Bones::hasTakeBone(sf::Vector2f position) {
	bool found = false;
	unsigned int i = 0;

	// Check for each bone if hero take it
	while (!found && i < m_positions.size()) {
		sf::IntRect rectHero(sf::Vector2i(position.x, position.y), sf::Vector2i(HERO_WIDTH, HERO_HEIGHT));
		sf::IntRect rectBone(sf::Vector2i(m_positions[i].x, m_positions[i].y), sf::Vector2i(BONE_SIZE, BONE_SIZE));

		found = rectHero.intersects(rectBone);
		if (found) {
			m_positions.erase(m_positions.begin()+i);
		}
		++i;
	}

	return found;
}

void Bones::update(const float dt) {
	// Pop new bones
	m_timeElapsed += dt;
	if (m_timeElapsed >= TIME_POP) {
		m_timeElapsed = 0.0f;
		sf::Vector2f position;

		do {
			position.x = m_random.computeUniformInteger(1, TILES_WIDTH-1) * TILE_SIZE;
			position.y = m_random.computeUniformInteger(2, TILES_HEIGTH-2) * TILE_SIZE + 16.0f;
		} while(std::find(m_positions.begin(), m_positions.end(), position) != m_positions.end());

		m_positions.push_back(position);
	}
}

void Bones::render(sf::RenderWindow& window) {
	sf::RectangleShape shape;
	shape.setSize({ 256.0f, 256.0f });
	shape.setTexture(m_texture);
	shape.setScale(RATIO, RATIO);

	for (auto position : m_positions) {
		shape.setPosition(position);
		window.draw(shape);
	}
}
