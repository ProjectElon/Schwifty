#include "Test3D.h"
#include "Application.h"
#include <glm/gtc/quaternion.hpp>
#include "Entity.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>

Test3D::Test3D()
{
	GLCall(glEnable(GL_MULTISAMPLE));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));

	m_LightPos = glm::vec3(0.0f, 30.0f, 0.0f);

	m_SkyBoxVa = MeshFactory::GetSkyBox();

	m_Lighting = new Shader(
		"res/shaders/SceneVS.shader", 
		"res/shaders/SceneFS.shader"
	);

	m_SkyBoxShader = new Shader(
		"res/shaders/SkyBoxVS.shader", 
		"res/shaders/SkyBoxFS.shader"
	);

	m_ShadowShader = new Shader("res/shaders/ShadowVS.shader", "res/shaders/ShadowFS.shader", "res/shaders/ShadowGO.shader");

	std::vector<std::string> faces =
	{
		"res/textures/skybox/right.jpg",
		"res/textures/skybox/left.jpg",
		"res/textures/skybox/top.jpg",
		"res/textures/skybox/bottom.jpg",
		"res/textures/skybox/front.jpg",
		"res/textures/skybox/back.jpg"
	};

	m_SkyBox = new CubeMap(faces);
	m_SkyBox->Load();
	
	// iamgui stuff
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(Application::GetWindow()->GetHandle(), false);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();

	m_Engine = new Engine();
	m_Engine->Init();

	Entity* plane = new Entity(m_Engine);
	plane->SetScale(glm::vec3(50.0f, 0.1f, 50.0f));
	
	btRigidBody* rb = m_Engine->GetPhysics()->AddBox(plane, 0.0f, 50.0f, 0.1f, 50.0f);
	rb->setFriction(10.0f);

	ModelComponent* mc = new ModelComponent(plane, AssetManager::GetModel("res/meshes/cube.obj"));

	mc->GetModel()->GetMeshes().front()->GetMaterial()->SetTexture(Diffuse,  AssetManager::GetTexture("res/textures/brickwall.jpg"));
	mc->GetModel()->GetMeshes().front()->GetMaterial()->SetTexture(Specular, AssetManager::GetTexture("res/textures/specular.jpg"));
	mc->GetModel()->GetMeshes().front()->GetMaterial()->SetTexture(Normal,   AssetManager::GetTexture("res/textures/brickwall_normal.jpg"));

	plane->AddComponent(mc);
	
	m_Player = new Player(m_Engine);
	
	m_Camera = new FollowCamera();
	m_Camera->Follow(m_Player);

	m_DepthMap = new DepthCubeMap(1024, 1024, m_ShadowShader);
	
	m_ShadowShader->Use();
	m_DepthMap->CalculateProjection(m_LightPos, m_Near, m_Far);
}

Test3D::~Test3D()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	delete m_Lighting;
	delete m_SkyBoxVa;
	delete m_SkyBoxShader;
	delete m_ShadowShader;
	delete m_DepthMap;
	delete m_Lighting;
	delete m_SkyBox;
	delete m_Camera;
	delete m_Engine;
}

void Test3D::Update(float deltaTime)
{
	m_Engine->GetEntityManager()->Update(deltaTime);
	m_Engine->GetPhysics()->Update(1.0 / 60.0);
	m_Camera->Update(deltaTime);
}

void Test3D::RenderScene(Shader* shader)
{
	m_Engine->GetRenderer()->Render(shader);
}

void Test3D::Render()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	ImGui::SliderFloat3("LightPos",   &m_LightPos.x, -1000.0f, 1000.0f);
	ImGui::SliderFloat("LightSpread", &m_Far,         1.0f, 200.0f);
	
	ImGui::SliderFloat("Horizontal Distance", &m_CameraHorizontalDistance,  0.0, 100.0f);
	ImGui::SliderFloat("Vertical Distance",   &m_CameraVerticalDistance,    0.0, 100.0f);
	ImGui::SliderFloat("Target Distance",     &m_CameraTargetDistance,    -100.0f, 100.0f);

	m_Camera->SetHorizontalDistance(m_CameraHorizontalDistance);
	m_Camera->SetVerticalDistance(m_CameraVerticalDistance);
	m_Camera->SetTargetDistance(m_CameraTargetDistance);
	
	ImGui::Text(
		"Application average %.3f ms/frame (%.1f FPS)",
		1000.0f / ImGui::GetIO().Framerate,
		ImGui::GetIO().Framerate
	);

	m_ShadowShader->Use();
	m_DepthMap->PrepareForRenderPass();
	RenderScene(m_ShadowShader);

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	GLCall(glViewport(0, 0, Application::GetWindow()->GetWidth(), Application::GetWindow()->GetHeight()));
	GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	m_Lighting->Use();

	m_Lighting->SetUniform("uLightPos",   m_LightPos);
	m_Lighting->SetUniform("uView",       m_Camera->GetView());
	m_Lighting->SetUniform("uProjection", m_Camera->GetProjection());
	m_Lighting->SetUniform("uViewPos",    m_Camera->GetPosition());
	m_Lighting->SetUniform("far_plane",   m_Far);

	m_Lighting->SetUniform("uShadowMap", 3);
	m_DepthMap->Bind(3);
	RenderScene(m_Lighting);

	GLCall(glDepthFunc(GL_LEQUAL));

	m_SkyBoxShader->Use();

	m_SkyBoxShader->SetUniform("uProjection", m_Camera->GetProjection());
	m_SkyBoxShader->SetUniform("uView", glm::mat4(glm::mat3(m_Camera->GetView())));
	m_SkyBoxShader->SetUniform("skyBox", 0);
	
	m_SkyBox->Bind(0);
	m_SkyBoxVa->Bind();
	
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
	GLCall(glDepthFunc(GL_LESS));

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}