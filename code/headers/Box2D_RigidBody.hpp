/*
*  // Written By: Santiago Arribas Maroto
*  // 2018/2019
*  // Contact: Santisabirra@gmail.com
*/

#include <Box2D/Box2D.h>

namespace B2D_Examples
{
	//Shape_Type permite seleccionar desde el constructor del RigidBody la forma que se desea que �ste tenga
	//Poniendo cualquiera de los integrantes de la enumeraci�n, variar� la forma del RB en el momento de situar los v�rtices de la forma
	enum shape_type
	{
		Box_Shape                 = 0,
		Circle_Shape              = 1,
		Custom_RectTriangleShape = 2,
		Custom_RampShape         = 3,
		Custom_InvertedRampShape = 4
	};

	class RigidBody
	{
	public:
		//Los par�metros del constructor permiten aportar todos los par�metros de posici�n, y tipo de elemento B2D
		//Adem�s, poseen un par�metro ID, que ser� utilizado en la detecci�n de colisiones, para saber cual elemento est� colisionando
		//ID se guardar� como UserData del RigidBody
		RigidBody(int id, std::shared_ptr< b2World > pysical_world, b2BodyType type, float posx, float posy, float angle_rotation);

	private:
		//Propiedades b�sicas de un rigidbody
		float density;
		float restitution;
		float friction;

		//Componenetes necesarios para la creaci�n de un rigidbody
		b2Body* rb_body;
		b2BodyDef rb_definition;	
		b2FixtureDef rb_fixture;
		b2PolygonShape rb_shape;

	public:

		//Setters para poder acceder a los par�metros del RigidBody creado y modificarlos
		void SetShape       (float size_x, float size_y, shape_type shape_type);
		void SetDensity     (float density );
		void SetRestitution (float restitution );
		void SetRotation    (float angle_rotation);
		void SetFriction    (float friction );

		//Getters para acceder a las propiedades de un RigidBody
		b2Body* GetBody()         { return rb_body;  };
		b2PolygonShape GetShape() { return rb_shape; };
		b2BodyDef GetDefinition() { return rb_definition; };
	};
}
