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

#ifndef LOCAL_HERO_H
#define LOCAL_HERO_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "../game/Entity.h"
#include "../game/Resources.h"

namespace local {

	class Hero : public game::Entity {
	public:
		Hero(b2World &b2_world, ResourceManager &resources, const sf::Vector2f position);

		void goLeft();
		void goRight();
		void stop();

		void jump();

		virtual void update(const float dt) override;
		virtual void render(sf::RenderWindow& window) override;

	private:
		enum class Direction {
			Left,
			Right,
		};

		b2Body *m_body;
		bool m_isJump;
		sf::Texture *m_textureStay;
		sf::Texture *m_textureRun;
		Direction m_direction;
		int m_cptAnime;
		float m_timeElapsed;
	};

}

#endif // LOCAL_HERO_H
