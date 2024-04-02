
#include "GrassMaterial.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>


GrassMaterial::GrassMaterial(string name) :
	MaterialGL(name)
{

	vp = new GLProgram(MaterialPath + "GrassMaterial/GrassMaterial-VS.glsl", GL_VERTEX_SHADER);
	fp = new GLProgram(MaterialPath + "GrassMaterial/GrassMaterial-FS.glsl", GL_FRAGMENT_SHADER);

	m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
	m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);


	l_View = glGetUniformLocation(vp->getId(), "View");
	l_Proj = glGetUniformLocation(vp->getId(), "Proj");
	l_Model = glGetUniformLocation(vp->getId(), "Model");
	
}

GrassMaterial::~GrassMaterial()
{
}

void GrassMaterial::addAlbedoMap(Texture2D* albedo, Texture2D* alpha) {
	l_Texture = glGetUniformLocation(fp->getId(), "albedo");
	glProgramUniformHandleui64ARB(fp->getId(), l_Texture, albedo->getHandle());
	glProgramUniformHandleui64ARB(fp->getId(), l_Texture2, albedo->getHandle());
	if (alpha != NULL) {
		glProgramUniformHandleui64ARB(fp->getId(), l_Texture2, alpha->getHandle());
	}
}


void GrassMaterial::render(Node* o)
{


	m_ProgramPipeline->bind();

	o->drawGeometry(GL_TRIANGLES);
	m_ProgramPipeline->release();
}
void GrassMaterial::animate(Node* o, const float elapsedTime)
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
	glProgramUniform3fv(vp->getId(), l_PosLum, 1,  glm::value_ptr(Scene::getInstance()->getNode("Light")->frame()->convertPtTo(glm::vec3(0.0,0.0,0.0),o->frame())));
	// convertir le point (0,0,0) du repère camera vers le repere de l'objet
	glProgramUniform3fv(vp->getId(), l_PosCam, 1, glm::value_ptr(Scene::getInstance()->camera()->frame()->convertPtTo(glm::vec3(0.0, 0.0, 0.0), o->frame())));



	auto now_time = std::chrono::high_resolution_clock::now();
	auto timevar = now_time.time_since_epoch();
	float millis = 0.001f*std::chrono::duration_cast<std::chrono::milliseconds>(timevar).count();
	glProgramUniform1fv(vp->getId(), l_Time, 1,&millis);
}







