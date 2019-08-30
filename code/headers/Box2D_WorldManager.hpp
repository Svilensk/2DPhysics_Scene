/*
*  // Written By: Santiago Arribas Maroto
*  // 2018/2019
*  // Contact: Santisabirra@gmail.com
*/

#include <Box2D/Box2D.h>
#include "Box2D_GameObject.hpp"

using namespace std;
using namespace B2D_Examples;

namespace B2D_Examples
{

class Box2D_WorldManager
{	
private:

	//Referencias a las plataformas animadas
	b2Body* platform01_Bodyref;
	b2Body* platform02_Bodyref;

	b2Body* circle_BodyRef;

	//Puntero al vehiculo principal del jugador
	shared_ptr<B2DGameObject> car_object_ptr;

	//Booleano que indica si el jugador está en contacto con una de las plataformas
	bool player_collision_platform1 = false;
	bool player_collision_platform2 = false;

public:	

	//Creamos el mundo
	shared_ptr< b2World > create_world(float scene_width, float scene_height);

	//Función encargada de la animación de las plataformas
	void AnimateBodies();

	//Funcion que permite recolocar los elementos de la escena
	void RestartScene();

	//Getter del puntero al vehiculo principal
	shared_ptr<B2DGameObject> GetMainVehicle(){			 
		return car_object_ptr;
	}

	//Funciones a las que llama el listener de colisiones al detectar una colisión con el jugador
	//Colisión con plataforma Derecha
	void Platform1Collision(bool collision_result){
		player_collision_platform1 = collision_result; 
	}

	//Colision con plataforma izquierda
	void Platform2Collision(bool collision_result){
		player_collision_platform2 = collision_result;
	}
};
}