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

static constexpr float HERO_SIZE = 32.0f;
static constexpr float X_VELOCITY = 2.0f;
static constexpr float Y_VELOCITY = -6.0f;

using namespace local;

Hero::Hero(b2World &b2_world, const sf::Vector2f position) 
: game::Entity(1)
, m_body(nullptr)
, m_isJump(false) {
	b2BodyDef b2_bodyDef;
	b2_bodyDef.type = b2_dynamicBody;
	b2_bodyDef.position.Set(position.x * BOX2D_SCALE, position.y * BOX2D_SCALE);

	b2PolygonShape b2_boxShape;
	b2_boxShape.SetAsBox(HERO_SIZE * BOX2D_SCALE * 0.5f, HERO_SIZE * BOX2D_SCALE * 0.5f);

	b2FixtureDef b2_fixture;
	b2_fixture.shape = &b2_boxShape;

	m_body = b2_world.CreateBody(&b2_bodyDef);
	m_body->CreateFixture(&b2_fixture);
}

void Hero::goLeft() {
	float yVelocity = m_body->GetLinearVelocity().y;
	m_body->SetLinearVelocity(b2Vec2(-X_VELOCITY, yVelocity));
}

void Hero::goRight() {
	float yVelocity = m_body->GetLinearVelocity().y;
	m_body->SetLinearVelocity(b2Vec2(X_VELOCITY, yVelocity));
}

void Hero::stop() {
	float yVelocity = m_body->GetLinearVelocity().y;
	m_body->SetLinearVelocity(b2Vec2(0.0f, yVelocity));
}

void Hero::jump() {
	// If he isn't jumping
	if (!m_isJump) {
		m_isJump = true;
		m_body->ApplyLinearImpulse(b2Vec2(0.0f, Y_VELOCITY), m_body->GetWorldCenter(), true);
	}
}

void Hero::update(const float dt) {
	// Check end jump
	if (m_isJump && m_body->GetLinearVelocity().y == 0) {
		m_isJump = false;
	}
}

void Hero::render(sf::RenderWindow& window) {
	auto pos = m_body->GetPosition();

	sf::RectangleShape shape({ HERO_SIZE, HERO_SIZE});
	shape.setOrigin(HERO_SIZE / 2, HERO_SIZE / 2);
	shape.setPosition(pos.x / BOX2D_SCALE, pos.y / BOX2D_SCALE);
	shape.setFillColor(sf::Color::Red);

	window.draw(shape);
}
