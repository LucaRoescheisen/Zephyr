#pragma once
#include "Core.h"

namespace Zephyr {

	class ZEPHYR_API Application
	{

	public:
		//Application();
		//virtual ~Application();
		void Run();
	};

	//Defined in client
	Application* CreateApplication();

}



