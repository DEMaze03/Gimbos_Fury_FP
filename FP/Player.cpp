/* CSCI 200: Final Project
 *
 * Author: Daylon Maze
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     Internet, CSCI 220 student
 *
 * implementation for the Player.h class
 */

#include "Player.h"

Player::Player(){

}

Player::~Player(){

}

void Player::init(std::string textureName, int frameCount, float animDuration, sf::Vector2f position, float mass){
    mPosition = position;
    mMass = mass;
    mGrounded = false;
    mFrameCount = frameCount;
    mAnimDuration = animDuration;

    //load texture
    mTexture.loadFromFile(textureName.c_str());
    mSpriteSize = sf::Vector2i(85,137);

    //create spr and attach texture
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(0,0,mSpriteSize.x, mSpriteSize.y));
    mSprite.setPosition(mPosition);
    mSprite.setOrigin(mSpriteSize.x/2,mSpriteSize.y/2);
}

void Player::update(float dt){
    //animate sprite
    mElapsedTime += dt;
    int animFrame = static_cast<int> ((mElapsedTime/mAnimDuration) * mFrameCount) % mFrameCount;
    mSprite.setTextureRect(sf::IntRect(animFrame * mSpriteSize.x, 0, mSpriteSize.x, mSpriteSize.y));

    //update position
    mVelocity -= mMass * MGRAVITY * dt;
    mPosition.y -= mVelocity*dt; 
    mSprite.setPosition(mPosition);

    if(mPosition.y >= 720 * 0.75f){
        mPosition.y = 720*0.75f;
        mVelocity = 0;
        mGrounded = true;
        mJumpCount = 0;
    }
}

void Player::jump(float velocity){
    if(mJumpCount < 2){
        mJumpCount++;
        mVelocity = velocity;
        mGrounded = false;
    }
}

sf::Sprite Player::getSprite(){
    return mSprite;
}