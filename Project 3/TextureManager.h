#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;
using sf::Texture;

class TextureManager {
private:
	static unordered_map<string, Texture> images;
	static void LoadTexture(string fileeName);

public:
	static Texture& GetTexture(string textureName);
	static void Clear();
};

