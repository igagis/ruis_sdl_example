#include <utki/config.hpp>

#if M_COMPILER == M_COMPILER_MSVC
#	include <SDL.h>
#else
#	include <SDL2/SDL.h>
#endif

#include <GL/glew.h>

#include <papki/FSFile.hpp>

#include <morda/gui.hpp>
#include <mordaren/OpenGL2Renderer.hpp>
#include <morda/widgets/label/Text.hpp>
#include <morda/widgets/button/Button.hpp>
#include <morda/widgets/button/PushButton.hpp>


int width = 640;
int height = 480;

std::array<morda::key, 0x100> keyMap = {{
	morda::key::unknown, // 0
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::a,
	morda::key::b, // x5
	morda::key::c,
	morda::key::d,
	morda::key::e,
	morda::key::f,
	morda::key::g, // 10
	morda::key::h,
	morda::key::i,
	morda::key::j,
	morda::key::k,
	morda::key::l, // x5
	morda::key::m,
	morda::key::n,
	morda::key::o,
	morda::key::p,
	morda::key::q, // 20
	morda::key::r,
	morda::key::s,
	morda::key::t,
	morda::key::u,
	morda::key::v, // x5
	morda::key::w,
	morda::key::x,
	morda::key::y,
	morda::key::z,
	morda::key::one, // 30
	morda::key::two,
	morda::key::three,
	morda::key::four,
	morda::key::five,
	morda::key::six, // x5
	morda::key::seven,
	morda::key::eight,
	morda::key::nine,
	morda::key::zero,
	morda::key::enter, // 40
	morda::key::escape,
	morda::key::backspace,
	morda::key::tabulator,
	morda::key::space,
	morda::key::minus, // x5
	morda::key::equals,
	morda::key::left_square_bracket,
	morda::key::right_square_bracket,
	morda::key::backslash,
	morda::key::backslash, // 50
	morda::key::semicolon,
	morda::key::apostrophe,
	morda::key::grave,
	morda::key::comma,
	morda::key::period, // x5
	morda::key::slash,
	morda::key::capslock,
	morda::key::f1,
	morda::key::f2,
	morda::key::f3, // 60
	morda::key::f4,
	morda::key::f5,
	morda::key::f6,
	morda::key::f7,
	morda::key::f8, // x5
	morda::key::f9,
	morda::key::f10,
	morda::key::f11,
	morda::key::f12,
	morda::key::print_screen, // 70
	morda::key::unknown,
	morda::key::pause,
	morda::key::insert,
	morda::key::home,
	morda::key::page_up, // x5
	morda::key::deletion,
	morda::key::end,
	morda::key::page_down,
	morda::key::right,
	morda::key::left,    // 80
	morda::key::down,
	morda::key::up,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // x5
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // 90
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // x5
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // 100
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::f13,
	morda::key::f14, // x5
	morda::key::f15,
	morda::key::f16,
	morda::key::f17,
	morda::key::f18,
	morda::key::f19, // 110
	morda::key::f20,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // x5
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // 120
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // x5
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // 130
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // x5
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // 140
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // x5
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // 150
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // x5
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // 160
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // x5
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // 170
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // x5
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // 180
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // x5
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // 190
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // x5
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // 200
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // x5
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // 210
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // x5
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // 220
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::left_control,
	morda::key::left_shift, // x5
	morda::key::left_alt,
	morda::key::unknown,
	morda::key::right_control,
	morda::key::right_shift,
	morda::key::right_alt, // 230
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // x5
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // 240
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // x5
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown, // 250
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown,
	morda::key::unknown  // 255
}};

morda::key sdlScancodeToMordaKey(SDL_Scancode sc){
	if(size_t(sc) >= keyMap.size()){
		return morda::key::unknown;
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
	
	//create morda singleton
	morda::gui gui(
			std::make_shared<mordaren::OpenGL2Renderer>(),
			std::make_shared<morda::updater>(),
			[userEventType](std::function<void()>&& f){
				SDL_Event e;
				SDL_memset(&e, 0, sizeof(e));
				e.type = userEventType;
				e.user.code = 0;
				e.user.data1 = new std::function<void()>(std::move(f));
				e.user.data2 = 0;
				SDL_PushEvent(&e);
			},
			96,
			1
		);
	
	gui.setViewportSize(morda::Vec2r(morda::real(width), morda::real(height)));
	
	papki::fs_file fi;

	gui.initStandardWidgets(fi);
	
	
	// Inflate widgets hierarchy from GUI description script and set it up
	{
		fi.setPath("res/main.gui");
		auto c = gui.context->inflater.inflate(fi);

		//set the widgets hierarchy to the application
		gui.setRootWidget(c);

		auto textLabel = c->findByNameAs<morda::Text>("info_text");
		ASSERT(textLabel)

		auto button = c->findByNameAs<morda::PushButton>("hw_button");

		auto textLabelWeak = utki::makeWeak(textLabel);//make a weak pointer to the TextLabel widget.

		bool even = true;

		// connect some action on button click
		button->clicked = [textLabelWeak, even](morda::PushButton& b) mutable {
			if(auto tl = textLabelWeak.lock()){
				even = !even;
				if(even){
					tl->setText("even");
				}else{
					tl->setText("odd");
				}
			}
			b.context->run_from_ui_thread([](){
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
							gui.setViewportSize(morda::Vec2r(morda::real(width), morda::real(height)));
							glViewport(0, 0, width, height);
							break;
						case SDL_WINDOWEVENT_ENTER:
							gui.onMouseHover(true, 0);
							break;
						case SDL_WINDOWEVENT_LEAVE:
							gui.onMouseHover(false, 0);
							break;
					}
				}else if(e.type == SDL_MOUSEMOTION){
					int x = 0, y = 0;
					SDL_GetMouseState(&x, &y);

					gui.onMouseMove(morda::Vec2r(morda::real(x), morda::real(y)), 0);
				}else if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
					int x = 0, y = 0;
					SDL_GetMouseState(&x, &y);

					gui.onMouseButton(
							e.button.type == SDL_MOUSEBUTTONDOWN,
							morda::Vec2r(morda::real(x), morda::real(y)),
							e.button.button == 1 ? morda::MouseButton_e::LEFT : morda::MouseButton_e::RIGHT,
							0
						);
				}else if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){
					if(e.key.repeat == 0){
						gui.onKeyEvent(e.key.type == SDL_KEYDOWN, sdlScancodeToMordaKey(e.key.keysym.scancode));
					}
					if(e.type == SDL_KEYDOWN){
						struct SDLUnicodeDummyProvider : public morda::gui::UnicodeProvider{
							std::u32string get()const override{
								return std::u32string();
							}
						};
						gui.onCharacterInput(SDLUnicodeDummyProvider(), sdlScancodeToMordaKey(e.key.keysym.scancode));
					}
				}else if( e.type == SDL_TEXTINPUT ) {
					struct SDLUnicodeProvider : public morda::gui::UnicodeProvider{
						char* text;
						SDLUnicodeProvider(char* text) :
								text(text)
						{}
						std::u32string get()const override{
							return unikod::toUtf32(this->text);
						}
					} sdlUnicodeProvider(e.text.text); //save pointer to text, the ownership of text buffer is not taken!!!
					gui.onCharacterInput(sdlUnicodeProvider, morda::key::unknown);
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
