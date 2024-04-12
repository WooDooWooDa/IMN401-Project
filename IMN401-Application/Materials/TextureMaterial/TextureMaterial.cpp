
#include "TextureMaterial.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>
#include <FlickeringLightColor.h>
#include <random>


TextureMaterial::TextureMaterial(string name) :
	MaterialGL(name)
{

	vp = new GLProgram(MaterialPath + "TextureMaterial/TextureMaterial-VS.glsl", GL_VERTEX_SHADER);
	fp = new GLProgram(MaterialPath + "TextureMaterial/TextureMaterial-FS.glsl", GL_FRAGMENT_SHADER);

	m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
	m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);


	l_View = glGetUniformLocation(vp->getId(), "View");
	l_Proj = glGetUniformLocation(vp->getId(), "Proj");
	l_Model = glGetUniformLocation(vp->getId(), "Model");
	l_PosLum = glGetUniformLocation(vp->getId(), "PosLum");
	l_PosCam = glGetUniformLocation(vp->getId(), "PosCam");

	l_Phong = glGetUniformLocation(fp->getId(), "Phong");
	l_Albedo = glGetUniformLocation(fp->getId(), "diffuseAlbedo");
	l_hasAOMap = glGetUniformLocation(fp->getId(), "hasAO");
	glProgramUniform1fv(fp->getId(), l_hasAOMap, 1, &hasAOMap);


	param.albedo = glm::vec3(1.0, 1.0, 1.0);
	param.coeff = glm::vec4(0.45,1.0,0.0,5.0);

	l_Time = glGetUniformLocation(vp->getId(), "Time");

	updatePhong();
}

TextureMaterial::~TextureMaterial()
{
}

void TextureMaterial::addAlbedoMap(Texture2D* albedo, Texture2D* alpha) {
	l_Texture = glGetUniformLocation(fp->getId(), "albedo");
	l_Texture2 = glGetUniformLocation(fp->getId(), "alpha");
	glProgramUniformHandleui64ARB(fp->getId(), l_Texture, albedo->getHandle());
	glProgramUniformHandleui64ARB(fp->getId(), l_Texture2, albedo->getHandle());
	if (alpha != NULL) {
		glProgramUniformHandleui64ARB(fp->getId(), l_Texture2, alpha->getHandle());
	}
}

void TextureMaterial::addNormalMap(Texture2D* normalMap) {
	l_normalMap = glGetUniformLocation(fp->getId(), "normalMap");
	glProgramUniformHandleui64ARB(fp->getId(), l_normalMap, normalMap->getHandle());
}

void TextureMaterial::addAOMap(Texture2D* ao) {
	l_aoMap = glGetUniformLocation(fp->getId(), "aoMap");
	glProgramUniformHandleui64ARB(fp->getId(), l_aoMap, ao->getHandle());
	hasAOMap = true;
	glProgramUniform1fv(fp->getId(), l_hasAOMap, 1, &hasAOMap);
}

void TextureMaterial::addDispMap(Texture2D* disp, float factor) {
	l_disp = glGetUniformLocation(vp->getId(), "dispMap");
	glProgramUniformHandleui64ARB(vp->getId(), l_disp, disp->getHandle());
	glProgramUniform1fv(vp->getId(), glGetUniformLocation(vp->getId(), "dispFactor"), 1, &factor);
	hasDispMap = true;
	glProgramUniform1fv(vp->getId(), glGetUniformLocation(vp->getId(), "hasDispMap"), 1, &hasDispMap);
}

void TextureMaterial::render(Node* o)
{


	m_ProgramPipeline->bind();

	o->drawGeometry(GL_TRIANGLES);
	m_ProgramPipeline->release();
}
void TextureMaterial::animate(Node* o, const float elapsedTime)
{

	//Recuperer la matrice view
	glm::mat4 view =  Scene::getInstance()->camera()->getViewMatrix();
	//Recuperer la matrice proj
	glm::mat4 proj = Scene::getInstance()->camera()->getProjectionMatrix();
	//Recuperer la matrice model
	glm::mat4 model = o->frame()->getModelMatrix();

	glProgramUniformMatrix4fv(vp->getId(), l_View, 1, GL_FALSE, glm::value_ptr(view));
	glProgramUniformMatrix4fv(vp->getId(), l_Proj, 1, GL_FALSE, glm::value_ptr(proj));
	glProgramUniformMatrix4fv(vp->getId(), l_Model, 1, GL_FALSE, glm::value_ptr(model));

	// convertir le point (0,0,0) du repère "light" vers le repere de l'objet
	LightNode* light = (LightNode*)Scene::getInstance()->getNode("Light");
	glProgramUniform4fv(vp->getId(), glGetUniformLocation(vp->getId(), "ColorLum"), 1, glm::value_ptr(light->color));

	glProgramUniform3fv(vp->getId(), l_PosLum, 1,  glm::value_ptr(Scene::getInstance()->getNode("Light")->frame()->convertPtTo(glm::vec3(0.0,0.0,0.0),o->frame())));
	// convertir le point (0,0,0) du repère camera vers le repere de l'objet
	glProgramUniform3fv(vp->getId(), l_PosCam, 1, glm::value_ptr(Scene::getInstance()->camera()->frame()->convertPtTo(glm::vec3(0.0, 0.0, 0.0), o->frame())));

	auto now_time = std::chrono::high_resolution_clock::now();
	auto timevar = now_time.time_since_epoch();
	float millis = 0.001f*std::chrono::duration_cast<std::chrono::milliseconds>(timevar).count();
	glProgramUniform1fv(vp->getId(), l_Time, 1,&millis);
}


void TextureMaterial::updatePhong()
{
	glProgramUniform4fv(fp->getId(), l_Phong, 1, glm::value_ptr(glm::vec4(param.coeff)));
	glProgramUniform3fv(fp->getId(), l_Albedo, 1, glm::value_ptr(param.albedo));
}


void TextureMaterial::displayInterface()
{
	if (ImGui::SliderFloat4("Phong coeff", glm::value_ptr(param.coeff), 0, 10)) {
		updatePhong();
	}
}



