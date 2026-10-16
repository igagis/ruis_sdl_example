#include <utki/config.hpp>

#if CFG_COMPILER == CFG_COMPILER_MSVC
#	include <SDL.h>
#else
#	include <SDL2/SDL.h>
#endif

#include <GL/glew.h>
#include <fsif/native_file.hpp>
#include <ruis/gui.hpp>
#include <ruis/render/opengl/context.hpp>
#include <ruis/widget/button/push_button.hpp>
#include <ruis/widget/label/rectangle.hpp>
#include <ruis/widget/label/text.hpp>
#include <utki/log.hpp>
#include <utki/unicode.hpp>

#include "gui.hpp"

namespace {
constexpr int default_window_width = 640;
constexpr int default_window_height = 480;
constexpr int standard_dpi = 96;
constexpr size_t scancode_count = 0x100;

std::array<ruis::key, scancode_count> const key_map = {
	{
     ruis::key::unknown, // 0
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::a,
     ruis::key::b, // x5
		ruis::key::c,
     ruis::key::d,
     ruis::key::e,
     ruis::key::f,
     ruis::key::g, // 10
		ruis::key::h,
     ruis::key::i,
     ruis::key::j,
     ruis::key::k,
     ruis::key::l, // x5
		ruis::key::m,
     ruis::key::n,
     ruis::key::o,
     ruis::key::p,
     ruis::key::q, // 20
		ruis::key::r,
     ruis::key::s,
     ruis::key::t,
     ruis::key::u,
     ruis::key::v, // x5
		ruis::key::w,
     ruis::key::x,
     ruis::key::y,
     ruis::key::z,
     ruis::key::one, // 30
		ruis::key::two,
     ruis::key::three,
     ruis::key::four,
     ruis::key::five,
     ruis::key::six, // x5
		ruis::key::seven,
     ruis::key::eight,
     ruis::key::nine,
     ruis::key::zero,
     ruis::key::enter, // 40
		ruis::key::escape,
     ruis::key::backspace,
     ruis::key::tabulator,
     ruis::key::space,
     ruis::key::minus, // x5
		ruis::key::equals,
     ruis::key::left_square_bracket,
     ruis::key::right_square_bracket,
     ruis::key::backslash,
     ruis::key::backslash, // 50
		ruis::key::semicolon,
     ruis::key::apostrophe,
     ruis::key::grave,
     ruis::key::comma,
     ruis::key::period, // x5
		ruis::key::slash,
     ruis::key::capslock,
     ruis::key::f1,
     ruis::key::f2,
     ruis::key::f3, // 60
		ruis::key::f4,
     ruis::key::f5,
     ruis::key::f6,
     ruis::key::f7,
     ruis::key::f8, // x5
		ruis::key::f9,
     ruis::key::f10,
     ruis::key::f11,
     ruis::key::f12,
     ruis::key::print_screen, // 70
		ruis::key::unknown,
     ruis::key::pause,
     ruis::key::insert,
     ruis::key::home,
     ruis::key::page_up, // x5
		ruis::key::deletion,
     ruis::key::end,
     ruis::key::page_down,
     ruis::key::arrow_right,
     ruis::key::arrow_left, // 80
		ruis::key::arrow_down,
     ruis::key::arrow_up,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // x5
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // 90
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // x5
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // 100
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::f13,
     ruis::key::f14, // x5
		ruis::key::f15,
     ruis::key::f16,
     ruis::key::f17,
     ruis::key::f18,
     ruis::key::f19, // 110
		ruis::key::f20,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // x5
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // 120
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // x5
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // 130
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // x5
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // 140
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // x5
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // 150
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // x5
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // 160
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // x5
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // 170
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // x5
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // 180
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // x5
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // 190
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // x5
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // 200
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // x5
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // 210
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // x5
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // 220
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::left_control,
     ruis::key::left_shift, // x5
		ruis::key::left_alt,
     ruis::key::unknown,
     ruis::key::right_control,
     ruis::key::right_shift,
     ruis::key::right_alt, // 230
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // x5
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // 240
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // x5
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown, // 250
		ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown,
     ruis::key::unknown // 255
	}
};

ruis::key sdl_scan_code_to_ruis_key(SDL_Scancode sc)
{
	if (size_t(sc) >= key_map.size()) {
		return ruis::key::unknown;
	}

	return key_map[sc];
}

} // namespace

int main(int argc, char* args[])
{
	int width = default_window_width;
	int height = default_window_height;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		utki::log([&](auto& o) {
			o << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		});
		return 1;
	}

	utki::scope_exit sdl_scope_exit([]() {
		SDL_Quit();
	});

	// use OpenGL 2.0
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_Window* window = SDL_CreateWindow(
		"SDL Tutorial",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
	if (window == nullptr) {
		utki::log([&](auto& o) {
			o << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		});
		return 1;
	}

	utki::scope_exit window_scope_exit([&window]() {
		SDL_DestroyWindow(window);
	});

	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	if (gl_context == nullptr) {
		utki::log([&](auto& o) {
			o << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
		});
		return 1;
	}

	utki::scope_exit gl_scope_exit([&gl_context]() {
		SDL_GL_DeleteContext(gl_context);
	});

	if (glewInit() != GLEW_OK) {
		return 1;
	}

	Uint32 user_event_type = SDL_RegisterEvents(1);
	if (user_event_type == ((Uint32)-1)) {
		return 1;
	}

	auto rendering_context =
		utki::make_shared<ruis::render::opengl::context>(utki::make_shared<ruis::render::native_window>());

	auto common_render_objects = utki::make_shared<ruis::render::renderer::objects>(rendering_context);
	auto common_shaders = rendering_context.get().make_shaders();

	auto ruis_resource_loader = utki::make_shared<ruis::resource_loader>(
		rendering_context, //
		common_render_objects
	);

	auto ruis_style_provider = utki::make_shared<ruis::style_provider>(std::move(ruis_resource_loader));

	// create ruis gui singleton
	ruis::gui gui(utki::make_shared<ruis::context>(ruis::context::parameters{
		.post_to_ui_thread_function =
			[user_event_type](std::function<void()> procedure) {
				// NOLINTNEXTLINE(cppcoreguidelines-owning-memory, "the SDL C API has no way to pass a C++ callable through user events")
				auto f = new std::function<void()>(std::move(procedure));
				SDL_Event e;
				SDL_zero(e);
				e.type = user_event_type;
				// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast, "the SDL C API has no way to pass a C++ callable through user events")
				e.user.data1 = reinterpret_cast<void*>(f);
				if (SDL_PushEvent(&e) < 0) {
					// NOLINTNEXTLINE(cppcoreguidelines-owning-memory, "the SDL C API has no way to pass a C++ callable through user events")
					delete f;
				}
			},
		.updater = utki::make_shared<ruis::updater>(),
		.renderer = utki::make_shared<ruis::render::renderer>(rendering_context, common_shaders, common_render_objects),
		.style_provider = std::move(ruis_style_provider),
		.units = ruis::units(standard_dpi, 1)
	}));

	gui.set_viewport(ruis::rect{
		{				0,				  0},
		{ruis::real(width), ruis::real(height)}
	});

	fsif::native_file fi;

	gui.ctx().loader().mount_ruis_res_pack(fi);

	{
		// namespace m = ruis::make;
		// gui.set_root(
		// 	m::rectangle(gui.context,
		// 		{
		// 			.color_params{
		// 				.color = 0xff00ff00
		// 			}
		// 		}
		// 	)
		// );
	}

	// set it up GUI widget structure
	{
		auto c = make_root_widget(gui.context);

		// set the widgets hierarchy to the application
		gui.set_root(c);

		auto text_label = c.get().try_get_widget_as<ruis::text>("info_text");
		utki::assert(text_label, SL);

		auto button = c.get().try_get_widget_as<ruis::push_button>("hw_button");

		auto text_label_weak = utki::make_weak(text_label); //make a weak pointer to the TextLabel widget.

		bool even = true;

		// connect some action on button click
		button->click_handler = [text_label_weak, even](ruis::push_button& b) mutable {
			if (auto tl = text_label_weak.lock()) {
				even = !even;
				if (even) {
					tl->set_string("even");
				} else {
					tl->set_string("odd");
				}
			}
			b.context.get().post_to_ui_thread([]() {
				std::cout << "Hello from UI thread!" << std::endl;
			});
		};
	}

	SDL_StartTextInput();

	utki::scope_exit text_input_scope_exit([]() {
		SDL_StopTextInput();
	});

	for (bool quit = false; !quit;) {
		if (SDL_WaitEventTimeout(nullptr, static_cast<int>(gui.context.get().updater.get().update())) == 1) {
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quit = true;
				} else if (e.type == SDL_WINDOWEVENT) {
					switch (e.window.event) {
						default:
							break;
						case SDL_WINDOWEVENT_RESIZED:
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							width = e.window.data1;
							height = e.window.data2;
							// std::cout << "w = " << e.window.data1 << " h = " << e.window.data2 << std::endl;
							gui.set_viewport({
								{                0,                  0}, //
								{ruis::real(width), ruis::real(height)}
							});
							break;
						case SDL_WINDOWEVENT_ENTER:
							gui.send_mouse_hover(true, 0);
							break;
						case SDL_WINDOWEVENT_LEAVE:
							gui.send_mouse_hover(false, 0);
							break;
					}
				} else if (e.type == SDL_MOUSEMOTION) {
					int x = 0, y = 0;
					SDL_GetMouseState(&x, &y);

					gui.send_mouse_move({ruis::real(x), ruis::real(y)}, 0);
				} else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
					int x = 0, y = 0;
					SDL_GetMouseState(&x, &y);

					gui.send_mouse_button(
						e.button.type == SDL_MOUSEBUTTONDOWN ? ruis::button_action::press
															 : ruis::button_action::release,
						{ruis::real(x), ruis::real(y)},
						e.button.button == 1 ? ruis::mouse_button::left : ruis::mouse_button::right,
						0
					);
				} else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
					if (e.key.repeat == 0) {
						gui.send_key(
							e.key.type == SDL_KEYDOWN ? ruis::button_action::press : ruis::button_action::release,
							sdl_scan_code_to_ruis_key(e.key.keysym.scancode)
						);
					}
					if (e.type == SDL_KEYDOWN) {
						struct sdl_unicode_dummy_provider : public ruis::gui::input_string_provider {
							std::u32string get() const override
							{
								return {};
							}
						};

						gui.send_character_input(
							sdl_unicode_dummy_provider(),
							sdl_scan_code_to_ruis_key(e.key.keysym.scancode)
						);
					}
				} else if (e.type == SDL_TEXTINPUT) {
					struct sdl_unicode_provider : public ruis::gui::input_string_provider {
						char* text;

						sdl_unicode_provider(char* text) :
							text(text)
						{}

						std::u32string get() const override
						{
							return utki::to_utf32(this->text);
						}
					} unicode_provider(&e.text.text[0]
					); // save pointer to text, the ownership of text buffer is not taken!!!

					gui.send_character_input(unicode_provider, ruis::key::unknown);
				} else if (e.type == user_event_type) {
					// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast, "the SDL C API has no way to pass a C++ callable through user events")
					std::unique_ptr<std::function<void()>> f(reinterpret_cast<std::function<void()>*>(e.user.data1));
					f->operator()();
				}
			}
		}

		gui.context.get().ren().rendering_context.get().clear_framebuffer_color();
		gui.render(gui.context.get().ren().rendering_context.get().initial_matrix);

		SDL_GL_SwapWindow(window);
	}

	return 0;
}
