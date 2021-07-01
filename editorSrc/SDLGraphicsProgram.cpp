
#include "SDLGraphicsProgram.hpp"
// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h):screenWidth(w),screenHeight(h){
  	// Initialize random number generation.
   	srand(time(NULL));

	// Initialization flag
	bool success = true;
	// String to hold any errors that occur.
	std::stringstream errorStream;
	// The window we'll be rendering to
	gWindow = NULL;
	// Render flag
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	// Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING)< 0){
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else{
		//Create window
		gWindow = SDL_CreateWindow( "Lab", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN );

		// Check if Window did not create.
		if( gWindow == NULL ){
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//Create a Renderer to draw on
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		// Check if Renderer did not create.
		if( gRenderer == NULL ){
			errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}
	}

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        success = false;
    }

    // Setup our characters
    // Remember, this can only be done after SDL has been
    // successfully initialized!
    // Here I am just building a little grid of characters

    //characters =  characters->get_instance();
    // initialize with the empty maps
    ResourceManager::get_instance()->init(gRenderer);

    ResourceManager::get_instance()->load_resource();


  // If initialization did not work, then print out a list of errors in the constructor.
  if(!success){
    	errorStream << "Failed to initialize!\n";
    	std::string errors=errorStream.str();
    	std::cout << errors << "\n";
  }else{
    	std::cout << "No SDL errors Detected in during init\n\n";
  }
}


SDLGraphicsProgram::~SDLGraphicsProgram(){}

// Proper shutdown and destroy initialized objects
void SDLGraphicsProgram::destroy(){
    // Destroy Renderer
    ResourceManager::get_instance()->destroy();

    SDL_DestroyRenderer(gRenderer);
    //Destroy window
    SDL_DestroyWindow( gWindow );
    // Point gWindow to NULL to ensure it points to nothing.
    gRenderer = NULL;
    gWindow = NULL;
    //Quit SDL subsystems
    SDL_Quit();
}



// Update OpenGL
void SDLGraphicsProgram::update()
{
    
    ResourceManager::get_instance()->update(spriteID);

}

// Render
// The render function gets called once per loop
void SDLGraphicsProgram::render(){

    SDL_SetRenderDrawColor(gRenderer, 0x22,0x22,0x22,0xFF);
    SDL_RenderClear(gRenderer);
    ResourceManager::get_instance()->render(spriteID, getSDLRenderer());
    SDL_RenderPresent(gRenderer);
}

// the Update() helper function that provide a frame stablizer
// adapted from my lab 1
void SDLGraphicsProgram::update_with_timer(std::chrono::steady_clock::time_point &previous_time, double &elapsed_time_total, int &frame_counter, double &lag, double mcs_per_update) {
    // time recorders
    //std::cout << "prev time: " << std::chrono::duration_cast<std::chrono::minutes>(previous_time).count();
    std::chrono::steady_clock::time_point current_time;
    // calculate how much time has elapsed since last record (usually 1 render loop earlier)
    current_time  = std::chrono::steady_clock::now();

    double elapsed_time;
    elapsed_time  = (double)std::chrono::duration_cast<std::chrono::microseconds>
                      (current_time - previous_time).count();
    // renew time record
    previous_time = current_time;
    // record overall time spend (in microseconds)
    elapsed_time_total += elapsed_time;
    // stablizer switch
    if(stable_frame) {
        // if the last update/render loop spent more than fps limit (16.67ms for 60 fps)
        // we update untill the game progress catches up
        lag += elapsed_time;
        while(lag >= mcs_per_update) {
            // Update our scene
            update();
            lag -= mcs_per_update;
            frame_counter++;
        }
    } else {
        update();
        frame_counter++;
    }
    // for every 1 second, report frame rate and re-initialize counters
    if (elapsed_time_total > mcs_per_second)
    {
        //std::cout << "current frame rate: " << frame_counter << std::endl;
        frame_counter = 0;
        elapsed_time_total = 0.0;
    }
}





//Loops forever!
void SDLGraphicsProgram::loop(){
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();

    // define microseconds per update
    // ===============================================================
    // use MAGIC NUMBER to make sure sprite with less grids run slower
    // ===============================================================
    int frame_rate = 60;
    double mcs_per_update = mcs_per_second / frame_rate;
    // elapsed_time_total - measure total time elapsed
    // lag - accumulate elapsed time for determining when to update to ensure steady frame rate
    double lag = 0, elapsed_time_total = 0.0;
    // frame_counter - measure the real frame rate
    int frame_counter = 0;
    // chrono::steadyclock for measuring times accurately while rendering
    std::chrono::steady_clock::time_point previous_time;
    // record the initial time
    previous_time = std::chrono::steady_clock::now();
    // While application is running

    promptMsg();
    // While application is running
    while(!quit){
      processInput(&quit);
      // Update our scene
      // update with a frame stablizer
      update_with_timer(previous_time, elapsed_time_total, frame_counter, lag, mcs_per_update);
      // Render using OpenGL
      render();
      //Update screen of our specified window
    }

    //Disable text input
    SDL_StopTextInput();
}

// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::getSDLWindow(){
  return gWindow;
}

// Get Pointer to Renderer
SDL_Renderer* SDLGraphicsProgram::getSDLRenderer(){
  return gRenderer;
}

void SDLGraphicsProgram::promptMsg() {
    std::cout << "Please select a sprite:" << std::endl;
    std::cout << "[0] Character idle" << std::endl;
    std::cout << "[1] Character walk" << std::endl;
    std::cout << "[2] Character jump" << std::endl;
    std::cout << "[3] Character fall" << std::endl;
    std::cout << "[4] Character idle" << std::endl;
    std::cout << "[5] Enemy walk" << std::endl;
    std::cout << "[6] Enemy idle" << std::endl;
    std::cout << "[7] Enemy run" << std::endl;
    std::cout << "[8] Enemy hit" << std::endl;
}

void SDLGraphicsProgram::processInput(bool *quit) {
    SDL_Event event;
    SDL_StartTextInput();
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            *quit = true;
            return;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_q:
                    *quit = true;
                    break;
                case SDLK_0:
                    spriteID = CHAR_IDLE_SPRITE_ID;
                    break;
                case SDLK_1:
                    spriteID = CHAR_WALK_SPRITE_ID;
                    break;
                case SDLK_2:
                    spriteID = CHAR_JUMP_SPRITE_ID;
                    break;
                case SDLK_3:
                    spriteID = CHAR_FALL_SPRITE_ID;
                    break;
                case SDLK_4:
                    spriteID = CHAR_HIT_SPRITE_ID;
                    break;
                case SDLK_5:
                    spriteID = ENEMY_WALK_SPRITE_ID;
                    break;
                case SDLK_6:
                    spriteID = ENEMY_IDLE_SPRITE_ID;
                    break;
                case SDLK_7:
                    spriteID = ENEMY_RUN_SPRITE_ID;
                    break;
                case SDLK_8:
                    spriteID = ENEMY_HIT_SPRITE_ID;
                    break;
                default:
                    spriteID = ENEMY_RUN_SPRITE_ID;
                    std::cout << std::endl << ">>>>>>>>Invalid ID!<<<<<<<" << std::endl << std::endl;
                    promptMsg();

            }
        } 
    }
}