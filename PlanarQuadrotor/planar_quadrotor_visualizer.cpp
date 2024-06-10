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
    
    //SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0x00, 0x00, 0x00);
    //filledCircleColor(gRenderer.get(), q_x + 700, q_y + 300, 50, 0xE6E6FA00);

    //SDL_RenderDrawLine(gRenderer.get(), q_x + 100, q_y + 100, q_x + 1000, q_y + 100);

	//int x1 = 600, y1 = 350, x2 = 700, y2 = 280;
	//Uint8 red = 255, green = 0, blue = 0, alpha = 255; // RGBA color components
	//boxColor(gRenderer.get(), q_x + x1 + , q_y + y1, q_x + x2, q_y + y2, SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), red, green, blue, alpha));

	int rect_width = 60;
	int rect_height = 20;
	int window_width = 1280, window_height = 720;


	//int x = (window_width - rect_width) / 2;
	//int y = (window_height - rect_height) / 2;

	//boxColor(gRenderer.get(), x , y, x + rect_width, y + rect_height, SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), red, green, blue, alpha));
    int center_x = window_width / 2;
    int center_y = window_height / 2;

    int screen_x = center_x + static_cast<int>(q_x * 100);
    int screen_y = center_y - static_cast<int>(q_y * 100);

    SDL_Rect quad = { screen_x - rect_width / 2, screen_y - rect_height / 2, rect_width, rect_height };
    //SDL_Point center = { rect_width / 2, rect_height / 2 };

    SDL_SetRenderDrawColor(gRenderer.get(), 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderFillRect(gRenderer.get(), &quad);

    SDL_RenderDrawRect(gRenderer.get(), &quad);
}
