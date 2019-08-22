#include "Physics.h"

Physics::Physics()
{}

bool Physics::Init()
{
	m_CollisionConfiguration = new btDefaultCollisionConfiguration();
	m_Dispatcher = new btCollisionDispatcher(m_CollisionConfiguration);
	m_Broadphase = new btDbvtBroadphase();
	m_Solver = new btSequentialImpulseConstraintSolver();
	m_DynamicWorld = new btDiscreteDynamicsWorld(
		m_Dispatcher, 
		m_Broadphase, 
		m_Solver, 
		m_CollisionConfiguration
	);
	
	if (!m_CollisionConfiguration ||
		!m_Dispatcher             ||
		!m_Broadphase             ||
		!m_Solver                 ||
		!m_DynamicWorld)
	{
		return false;
	}
	
	return true;
}

Physics::~Physics()
{
	for (auto rigidBody : m_RigidBodies)
	{
		m_DynamicWorld->removeCollisionObject(rigidBody);

		btCollisionShape* shape = rigidBody->getCollisionShape();
		btMotionState* motion = rigidBody->getMotionState();

		delete motion;
		delete shape;
		delete rigidBody;
	}

	delete m_CollisionConfiguration;
	delete m_Dispatcher;
	delete m_Solver;
	delete m_Broadphase;
	delete m_DynamicWorld;
}

btVector3 Physics::GetVector3(const glm::vec3& vector)
{
	btVector3 v;
	
	v.setX(vector.x);
	v.setY(vector.y);
	v.setZ(vector.z);
	
	return v;
}

btQuaternion Physics::GetQuaternion(const glm::quat& quaternion)
{
	btQuaternion q;
	
	q.setX(quaternion.x);
	q.setY(quaternion.y);
	q.setZ(quaternion.z);
	q.setW(quaternion.w);
	
	return q;
}

glm::vec3 Physics::GetVector3(const btVector3& vector)
{
	glm::vec3 v;
	
	v.x = vector.getX();
	v.y = vector.getY();
	v.z = vector.getZ();

	return v;
}

glm::quat Physics::GetQuaternion(const btQuaternion& quaternion)
{
	glm::quat q;

	q.x = quaternion.getX();
	q.y = quaternion.getY();
	q.z = quaternion.getZ();
	q.w = quaternion.getW();

	return q;
}

void Physics::Update(float deltaTime)
{
	m_DynamicWorld->stepSimulation(deltaTime);
}

btRigidBody* Physics::AddSphere(class Entity* entity, float mass, float radius)
{
	btTransform transform;

	transform.setIdentity();
	transform.setOrigin(GetVector3(entity->GetPosition()));
	transform.setRotation(GetQuaternion(entity->GetRotation()));
	
	btSphereShape* sphere = new btSphereShape(radius);
	
	btVector3 inertia(0.0, 0.0, 0.0);
	
	if (mass != 0.0f)
	{
		sphere->calculateLocalInertia(mass, inertia);
	}

	btMotionState* motion = new btDefaultMotionState(transform);
	
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, sphere, inertia);
	btRigidBody* rigidBody = new btRigidBody(info);
	
	m_DynamicWorld->addRigidBody(rigidBody);
	m_RigidBodies.emplace_back(rigidBody);
	
	return rigidBody;
}

btRigidBody* Physics::AddBox(class Entity* entity, float mass, float width, float height, float depth)
{
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(GetVector3(entity->GetPosition()));
	transform.setRotation(GetQuaternion(entity->GetRotation()));

	btBoxShape* box = new btBoxShape(btVector3(
		width   / 2.0f,
		height / 2.0f,
		depth / 2.0f
	));

	btVector3 inertia(0.0, 0.0, 0.0);

	if (mass != 0.0f)
	{
		box->calculateLocalInertia(mass, inertia);
	}

	btMotionState* motion = new btDefaultMotionState(transform);

	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, box, inertia);
	btRigidBody* rigidBody = new btRigidBody(info);

	m_DynamicWorld->addRigidBody(rigidBody);
	m_RigidBodies.emplace_back(rigidBody);

	return rigidBody;
}