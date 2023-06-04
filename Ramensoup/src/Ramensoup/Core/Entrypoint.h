#pragma once


int main(int argc, char** argv)
{
	Ramensoup::Application* app = Ramensoup::CreateApplication();

	app->Run();

	delete app;

	return 0;
}
