#include <makina/api.hpp>
#include <makina/renderer/backend/opengl/render_tasks.hpp>

int main(int argc, char** argv)
{
  auto engine = mak::make_default_engine();
 
  const auto display_system = engine->get_system<mak::display_system>();
  const auto window         = display_system->create_opengl_window(
    "Makina Example", 
    std::array<std::size_t, 2>{32 , 32 }, 
    std::array<std::size_t, 2>{800, 600}, 
    di::opengl_context_settings{di::opengl_profile::core, 4, 5});
  window->set_resizable(true);
  window->on_resize.connect([&engine] (const std::array<std::size_t, 2>& size)
  {
    engine->scene()->entities<mak::projection>()[0]->component<mak::projection>()->set_perspective(60.0f, float(size[0]) / float(size[1]), {0.3f, 1000.0f});
  });

  mak::opengl::make_default_framegraph(engine.get(), window);

  auto& models = mak::registry->get<mak::model>().storage();
  auto& model  = models.emplace_back();
  model.load(mak::model::description{"C:/dev/src/cpp/makina/data/model/setesh/setesh.fbx", true});
  mak::append_scene(model.scene.get(), engine->scene());
  
  engine->run();
  return 0;
}