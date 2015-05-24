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

#include <cassert>
#include <iostream>

#include "Platforms.h"

static constexpr float X_VELOCITY = 4.0f;
static constexpr float Y_VELOCITY = -5.0f;
static constexpr float LIMIT_ANIME = 0.03f;
static constexpr float LIMIT_ANIME_JUMP = 0.10f;

using namespace local;

Hero::Hero(b2World &b2_world, game::ResourceManager &resources, Bones &bones, const sf::Vector2f position) 
: game::Entity(1)
, m_body(nullptr)
, m_isJump(false)
, m_textureStay(nullptr)
, m_textureRun(nullptr)
, m_textureJump(nullptr)
, m_font(nullptr)
, m_direction(Direction::Left)
, m_cptAnime(0)
, m_timeElapsed(0.0f)
, m_bones(bones)
, m_score(0)
, m_move(Move::NONE) {
	b2BodyDef b2_bodyDef;
	b2_bodyDef.type = b2_dynamicBody;
	b2_bodyDef.position.Set(position.x * BOX2D_SCALE, position.y * BOX2D_SCALE);

	float half_w = HERO_WIDTH * BOX2D_SCALE * 0.5f;
	float half_h = HERO_HEIGHT * BOX2D_SCALE * 0.5f;

	static constexpr float X = 0.6f;

	b2Vec2 vertices[8];
	vertices[0].Set(- half_w, X * half_h);
	vertices[1].Set(- X * half_w, half_h);
	vertices[2].Set(  X * half_w, half_h);
	vertices[3].Set(  half_w, X * half_h);
	vertices[4].Set(  half_w, - X * half_h);
	vertices[5].Set(  X * half_w, - half_h);
	vertices[6].Set(- X * half_w, - half_h);
	vertices[7].Set(- half_w, - X * half_h);

	b2PolygonShape b2_boxShape;
	b2_boxShape.Set(vertices, 8);

	b2FixtureDef b2_fixture;
	b2_fixture.shape = &b2_boxShape;

	m_body = b2_world.CreateBody(&b2_bodyDef);
	m_body->CreateFixture(&b2_fixture);

	// Load resources
	m_textureStay = resources.getTexture("stay.png");
	assert(m_textureStay != nullptr);

	m_textureRun = resources.getTexture("tileset_run.png");
	assert(m_textureRun != nullptr);

	m_textureJump = resources.getTexture("tileset_jump.png");
	assert(m_textureJump != nullptr);

	m_font = resources.getFont("font.otf");
	assert(m_font != nullptr);
}

void Hero::goLeft() {
	m_move = Move::LEFT;
}

void Hero::goRight() {
	m_move = Move::RIGHT;
}

void Hero::stop() {
	m_move = Move::NONE;
}

void Hero::jump() {
	// If he isn't jumping
	if (!m_isJump) {
		m_isJump = true;
		m_body->ApplyLinearImpulse(b2Vec2(0.0f, Y_VELOCITY), m_body->GetWorldCenter(), true);
	}
}

void Hero::update(const float dt) {
	// Manage move
	float yVelocity = 0.0f;
	switch (m_move) {
		case Move::LEFT:
			yVelocity = m_body->GetLinearVelocity().y;
			m_body->SetLinearVelocity(b2Vec2(-X_VELOCITY, yVelocity));
			break;

		case Move::RIGHT:
			yVelocity = m_body->GetLinearVelocity().y;
			m_body->SetLinearVelocity(b2Vec2(X_VELOCITY, yVelocity));
			break;

		case Move::NONE:
			yVelocity = m_body->GetLinearVelocity().y;
			m_body->SetLinearVelocity(b2Vec2(0.0f, yVelocity));
			break;
	}

	// Check bones
	auto pos = m_body->GetPosition();
	if (m_bones.hasTakeBone(sf::Vector2f((pos.x / BOX2D_SCALE) - (HERO_WIDTH * 0.5f), (pos.y / BOX2D_SCALE) - (HERO_WIDTH * 0.5f)))) {
		m_score += 50;
	}

	// Check end jump
	if (m_isJump && m_body->GetLinearVelocity().y == 0) {
		m_isJump = false;
		m_cptAnime = 0;
	}

	// Check direction
	if (m_body->GetLinearVelocity().x < -0.1) {
		m_direction = Direction::Left;
	}
	else if (m_body->GetLinearVelocity().x > 0.1) {
		m_direction = Direction::Right;
	}
	else {
		if (!m_isJump) {
			m_cptAnime = 0;
			return;
		}
	}

	// Update the cpt anime
	m_timeElapsed += dt;
	if (!m_isJump && m_timeElapsed >= LIMIT_ANIME) {
		m_timeElapsed = 0.0f;
		++m_cptAnime;
		if (m_cptAnime > 8) {
			m_cptAnime = 1;
		}
	}
	if (m_isJump && m_timeElapsed >= LIMIT_ANIME_JUMP) {
		m_timeElapsed = 0.0f;
		++m_cptAnime;
		if (m_cptAnime > 19) {
			m_cptAnime = 1;
		}
	}
}

void Hero::render(sf::RenderWindow& window) {
	// Render the score
	sf::Text text;
	text.setFont(*m_font);
	text.setString("Score : " + std::to_string(m_score));
	text.setCharacterSize(24);
	text.setColor(sf::Color::Black);
	text.setPosition(10, 10);
	window.draw(text);

	// Render the hero
	auto pos = m_body->GetPosition();

	sf::RectangleShape shape;
	shape.setSize({ 256, 256 });
	shape.setScale(0.5, 0.5f);
	shape.setOrigin(192, 192);
	shape.setPosition(pos.x / BOX2D_SCALE, pos.y / BOX2D_SCALE);

	// Set the texure
	if (m_cptAnime == 0) {
		shape.setTexture(m_textureStay);
	}
	else if (!m_isJump) {
		shape.setTexture(m_textureRun);
		shape.setTextureRect(sf::IntRect({ 256 * ((m_cptAnime - 1) % 4), 256 * ((m_cptAnime - 1) / 4) }, { 256, 256 }));
	}
	else if (m_isJump) {
		shape.setTexture(m_textureJump);
		shape.setTextureRect(sf::IntRect({ 256 * ((m_cptAnime - 1) % 5), 256 * ((m_cptAnime - 1) / 5) }, { 256, 256 }));
	}

	// Set direction
	sf::Vector2f scale = shape.getScale();
	if (m_direction == Direction::Left) {
		shape.setScale(scale.x * -1, scale.y * 1);
	}
	else {
		shape.setScale(scale.x * 1, scale.y * 1);
	}

	window.draw(shape);
}
