#include "Box2D_GameObject.hpp"

namespace B2D_Examples
{
	//Constructor del GameObject del ejemplo (Vehiculo)
	B2DGameObject::B2DGameObject(int wheel_id, int chassis_id, std::shared_ptr<b2World> pysical_world, float posx, float posy)
	{
		//Creamos los 3 RigidBodies que compondrán el vehiculo
		RigidBody vehicle_lowerChassis(chassis_id, pysical_world, b2_dynamicBody, posx, posy, 0);
		vehicle_lowerChassis.SetDensity(1.f);
		vehicle_lowerChassis.SetShape(52, 5, Box_Shape);

		//Guardamos referencias del body y de la posicion del body
		bodies.push_back(vehicle_lowerChassis.GetBody());
		bodies_location.push_back(b2Vec2(posx, posy));

		RigidBody vehicle_leftChassis(chassis_id + 1, pysical_world, b2_dynamicBody, posx - 50, posy + 35, 0);
		vehicle_leftChassis.SetDensity(.1f);
		vehicle_leftChassis.SetShape(5, 40, Box_Shape);

		//Guardamos referencias del body y de la posicion del body
		bodies.push_back(vehicle_leftChassis.GetBody());
		bodies_location.push_back(b2Vec2(posx - 50, posy + 35));

		RigidBody vehicle_rightChassis(chassis_id + 2, pysical_world, b2_dynamicBody, posx + 50, posy + 35, 0);
		vehicle_rightChassis.SetDensity(.1f);
		vehicle_rightChassis.SetShape(5, 40, Box_Shape);

		//Guardamos referencias del body y de la posicion del body
		bodies.push_back(vehicle_rightChassis.GetBody());
		bodies_location.push_back(b2Vec2(posx + 50, posy + 35));

		//Creamos la unión entre rigidbodies, en este caso rígida, ya que unirá las partes del chasis del vehiculo
		b2WeldJointDef weld_joint;

		//Unión entre la plataforma inferior del vehiculo y la plataforma izquierda
		weld_joint.Initialize(vehicle_lowerChassis.GetBody(), vehicle_leftChassis.GetBody(), vehicle_leftChassis.GetBody()->GetPosition());
		weld_joint.frequencyHz = motor_hz;
		weld_joint.dampingRatio = 1;
		b2Joint* weld_joint01 = (b2Joint*)pysical_world->CreateJoint(&weld_joint);

		//Unión entre la plataforma inferior del vehiculo y la plataforma derecha
		weld_joint.Initialize(vehicle_lowerChassis.GetBody(), vehicle_rightChassis.GetBody(), vehicle_rightChassis.GetBody()->GetPosition());
		weld_joint.frequencyHz = motor_hz;
		weld_joint.dampingRatio = 1;
		b2Joint* weld_joint02 = (b2Joint*)pysical_world->CreateJoint(&weld_joint);

		//Creo los 2 RigidBodies de las ruedas
		RigidBody vehicle_backWheel(wheel_id, pysical_world, b2_dynamicBody, posx - 35, posy - 15, 0);
		vehicle_backWheel.SetDensity (.5f);
		vehicle_backWheel.SetFriction(1.f);
		vehicle_backWheel.SetRestitution(.0f);
		vehicle_backWheel.SetShape(10.f, 10.f, Circle_Shape);

		bodies.push_back(vehicle_backWheel.GetBody());
		bodies_location.push_back(b2Vec2(posx - 35, posy - 15));

		RigidBody vehicle_frontWheel(wheel_id + 1, pysical_world, b2_dynamicBody, posx + 35, posy - 15, 0);
		vehicle_frontWheel.SetDensity(.5f);
		vehicle_frontWheel.SetFriction(1.f);
		vehicle_frontWheel.SetRestitution(.0f);
		vehicle_frontWheel.SetShape(10.f, 10.f, Circle_Shape);

		bodies.push_back(vehicle_frontWheel.GetBody());
		bodies_location.push_back(b2Vec2(posx + 35, posy - 15));

		//Creo el eje de funcionamiento de WheelJoint
		b2Vec2 axis(0.0f, 1.0f);

		//Creo la wheel_joint que funcionará como motor para las ruedas
		b2WheelJointDef wheel_joint;
		wheel_joint.motorSpeed = 0.f;
		wheel_joint.maxMotorTorque = motor_maxTorque;
		wheel_joint.enableMotor = true;
		wheel_joint.frequencyHz = motor_hz;
		wheel_joint.dampingRatio = motor_damplingRatio;

		//Inicializo el wheel joint y lo instancio en la rueda delantera, uniendose al chasis
		wheel_joint.Initialize(vehicle_lowerChassis.GetBody(), vehicle_frontWheel.GetBody(), vehicle_frontWheel.GetBody()->GetPosition(), axis);
		wheel_joint1 = (b2WheelJoint*)pysical_world->CreateJoint(&wheel_joint);

		//Inicializo el wheel joint y lo instancio en la rueda trasera
		wheel_joint.Initialize(vehicle_lowerChassis.GetBody(), vehicle_backWheel.GetBody(), vehicle_backWheel.GetBody()->GetPosition(), axis);
		wheel_joint2 = (b2WheelJoint*)pysical_world->CreateJoint(&wheel_joint);
	}

	void B2DGameObject::SetDirection(float direction)
	{
		wheel_joint1->SetMotorSpeed(direction * 5000.f);
		wheel_joint2->SetMotorSpeed(direction * 5000.f);
	}

	std::vector<b2Body*> B2DGameObject::GetBodies()
	{
		return bodies;
	}

	std::vector<b2Vec2> B2DGameObject::GetBodiesLocation()
	{
		return bodies_location;
	}

}