#include <Ramensoup.h>


namespace Ramensoup
{
	class EditorApp : public Application
	{
	public:
		EditorApp()
			:Application()
		{
			Logger::Info("Hello Editor!");
		}
	};

	Application* CreateApplication()
	{
		return new EditorApp();
	}
}


