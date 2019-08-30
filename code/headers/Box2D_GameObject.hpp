#include <Box2D/Box2D.h>
#include "Box2D_RigidBody.hpp"
#include <vector>

namespace B2D_Examples
{
	class B2DGameObject
	{
	private:

		b2WheelJoint* wheel_joint1;
		b2WheelJoint* wheel_joint2;

		float motor_hz = 50.0f;
		float motor_damplingRatio = 0.1f;
		float motor_maxTorque = 250000.f;

		std::vector<b2Body*> bodies;
		std::vector<b2Vec2> bodies_location;

	public:

		//Constructor del vehiculo
		B2DGameObject(int wheel_id, int chassis_id, std::shared_ptr< b2World > pysical_world, float posx, float posy);

		//Setter de la dirección del vehiculo
		void SetDirection(float direction);

		//Getters de los componentes y la localizacion de los mismos 
		std::vector<b2Body*> GetBodies();
		std::vector<b2Vec2>  GetBodiesLocation();
		
	};

}