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

Platforms::Platforms() 
: m_vertices(sf::Quads, TILES_WIDTH * TILES_HEIGTH * 4) {
	for (unsigned int i = 0; i < TILES_WIDTH; ++i) {
		for (unsigned int j = 0; j < TILES_HEIGTH; ++j)
		{
			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * TILES_WIDTH) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
			quad[1].position = sf::Vector2f((i + 1) * TILE_SIZE, j * TILE_SIZE);
			quad[2].position = sf::Vector2f((i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
			quad[3].position = sf::Vector2f(i * TILE_SIZE, (j + 1) * TILE_SIZE);

			// define its 4 color
			if (j != TILES_HEIGTH - 1) {
				quad[0].color = sf::Color::White;
				quad[1].color = sf::Color::White;
				quad[2].color = sf::Color::White;
				quad[3].color = sf::Color::White;

				m_matrixCollision[i + j * TILES_WIDTH] = false;
			}
			else {
				quad[0].color = sf::Color::Green;
				quad[1].color = sf::Color::Green;
				quad[2].color = sf::Color::Green;
				quad[3].color = sf::Color::Red;

				m_matrixCollision[i + j * TILES_WIDTH] = true;
			}
		}
	}
}

void Platforms::render(sf::RenderWindow& window) {
	window.draw(m_vertices);
}
