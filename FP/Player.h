/* CSCI 200: Final Project
 *
 * Author: Daylon Maze
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     Internet, CSCI 220 student
 *
 * .h file for Player class
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player{
    public:
        Player();
        ~Player();

        void init(std::string textureName, int frameCount, float animDuration, sf::Vector2f position, float mass);
        void update(float dt);
        void jump(float velocity);
        sf::Sprite getSprite();

    private:
        sf::Texture mTexture;
        sf::Sprite mSprite;
        sf::Vector2f mPosition;

        int mJumpCount = 0;
        float mMass;
        float mVelocity;
        const float MGRAVITY = 9.8f;
        bool mGrounded;

        int mFrameCount;
        float mAnimDuration;
        float mElapsedTime;
        sf::Vector2i mSpriteSize;
};

#endif