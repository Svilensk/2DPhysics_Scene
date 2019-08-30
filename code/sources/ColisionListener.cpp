/*
*  // Written By: Santiago Arribas Maroto
*  // 2018/2019
*  // Contact: Santisabirra@gmail.com
*/

#include "ColisionListener.hpp"

namespace B2D_Examples
{
	void CollisionListener::BeginContact(b2Contact* contact)
	{
		//Guardamos referencias a los elementos que provocaron la colisión
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();
		b2Body* body1 = fixtureA->GetBody();
		b2Body* body2 = fixtureB->GetBody();

		//PLATAFORMA 1 (Der): Al colisionar la plataforma derecha (ID 001) con la rueda trasera del vehiculo (ID 500) se activa la colisión que anima la Plataforma
		if ((int)body1->GetUserData() == 001 && (int)body2->GetUserData() == 500) { world_manager->Platform1Collision(true); }

		//PLATAFORMA 1 (Der): Al colisionar el suelo inferior (ID 101) con la rueda delantera del vehiculo (ID 501) se desactiva la colisión que anima la Plataforma
		if ((int)body1->GetUserData() == 101 && (int)body2->GetUserData() == 501) { world_manager->Platform1Collision(false); }

		//PLATAFORMA 1 (Der): Al colisionar el suelo superior (ID 105) con la rueda delantera del vehiculo (ID 501) se desactiva la colisión que anima la Plataforma
		if ((int)body1->GetUserData() == 105 && (int)body2->GetUserData() == 501) { world_manager->Platform1Collision(false); }

		//PLATAFORMA 2 (Izq): Al colisionar la plataforma izquierda (ID 002) con la rueda delantera del vehiculo (ID 501) se activa la colisión que anima la Plataforma
		if ((int)body1->GetUserData() == 002 && (int)body2->GetUserData() == 501) { world_manager->Platform2Collision(true); }

		//PLATAFORMA 2 (Izq): Al colisionar la rampa destino (ID 002) con la rueda trasera del vehiculo (ID 501) se desactiva la colisión que anima la Plataforma
		if ((int)body1->GetUserData() == 105 && (int)body2->GetUserData() == 500) { world_manager->Platform2Collision(false); }

		//PLATAFORMA 2 (Izq): Al colisionar el suelo superior2 (ID 106) con la rueda trasera del vehiculo (ID 501) se desactiva la colisión que anima la Plataforma
		if ((int)body1->GetUserData() == 106 && (int)body2->GetUserData() == 501) { world_manager->Platform2Collision(false); }
	}

	void CollisionListener::EndContact(b2Contact * contact) {}
}