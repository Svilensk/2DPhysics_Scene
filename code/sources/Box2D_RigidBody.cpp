/*
*  // Written By: Santiago Arribas Maroto
*  // 2018/2019
*  // Contact: Santisabirra@gmail.com
*/

#include "Box2D_RigidBody.hpp"
#include <Box2D/Box2D.h>

namespace B2D_Examples
{
	//El constructor necesita la información obligatoria para la construcción de un RB, el resto de propiedades se pueden ajustar con
	//Los setters proporcionados
	RigidBody::RigidBody(int id, std::shared_ptr< b2World > pysical_world, b2BodyType type, float posx, float posy, float angle_rotation)
	{
		rb_definition.type = type;
		rb_definition.position.Set(posx, posy);
		rb_definition.angle = angle_rotation;
		rb_definition.userData = (void*)id;
		rb_body = pysical_world->CreateBody(&rb_definition);
	}

	//Configuración de la densidad del RB
	void RigidBody::SetDensity(float density){
		rb_fixture.density = density;
	}

	//Configuración de la fricción del RB
	void RigidBody::SetFriction(float friction){
		rb_fixture.friction = friction;
	}

	//Configuración de la capacidad de restitución del RB
	void RigidBody::SetRestitution(float restitution){
		rb_fixture.restitution = restitution;
	}

	//Configuración de la rotación del RB
	void RigidBody::SetRotation(float angle_rotation){
		rb_body->SetTransform(rb_body->GetWorldCenter(), (float)(angle_rotation * (double)(3.1415f / 180)));
	}

	//La configuración de la forma del RB tiene en cuenta cual de los elementos de la enumeración se ha escogido
	//Se han creado previamente aquellos necesarios para el ejemplo (Box / Circle / Rectangle Triangle / Ramp / Inverted Ramp)
	void RigidBody::SetShape(float size_x, float size_y, shape_type shape_type)
	{
		b2PolygonShape poly_shape;
		b2CircleShape  circle_shape;

		b2Vec2 custom_triangle  [3];
		b2Vec2 custom_square    [4];

		switch (shape_type)
		{
			//Box
			case 0:
				poly_shape.SetAsBox(size_x, size_y);
				rb_fixture.shape = &poly_shape;
				break;

			//Circle
			case 1:
				circle_shape.m_radius = size_x;
				rb_fixture.shape = &circle_shape;
				break;

			//Triangle Rectangle
			case 2:
				custom_triangle[0].Set(0, 0);
				custom_triangle[1].Set(1 * size_x*2, 0);
				custom_triangle[2].Set(0, 1 * size_y*2);

				poly_shape.Set(custom_triangle, 3);
				rb_fixture.shape = &poly_shape;
				break;

			//Ramp
			case 3:
				custom_square[0].Set(0, 0);
				custom_square[1].Set(0, size_y);
				custom_square[2].Set(2*size_x, size_x + size_y);
				custom_square[3].Set(2*size_x, size_x);

				poly_shape.Set(custom_square, 4);
				rb_fixture.shape = &poly_shape;
				break;

			//Inverted Ramp
			case 4:
				custom_square[0].Set((2 * size_x), -size_x + size_y);
				custom_square[1].Set((2 * size_x), -size_x);
				custom_square[2].Set(0, size_y);
				custom_square[3].Set(0, 0);

				poly_shape.Set(custom_square, 4);
				rb_fixture.shape = &poly_shape;
				break;

			default:
				break;
		}

		RigidBody::rb_body->CreateFixture(&rb_fixture);
	}

}