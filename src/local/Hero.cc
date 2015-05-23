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

#include <iostream>

static constexpr float RADIUS = 20.0f;
static constexpr float X_VELOCITY = 2.0f;
static constexpr float Y_VELOCITY = 300.0f;
static constexpr float GRAVITY = 450.0f;

using namespace local;

Hero::Hero(b2World &b2_world, const sf::Vector2f position) 
: game::Entity(1)
, m_body(nullptr)
, m_isJump(false) {
	b2BodyDef b2_bodyDef;
	b2_bodyDef.type = b2_dynamicBody;
	b2_bodyDef.position.Set(position.x * BOX2D_SCALE, position.y * BOX2D_SCALE);

	b2PolygonShape b2_boxShape;
	b2_boxShape.SetAsBox((TILE_SIZE / 2) * BOX2D_SCALE * 0.5f, TILE_SIZE * BOX2D_SCALE * 0.5f);

	b2FixtureDef b2_fixture;
	b2_fixture.shape = &b2_boxShape;

	m_body = b2_world.CreateBody(&b2_bodyDef);
	m_body->CreateFixture(&b2_fixture);
}

void Hero::goLeft() {
	m_body->SetLinearVelocity(b2Vec2(-X_VELOCITY, 0.0f));
}

void Hero::goRight() {
	m_body->SetLinearVelocity(b2Vec2(X_VELOCITY, 0.0f));
}

void Hero::stop() {
	m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
}

void Hero::jump() {
	if (!m_isJump) {
		m_isJump = true;
	}
}

void Hero::update(const float dt) {
	// Manage jump
	/*if (m_isJump) {
		m_velocity.y += dt * GRAVITY;
	}

	m_position += m_velocity * dt;

	if (m_platforms.hasCollision({ m_position.x + RADIUS, m_position.y + RADIUS })) {
		m_velocity.y = 0.0f;
		m_isJump = false;
		// Fix position
		float y_fix = ((static_cast<unsigned int>(m_position.y + RADIUS ) / TILE_SIZE) * TILE_SIZE) - RADIUS;
		m_position.y = y_fix;
	}*/

	// Check end of jump
	/*if (m_isJump && m_position.y >= m_startJump) {
		m_position.y = m_startJump;
		m_isJump = false;
		m_velocity.y = 0.0f;
	}*/
}

void Hero::render(sf::RenderWindow& window) {
	auto pos = m_body->GetPosition();

	sf::RectangleShape shape({ TILE_SIZE / 2, TILE_SIZE});
	shape.setOrigin(TILE_SIZE / 4, TILE_SIZE / 2);
	shape.setPosition(pos.x / BOX2D_SCALE, pos.y / BOX2D_SCALE);
	shape.setFillColor(sf::Color::Red);

	window.draw(shape);
}
