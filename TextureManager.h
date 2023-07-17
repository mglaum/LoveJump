#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager {
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string name);
public:
    static sf::Texture& GetTexture(string name);
    static void Clear(); // Call this once at the end of main()
};