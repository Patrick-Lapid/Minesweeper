#pragma once
#include <functional>
#include<SFML/Graphics.hpp>

class Button {
private:
    sf::Vector2f posButton; // vector of button position
    sf::Sprite buttonSprite;
    std::function<void(void)> onClickBtn; // functionality of button
public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);
    sf::Vector2f getPosition();
    sf::Sprite* getSprite(); // getter for button sprite
    void setSprite(sf::Sprite* _sprite); // setter for button sprite
    void onClick(); // activates button functionality
};

