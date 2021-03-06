#pragma once

#include "Hildur/Core/Window.h"
#include "Hildur/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Hildur {


	class WindowsWindow : public Window 
	{
	public:

		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		glm::vec2 GetPosition() const override { return glm::vec2(m_Data.PosX, m_Data.PosY); }
		unsigned int GetPositionX() const override { return (unsigned int)m_Data.PosX; }
		unsigned int GetPositionY() const override { return (unsigned int)m_Data.PosY; }

		void SetName(std::string& name) override;

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:

		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;

		struct WindowData 
		{
			std::string Title;
			unsigned int Width, Height;
			int PosX, PosY;
			bool IsFullscreen;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};


}