#include <queue>
#include <glbinding/gl/gl.h>

#include "rendertarget.h"
#include "../core/gqtypes.h"
#include "camera.h"

using namespace gquake;
using namespace gl;

RenderTarget::RenderTarget() : m_MainCam(nullptr)
{
	
}

void RenderTarget::init()
{
	printf("Flag1\n");
	glGenBuffers(1, &m_UboMats);
	printf("Flag2\n");
	glBindBuffer(GL_UNIFORM_BUFFER, m_UboMats);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(mat4x4), NULL, GL_STATIC_DRAW);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_UboMats);
}

RenderTarget::~RenderTarget()
{
	glDeleteBuffers(1, &m_UboMats); // Dekete UBOs
	// if (m_MainCam) delete m_MainCam; // Delete main camera if scene doesnt (WARNING!!! CAUSES DOUBLE FREE BECAUSE PTR IS NOT NULL)
	while (!m_RenderQueue.empty())
	{
		delete m_RenderQueue.front();
		m_RenderQueue.pop();
	}
}

void RenderTarget::set_main_cam(Camera* cam)
{
	m_MainCam = cam;
}

void RenderTarget::update_ubo()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_UboMats);
	mat4x4 transposed;

	transposed = m_MainCam->get_view().transpose();
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4x4), &transposed);

	transposed = m_MainCam->get_proj().transpose();
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4x4), sizeof(mat4x4), &transposed);

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void RenderTarget::add_to_queue(RenderObject* object)
{
	m_RenderQueue.push(object);
}

void RenderTarget::process_queue()
{
	while (!m_RenderQueue.empty())
	{
		m_RenderQueue.front()->draw();
		m_RenderQueue.pop();
	}
}
