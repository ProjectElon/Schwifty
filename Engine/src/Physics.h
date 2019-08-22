#pragma once

#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <vector>

#include "Entity.h"

class Physics
{
private:
	btDynamicsWorld*                 m_DynamicWorld;
	btBroadphaseInterface*           m_Broadphase;
	btCollisionDispatcher*           m_Dispatcher;
	btConstraintSolver*	             m_Solver;
	btDefaultCollisionConfiguration* m_CollisionConfiguration;
	std::vector<btRigidBody*>		 m_RigidBodies;

public:
	Physics();
	~Physics();

	bool Init();
	
	// converting between glm and bullet phyisc math library
	static btVector3    GetVector3(const glm::vec3& vector);
	static btQuaternion GetQuaternion(const glm::quat& quaternion);
	static glm::vec3    GetVector3(const btVector3& vector);
	static glm::quat    GetQuaternion(const btQuaternion& quaternion);

	void Update(float deltaTime);

	btRigidBody* AddSphere(Entity* entity, float mass, float radius);
	btRigidBody* AddBox(Entity* entity, float mass, float width, float height, float depth);
};