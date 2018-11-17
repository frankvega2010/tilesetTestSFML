//#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "STP/TMXLoader.hpp"
#include "pugixml.hpp"
#include "pugiconfig.hpp"
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

void main()
{
	const int maxColisionsBoxes = 4;

	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file("res/assets/tiles/testlevel.tmx"); // Locates the file to be used.

	pugi::xml_node object = doc.child("map").child("objectgroup"); // Clean way to locate a specific group of attributes instead of always typing the same command.


		/////////////////////////
		// Example :
		/*Manually

		doc.child("map").child("objectgroup").child("object").attribute("x").as_int()
		doc.child("map").child("objectgroup").child("object").attribute("y").as_int()

		With xml_node

		object()->attribute("x").as_int();
		object()->attribute("y").as_int();*/
		//
		/////////////////////////

	pugi::xml_node_iterator someObjects = object.begin(); // test purposes, not used for making collision shapes. 
	// It was used to manually select objects ids.

	sf::ContextSettings settings; // render settings
	settings.antialiasingLevel = 8;

	//sf::RenderWindow window(sf::VideoMode(1300, 800), "STP Example");
	sf::RenderWindow window(sf::VideoMode(1300, 800), "STP Example", sf::Style::Default, settings);


	tmx::TileMap map("res/assets/tiles/testlevel.tmx"); // TileMap

	sf::CircleShape triangle(80.f, 3); // player
	

	map.ShowObjects(); // Display all the layer objects.

	sf::View view(sf::FloatRect(200.f, 200.f, 800.f, 600.f));

	//map.GetLayer("World").visible = false; // Hide a Layer named World

										   // Start the game loop

	view.setCenter(1930.0f, 450.f);
	view.zoom(2.0f);
	triangle.move(1930.0f, 450.0f);

	sf::RectangleShape test; // not used in final game, just for testing purposes.
	sf::RectangleShape rectangles[maxColisionsBoxes];


	someObjects = ++someObjects; // manually changing the object id
	someObjects = ++someObjects; // manually changing the object id

	cout << someObjects->attribute("x").as_int(); // it will use the third object "x" value.


	//// Adding Colission box Rectangles from the .tmx Tilemap File
	//
	int i = 0;
	for (pugi::xml_node_iterator it = object.begin(); it != object.end(); ++it)
	{
		rectangles[i].setPosition(sf::Vector2f(it->attribute("x").as_int(),
												it->attribute("y").as_int()));

		rectangles[i].setSize(sf::Vector2f(it->attribute("width").as_int(),
											it->attribute("height").as_int()));

		rectangles[i].setFillColor(sf::Color::Green);
		i++;
	}
	i = 0;
	//
	////
	test.setPosition(sf::Vector2f(0, 0));
	test.setSize(sf::Vector2f(0, 0));
	test.setFillColor(sf::Color::Transparent);

	sf::Clock deltaClock;
	sf::Time deltaTime;

	int DefaultSpeedX = 0.0f;
	int DefaultSpeedY = 0.0f;
	bool unBool = false;
	bool otroBool = false;
	bool unBoolY = false;
	bool otroBoolY = false;

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

		for (int i = 0; i < maxColisionsBoxes; i++)
		{
			window.draw(rectangles[i]);
		}

		if (triangle.getPosition().x > view.getCenter().x + 300)
		{
			if (!(unBool))
			{
				unBool = true;
				otroBool = false;
			}
		}
		else if (triangle.getPosition().x < view.getCenter().x - 300)
		{
			if (!(otroBool))
			{
				otroBool = true;
				unBool = false;
			}
		}

		if (triangle.getPosition().y > view.getCenter().y + 300)
		{
			if (!(unBoolY))
			{
				unBoolY = true;
				otroBoolY = false;
			}
		}
		else if (triangle.getPosition().y < view.getCenter().y - 300)
		{
			if (!(otroBoolY))
			{
				otroBoolY = true;
				unBoolY = false;
			}
		}

		

		if (unBoolY) view.setCenter(view.getCenter().x, triangle.getPosition().y - 300); //triangle.getPosition().y - 300
		if (otroBoolY) view.setCenter(view.getCenter().x, triangle.getPosition().y + 300); ////triangle.getPosition().y + 300

		if (unBool) view.setCenter(triangle.getPosition().x - 300, view.getCenter().y);
		if (otroBool) view.setCenter(triangle.getPosition().x + 300, view.getCenter().y);

		DefaultSpeedX = 800.0f;
		DefaultSpeedY = 800.0f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			otroBoolY = false;
			triangle.move(0, (DefaultSpeedY * deltaTime.asSeconds()));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			unBoolY = false;
			triangle.move(0, (DefaultSpeedY * deltaTime.asSeconds())*(-1));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			unBool = false;
			triangle.move((DefaultSpeedX * deltaTime.asSeconds())*(-1), 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			otroBool = false;
			triangle.move((DefaultSpeedX * deltaTime.asSeconds()), 0);
		}

		if (triangle.getGlobalBounds().intersects(test.getGlobalBounds()))
		{
			triangle.setPosition(triangle.getPosition().x,test.getPosition().y - (triangle.getLocalBounds().height));
			map.GetLayer("plataforma").SetColor({255,0,0});
		}
		else
		{
			map.GetLayer("plataforma").SetColor({ 255,255,255});
		}

		for (int i = 0; i < maxColisionsBoxes; i++)
		{
			if (triangle.getGlobalBounds().intersects(rectangles[i].getGlobalBounds()))
			{
				triangle.setPosition(triangle.getPosition().x, rectangles[i].getPosition().y - (triangle.getLocalBounds().height));
				map.GetLayer("plataforma").SetColor({ 255,0,0 });
			}
			else
			{
				map.GetLayer("plataforma").SetColor({ 255,255,255 });
			}
		}
		
		window.setView(view);
		//view.move(100.0f, 100.f);
		// Update the window
		window.display();

		
		deltaTime = deltaClock.restart();
	}
}