//#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "STP/TMXLoader.hpp"

void main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "STP Example");
	tmx::TileMap map("res/assets/tiles/algo.tmx");

	map.ShowObjects(); // Display all the layer objects.

	sf::View view(sf::FloatRect(200.f, 200.f, 800.f, 600.f));

	//map.GetLayer("World").visible = false; // Hide a Layer named World

										   // Start the game loop

	view.setCenter(400.f, 0.f);
	view.zoom(1.0f);
	//view.move(300.0f, 300.f);
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			view.move(0.0f, 0.05f);
		}
		
		window.setView(view);
		//view.move(100.0f, 100.f);
		// Update the window
		window.display();

	}
}