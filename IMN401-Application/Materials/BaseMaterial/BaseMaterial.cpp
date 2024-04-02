
#include "BaseMaterial.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>
#include <chrono>


BaseMaterial::BaseMaterial(string name) :
	MaterialGL(name)
{
	
	vp = new GLProgram(MaterialPath+"BaseMaterial/Main-VS.glsl", GL_VERTEX_SHADER);
	fp = new GLProgram(MaterialPath+"BaseMaterial/Main-FS.glsl", GL_FRAGMENT_SHADER);
	
	m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
	m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);


	l_View = glGetUniformLocation(vp->getId(), "View");
	l_Proj = glGetUniformLocation(vp->getId(), "Proj");
	l_Model = glGetUniformLocation(vp->getId(), "Model");

	timeStart = std::chrono::steady_clock::now();

	
}

BaseMaterial::~BaseMaterial()
{
	
}

void BaseMaterial::render(Node *o)
{

	
	m_ProgramPipeline->bind();

	o->drawGeometry(GL_TRIANGLES);
	m_ProgramPipeline->release();
}
void BaseMaterial::animate(Node* o, const float elapsedTime)
{
	/**********************************************
	*
	* TP 2 - A completer
	Calculer et Transmettre les matrices Model View et Proj au shaders
	- Utilisez glm::value_ptr(mat) pour trouver le pointeur de la matrice mat a transmettre au GPU via la fonction glProgramUniform*()
	- Une matrice 4X4 se transmet grace a glProgramUniformMatrix4fv

	****************************************************/

	glm::mat4 model = glm::mat4(o->frame()->getModelMatrix());
	glm::mat4 view = glm::mat4(scene->camera()->getViewMatrix());
	glm::mat4 projection = glm::mat4(scene->camera()->getProjectionMatrix());
	GLint loc = glGetUniformLocation(vp->getId(), "timePassed");

	float timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timeStart).count();
	timePassed /= 1000;
	glProgramUniform1fv(vp->getId(), loc, 1, &timePassed);
	glProgramUniformMatrix4fv(vp->getId(), l_View, 1, GL_FALSE, glm::value_ptr(view));
	glProgramUniformMatrix4fv(vp->getId(), l_Model, 1, GL_FALSE, glm::value_ptr(model));
	glProgramUniformMatrix4fv(vp->getId(), l_Proj, 1, GL_FALSE, glm::value_ptr(projection));


	/*********************************************/


}
