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

#include <iostream>

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "game/Group.h"
#include "game/Resources.h"
#include "local/Hero.h"
#include "local/Platforms.h"
#include "local/SFMLDebugDraw.h"

int main(void) {
	sf::RenderWindow window(sf::VideoMode(local::TILE_SIZE * local::TILES_WIDTH, local::TILE_SIZE * local::TILES_HEIGTH), "CyberTech - demo");
	//window.setKeyRepeatEnabled(false);

	ResourceManager resources;
	resources.addSearchDir("../data");
	
	// Create the world physic
	b2World b2_world(b2Vec2(0.0f, 10.0f));

	// Debug Box2D
	SFMLDebugDraw debugDraw(window);
	b2_world.SetDebugDraw(&debugDraw);
	debugDraw.SetFlags(b2Draw::e_shapeBit);

	local::Platforms platforms(b2_world, resources);

	local::Hero hero(b2_world, resources, { local::TILE_SIZE * local::TILES_WIDTH / 2.0f, local::TILE_SIZE * (local::TILES_HEIGTH - 1) * 0.5f });

	game::Group group;
	group.addEntity(hero);
	group.addEntity(platforms);
	
	sf::Clock clock;
	float dt = 0.0f;

	while (window.isOpen()) {
	sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				switch  (event.key.code) {
					case sf::Keyboard::Right:
						hero.goRight();
						break;

					case sf::Keyboard::Left:
						hero.goLeft();
						break;

					case sf::Keyboard::Space:
						hero.jump();
						break;

					default:
						break;
				}
			}

			if (event.type == sf::Event::KeyReleased) {
				switch  (event.key.code) {
					case sf::Keyboard::Right:
					case sf::Keyboard::Left:
						hero.stop();
						break;

					default:
						break;
				}
			}
		}

		// update
		dt = clock.restart().asSeconds();
		b2_world.Step(dt, 8, 3);
		group.update(dt);

		// render
		window.clear(sf::Color::White);
		group.render(window);
		b2_world.DrawDebugData();

		window.display();
	}

	return EXIT_SUCCESS;
}
