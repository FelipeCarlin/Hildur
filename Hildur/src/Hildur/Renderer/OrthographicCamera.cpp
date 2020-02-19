#include "hrpcheaders.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>


namespace Hildur {


	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) 
		:m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f) {
		//:m_ProjectionMatrix(glm::perspective(1.57f, 16.0f / 9.0f, 0.1f, 100.0f)) {

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

		m_Position = { 0.0f, 0.0f, 0.0f };
	
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top) {

		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}

	void OrthographicCamera::RecalculateViewMatrix() {

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));


		m_ViewMatrix = glm::inverse(transform);
		//m_ViewMatrix = glm::lookAt(m_Position, m_Position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}


}