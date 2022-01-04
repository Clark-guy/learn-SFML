#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>


#define PIXEL 50

int printVec(std::vector<std::vector<float>> vec){
    for(int i=0; i<vec.size(); i++){
        for(int j=0; j<vec[0].size(); j++){
            std::cout << vec[i][j];
        }
        std::cout << std::endl;
    }
    return 0;
}

std::vector<std::vector<float>> buildBox(){
    //make 2d vector, put it in for loop
    std::vector<float> oneVec; 
    std::vector<float> tempVec;
    std::vector<std::vector<float>> finalVec;
    
    
    
    for(int i=0; i<10; i++){
        oneVec.push_back(1);
        if(i==0 || i==9)
            tempVec.push_back(1);
        else
            tempVec.push_back(0);
    }
    
    finalVec.push_back(oneVec);
    for(int i=0; i<10; i++){
        finalVec.push_back(tempVec);
    }
    finalVec.push_back(oneVec);
    
    //wait this 3d vector essentially makes a 2d box- i need a vector of these (4d)
    return finalVec;
}




int drawBox(sf::RenderWindow& window, std::vector<std::vector<float>> roomVec){
    //walk through vector - if 1: draw shape at that position. if not, do nothing
    std::vector<sf::RectangleShape> shapeVec;
    sf::RectangleShape shape(sf::Vector2f(PIXEL,PIXEL));
    sf::Color color(0,0,0);
    for(int i=0; i<roomVec.size(); i++){
        for(int j=0; j<roomVec[0].size(); j++){    
            if(roomVec[i][j] == 1){
                color.b = i*10+40;
                shape.setFillColor(color);
                shape.setPosition(i*PIXEL, j*PIXEL);
                shapeVec.push_back(shape);
                //set position, push back
            }
        }
    }
    for(int i=0; i<shapeVec.size(); i++){
        window.draw(shapeVec[i]);
    }
    return 0;
}

int main() {
    sf::Texture ghostText;
    if(!ghostText.loadFromFile("ghost.png"))
        return 1;
    sf::Sprite ghostSprite;
    ghostSprite.setTexture(ghostText);
    ghostSprite.setPosition(PIXEL*4,PIXEL*4);
    ghostSprite.setScale(PIXEL/50., PIXEL/50.);
    
    sf::RenderWindow window(sf::VideoMode(200, 200), "test");
    sf::RectangleShape shape(sf::Vector2f(100,100));
    //sf::CircleShape shape(40.f);
    shape.setFillColor(sf::Color::Green);
    
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
    bool in = false;
    bool out = false;
    
    float speed = .3;    

    std::vector<std::vector<float>> boxVec = buildBox();
    printVec(boxVec);
    
    while (window.isOpen()){
        
        //movement
        if(left)
            ghostSprite.move((PIXEL/50.)*speed*-1, 0);
        else if(right)
            ghostSprite.move((PIXEL/50.)*speed*1, 0);
        if(up)
            ghostSprite.move(0, (PIXEL/50.)*speed*-1);
        else if(down)
            ghostSprite.move(0, (PIXEL/50.)*speed*1);
        
        sf:: Event event;
        //sf::Input::Input();
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::W)
                    up = true;
                else if (event.key.code == sf::Keyboard::S)
                    down = true;
                else if (event.key.code == sf::Keyboard::A)
                    left = true;
                else if (event.key.code == sf::Keyboard::D)
                    right = true;
            }
            else if (event.type == sf::Event::KeyReleased){
                if (event.key.code == sf::Keyboard::W)
                    up = false;
                else if (event.key.code == sf::Keyboard::S)
                    down = false;
                else if (event.key.code == sf::Keyboard::A)
                    left = false;
                else if (event.key.code == sf::Keyboard::D)
                    right = false;
            }
        }
        window.clear();
        window.draw(shape);
        window.draw(ghostSprite);
        drawBox(window, boxVec);
        window.display();
    }
    return 0;
}


//notes
/*
want to create illusion of 3d in a 2d game- sidescroller, but you can 'jump' forward or backwards a level
how to encode levels?
start basic- maybe just a box with walls that block you from exiting.
then maybe a box that you can go forward and back in too.
then 2 3D boxes connected to each other so i can go forward and backwards but only if there's room- etc


this format of 3d space could lend itself to fighting enemies, in which normal 2d scroller fighting would occur but
with an added dimension specifically for sidestepping attacks. 

Questions
how far is a single jump? 5 feet? 2?

*/
