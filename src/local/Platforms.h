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

#ifndef LOCAL_PLATFORMS_H
#define LOCAL_PLATFORMS_H

#include <vector>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "../game/Entity.h"
#include "../game/Resources.h"

namespace local {
	static constexpr float BOX2D_SCALE = 0.01f;
	static constexpr unsigned int TILE_SIZE = 64;
	static constexpr unsigned int TILES_WIDTH = 12;
	static constexpr unsigned int TILES_HEIGTH = 10;
	static constexpr unsigned int PLATFORM_WIDTH = TILE_SIZE;
	static constexpr unsigned int PLATFORM_HEIGHT = 16;

	class Platforms : public game::Entity {
	public:
		Platforms(b2World &b2_world, ResourceManager &resources);

		virtual void render(sf::RenderWindow& window) override;

	private:
		std::vector<b2Body*> m_platformsPosition;
		sf::Texture *m_textureBackground;
		sf::Texture *m_textureGrass;
	};

}

#endif // LOCAL_PLATFORM_H
