//general FLTK tutorial:
//https://www.youtube.com/watch?v=U83xH1KZ_is
//FLTK linux tutorial:
//https://www.youtube.com/watch?v=UUsZAEEn1cw
//FLTK Microsoft Visual Studio tutorial:
//https://www.youtube.com/watch?v=wT-6ysL0f7c
#include <cstdio> 
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>

using namespace std;

int shortcut_handler( int e, Fl_Window *w )
{	//linux key exceptions: {ESC, F11, PrintScreen}
	if( e == FL_KEYBOARD )
	{	int keycode;
		keycode = Fl::event_original_key();
		printf( "keycode : 0x%08X\n", keycode );
	}
	return Fl::handle_( e, w );
};

void foo( void )
{	Fl_Window win( 600, 800, "Demo Window" ); //runs everywhere
	win.begin();
	//layout must be designed
	Fl_Button but( 20, 20, 80, 25, "New Button" ); 
	win.end();
	win.resizable( win );	//flexible resizing
	win.show();
	Fl::event_dispatch( shortcut_handler ); //keyboard shortcuts
	Fl::run();
};//foo()

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	foo();
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

