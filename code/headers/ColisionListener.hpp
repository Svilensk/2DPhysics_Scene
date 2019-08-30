/*
*  // Written By: Santiago Arribas Maroto
*  // 2018/2019
*  // Contact: Santisabirra@gmail.com
*/

#include <Box2D/Box2D.h>
#include "Box2D_WorldManager.hpp"

namespace B2D_Examples
{
	class CollisionListener : public b2ContactListener
	{
		//Referencia al gestor del mundo
		Box2D_WorldManager* world_manager;

	public:

		CollisionListener(Box2D_WorldManager* world_manager) : world_manager(world_manager){};

		//Funciones llamadas al iniciar un contacto y al finalizarlo
		void BeginContact(b2Contact* contact);
		void EndContact  (b2Contact* contact);
	};
}
