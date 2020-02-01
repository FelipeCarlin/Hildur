#pragma once

#include "Core.h"

#include "Events/Event.h"
#include "Hildur/Window.h"
#include "Hildur/LayerStack.h"
#include "Hildur/Events/ApplicationEvent.h"

#include "Hildur/ImGui/imGuiLayer.h"

#include "Hildur/Renderer/Shader.h"
#include "Hildur/Renderer/Buffer.h"


namespace Hildur {

	class HILDUR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:

		bool OnWindoClose(WindowCloseEvent& e);


		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:

		static Application* s_Instance;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}
