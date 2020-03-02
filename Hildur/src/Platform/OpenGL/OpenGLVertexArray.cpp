#include "hrpcheaders.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>


namespace Hildur {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Hildur::ShaderDataType::Float:    return GL_FLOAT;
			case Hildur::ShaderDataType::Float2:   return GL_FLOAT;
			case Hildur::ShaderDataType::Float3:   return GL_FLOAT;
			case Hildur::ShaderDataType::Float4:   return GL_FLOAT;
			case Hildur::ShaderDataType::Mat3:     return GL_FLOAT;
			case Hildur::ShaderDataType::Mat4:     return GL_FLOAT;
			case Hildur::ShaderDataType::Int:      return GL_INT;
			case Hildur::ShaderDataType::Int2:     return GL_INT;
			case Hildur::ShaderDataType::Int3:     return GL_INT;
			case Hildur::ShaderDataType::Int4:     return GL_INT;
			case Hildur::ShaderDataType::Bool:     return GL_BOOL;
		}

		HR_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
	
		glGenVertexArrays(1, &m_RendererID);
		
	}

	OpenGLVertexArray::~OpenGLVertexArray() {

		glDeleteVertexArrays(1, &m_RendererID);

	}

	void OpenGLVertexArray::Bind() const {

		glBindVertexArray(m_RendererID);

	}

	void OpenGLVertexArray::Unbind() const {

		glBindVertexArray(0);

	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {

		HR_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : vertexBuffer->GetLayout()) {

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);

	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;

	}


}