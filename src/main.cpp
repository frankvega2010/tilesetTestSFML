//#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "STP/TMXLoader.hpp"
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

void main()
{
	//struct untest
	//{
	//	Vector4
	//};

	std::string algo = "algo";

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	//sf::RenderWindow window(sf::VideoMode(1300, 800), "STP Example");
	sf::RenderWindow window(sf::VideoMode(1300, 800), "STP Example", sf::Style::Default, settings);
	tmx::TileMap map("res/assets/tiles/testlevel.tmx");

	sf::CircleShape triangle(80.f, 3);
	

	//map.ShowObjects(); // Display all the layer objects.

	sf::View view(sf::FloatRect(200.f, 200.f, 800.f, 600.f));

	//map.GetLayer("World").visible = false; // Hide a Layer named World

										   // Start the game loop

	view.setCenter(450.f, 450.f);
	view.zoom(2.0f);
	triangle.move(450.0f, 450.0f);
	//view.move(300.0f, 300.f);

	/*cout << map.GetLayer("fondo").GetHeight();
	cout << map.GetLayer("fondo").GetWidth();*/

	cout << map.GetTileSet(1)->GetTileWidth() << endl;
	cout << map.GetTileSet(1)->GetTileHeight() << endl;
	//sf::Vector2f asd = map.GetTileSet(1)->GetTile(1).GetTextureRect();
	sf::RectangleShape test;

	test.setSize(sf::Vector2f(map.GetTileSet(30)->GetTileWidth(), map.GetTileSet(30)->GetTileHeight()));
	//test.setPosition(sf::Vector2f(2, 2));
	cout << map.GetTileSet(30);
	map.GetLayer("1");
	map.GetTileSet(1)->GetTile(0);
	
	test.setPosition(sf::Vector2f(map.GetTileSet(30)->GetTile(0).GetTextureRect().left, map.GetTileSet(30)->GetTile(0).GetTextureRect().top));
	test.setFillColor(sf::Color::Green);

	while (window.isOpen()) {
		// Process events
		sf::Event event;
		while (window.pollEvent(event)) {
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// Clear screen
		window.clear();
		// Draw the map
		window.draw(map);
		window.draw(test);
		window.draw(triangle);

		

		/*view.move(0.0f, 1.0f);

		triangle.move(view.getCenter());*/

		
		
		
		// ;

		//view.move(triangle.getOrigin());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			view.move(0.0f, 1.0f);
			triangle.move(0,1.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			view.move(0.0f, -1.0f);
			triangle.move(0, -1.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			view.move(-1.0f, 0.0f);
			triangle.move(-1.0f, 0.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			view.move(1.0f, 0.0f);
			triangle.move(1.0f, 0.0f);
		}

		if (triangle.getGlobalBounds().intersects(test.getGlobalBounds()))
		{
			map.GetLayer("1").SetColor({255,0,0});
		}
		else
		{
			map.GetLayer("1").SetColor({ 255,255,255});
		}
		
		window.setView(view);
		//view.move(100.0f, 100.f);
		// Update the window
		window.display();

	}
}