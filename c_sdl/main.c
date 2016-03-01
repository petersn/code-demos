// SDL demo.

#include <SDL.h>

// Global storage. Eww.
int screen_width, screen_height;
SDL_Surface* screen;
int up_held = 0;
int counter = 0;

void main_loop(void) {
	while (1) {
		// We begin each loop by getting events.
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
				// SDL_QUIT corresponds to someone hitting the X on the window decoration, so we close the program.
				case SDL_QUIT:
					SDL_Quit();
					exit(0);
					break;
				case SDL_KEYDOWN:
					// This corresponds to a user hitting escape, so we close the program. (keycode 27 = esc)
					if (ev.key.keysym.sym == 27) {
						SDL_Quit();
						exit(0);
					} else if (ev.key.keysym.sym == SDLK_UP) {
						// Track when the user hits up...
						up_held = 1;
					}
					break;
				case SDL_KEYUP:
					// ... and clear the flag when they release up.
					if (ev.key.keysym.sym == SDLK_UP)
						up_held = 0;
					break;
			}
		}

		// We must make these calls, to avoid violating SDL's rules.
		if (SDL_MUSTLOCK(screen))
	        SDL_LockSurface(screen);

		// Once we're done handling all the key presses, draw some random shit.
		if (up_held)
			counter++;
		int x, y;
		for (y = 0; y < screen_height; y++) {
			for (x = 0; x < screen_width; x++) {
				char* pixel_pointer = ((char*)screen->pixels) + 4*(x + y*screen_width);
				// Set the B, G, and R components separately.
				// The fourth byte is reserved for alpha, but not used in RGB video mode for alignment reasons.
				pixel_pointer[0] = x+y + counter;
				pixel_pointer[1] = y-x + counter;
				pixel_pointer[2] = x*y*counter;
			}
		}

		// We must make these calls, to avoid violating SDL's rules.
		if (SDL_MUSTLOCK(screen))
	        SDL_UnlockSurface(screen);

		// This call actually makes our changes visible, by flipping the double buffer.
		SDL_Flip(screen);
	}
}

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Unable to SDL_Init.\n");
		exit(1);
	}
	// This call lets us get the screen resolution, to be completely fullscreen.
	const SDL_VideoInfo* info = SDL_GetVideoInfo();
	if (info == NULL) {
		fprintf(stderr, "Unable to get video info: %s\n", SDL_GetError());
		exit(1);
	}
	// Choose the maximum possible screen resolution to be our target resolution.
	// Of course, if you want a smaller window, set these to other values.
	screen_width  = info->current_w;
	screen_height = info->current_h;
	int video_flags = 0;
	// These guys aren't super critical, but change video performance/behavior on some systems.
	video_flags |= SDL_GL_DOUBLEBUFFER;
	video_flags |= SDL_HWPALETTE;
	// Comment this one out if you don't want fullscreen!
	video_flags |= SDL_FULLSCREEN;
	screen = SDL_SetVideoMode(screen_width, screen_height, 32, video_flags);
	if (screen == NULL) {
		fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}
	// Drop into the main loop.
	main_loop();
	return 0;
}
