/*
*  // Written By: Santiago Arribas Maroto
*  // 2018/2019
*  // Contact: Santisabirra@gmail.com
*/

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "Renderer.hpp"
#include "ColisionListener.hpp"

using namespace std;
using namespace sf;
using namespace B2D_Examples;

	int main()
	{
		//Creamos un Renderizador(Visualización de elementos) y un gestor (Lógica de comportamiento) de la escena 
		Renderer scene_renderer;
		Box2D_WorldManager world_manager;

		//Creamos la ventana y el mundo físico
		RenderWindow window(VideoMode(1280, 720), "Box2D_Example", Style::Titlebar | Style::Close, ContextSettings(32));
		shared_ptr< b2World > physics_world = world_manager.create_world(1280, 720);

		//Temporizador para el frametime, necesario para el control de físicas
		Clock clock_timer;
		float delta_time = 0.017f; 

		//Color para el clear de Render Window
		Color clear_color = Color(50, 50, 50, 255);

		//Creo un Listener para las colisiones del mundo
		CollisionListener listener(&world_manager);
		physics_world->SetContactListener(&listener);

		//Bucle principal de la ejecución
		bool active = true;
		do
		{
			//Reiniciamos el contador del frame
			clock_timer.restart();

			//Captamos eventos de ventana
			Event win_event;
			while (window.pollEvent(win_event))
			{
				if (win_event.type == Event::Closed)
				{
					active = false;
				}
			}

			//Mediante SFML2 Captamos eventos de teclado, con los cuales modificamos elementos de la escena
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ world_manager.GetMainVehicle()->SetDirection(1); }
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ world_manager.GetMainVehicle()->SetDirection(-1);}
			else world_manager.GetMainVehicle()->SetDirection(0);

			//Botón de reinicio para la escena, permite recolocar los elementos de la escena
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) world_manager.RestartScene();

			//Actualizamos el control de físicas de Box3D
			physics_world->Step(delta_time, 4, 8);

			//Renderizamos el nuevo frame tras limpiar el frame anterior
			window.clear(clear_color);
			scene_renderer.render_view(*physics_world, window);
			window.display();

			//Actualizamos DeltaTime
			delta_time = (delta_time + clock_timer.getElapsedTime().asSeconds()) * 0.5f;

			//Comprobamos las animaciónes y el comportamiento de los elementos animados de la escena
			world_manager.AnimateBodies();

		} while (active);

		return EXIT_SUCCESS;
	}
