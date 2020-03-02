#pragma once

#include "Hildur/Renderer/RendererAPI.h"


namespace Hildur {


	class OpenGLRendererAPI : public RendererAPI {

	public:

		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4 color) override;
		virtual void Clear() override;

		virtual void SetRenderTarget(const int& ID) override;
		virtual int GetRenderTarget() override { return RendererAPI::m_TargetID; }

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

	};


}