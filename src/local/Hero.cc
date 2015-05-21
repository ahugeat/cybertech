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

#include "Hero.h"

static constexpr float RADIUS = 20.0f;
static constexpr float VELOCITY = 90.0f;

using namespace local;

Hero::Hero(const sf::Vector2f position) 
: m_position(position)
, m_x(Direction::STAY)
, m_y(Direction::STAY) {

}

void Hero::setDirectionX(Direction direction) {
	m_x = direction;
}

void Hero::setDirectionY(Direction direction) {
	m_y = direction;
}

void Hero::update(const float dt) {
	sf::Vector2f velocity(0.0f, 0.0f);

	// Move in X
	if(m_x == Direction::FORWARD) {
		velocity.x = VELOCITY;
	}
	else if (m_x == Direction::BACKWARD) {
		velocity.x = -VELOCITY;
	}

	m_position += velocity * dt;
}

void Hero::render(sf::RenderWindow& window) {
	sf::CircleShape shape(RADIUS);
	shape.setOrigin(RADIUS, RADIUS);
	shape.setPosition(m_position);
	shape.setFillColor(sf::Color::Red);

	window.draw(shape);
}
