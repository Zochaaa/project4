#include "planar_quadrotor_visualizer.h"

PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {}

/**
 * TODO: Improve visualizetion
 * 1. Transform coordinates from quadrotor frame to image frame so the circle is in the middle of the screen
 * 2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier)
 * 3. Animate proppelers (extra points)
 */
void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer) {
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, q_theta;

    /* x, y, theta coordinates */
    q_x = state[0];
    q_y = state[1];
    q_theta = state[2];
    
	int rect_width = 100;
	int rect_height = 20;
	int window_width = 1280, window_height = 720;

    int center_x = window_width / 2;
    int center_y = window_height / 2;

    int screen_x = center_x + static_cast<int>(q_x * 256);
    int screen_y = center_y - static_cast<int>(q_y * 256);

    SDL_Rect quad = { screen_x - rect_width / 2, screen_y - rect_height / 2, rect_width, rect_height };
  
     SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Point center = { rect_width / 2, rect_height / 2 };

    SDL_RenderFillRect(gRenderer.get(), &quad);
    SDL_RenderDrawRect(gRenderer.get(), &quad);

    SDL_Texture* texture = SDL_CreateTexture(gRenderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect_width, rect_height);

    SDL_SetRenderTarget(gRenderer.get(), texture);

    SDL_SetRenderDrawColor(gRenderer.get(), 0x8A, 0x2B, 0xE2, 0xFF);
    SDL_RenderClear(gRenderer.get());

    SDL_SetRenderTarget(gRenderer.get(), nullptr);

    SDL_RenderCopyEx(gRenderer.get(), texture, nullptr, &quad, q_theta * 180.0 / M_PI, &center, SDL_FLIP_NONE);

    SDL_DestroyTexture(texture);
}
