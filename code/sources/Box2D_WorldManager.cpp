/*
*  // Written By: Santiago Arribas Maroto
*  // 2018/2019
*  // Contact: Santisabirra@gmail.com
*/

#include "Box2D_WorldManager.hpp"

namespace B2D_Examples
{
	//Creamos el mundo
	shared_ptr< b2World > Box2D_WorldManager::create_world(float scene_width, float scene_height)
	{
		//Creamos un contexto en el mundo físico, y creamos los elementos que compondrán el mundo,
		//Usamos el contructor de RigidBodies para crear los elementos y colocarlos en la escena
		shared_ptr< b2World > pysical_world(new b2World(b2Vec2(0, -100.f)));
		{
			//Creamos la plataforma animada derecha
			           //(ID, Contexto, tipo de body, Pos X, Pos Y, Rotación)
			RigidBody box(001, pysical_world, b2_kinematicBody, 1190, 10, 0 );
			box.SetShape(90, 10, Box_Shape);
			Box2D_WorldManager::platform01_Bodyref = box.GetBody();

			//Creamos otra plataforma animada, en la izquierda
			RigidBody box2(002, pysical_world, b2_kinematicBody, 400, 400, 0);
			box2.SetShape(100, 10, Box_Shape);
			Box2D_WorldManager::platform02_Bodyref = box2.GetBody();

			//Añadimos un Rigidbody circulo, el cual deberá ser transportado y ajustamos sus propiedades
						  //(ID, Contexto, tipo de body, Pos X, Pos Y, Rotación)
			RigidBody circle(999, pysical_world, b2_dynamicBody, 150, 300, 0   );
			circle.SetDensity(.1f);
			circle.SetFriction(1.f);
			circle.SetRestitution(.1f);
			circle.SetShape(20, 20, Circle_Shape);
			Box2D_WorldManager::circle_BodyRef = circle.GetBody();

			//Creamos todos los componenetes estáticos de la escena, Suelo, paredes y rampas

			//Suelo 101
			RigidBody floor(101, pysical_world, b2_staticBody, 300, 10, 0);
			floor.SetShape(800, 10, Box_Shape);

			//Suelo 102
			RigidBody floor_01(102, pysical_world, b2_staticBody, 100, 120, 0);
			floor_01.SetShape(200, 100, Box_Shape);

			//Suelo 103
			RigidBody floor_02(103, pysical_world, b2_staticBody, 300, 20, 0);
			floor_02.SetShape(100, 100, Custom_RectTriangleShape);

			//Suelo 104
			RigidBody floor_03(104, pysical_world, b2_staticBody, 600, 400, 0);
			floor_03.SetShape(100, 10, Box_Shape);

			//Suelo 105
			RigidBody floor_04(105, pysical_world, b2_staticBody, 1000, 500, 0);
			floor_04.SetShape(100, 10, Box_Shape);

			//Suelo 106
			RigidBody floor_05(106, pysical_world, b2_staticBody, 150, 390, 0);
			floor_05.SetShape(75, 20, Custom_RampShape);

			//Suelo 107
			RigidBody floor_06(107, pysical_world, b2_staticBody, 150, 390, 0);
			floor_06.SetShape(-75, 20, Custom_InvertedRampShape);

			//Suelo 108
			RigidBody floor_07(108, pysical_world, b2_staticBody, 700, 390, 0);
			floor_07.SetShape(100, 20, Custom_RampShape);

			//Pared 201
			RigidBody wall_01(201, pysical_world, b2_staticBody, 1275, 0, 0);
			wall_01.SetShape(5, 720, Box_Shape);

			//Pared 202
			RigidBody wall_02(202, pysical_world, b2_staticBody, 5, 0, 0);
			wall_02.SetShape(5, 720, Box_Shape);

			//Creamos el GameObject vehiculo del jugador (ID Ruedas / ID Chasis / Contexto / Pos X / Pos Y)
			B2DGameObject carObject(500, 301, pysical_world, 150, 250);

			//Guardamos el puntero al vehiculo
			car_object_ptr = make_shared<B2DGameObject>(carObject);
		}
		return pysical_world;
	}

	void Box2D_WorldManager::AnimateBodies()
	{
		//Control de la animación ascendente de la plataforma derecha
		//Si la plataforma está en la parte inferior y detecta una colisión con el jugador, asciende
		if (platform01_Bodyref->GetPosition().y <= 10 && !player_collision_platform1) { platform01_Bodyref->SetLinearVelocity(b2Vec2(0, 0)); }
		else if (platform01_Bodyref->GetPosition().y <= 10 && player_collision_platform1) { platform01_Bodyref->SetLinearVelocity(b2Vec2(0, 50)); }

		//Control de la animación descendente de la plataforma derecha
		//Similar ocurre con el descenso, salvo que se tiene en cuenta si el jugador no está en la plataforma y las unidades de velocidad son negativas
		if (platform01_Bodyref->GetPosition().y >= 500 && player_collision_platform1) { platform01_Bodyref->SetLinearVelocity(b2Vec2(0, 0)); }
		else if (platform01_Bodyref->GetPosition().y >= 500 && !player_collision_platform1) { platform01_Bodyref->SetLinearVelocity(b2Vec2(0, -50)); }

		//Control de animación ascendente de la plataforma izquierda
		if (platform02_Bodyref->GetPosition().y <= 400 && !player_collision_platform2) { platform02_Bodyref->SetLinearVelocity(b2Vec2(0, 0)); }
		else if (platform02_Bodyref->GetPosition().y <= 400 && player_collision_platform2) { platform02_Bodyref->SetLinearVelocity(b2Vec2(0, 20)); }

		//Control de animación descendente de la plataforma izquierda
		if (platform02_Bodyref->GetPosition().y >= 475 && player_collision_platform2) { platform02_Bodyref->SetLinearVelocity(b2Vec2(0, 0)); }
		else if (platform02_Bodyref->GetPosition().y >= 475 && !player_collision_platform2) { platform02_Bodyref->SetLinearVelocity(b2Vec2(0, -20)); }
	}

	//Funcion que permite reposicionar los elementos a su posicion inicial, sin energia acumulada
	void Box2D_WorldManager::RestartScene()
	{
		//Devolvemos el circulo a su posicion inicial
		circle_BodyRef->SetTransform(b2Vec2(150, 300), 0);
		circle_BodyRef->SetLinearVelocity(b2Vec2_zero);
		circle_BodyRef->SetAngularVelocity(0);

		//Devolvemos cada body del vehiculo a su posicion inicial
		for(size_t i = 0; i < car_object_ptr->GetBodies().size(); ++i)
		{
			car_object_ptr->GetBodies().at(i)->SetTransform(car_object_ptr->GetBodiesLocation().at(i), 0);
			car_object_ptr->GetBodies().at(i)->SetAngularVelocity(0);
			car_object_ptr->GetBodies().at(i)->SetLinearVelocity(b2Vec2_zero);
		}

		//Reposicionamos las plataformas
		platform01_Bodyref->SetTransform(b2Vec2(1190, 10), 0);
		platform01_Bodyref->SetLinearVelocity(b2Vec2(0, 0));
		player_collision_platform1 = false;

		platform02_Bodyref->SetTransform(b2Vec2(400, 400), 0);
		platform02_Bodyref->SetLinearVelocity(b2Vec2(0, 0));
		player_collision_platform2 = false;
	}
}