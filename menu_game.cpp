#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <cstdlib>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

enum GameMode {
    CLASSIC,
    UPDATE,
    COMINGSOON
};

class Button {
public:
    Button(int x, int y, int w, int h, const std::string& text);
    void render(SDL_Renderer* renderer, TTF_Font* font);
    bool isMouseOver(int mouseX, int mouseY);

private:
    SDL_Rect rect;
    std::string text;
};

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;
SDL_Texture* backgroundTexture = nullptr;

Button classicButton(220, 300, 200, 50, "Classic (4x4)");
Button updateButton(220, 370, 200, 50, "Update (5x5)");
Button comingsoonButton(220, 440, 200, 50, "Coming Soon");

void Button::render(SDL_Renderer* renderer, TTF_Font* font) {
    // Vẽ nền của nút
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);  // Màu xám nhạt
    SDL_RenderFillRect(renderer, &rect);

    // Vẽ viền của nút
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Màu đen
    SDL_RenderDrawRect(renderer, &rect);

    // Tạo texture cho text
    SDL_Color textColor = {0, 0, 0, 255};  // Màu đen
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == nullptr) {
        // Xử lý lỗi
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        // Xử lý lỗi
        SDL_FreeSurface(textSurface);
        return;
    }

    // Đặt vị trí của text ở giữa nút
    SDL_Rect textRect;
    textRect.x = rect.x + (rect.w - textSurface->w) / 2;
    textRect.y = rect.y + (rect.h - textSurface->h) / 2;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;

    // Render text
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Giải phóng bộ nhớ
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

Button::Button(int x, int y, int w, int h, const std::string& text)
    : rect{x, y, w, h}, text(text) {}

bool Button::isMouseOver(int mouseX, int mouseY) {
    return (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
            mouseY >= rect.y && mouseY <= rect.y + rect.h);
}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    if (TTF_Init() < 0) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    font = TTF_OpenFont("arial.ttf", 24);
    if (!font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    SDL_Surface* backgroundSurface = IMG_Load("menu.png");
    if (!backgroundSurface) {
        printf("Failed to load background image! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (!backgroundTexture) {
        printf("Failed to create background texture! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void close() {
    SDL_DestroyTexture(backgroundTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void renderMenu() {
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    SDL_Color titleColor = {255, 255, 255, 255};
    SDL_Surface* titleSurface = TTF_RenderText_Solid(font, "2048", titleColor);
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_Rect titleRect = {220, 200, titleSurface->w, titleSurface->h};
    SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);

    classicButton.render(renderer, font);
    updateButton.render(renderer, font);
    comingsoonButton.render(renderer, font);

    SDL_RenderPresent(renderer);
}

GameMode handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return GameMode::COMINGSOON;  // Quit the game
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if (classicButton.isMouseOver(mouseX, mouseY)) return GameMode::CLASSIC;
            if (updateButton.isMouseOver(mouseX, mouseY)) return GameMode::UPDATE;
            if (comingsoonButton.isMouseOver(mouseX, mouseY)) return GameMode::COMINGSOON;
        }
    }
    return GameMode::COMINGSOON;  // Continue in menu
}

void compileAndRunCpp(const std::string& filepath) {
    std::string sdlFlags = "-ID:/CodeBlocks/menu/Project_Game/SDL2/include/SDL2 -LD:/CodeBlocks/menu/Project_Game/SDL2/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -mconsole";

    std::string compileCommand = "g++ " + filepath + " -o temp_game " + sdlFlags;
    std::string runCommand = "./temp_game";

    #ifdef _WIN32
    runCommand = "temp_game.exe";
    #endif

    int compileResult = system(compileCommand.c_str());
    if (compileResult == 0) {
        std::cout << "Compilation successful. Running the game..." << std::endl;
        system(runCommand.c_str());
    } else {
        std::cout << "Compilation failed." << std::endl;
    }
}

int main(int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
        return 1;
    }

    GameMode selectedMode = GameMode::COMINGSOON;
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (classicButton.isMouseOver(mouseX, mouseY)) {
                    close();  // Đóng SDL trước khi chạy game mới
                    compileAndRunCpp("Project_Game/src.cpp");
                    return 0;  // Kết thúc chương trình hiện tại
                }
                if (updateButton.isMouseOver(mouseX, mouseY)) {
                    selectedMode = GameMode::UPDATE;
                    // Xử lý cho chế độ update
                }
                if (comingsoonButton.isMouseOver(mouseX, mouseY)) {
                    selectedMode = GameMode::COMINGSOON;
                    // Xử lý cho
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Render menu
        renderMenu();

        // Update screen
        SDL_RenderPresent(renderer);
    }

    close();
    return 0;
}
