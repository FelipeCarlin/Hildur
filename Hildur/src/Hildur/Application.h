#pragma once

#include "Core.h"

namespace Hildur {

	class HILDUR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}