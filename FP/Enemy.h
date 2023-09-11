/* CSCI 200: Final Project
 *
 * Author: Daylon Maze
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     Internet, CSCI 220 student
 *
 * .h file for Enemy class
 */

#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy{
public:
    Enemy();
    ~Enemy();
    void init(std::string textureName, sf::Vector2f position, float speed);
    void update(float dt);
    sf::Sprite getSprite();

private:
    sf::Texture mTexture;
    sf::Sprite mSprite;
    sf::Vector2f mPosition;
    float mSpeed;

};

#endif