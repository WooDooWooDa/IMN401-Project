
#include "EngineGL.h"
#include "Scene.h"



#include "Texture2D.h"
#include <Materials/BaseMaterial/BaseMaterial.h>
#include <Materials/Rotation/Rotation.h>
#include <Materials/PhongMaterial/PhongMaterial.h>
#include <Materials/TextureMaterial/TextureMaterial.h>
#include <Effects/Flou/Flou.h>


// Message callbck error for getting OpenGL problems 
// All credits to https://github.com/fendevel/Guide-to-Modern-OpenGL-Functions/blob/master/README.md#gltexture
void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
{
	auto const src_str = [source]() {
		switch (source)
		{
		case GL_DEBUG_SOURCE_API: return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
		case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
		case GL_DEBUG_SOURCE_OTHER: return "OTHER";
		default:return "";
		}
	}();

	auto const type_str = [type]() {
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR: return "ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER: return "MARKER";
		case GL_DEBUG_TYPE_OTHER: return "OTHER";
		default:return "";
		}
	}();

	auto const severity_str = [severity]() {
		switch (severity) {
		case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
		case GL_DEBUG_SEVERITY_LOW: return "LOW";
		case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
		case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
		default:return "";
		}
	}();
	LOG_INFO << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
}



EngineGL::EngineGL(int width, int height) 
{
	m_Width = width;
	m_Height = height;

	myFBO = NULL;

	scene = Scene::getInstance();	
	scene->resizeViewport(m_Width, m_Height);

}

EngineGL::~EngineGL()
{


}


void EngineGL::setupEngine()
{
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, m_Width, m_Height);
	setClearColor(glm::vec4(0.5,0.5,0.5,1.0));


	this->allNodes = new NodeCollector();

	allNodes->collect(scene->getRoot());

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
	glDebugMessageCallback(message_callback, nullptr);

	LOG_INFO << "initialisation complete" << std::endl;
}

bool EngineGL::init()
{

	LOG_INFO << "Initializing Scene" << std::endl;

	myFBO = new FrameBufferObject();
	display = new Display("Main");
	flou = new Flou("Flou");

	//Création d'un materiau de Base
	// 
	// TP 2 *******************************************
	// 
	//BaseMaterial* material = new BaseMaterial("IMN401-TP2-bunny");
	Texture2D* lionTexture = new Texture2D(ObjPath + "Textures/Lion.jpg");
	Texture2D* lionNormal = new Texture2D(ObjPath + "Textures/Lion_Normal.jpg");
	TextureMaterial* materialLion = new TextureMaterial("IMN401-Projet-lion");
	materialLion->addAlbedoMap(lionTexture);
	materialLion->addNormalMap(lionNormal);

	Texture2D* solTexture = new Texture2D(ObjPath + "Textures/Grass_005_BaseColor.jpg");
	Texture2D* solNormal = new Texture2D(ObjPath + "Textures/Grass_005_Normal.jpg");
	Texture2D* solAO = new Texture2D(ObjPath + "Textures/Grass_005_AmbientOcclusion.jpg");
	Texture2D* solDisp = new Texture2D(ObjPath + "Textures/Grass_005_Height.jpg");
	TextureMaterial* materialSol = new TextureMaterial("IMN401-TP2-sol");
	materialSol->addAlbedoMap(solTexture);
	materialSol->addNormalMap(solNormal);
	materialSol->addAOMap(solAO);
	materialSol->addDispMap(solDisp, 10);

	BaseMaterial* materialSphere = new BaseMaterial("IMN401-TP2-sphere");
	Rotation* rotation = new Rotation("IMN401-TP2-rotation");
	

	// d'un objet, méthode détaillée
	Node* lion = scene->getNode("Lion");
	lion->setModel(scene->m_Models.get<ModelGL>(ObjPath + "LION_STATUE-triangulated.obj"));
	//lion->frame()->scale(glm::vec3(2.0));
	lion->frame()->translate(glm::vec3(0.0, -2, 0.0));
	lion->setMaterial(materialLion);
	scene->getSceneNode()->adopt(lion);

	Node* A = scene->getNode("A");
	A->setMaterial(rotation);
	lion->adopt(A);
	
	Node* L = scene->getNode("Light");
	L->setModel(scene->m_Models.get<ModelGL>(ObjPath + "sphere.obj"));
	L->setMaterial(materialSphere);
	L->frame()->translate(glm::vec3(0.2, 0.0, 0.0));
	L->frame()->scale(glm::vec3(0.03));
	A->adopt(L);

	Node* sol = scene->getNode("Sol");
	sol->setModel(scene->m_Models.get<ModelGL>(ObjPath + "wall.obj"));
	sol->frame()->translate(glm::vec3(0, -2.4, 0));
	sol->frame()->scale(glm::vec3(2));
	sol->setMaterial(materialSol);
	scene->getSceneNode()->adopt(sol);


	scene->getEffect<Flou>("Flou");

	setupEngine();	
	return(true);
}


void EngineGL::render ()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	myFBO->enable();
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (unsigned int i = 0; i < allNodes->nodes.size(); i++)
		allNodes->nodes[i]->render();
	
	myFBO->disable();
	flou->apply(myFBO, NULL);
	//display->apply(myFBO, NULL);
}

void EngineGL::animate (const float elapsedTime)
{
	// Animate each node
	for (unsigned int i = 0; i < allNodes->nodes.size(); i++)
	{
		allNodes->nodes[i]->animate(elapsedTime);
	}
		

	// Update Camera Buffer
	scene->camera()->updateBuffer();
}

void EngineGL::onWindowResize(int w, int h)
{
	m_Width = w;
	m_Height = h;
	glViewport(0, 0, w, h);
	float ratio = (float)w / (float)h;

	scene->resizeViewport(w,h);
	scene->camera()->setPerspectiveProjection(glm::radians(45.0f), ratio, 1.0f, 2000.0f);

}

void EngineGL::setClearColor(glm::vec4 color)
{
	glClearColor(color.x, color.y, color.z,color.w);
}
void EngineGL::displayInterface()
{
	if (myFBO)
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("FBOs"))
			{
				ImGui::MenuItem(myFBO->getName().c_str(), NULL, &(myFBO->show_interface));
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		myFBO->displayInterface();
	}
	if (flou) {
		flou->displayInterface();
	}
}
