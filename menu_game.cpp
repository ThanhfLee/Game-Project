#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

enum GameMode {
    EASY,
    MEDIUM,
    HARD
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

Button easyButton(220, 300, 200, 50, "Easy");
Button mediumButton(220, 370, 200, 50, "Medium");
Button hardButton(220, 440, 200, 50, "Hard");

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

    easyButton.render(renderer, font);
    mediumButton.render(renderer, font);
    hardButton.render(renderer, font);

    SDL_RenderPresent(renderer);
}

GameMode handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return GameMode::HARD;  // Quit the game
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if (easyButton.isMouseOver(mouseX, mouseY)) return GameMode::EASY;
            if (mediumButton.isMouseOver(mouseX, mouseY)) return GameMode::MEDIUM;
            if (hardButton.isMouseOver(mouseX, mouseY)) return GameMode::HARD;
        }
    }
    return GameMode::HARD;  // Continue in menu
}

int main(int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
        return 1;
    }

    GameMode selectedMode = GameMode::HARD;
    bool quit = false;
    SDL_Event e;  // Khai báo biến e ở đây

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (easyButton.isMouseOver(mouseX, mouseY)) selectedMode = GameMode::EASY;
                if (mediumButton.isMouseOver(mouseX, mouseY)) selectedMode = GameMode::MEDIUM;
                if (hardButton.isMouseOver(mouseX, mouseY)) selectedMode = GameMode::HARD;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Render menu
        renderMenu();

        // Update screen
        SDL_RenderPresent(renderer);

        if (selectedMode != GameMode::HARD) {
            printf("Selected mode: %d\n", selectedMode);
            break;
        }
    }

    close();
    return 0;
}
// Implement Button class methods here