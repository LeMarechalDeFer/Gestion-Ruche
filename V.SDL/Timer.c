#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

// Initialize SDL and TTF
void init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    TTF_Init();
}

// Clean up SDL and TTF
void quit(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

// Main function to create a timer and display it
int main(int argc, char* args[]) {
    init();

    SDL_Window* window = SDL_CreateWindow("Timer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load a font
    TTF_Font* font = TTF_OpenFont("Roboto-BlackItalic.ttf", 24); // Make sure to provide the correct path to your font file
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        quit(window, renderer, font);
        return -1;
    }

    SDL_Color color = {255, 255, 255, 255}; // White color for the font
    Uint32 start = SDL_GetTicks();
    char timeText[100];

    // Event loop flag
    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Calculate the time elapsed
        Uint32 elapsed = (SDL_GetTicks() - start) / 1000;
        sprintf(timeText, "Time: %u seconds", elapsed);

        // Create surface and texture for the text
        SDL_Surface* surface = TTF_RenderText_Solid(font, timeText, color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        // Clear the window
        SDL_RenderClear(renderer);

        // Get the texture width and height
        int text_width = surface->w;
        int text_height = surface->h;

        // Define where on the window we want to render the text
        SDL_Rect renderQuad = { 10, 10, text_width, text_height };

        // Render the text
        SDL_RenderCopy(renderer, texture, NULL, &renderQuad);

        // Update the window
        SDL_RenderPresent(renderer);

        // Free the surface and texture
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_Delay(1000); // Update every second
    }

    quit(window, renderer, font);
    return 0;
}
