
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

void GrassMaterial::addAlbedoMap(Texture2D* albedo) {
	l_Texture = glGetUniformLocation(fp->getId(), "albedo");
	glProgramUniformHandleui64ARB(fp->getId(), l_Texture, albedo->getHandle());
	
}


void GrassMaterial::render(Node* o)
{
	//glDepthMask(GL_FALSE);

	m_ProgramPipeline->bind();
	for (unsigned int i = 0; i < transformations.size(); i++) {
		glm::mat4 model = o->frame()->getModelMatrix() * transformations[i];
		glProgramUniformMatrix4fv(vp->getId(), l_Model, 1, GL_FALSE, glm::value_ptr(model));
		o->drawGeometry(GL_TRIANGLES);
	}
	m_ProgramPipeline->release();
	/*glDepthMask(GL_TRUE);*/
}
void GrassMaterial::animate(Node* o, const float elapsedTime)
{

	//Recuperer la matrice view
	glm::mat4 view =  Scene::getInstance()->camera()->getViewMatrix();
	//Recuperer la matrice proj
	glm::mat4 proj = Scene::getInstance()->camera()->getProjectionMatrix();
	//Recuperer la matrice model




	glProgramUniformMatrix4fv(vp->getId(), l_View, 1, GL_FALSE, glm::value_ptr(view));
	glProgramUniformMatrix4fv(vp->getId(), l_Proj, 1, GL_FALSE, glm::value_ptr(proj));



}

void GrassMaterial::setTransformations(vector<glm::mat4> trans)
{
	transformations = trans;
}







