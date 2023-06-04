#include <Ramensoup.h>


namespace Ramensoup
{
	class EditorApp : public Application
	{
	public:
		EditorApp()
			:Application()
		{}
	};

	Application* CreateApplication()
	{
		return new EditorApp();
	}
}


