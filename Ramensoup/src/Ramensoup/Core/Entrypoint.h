#pragma once




int main(int argc, char** argv)
{
	Ramensoup::InitLoggers();

	Ramensoup::Application* app = Ramensoup::CreateApplication();

	app->Run();

	delete app;

	return 0;
}
