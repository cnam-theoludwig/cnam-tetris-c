#include "tetris_ui_1v1.h"

SDL_Texture* load_texture_from_file(const char* path, SDL_Renderer* renderer);

TetrisUIAction tetris_ui_1v1(struct Tetris* p1, struct Tetris* p2) {
    SDL_Window* window = SDL_CreateWindow(
        "Tetris 1v1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        TETRIS_WINDOW_WIDTH * 2 + 100,
        TETRIS_WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        return UI_ACTION_QUIT;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        return UI_ACTION_QUIT;
    }

    // Load and play music
    SDL_AudioSpec wav_spec;
    Uint32 wav_length;
    Uint8* wav_buffer;
    SDL_AudioDeviceID audio_device = 0;
    if (SDL_LoadWAV("assets/music.wav", &wav_spec, &wav_buffer, &wav_length)) {
        audio_device = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
        if (audio_device) {
            SDL_QueueAudio(audio_device, wav_buffer, wav_length);
            SDL_PauseAudioDevice(audio_device, 0);
        } else {
            SDL_FreeWAV(wav_buffer);
            wav_buffer = NULL;
        }
    }

    SDL_Texture* pause_button_texture = load_texture_from_file("assets/pause_icon.png", renderer);
    SDL_Rect pause_button_rect = {PAUSE_BUTTON_X, PAUSE_BUTTON_Y, PAUSE_BUTTON_SIZE, PAUSE_BUTTON_SIZE};

    // Spawn initial tetrominoes
    tetris_add_tetromino(p1);
    tetris_add_tetromino(p2);

    bool running = true;
    bool paused = false;
    Uint32 last_drop_time_p1 = SDL_GetTicks();
    Uint32 last_drop_time_p2 = SDL_GetTicks();
    SDL_Event event;
    int offset_x1 = 50;
    int offset_x2 = TETRIS_WINDOW_WIDTH + 100;

    while (running) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
            if (!paused && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mx = event.button.x, my = event.button.y;
                if (mx >= pause_button_rect.x && mx <= pause_button_rect.x + pause_button_rect.w &&
                    my >= pause_button_rect.y && my <= pause_button_rect.y + pause_button_rect.h) {
                    paused = true;
                }
            }
            if (!paused && event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    // Player 1 controls
                    case SDLK_q: tetris_last_tetromino_step_left(p1); break;
                    case SDLK_d: tetris_last_tetromino_step_right(p1); break;
                    case SDLK_s: tetris_last_tetromino_step_down(p1); break;
                    case SDLK_a: tetris_last_tetromino_step_rotate_left(p1); break;
                    case SDLK_e: tetris_last_tetromino_step_rotate_right(p1); break;
                    case SDLK_SPACE: {
                        while (tetris_last_tetromino_step_down(p1)) {}
                        tetris_1v1_handle_lines_and_attack(p1, p2);
                        if (!tetris_add_tetromino(p1)) p1->game_over = true;
                        break;
                    }
                    // Player 2 controls
                    case SDLK_LEFT: tetris_last_tetromino_step_left(p2); break;
                    case SDLK_RIGHT: tetris_last_tetromino_step_right(p2); break;
                    case SDLK_DOWN: tetris_last_tetromino_step_down(p2); break;
                    case SDLK_RCTRL: tetris_last_tetromino_step_rotate_right(p2); break;
                    case SDLK_LCTRL: tetris_last_tetromino_step_rotate_left(p2); break;
                    case SDLK_RETURN: {
                        while (tetris_last_tetromino_step_down(p2)) {}
                        tetris_1v1_handle_lines_and_attack(p2, p1);
                        if (!tetris_add_tetromino(p2)) p2->game_over = true;
                        break;
                    }
                    case SDLK_p:
                    case SDLK_ESCAPE:
                        paused = true;
                        break;
                }
            } else if (paused && event.type == SDL_KEYDOWN &&
                       (event.key.keysym.sym == SDLK_p || event.key.keysym.sym == SDLK_ESCAPE)) {
                paused = false;
            }
        }

        // Automatic drop logic
        if (!paused) {
            Uint32 now = SDL_GetTicks();
            float lvl1 = (float)tetris_get_level(p1);
            float lvl2 = (float)tetris_get_level(p2);
            Uint32 delay1 = (Uint32)(0.6f * powf(0.85f, lvl1) * 1000);
            Uint32 delay2 = (Uint32)(0.6f * powf(0.85f, lvl2) * 1000);

            if (now - last_drop_time_p1 >= delay1) {
                if (!tetris_last_tetromino_step_down(p1)) {
                    tetris_1v1_handle_lines_and_attack(p1, p2);
                    if (!tetris_add_tetromino(p1)) p1->game_over = true;
                }
                last_drop_time_p1 = now;
            }
            if (now - last_drop_time_p2 >= delay2) {
                if (!tetris_last_tetromino_step_down(p2)) {
                    tetris_1v1_handle_lines_and_attack(p2, p1);
                    if (!tetris_add_tetromino(p2)) p2->game_over = true;
                }
                last_drop_time_p2 = now;
            }
        }

        // Rendering
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        SDL_RenderSetViewport(renderer, &(SDL_Rect){offset_x1, 0, TETRIS_WINDOW_WIDTH, TETRIS_WINDOW_HEIGHT});
        tetris_ui_render_grid(renderer, p1);
        tetris_ui_render_score(renderer, p1);
        tetris_ui_render_level(renderer, p1);

        SDL_RenderSetViewport(renderer, &(SDL_Rect){offset_x2, 0, TETRIS_WINDOW_WIDTH, TETRIS_WINDOW_HEIGHT});
        tetris_ui_render_grid(renderer, p2);
        tetris_ui_render_score(renderer, p2);
        tetris_ui_render_level(renderer, p2);

        SDL_RenderSetViewport(renderer, NULL);
        if (!paused) {
            SDL_RenderCopy(renderer, pause_button_texture, NULL, &pause_button_rect);
        } else {
            SDL_Rect vp1 = {offset_x1, 0, TETRIS_WINDOW_WIDTH, TETRIS_WINDOW_HEIGHT};
            SDL_Rect vp2 = {offset_x2, 0, TETRIS_WINDOW_WIDTH, TETRIS_WINDOW_HEIGHT};
            SDL_RenderSetViewport(renderer, &vp1);
            tetris_ui_render_pause_menu(renderer, p1);
            SDL_RenderSetViewport(renderer, &vp2);
            tetris_ui_render_pause_menu(renderer, p2);
            SDL_RenderSetViewport(renderer, NULL);
        }

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    if (audio_device) SDL_CloseAudioDevice(audio_device);
    if (wav_buffer) SDL_FreeWAV(wav_buffer);
    if (pause_button_texture) SDL_DestroyTexture(pause_button_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return UI_ACTION_QUIT;
}
