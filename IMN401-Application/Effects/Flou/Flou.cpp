
#include "Flou.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>


Flou::Flou(string name) :
	EffectGL(name)
{

	vp = new GLProgram(EffectPath + "common/Effect-VS.glsl", GL_VERTEX_SHADER);
	//fp = new GLProgram(EffectPath + "Flou/Flou-FS.glsl", GL_FRAGMENT_SHADER);
	fpH = new GLProgram(EffectPath + "Flou/FlouH-FS.glsl", GL_FRAGMENT_SHADER);
	fpV = new GLProgram(EffectPath + "Flou/FlouV-FS.glsl", GL_FRAGMENT_SHADER);

	m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
	//m_ProgramPipeline->useProgramStage(fpH, GL_FRAGMENT_SHADER_BIT);
	m_ProgramPipeline->link();
	m_ProgramPipeline->printInfoLog();

	l_Texture = glGetUniformLocation(fpH->getId(), "myFBO");
	
	tmpFBO = new FrameBufferObject();
	blurValue = 1;
	show_interface = false;
	glProgramUniform1f(fpH->getId(), glGetUniformLocation(fpH->getId(), "k"), blurValue);
	glProgramUniform1f(fpV->getId(), glGetUniformLocation(fpV->getId(), "k"), blurValue);
}

Flou::~Flou()
{

}

void Flou::apply(FrameBufferObject* src, FrameBufferObject* target)
{	
	// note the most efficient but here for usability purposes (could be set up in the constructor if src is constant)
	//Passe 1
	l_Texture = glGetUniformLocation(fpH->getId(), "myFBO");
	glProgramUniformHandleui64ARB(fpH->getId(), l_Texture, src->getColorTexture()->getHandle());

	if (tmpFBO)
		tmpFBO->enable();

	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_ProgramPipeline->useProgramStage(fpH, GL_FRAGMENT_SHADER_BIT);
	m_ProgramPipeline->link();
	m_ProgramPipeline->bind();
	drawQuad();	
	m_ProgramPipeline->release(); 
	if (tmpFBO)
		tmpFBO->disable();

	//Passe 2
	l_Texture = glGetUniformLocation(fpV->getId(), "myFBO");
	glProgramUniformHandleui64ARB(fpV->getId(), l_Texture, tmpFBO->getColorTexture()->getHandle());

	if (target)
		target->enable();

	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_ProgramPipeline->useProgramStage(fpV, GL_FRAGMENT_SHADER_BIT);
	m_ProgramPipeline->link();
	m_ProgramPipeline->bind();
	drawQuad();
	m_ProgramPipeline->release();
	if (target)
		target->disable();

}
void Flou::animate( const float elapsedTime)
{
	
}

void Flou::displayInterface()
{
	if (!ImGui::Begin("Flou", &show_interface))
	{
		ImGui::End();
		return;
	}
	if (ImGui::SliderFloat("Blur Value", &blurValue, 1.0f, 25.0f)) {
		glProgramUniform1f(fpH->getId(), glGetUniformLocation(fpH->getId(), "k"), blurValue);
		glProgramUniform1f(fpV->getId(), glGetUniformLocation(fpV->getId(), "k"), blurValue);
	}
	ImGui::End();
	
}
