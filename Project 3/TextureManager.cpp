#include "TextureManager.h"

unordered_map<string, Texture> TextureManager::images;

void TextureManager::LoadTexture(string fileName) {
    string filePath = "images/" + fileName + ".png";
    images[fileName].loadFromFile(filePath);
}

Texture& TextureManager::GetTexture(string textureName) {
    if (images.find(textureName) == images.end()) {
        LoadTexture(textureName);
    }
    return images[textureName];
}

void TextureManager::Clear() {
    images.clear();
}

