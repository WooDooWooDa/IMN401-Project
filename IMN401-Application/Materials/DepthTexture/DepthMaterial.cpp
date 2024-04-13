#include "DepthMaterial.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>

DepthMaterial::DepthMaterial(string name) :
	MaterialGL(name)
{
	vp = new GLProgram(EffectPath + "DepthFieldBlur/depth-VS.glsl", GL_VERTEX_SHADER);
	fp = new GLProgram(EffectPath + "DepthFieldBlur/depth-FS.glsl", GL_FRAGMENT_SHADER);

	m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
	m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);

	l_View = glGetUniformLocation(vp->getId(), "View");
	l_Proj = glGetUniformLocation(vp->getId(), "Proj");
	l_Model = glGetUniformLocation(vp->getId(), "Model");
}

DepthMaterial::~DepthMaterial()
{
}

void DepthMaterial::render(Node* o)
{
	glm::mat4 view = Scene::getInstance()->camera()->getViewMatrix();
	glm::mat4 proj = Scene::getInstance()->camera()->getProjectionMatrix();
	glm::mat4 model = o->frame()->getModelMatrix();

	glProgramUniformMatrix4fv(vp->getId(), l_View, 1, GL_FALSE, glm::value_ptr(view));
	glProgramUniformMatrix4fv(vp->getId(), l_Proj, 1, GL_FALSE, glm::value_ptr(proj));
	glProgramUniformMatrix4fv(vp->getId(), l_Model, 1, GL_FALSE, glm::value_ptr(model));
	m_ProgramPipeline->bind();
	o->drawGeometry(GL_TRIANGLES);
	m_ProgramPipeline->release();
}
void DepthMaterial::animate(Node* o, const float elapsedTime)
{

}
