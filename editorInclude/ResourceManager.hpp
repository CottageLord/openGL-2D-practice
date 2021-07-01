#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

// I recommend a map for filling in the resource manager
#include <map>
#include <string>
#include <memory>
#include <iterator>
#include "Config.hpp"
#include "Sprite.hpp"

// Just a cheap little class to demonstrate loading characters.
class ResourceManager{

	ResourceManager();
public:

	~ResourceManager();

	static ResourceManager *get_instance();

	void init(SDL_Renderer* ren);

	void load_resource();

	void destroy();

	void update(int id);

	void render(int id, SDL_Renderer* ren);


private:
	SDL_Renderer* renderer;
	static ResourceManager *instance;
	std::map<int, Sprite*> loaded_resources;
};

#endif
