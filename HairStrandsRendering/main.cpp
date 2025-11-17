#include "viewer.h"
#include "elems/camera.h"

class Application
{
public:
    Application(const std::string& app_name)
    {
        m_window = std::make_unique<GLWindow>();
        m_window->init(1580, 1280, app_name);
    }
  
    static Application& Instance() { return *m_instance; }
  
    void loop()
    {
        while (m_window->is_running())
        {
          m_window->render();
        }
    }

private:
    static Application* m_instance;

    std::unique_ptr<GLWindow> m_window;
};

extern std::string file_dialog_path;

int main(int argc, char** argv)
{
    if (argc > 1)
        ::file_dialog_path = std::string(argv[1]);
    auto app = std::make_unique<Application>("StrandsViewer");
    app->loop();

    return 0;
}