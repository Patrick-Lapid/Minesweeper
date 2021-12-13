//
// Created by Patrick on 12/4/2021.
//

#include "Button.h"
// Button
Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick) {
    posButton = _position;
    buttonSprite.setPosition(posButton);
    onClickBtn = _onClick;
}
// returns Button Position as Vector2f
sf::Vector2f Button::getPosition() {
    return posButton;
}
// sets button Sprite
void Button::setSprite(sf::Sprite *_sprite) {
    buttonSprite = *_sprite;
}
sf::Sprite* Button::getSprite(){
    return &buttonSprite;
}

// Runs onClick function
void Button::onClick() {
    this->onClickBtn();
}
