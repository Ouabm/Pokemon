
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include  <giflib.h> // You'll need a GIF loading library

class GifAnimation {
public:
    GifAnimation() = default;
    
    bool loadFromFile(const std::string& filename) {
        // Load GIF file
        GIF* gif = gifLoad(filename.c_str());
        if (!gif) {
            return false;
        }

        // Store frame durations and convert GIF frames to SFML textures
        for (int i = 0; i < gif->imageCount; ++i) {
            // Create texture from frame
            sf::Texture texture;
            texture.create(gif->width, gif->height);
            texture.update(gif->frames[i].pixels);
            
            frames.push_back(texture);
            frameTimes.push_back(gif->frames[i].delay / 100.0f); // Convert to seconds
        }

        gifFree(gif);
        
        if (frames.empty()) {
            return false;
        }

        // Setup sprite with first frame
        sprite.setTexture(frames[0]);
        return true;
    }

    void update(float deltaTime) {
        if (frames.size() <= 1) return;

        currentTime += deltaTime;
        if (currentTime >= frameTimes[currentFrame]) {
            currentTime = 0;
            currentFrame = (currentFrame + 1) % frames.size();
            sprite.setTexture(frames[currentFrame]);
        }
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    void setScale(float scaleX, float scaleY) {
        sprite.setScale(scaleX, scaleY);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    std::vector<sf::Texture> frames;
    std::vector<float> frameTimes;
    sf::Sprite sprite;
    size_t currentFrame = 0;
    float currentTime = 0;
};
class PokemonSprite {
public:
    PokemonSprite() {
        // Initialize default values
        scale = 2.0f; // Adjust based on your sprite size
    }

    bool loadFromFile(const std::string& pokemonName, bool isBackSprite) {
        std::string path = "Palkia_Back_BW-ezgif.com-webp-to-gif-converter.gif"
        
        if (!texture.loadFromFile(path)) {
            return false;
        }

        sprite.setTexture(texture);
        sprite.setScale(scale, scale);
        
        // Set origin to center of sprite for easier positioning
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2, bounds.height / 2);

        return true;
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    // Optional: Add animation support
    void animate(float deltaTime) {
        if (isAnimating) {
            animationTime += deltaTime;
            if (animationTime >= frameDuration) {
                currentFrame = (currentFrame + 1) % frameCount;
                animationTime = 0;
                
                // Update texture rectangle for animation
                int frameWidth = texture.getSize().x / frameCount;
                sprite.setTextureRect(sf::IntRect(
                    currentFrame * frameWidth, 0,
                    frameWidth, texture.getSize().y
                ));
            }
        }
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
    float scale;
    
    // Animation properties
    bool isAnimating = false;
    int currentFrame = 0;
    int frameCount = 1;
    float animationTime = 0;
    float frameDuration = 0.1f; // seconds per frame
};