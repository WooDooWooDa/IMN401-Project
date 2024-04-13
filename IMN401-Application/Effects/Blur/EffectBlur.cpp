
#include "EffectBlur.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>


EffectBlur::EffectBlur(string name) :
	EffectGL(name)
{

	vp = new GLProgram(EffectPath + "common/Effect-VS.glsl", GL_VERTEX_SHADER);
	fp = new GLProgram(EffectPath + "Blur/Shaders/EffectBlur-FS.glsl", GL_FRAGMENT_SHADER);

	m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
	m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);
	m_ProgramPipeline->link();
	m_ProgramPipeline->printInfoLog();

	glProgramUniform1i(fp->getId(), glGetUniformLocation(fp->getId(), "myFBO"), 0);

	l_Direction = glGetUniformLocation(fp->getId(), "direction");	

	tmp = new FrameBufferObject("tmp");

}

EffectBlur::~EffectBlur()
{
	delete tmp;
	delete depth;
}

void EffectBlur::apply(FrameBufferObject* src, FrameBufferObject* target)
{
	glProgramUniformHandleui64ARB(fp->getId(), glGetUniformLocation(fp->getId(), "myFBO"), src->getColorTexture()->getHandle());
	glProgramUniformHandleui64ARB(fp->getId(), glGetUniformLocation(fp->getId(), "depthFBO"), depth->getColorTexture()->getHandle());
	
	tmp->enable();	

	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glProgramUniform2fv(fp->getId(), l_Direction, 1, glm::value_ptr(glm::vec2(1.0f, 0.0f)));

	m_ProgramPipeline->bind();

	drawQuad();	

	m_ProgramPipeline->release();

	tmp->disable();

	glBindTextureUnit(0, tmp->getColorTexture()->getId());

	if (target)
		target->enable();

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glProgramUniform2fv(fp->getId(), l_Direction, 1, glm::value_ptr(glm::vec2(0.0f, 1.0f)));

	m_ProgramPipeline->bind();
	drawQuad();

	m_ProgramPipeline->release(); 
	if (target)
		target->disable();

}
void EffectBlur::animate( const float elapsedTime)
{


}
