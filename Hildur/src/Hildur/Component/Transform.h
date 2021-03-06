#pragma once

#include "Hildur/Core/Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <vector>


namespace Hildur {


	class Transform : public Component
	{
	public:

		void SetPosition(glm::vec3 position);
		void SetRotation(glm::vec3 rotation);
		void SetScale(glm::vec3 scale);
		void SetParent(Transform* _parent);
		void SetParent(Entity* _entity);
		void Rotate(glm::quat quat);

		void AddPosition(glm::vec3 position);
		void AddRotation(glm::vec3 rotation);
		void AddScale(glm::vec3 scale);
		
		glm::mat4 GetRotationMatrix();
		glm::vec3 GetRotation();
		glm::vec3 GetPosition();
		glm::vec3 GetPositionWorld();
		glm::vec3 GetScale();

		glm::mat4 GetTransformationMatrix();
		glm::mat4 GetLocalTransformationMatrix();
		glm::vec3 Forward();
		glm::vec3 ForwardWorld();
		glm::vec3 Up();
		glm::vec3 UpWorld();
		glm::vec3 Right();
		glm::vec3 RightWorld();

		//void LookAt(glm::vec3 position);

		bool HasChildren();
		bool HasChangedSince(unsigned long int tick);
		bool HasChangedLastTick();
		
		Transform* GetParent();
		std::vector<Transform*> GetChildren();
		void RenderInspector();

	private:

		unsigned long int m_LastChangedTick = -1;
		bool m_IsMatrixCached = false;
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);
		glm::mat4 m_TransformationMatrixCached;
		glm::mat4 m_TransformationMatrixLast;
		Transform* m_Parent;
		std::vector<Transform*> m_Children;

		void RemoveChild(Transform* child);
		void SetChanged();
	};


}