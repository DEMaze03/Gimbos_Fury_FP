/* CSCI 200: Final Project
 *
 * Author: Daylon Maze
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     Internet, CSCI 220 student
 *
 * implementation for the Enemy.h class
 */

#include "Enemy.h"

Enemy::Enemy(){

}

Enemy::~Enemy(){

}

void Enemy::init(std::string textureName, sf::Vector2f position, float speed){
    mSpeed = speed;
    mPosition = position;

    //load texture
    mTexture.loadFromFile(textureName.c_str());

    //create sprite and attach a texture
    mSprite.setTexture(mTexture);
    mSprite.setPosition(mPosition);
    mSprite.setOrigin(mTexture.getSize().x/2, mTexture.getSize().y/2);
}

void Enemy::update(float dt){
    mSprite.move(mSpeed*dt,0);
}

sf::Sprite Enemy::getSprite(){
    return mSprite;
}