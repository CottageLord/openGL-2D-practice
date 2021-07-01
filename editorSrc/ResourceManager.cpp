
#include "ResourceManager.hpp"

// initialize the singleton pointer field
ResourceManager* ResourceManager::instance = nullptr;

ResourceManager::ResourceManager(){}


ResourceManager::~ResourceManager(){}

void ResourceManager::destroy() {
	
	for( auto it = loaded_resources.begin(); it != loaded_resources.end(); ++it )
    {
	    delete (Sprite*) (it->second);
    }
    loaded_resources.clear();
    
}

ResourceManager *ResourceManager::get_instance() {
	if (!instance) instance = new ResourceManager;
	return instance;
}

void ResourceManager::init(SDL_Renderer* ren) {
	// initialize the maps
	renderer = ren;
	
}

void ResourceManager::load_resource() {
	//std::string resource_path = "./sprite.bmp";
	// if the resource is a new one, load it to a map
	// if new resource
	loaded_resources[IMG_FILES::CHAR_IDLE_SPRITE_ID] = new Sprite(CHAR_IDLE_SPRITE, renderer, CHAR_IDLE_IMG_INFO);
	loaded_resources[IMG_FILES::CHAR_WALK_SPRITE_ID] = new Sprite(CHAR_WALK_SPRITE, renderer, CHAR_WALK_IMG_INFO);
	loaded_resources[IMG_FILES::CHAR_JUMP_SPRITE_ID] = new Sprite(CHAR_JUMP_SPRITE, renderer, CHAR_JUMP_IMG_INFO);
	loaded_resources[IMG_FILES::CHAR_FALL_SPRITE_ID] = new Sprite(CHAR_FALL_SPRITE, renderer, CHAR_FALL_IMG_INFO);
	loaded_resources[IMG_FILES::CHAR_HIT_SPRITE_ID] = new Sprite(CHAR_HIT_SPRITE, renderer, CHAR_HIT_IMG_INFO);
	loaded_resources[IMG_FILES::ENEMY_WALK_SPRITE_ID] = new Sprite(ENEMY_WALK_SPRITE, renderer, ENEMY_WALK_IMG_INFO);
	loaded_resources[IMG_FILES::ENEMY_IDLE_SPRITE_ID] = new Sprite(ENEMY_IDLE_SPRITE, renderer, ENEMY_IDLE_IMG_INFO);
	loaded_resources[IMG_FILES::ENEMY_RUN_SPRITE_ID] = new Sprite(ENEMY_RUN_SPRITE, renderer, ENEMY_RUN_IMG_INFO);
	loaded_resources[IMG_FILES::ENEMY_HIT_SPRITE_ID] = new Sprite(ENEMY_HIT_SPRITE, renderer, ENEMY_HIT_IMG_INFO);
	loaded_resources[IMG_FILES::BACKGROUND_IMG_FILE_ID] = new Sprite(BACKGROUND_IMG_FILE, renderer, STILL_SPRITE_INFO);
}


void ResourceManager::update(int id){
	loaded_resources[id]->Update();
}

void ResourceManager::render(int id, SDL_Renderer* ren){
	loaded_resources[id]->Render(ren);
}
