#include "Engine.h"
#include "Player.h"

Player::Player(Engine* engine)
	: Entity(engine)
{
	m_Model = new ModelComponent(this, AssetManager::GetModel("res/meshes/sphere.obj"));

	m_Model->GetModel()->GetMeshes().front()->GetMaterial()->SetTexture(Diffuse, 
		AssetManager::GetTexture("res/textures/ball_diffuse.jpg"));
	
	m_Model->GetModel()->GetMeshes().front()->GetMaterial()->SetTexture(Specular,
		AssetManager::GetTexture("res/textures/specular.jpg"));

	m_Model->GetModel()->GetMeshes().front()->GetMaterial()->SetTexture(Normal, 
		AssetManager::GetTexture("res/textures/ball_normal.jpg"));

	SetPosition(glm::vec3(0.0f, 20.0f, 0.0f));
	SetScale(glm::vec3(0.5f));
	
	btRigidBody* rb  = GetEngine()->GetPhysics()->AddSphere(this, 3.0, 1.0f);
	
	rb->setRollingFriction(0.3f);
	rb->setFriction(8.5f);
	
	rb->setActivationState(DISABLE_DEACTIVATION);
	
	m_RigidBody = new RigidBodyComponent(this);
	m_RigidBody->SetRigidBody(rb);

	m_IsInAir = true;
}

Player::~Player()
{
}

void Player::OnUpdate(float deltaTime)
{
	btRigidBody* rb = m_RigidBody->GetRigidBody();

	btVector3 force = GetEngine()->GetPhysics()->GetVector3(GetForward());
	float velocity = rb->getLinearVelocity().length2();

	if (GetPosition().y <= 1.6f)
	{
		m_IsInAir = false;
	}
	else
	{
		m_IsInAir = true;
	}

	if (Input::IsKeyDown(GLFW_KEY_W) && velocity <= 100.0f * 100.0f && !m_IsInAir)
	{
		rb->applyCentralImpulse(force * deltaTime * 200.0f);
	}

	if (Input::IsKeyDown(GLFW_KEY_S) && velocity <= 100.0f * 100.0f && !m_IsInAir)
	{
		rb->applyCentralImpulse(-1.0f * force * deltaTime * 200.0f);
	}

	if (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT) && !m_IsInAir)
	{
		m_IsInAir = true;
		btVector3 up = GetEngine()->GetPhysics()->GetVector3(GetUp());
		rb->applyCentralImpulse(up * 9.81f * 200.0f * deltaTime);
	}

	if (GetPosition().y <= -20.0f)
	{
		m_IsInAir = true;
		btTransform t;
		t.setIdentity();
		t.setOrigin(btVector3(0.0f, 20.0f, 0.0f));
		rb->setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
		rb->setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
		rb->setWorldTransform(t);
	}

}