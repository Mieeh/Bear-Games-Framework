#include<iostream>

#include<window\window.h>
#include<sound\sound.h>
#include<core\bounding_box.h>
#include<core\vector2.h>
#include<graphics\graphics.h>

#include<graphics/renderers/batch_renderer.h>
#include<graphics/renderers/particle_renderer.h>

#include<core/random.h>

using namespace bear;

constexpr auto WIDTH = 720;
constexpr auto HEIGHT = 510;

int main()
{
	bear::window::Window myWindow(WIDTH, HEIGHT, "THIS IS A WINDOW");
	myWindow.setVSync(true);

	if (!graphics::Graphics::init(WIDTH, HEIGHT))
		std::cout << "Graphics failed to init send help\n";

	graphics::ParticleRenderer *pr = new graphics::ParticleRenderer();
	pr->init();
	graphics::ParticlePool pool;

	graphics::BatchRenderer _renderer;
	_renderer.init();
	
	core::Vector2f v1(10, 10);
	core::Vector2f v2(100, 105);
	core::Vector2f directionVector;
	float speed = 1.0f;
	
	graphics::Renderable torch(graphics::renderable_type::Rectangle);
	torch.transform().m_Position = v1;
	torch.transform().m_Size = core::Vector2f(30, 30);
	torch.setColor(core::Color::Red());

	graphics::Renderable torch2(graphics::renderable_type::Rectangle);
	torch2.transform().m_Position = v2;
	torch2.transform().m_Size = core::Vector2f(30, 30);
	torch2.setColor(core::Color::Blue());

	graphics::Image testImage("shaders\\dide.png", graphics::image_format::RGBA);
	graphics::Renderable dide(testImage);
	dide.transform().m_Position = core::Vector2f(100, 100);
	
	while (myWindow.isOpen()) 
	{
		float dt = myWindow.getDeltaTime(); // Get the delta time for the last frame
		for (Event event : myWindow.getRegisteredEvents()) { // Process the events here
			if (event.type == EventType::WindowReiszed) {
				graphics::Graphics::window_resize_callback(event.size.x, event.size.y);
			}
			if (event.type == EventType::KeyPressed) {
				//if(event.key )
			}
		}	

		if (myWindow.isKeyDown(Key::D)) {
			v2.x += .1 * dt;
		}
		if (myWindow.isKeyDown(Key::A)) {
			v2.x -= .1 * dt;
		}
		if (myWindow.isKeyDown(Key::S)) {
			v2.y += .1 * dt;
		}
		if (myWindow.isKeyDown(Key::W)) {
			v2.y -= .1 * dt;
		}

		//if (myWindow.isKeyDown(Key::X))
		{
			graphics::ParticleConfig config;
			config.color = core::Color::White();
			config.makeColorRandom();
			config.size = core::randomIntegerInterval(5, 50);
			config.position = core::Vector2f(WIDTH/2,HEIGHT/2) + core::randomPointInsideCircle(200);
			//config.velocity = core::Vector2f(0, -0.1f);

			pool.addParticles(1, config, core::randomIntegerInterval(1000, 3000));
		}

		// Vector test thingy
		dide.transform().m_Position = v2;
		directionVector = v2 - v1;
		v1 += directionVector.normalize() * speed;
		//std::cout << v1 << std::endl;
		torch.transform().m_Position = v1;
		torch2.transform().m_Position = v2;
			
		// RENDERING BEGINS HERE
		myWindow.clear(core::Color(0.09f,0.09f,0.12f)); // Here is where the window is cleared and we can now render to the fresh window
		
		// The normal renderer
		_renderer.begin();
		_renderer.submit(torch);
		_renderer.submit(torch2);
		_renderer.submit(dide);
		_renderer.flush();

		// Particles
		pool.process(dt);
		pr->begin();
		pr->submit(pool);
		pr->flush();
		
		myWindow.display(); 
	}

	graphics::Graphics::exit();

	return 0;
}