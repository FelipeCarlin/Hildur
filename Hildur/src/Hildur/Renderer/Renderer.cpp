#include "hrpcheaders.h"
#include "Renderer.h"

#include "Hildur/Renderer/Texture.h"

#include "Hildur/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"


namespace Hildur {


	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;


	void Renderer::Init() {

		RenderCommand::Init();

	}

	void Renderer::BeginScene(OrthographicCamera& camera) {

		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

	}

	void Renderer::BeginScene(PerspectiveCamera& camera) {

		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();

	}

	void Renderer::EndScene() {



	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {

		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader> (shader)->UploadUniformMat4("u_ViewProjectionMat", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader> (shader)->UploadUniformMat4("u_ModelMat", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);

	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<Mesh>& mesh, const glm::mat4& transform) {

		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader> (shader)->UploadUniformMat4("u_ViewProjectionMat", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader> (shader)->UploadUniformMat4("u_ModelMat", transform);


		mesh->GetDiffuseTex()->Bind(mesh->GetDiffuseTex()->GetTextureUnit());
		std::dynamic_pointer_cast<OpenGLShader> (shader)->UploadUniformInt("diffuseTex1", mesh->GetDiffuseTex()->GetTextureUnit());


		mesh->GetVertexArray()->Bind();

		RenderCommand::DrawIndexed(mesh->GetVertexArray());

	}

}