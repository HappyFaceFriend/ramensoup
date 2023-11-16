#pragma once




int main(int argc, char** argv)
{
#ifdef RS_ENABLE_LOGS
	Ramensoup::Logger::Init();
#endif

	Ramensoup::Application* app = Ramensoup::CreateApplication();

	app->Run();

	delete app;

	return 0;
}
