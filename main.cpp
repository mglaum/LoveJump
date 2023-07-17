#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

struct point {
    int x, y;
};

int main() {
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(400, 533), "LOVE Jump!");
    window.setFramerateLimit(60);

    sf::Font MyFont;
    MyFont.loadFromFile("assets/PixelColeco-4vJW.ttf");


    sf::Sprite player(TextureManager::GetTexture("player"));
    sf::Sprite background(TextureManager::GetTexture("background"));
    sf::Sprite platform(TextureManager::GetTexture("platform"));
    sf::Sprite testPlatform(TextureManager::GetTexture("platform"));

    testPlatform.setPosition(0,530);

    player.setScale(0.25f, 0.25f);
    point plat[20]; // array size 20

    for (int i = 0; i < 10; i++) {
        plat[i].x = rand() % 400; // create random location for platform
        plat[i].y = rand() % 533;
    }




    sf::Text text;
    text.setFont(MyFont);
    text.setCharacterSize(30);

    text.setFillColor(sf::Color::Black);


    bool gameOver = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        int x = 100;
        int y = 100;
        int h = 200;
        float dx = 0;
        float dy = 0;
        int min = 200;
        int score = 0;

        text.setString("Score: " + std::to_string(score));

        while (!gameOver) {
            text.setPosition(10, 10);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                x += 3;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                x -= 3;
            }

            for (int i = 0; i < 10; i++) {
                if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68) && (y + 70 > plat[i].y) &&
                    (y + 70 < plat[i].y + 14) && (dy > 0)) {
                    dy = -10;
                    score++;
                    std::cout << "Score: " << score << std::endl;
                    text.setString("Score: " + std::to_string(score));
                }
            }

            dy += 0.2;
            y += dy;
            if (y > 500) {
                dy = -10;
            }

            if (y < h) {
                for (int i = 0; i < 10; i++) {
                    y = h;
                    plat[i].y = plat[i].y - dy;
                    if (plat[i].y > 533) {
                        plat[i].y = 0;
                        plat[i].x = rand() % 400;
                    }
                }
            }

            if (x < -40) {
                x = 440;
            }

            if (x > 440) {
                x = -40;
            }

            // ENDGAME
            player.setPosition(x, y);
            if (y == 508) {
                player.setPosition(x, 533);
                gameOver = true;
                continue;
            }

//
//        if (y > min) {
//            min = y;
//            std::cout << min << std::endl;
//        }

            window.clear();
            window.draw(background);
            window.draw(player);
            for (int i = 0; i < 10; i++) {
                platform.setPosition(plat[i].x, plat[i].y);
                window.draw(platform);
            }
//            window.draw(testPlatform);
            window.draw(text);
            window.display();
        }
        window.clear();
        window.draw(background);

        sf::Text gameOverText;
        gameOverText.setCharacterSize(45);
        gameOverText.setPosition(70, window.getSize().y / 3);
        gameOverText.setString("Game Over!");
        gameOverText.setFont(MyFont);
        gameOverText.setFillColor(sf::Color::Black);
        text.setPosition(90, window.getSize().y / 2);
        window.draw(gameOverText);
        window.draw(text);
        sf::Text playAgain;
        playAgain.setCharacterSize(20);
        playAgain.setPosition(50, 400);
        playAgain.setString("Press Enter to Play Again");
        playAgain.setFont(MyFont);
        playAgain.setFillColor(sf::Color::Black);
        window.draw(playAgain);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            gameOver = false;
            score = 0;
        }
        window.display();
    }
    return 0;
}
