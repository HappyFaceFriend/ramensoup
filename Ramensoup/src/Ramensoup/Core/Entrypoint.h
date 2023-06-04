#pragma once




int main(int argc, char** argv)
{
	Ramensoup::Logger::Init();
	Ramensoup::CoreLogger::Init();

	Ramensoup::Application* app = Ramensoup::CreateApplication();

	app->Run();

	delete app;

	return 0;
}
