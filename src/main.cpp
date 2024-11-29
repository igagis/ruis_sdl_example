#include <utki/config.hpp>

#if CFG_COMPILER == CFG_COMPILER_MSVC
#	include <SDL.h>
#else
#	include <SDL2/SDL.h>
#endif

#include <GL/glew.h>

#include <papki/fs_file.hpp>

#include <utki/unicode.hpp>

#include <ruis/gui.hpp>
#include <ruis/render/opengl/renderer.hpp>
#include <ruis/widget/label/text.hpp>
#include <ruis/widget/button/push_button.hpp>

int width = 640;
int height = 480;

std::array<ruis::key, 0x100> keyMap = {{
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
	ruis::key::arrow_left,    // 80
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
	ruis::key::unknown  // 255
}};

ruis::key sdlScancodeToMordaKey(SDL_Scancode sc){
	if(size_t(sc) >= keyMap.size()){
		return ruis::key::unknown;
	}
	
	return keyMap[sc];
}


int main( int argc, char* args[] ) {
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) { 
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
		return 1;
	}
	
	//Use OpenGL 2.0
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 ); 
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 0 );
	
	SDL_Window* window = SDL_CreateWindow(
			"SDL Tutorial",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
		); 
	if( window == NULL ) { 
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() ); 
		SDL_Quit();
		return 1;
	}
	
	SDL_GLContext gContext = SDL_GL_CreateContext( window );
	if( gContext == NULL ) {
		printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
		SDL_DestroyWindow( window ); 
		SDL_Quit();
	}
	
	if(glewInit() != GLEW_OK){
		SDL_DestroyWindow( window ); 
		SDL_Quit();
		return 1;
	}
	
	Uint32 userEventType = SDL_RegisterEvents(1);
	if(userEventType == ((Uint32)-1)){
		SDL_DestroyWindow( window ); 
		SDL_Quit();
		return 1;
	}
	
	// create ruis gui singleton
	ruis::gui gui(
		utki::make_shared<ruis::context>(
			utki ::make_shared<ruis::render::opengl::renderer>(),
			utki::make_shared<ruis::updater>(),
			[userEventType](std::function<void()>&& f){
				SDL_Event e;
				SDL_memset(&e, 0, sizeof(e));
				e.type = userEventType;
				e.user.code = 0;
				e.user.data1 = new std::function<void()>(std::move(f));
				e.user.data2 = 0;
				SDL_PushEvent(&e);
			},
			[](ruis::mouse_cursor){},
			96,
			1
		)
	);
	
	gui.set_viewport(ruis::vector2(ruis::real(width), ruis::real(height)));
	
	papki::fs_file fi;

	gui.init_standard_widgets(fi);
	
	
	// Inflate widgets hierarchy from GUI description script and set it up
	{
		fi.set_path("res/main.gui");
		auto c = gui.context.get().inflater.inflate(fi);

		// set the widgets hierarchy to the application
		gui.set_root(c);

		auto textLabel = c.get().try_get_widget_as<ruis::text>("info_text");
		ASSERT(textLabel)

		auto button = c.get().try_get_widget_as<ruis::push_button>("hw_button");

		auto textLabelWeak = utki::make_weak(textLabel);//make a weak pointer to the TextLabel widget.

		bool even = true;

		// connect some action on button click
		button->click_handler = [textLabelWeak, even](ruis::push_button& b)mutable{
			if(auto tl = textLabelWeak.lock()){
				even = !even;
				if(even){
					tl->set_text("even");
				}else{
					tl->set_text("odd");
				}
			}
			b.context.get().run_from_ui_thread([](){
				std::cout << "Hello from UI thread!" << std::endl;
			});
		};
	}
	
	SDL_StartTextInput(); 

	for(bool quit = false; !quit;) { 
		if(SDL_WaitEventTimeout(nullptr, gui.update()) == 1){
			SDL_Event e;
			while( SDL_PollEvent( &e ) != 0 ) { 
				if( e.type == SDL_QUIT ) { 
					quit = true; 
				}else if(e.type == SDL_WINDOWEVENT){
					switch(e.window.event) {
						default:
							break;
						case SDL_WINDOWEVENT_RESIZED:
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							width = e.window.data1;
							height = e.window.data2;
//							std::cout << "w = " << e.window.data1 << " h = " << e.window.data2 << std::endl;
							gui.set_viewport(ruis::vector2(ruis::real(width), ruis::real(height)));
							glViewport(0, 0, width, height);
							break;
						case SDL_WINDOWEVENT_ENTER:
							gui.send_mouse_hover(true, 0);
							break;
						case SDL_WINDOWEVENT_LEAVE:
							gui.send_mouse_hover(false, 0);
							break;
					}
				}else if(e.type == SDL_MOUSEMOTION){
					int x = 0, y = 0;
					SDL_GetMouseState(&x, &y);

					gui.send_mouse_move(ruis::vector2(ruis::real(x), ruis::real(y)), 0);
				}else if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
					int x = 0, y = 0;
					SDL_GetMouseState(&x, &y);

					gui.send_mouse_button(
							e.button.type == SDL_MOUSEBUTTONDOWN,
							ruis::vector2(ruis::real(x), ruis::real(y)),
							e.button.button == 1 ? ruis::mouse_button::left : ruis::mouse_button::right,
							0
						);
				}else if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){
					if(e.key.repeat == 0){
						gui.send_key(e.key.type == SDL_KEYDOWN, sdlScancodeToMordaKey(e.key.keysym.scancode));
					}
					if(e.type == SDL_KEYDOWN){
						struct SDLUnicodeDummyProvider : public ruis::gui::input_string_provider{
							std::u32string get()const override{
								return std::u32string();
							}
						};
						gui.send_character_input(SDLUnicodeDummyProvider(), sdlScancodeToMordaKey(e.key.keysym.scancode));
					}
				}else if( e.type == SDL_TEXTINPUT ) {
					struct SDLUnicodeProvider : public ruis::gui::input_string_provider{
						char* text;
						SDLUnicodeProvider(char* text) :
								text(text)
						{}
						std::u32string get()const override{
							return utki::to_utf32(this->text);
						}
					} sdlUnicodeProvider(e.text.text); // save pointer to text, the ownership of text buffer is not taken!!!
					gui.send_character_input(sdlUnicodeProvider, ruis::key::unknown);
				}else if(e.type == userEventType){
					std::unique_ptr<std::function<void()>> f(reinterpret_cast<std::function<void()>*>(e.user.data1));
					f->operator ()();
				}
			}
		}
		
		glClearColor( 0.5f, 0.5f, 0.5f, 1.f );
		glClear( GL_COLOR_BUFFER_BIT );
		
		gui.render();
		
		SDL_GL_SwapWindow( window ); 
	} 
	
	SDL_StopTextInput();

	SDL_GL_DeleteContext(gContext);
	
	SDL_DestroyWindow( window ); 
	
	SDL_Quit();
	
	return 0;
}
