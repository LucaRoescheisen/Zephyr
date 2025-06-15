#pragma once

#ifdef ZP_PLATFORM_WINDOWS

extern Zephyr::Application* Zephyr::CreateApplication();


int main(int argc, char** argv) {
	printf("Zephyr Engine\n");
	auto app = Zephyr::CreateApplication();
	app->Run();
	delete app;
}

#endif