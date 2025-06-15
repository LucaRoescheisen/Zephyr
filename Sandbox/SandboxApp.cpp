#include <Zephyr.h>


class Sandbox : public Zephyr::Application {

public:
	Sandbox() {

	}
	~Sandbox() {

	}


};


Zephyr::Application* Zephyr::CreateApplication() {

	return new Sandbox();
}