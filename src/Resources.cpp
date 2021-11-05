#include "Game.h"
#include "Resources.h"
#include <iostream>

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(string file)
{
  if (!imageTable.count(file))
  {
    SDL_Texture *texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    imageTable.emplace(file, texture);
  }
  if (!imageTable.at(file))
  {
    std::cout << "Error loading texture: " << SDL_GetError() << std::endl;
    exit(1);
  }
  return imageTable.at(file);
}

void Resources::ClearImages()
{
  imageTable.clear();
}

Mix_Music* Resources::GetMusic(string file)
{
  if (!musicTable.count(file))
  {
    Mix_Music *music = Mix_LoadMUS(file.c_str());
    musicTable.emplace(file, music);
  }
  if (musicTable.at(file) == nullptr)
  {
    std::cout << "Error loading music: " << SDL_GetError() << std::endl;
    exit(1);
  }
  return musicTable.at(file);
}

void Resources::ClearMusics()
{
  musicTable.clear();
}

Mix_Chunk* Resources::GetSound(string file)
{
  if (!soundTable.count(file))
  {
    Mix_Chunk *chunk = Mix_LoadWAV(file.c_str());
    soundTable.emplace(file, chunk);
  }
  if (soundTable.at(file) == nullptr)
  {
    std::cout << "Error loading sound: " << SDL_GetError() << std::endl;
    exit(1);
  }
  return soundTable.at(file);
}

void Resources::ClearSounds()
{
  soundTable.clear();
}