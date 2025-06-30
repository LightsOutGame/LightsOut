#include "Utils.h"

#include "SDL3/SDL.h"
#include <stdexcept>

void RaiseError(std::string error) {
	SDL_Log(error.c_str());
	throw new std::runtime_error(error);
}
