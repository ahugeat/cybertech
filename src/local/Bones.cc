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

#include "Platforms.h"

static constexpr unsigned int NUMBER_BONES = 5;
static constexpr float RATIO = 32.0f / 256.0f;

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

void Bones::update(const float dt) {
	
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
