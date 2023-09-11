/* CSCI 200: Final Project
 *
 * Author: Daylon Maze
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     Internet, CSCI 220 student
 *
 * main.cpp responsible for running the game and taking in input
 */

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

using namespace sf;
using namespace std;

//Player scores
ifstream fileIn("Scores.txt");

//Initialize window
Vector2f viewSize(1280, 720);
VideoMode vm(viewSize.x, viewSize.y);
RenderWindow window(vm, "Gimbo's Fury");

//function declarations
void spawnEnemy();
void reset();
void shoot();
bool checkCollision(Sprite sprite1, Sprite sprite2);

//Player
Player player;
sf::Vector2f playerPosition;
bool playerMoving = false;

//list of objects
vector<Enemy*> enemies;
vector<Bullet*> Bullets;

//Global vars
float currentTime;
float previousTime = 0.0f;
int score = 0;
int hScore = 0;
bool gameOver = true;

//Text
Font headingFont;
Text headingText;
Font scoreFont;
Text scoreText;
Text tutorialText;
Text hScoreText;

void init(){

    player.init("Assets/Graphics/s_guy_strip4.png", 4, 0.3f, sf::Vector2f(viewSize.x*0.25f,viewSize.y*0.5f), 200);

    srand((int)time(0));

    //load header font
    headingFont.loadFromFile("Assets/Fonts/SuperMario256.ttf");

    //Init header text
    headingText.setFont(headingFont);
    headingText.setString("Gimbo's Fury");
    scoreText.setCharacterSize(560);
    headingText.setFillColor(Color::Black);

    FloatRect headingBounds = headingText.getLocalBounds();
    headingText.setOrigin(headingBounds.width/2, headingBounds.height/2);
    headingText.setPosition(Vector2f(viewSize.x*0.5f, viewSize.y*0.10f));

    //Load score font
    scoreFont.loadFromFile("Assets/Fonts/pixelFont.ttf");

    //Init score text
    scoreText.setFont(scoreFont);
    scoreText.setString("Score: 0");
    scoreText.setCharacterSize(45);
    scoreText.setFillColor(Color::Black);

    FloatRect scoreBounds = scoreText.getLocalBounds();
    scoreText.setOrigin(scoreBounds.width/2, scoreBounds.height/2);
    scoreText.setPosition(Vector2f(viewSize.x*0.5f, viewSize.y*0.10f));

    //highscore text
    hScoreText.setFont(scoreFont);
    hScoreText.setString("Highscore: 0");
    hScoreText.setCharacterSize(25);
    hScoreText.setFillColor(Color::Black);

    FloatRect hScoreBounds = hScoreText.getLocalBounds();
    hScoreText.setOrigin(hScoreBounds.width/2, hScoreBounds.height/2);
    hScoreText.setPosition(Vector2f(viewSize.x*0.5f, viewSize.y*0.25f));

    //tutorial text
    tutorialText.setFont(scoreFont);
    tutorialText.setString("Press Down to start the game. Press Enter to Fire and Space to jump");
    tutorialText.setCharacterSize(25);
    tutorialText.setFillColor(Color::Black);
    FloatRect tutorialBounds = tutorialText.getLocalBounds();
    tutorialText.setOrigin(tutorialBounds.width/2, tutorialBounds.height/2);
    tutorialText.setPosition(Vector2f(viewSize.x * 0.5f, viewSize.y * 0.15f));


}

void draw(){
    window.draw(player.getSprite());

    if(gameOver){
        window.draw(headingText);
        window.draw(tutorialText);
    }else{
        window.draw(scoreText);
        window.draw(hScoreText);
    }

    for(Enemy* enemy : enemies){
        window.draw(enemy->getSprite());
    }

    for(Bullet* bullet : Bullets){
        window.draw(bullet->getSprite());
    }


}

void update_input(){
    Event event;

    while(window.pollEvent(event)){

        if(event.type == Event::KeyPressed){
            if(event.key.code == Keyboard::Space){
                player.jump(1000.0f);
            }
            if(event.key.code == Keyboard::Down){
                if(gameOver){
                    gameOver = false;
                    reset();
                
            }
            }
                if(event.key.code == Keyboard::Enter){
                    shoot();
                }
        }

        if(event.key.code == Keyboard::Escape || event.type == Event::Closed){
            window.close();
            fileIn.close();
        }
    }
}

void update(float dt){
    fileIn >> hScore;
    player.update(dt);
    currentTime += dt;
    //spawn enemies
    if(currentTime >= previousTime + 1.25f){
        spawnEnemy();
        previousTime = currentTime;
    }

    //update enemies
    for(unsigned int i = 0; i < enemies.size(); i++){
        Enemy* enemy = enemies[i];

        enemy->update(dt);
        
        if(enemy->getSprite().getPosition().x <0){
            enemies.erase(enemies.begin() + i);

            delete(enemy);
            gameOver = true;

    
            if(score > hScore){
                hScore = score;
                ofstream fileOut("Scores.txt", ofstream::trunc);
                fileOut << score;
                fileOut.close();
                score = 0;
            }


        }
    }

    //update bullets
    for(unsigned int i = 0; i < Bullets.size(); i++){
        Bullet* bullet = Bullets[i];
        bullet->update(dt);
        if(bullet->getSprite().getPosition().x > viewSize.x){
            Bullets.erase(Bullets.begin() + i);
            delete(bullet);
        }
    }

    //check collision between bullets and enemies
    for(unsigned int i = 0; i < Bullets.size(); i++){
        for(unsigned int j = 0; j < enemies.size(); j++){
            Bullet* bullet = Bullets[i];
            Enemy* enemy = enemies[j];

            if(checkCollision(bullet->getSprite(), enemy->getSprite())){
                //play hitsound
                score++;

                Bullets.erase(Bullets.begin()+i);
                enemies.erase(enemies.begin()+j);

                delete bullet;
                delete enemy;

                printf(" bullet intersects enemy \n");

            }

            
        }
    }

    //check collision between enemies and player
    for(unsigned int i = 0; i < enemies.size(); i++){
            Enemy* enemy = enemies[i];

            if(checkCollision(enemy->getSprite(), player.getSprite())){
                //play hitsound

                enemies.erase(enemies.begin()+i);

                delete enemy;

                gameOver = true;

                printf(" enemy intersects player \n");

            }

            
    }

    //update score text
    string finalScore = "Score: " + to_string(score);
    scoreText.setString(finalScore);
    FloatRect scoreBounds = scoreText.getLocalBounds();
    scoreText.setOrigin(scoreBounds.width/2,scoreBounds.height/2);
    scoreText.setPosition(Vector2f(viewSize.x * 0.5f, viewSize.y * 0.10f));
    
    //update highscore text
    string finalHScore = "Highscore: " + to_string(hScore);
    hScoreText.setString(finalHScore);
    FloatRect hScoreBounds = hScoreText.getLocalBounds();
    hScoreText.setOrigin(hScoreBounds.width/2,hScoreBounds.height/2);
    hScoreText.setPosition(Vector2f(viewSize.x * 0.5f, viewSize.y * 0.15f));
}






int main(){

    Clock clock;
    window.setFramerateLimit(60);
    init();
    while(window.isOpen()){
        update_input();

        Time dt = clock.restart();
        if(!gameOver){
            update(dt.asSeconds());
        }
        //Draw
        window.clear(Color::Blue);
        draw();

        //show
        window.display();
    }

    return 0;
}

void spawnEnemy(){
    int randLoc = rand() % 3;

    Vector2f enemyPos;

    float speed;

    switch(randLoc){
        case 0: enemyPos = Vector2f(viewSize.x, viewSize.y*0.75f);
            speed = -400; break;
        case 1: enemyPos = Vector2f(viewSize.x, viewSize.y*0.60f);
            speed = -550; break;
        case 2: enemyPos = Vector2f(viewSize.x, viewSize.y*0.40f);
            speed = -650; break;
        default: printf("Incorrect y value :) \n"); return;
    }

    Enemy* enemy = new Enemy();
    enemy->init("Assets/Graphics/s_enemy.png", enemyPos, speed);

    enemies.push_back(enemy);
}

void shoot(){
    Bullet* bullet = new Bullet();

    bullet->init("Assets/graphics/s_bullet.png", player.getSprite().getPosition(), 600.0f);

    Bullets.push_back(bullet);
}

bool checkCollision(Sprite sprite1, Sprite sprite2){
    FloatRect shape1 = sprite1.getGlobalBounds();
    FloatRect shape2 = sprite2.getGlobalBounds();
    if(shape1.intersects(shape2)){
        return true;
    }else{
        return false;
    }
}

void reset(){
    score = 0;
    currentTime = 0.0f;
    previousTime = 0.0;
}