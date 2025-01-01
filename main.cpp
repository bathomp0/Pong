#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    unsigned int xSize = 20;
    unsigned int ySize = 150;
    unsigned int xSizeBall = 20;
    unsigned int ySizeBall = 20;

    unsigned int xWindow = 720;
    unsigned int yWindow = 1280;

    sf::RenderWindow window(sf::VideoMode({xWindow, yWindow}), "Pong");
    window.setFramerateLimit(60);

    sf::RectangleShape pong1;
    sf::RectangleShape opp;
    sf::RectangleShape ball;
    
    sf::Vector2f pong1Pos(45, window.getSize().y/2);
    sf::Vector2f oppPos(window.getSize().x - 45, window.getSize().y/2);
    sf::Vector2f ballPos(window.getSize().x/2 , window.getSize().y/2 + (ySize/2)); // Added the half so it's in the vertical  middle of the pong1
    sf::Vector2f textPos(window.getSize().x/2 , 40);
    sf::Vector2f startPos(window.getSize().x/2 -100 , window.getSize().y/2);
    sf::Vector2f quitPos(window.getSize().x/2 +100 , window.getSize().y/2);

    pong1.setPosition(pong1Pos);
    opp.setPosition(oppPos);
    ball.setPosition(ballPos);

    pong1.setFillColor(sf::Color::White);
    opp.setFillColor(sf::Color::White);
    ball.setFillColor(sf::Color::White);
    
    pong1.setSize(sf::Vector2f(xSize, ySize));
    opp.setSize(sf::Vector2f(xSize, ySize));
    ball.setSize(sf::Vector2f(xSizeBall, ySizeBall));

    sf::FloatRect ballBounds = ball.getGlobalBounds();
    sf::FloatRect pong1Bounds = pong1.getGlobalBounds();

    float xVel = 3.5;
    float yVel = 3.5;
    sf::Font font;
    font.openFromFile("Pong\\Font\\Roboto-Black.ttf");

    sf::Text my_text(font, sf::String("Test")); 
    sf::Text homeStart(font, sf::String("Start"), 50); // Home page's Start & Quit
    sf::Text homeQuit(font, sf::String("Quit"), 50);    

    // my_text.setFont(font);
    my_text.setFillColor(sf::Color::White);
    bool start = false;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();
        }
        if (start){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && pong1Pos.y > 0)
                pong1Pos.y -= 5;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && oppPos.y > 0)
                oppPos.y -= 5;            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && pong1Pos.y <  window.getSize().y - ySize){
                pong1Pos.y += 5;
                std::cout << pong1.getPosition().y;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && oppPos.y <  window.getSize().y - ySize){
                oppPos.y += 5;
                std::cout << opp.getPosition().y;
            }        
            if (ballPos.x <= 0 || ballPos.x >= window.getSize().x - xSizeBall) xVel *= -1;
            if (ballPos.y <= 0 || ballPos.y >= window.getSize().y - ySizeBall ) yVel *= -1;
            std::cout << "ball position " << ball.getPosition().x << std::endl;
            std::cout << pong1.getPosition().x + xSize << std::endl;

            if (ball.getPosition().x > pong1.getPosition().x + xSize - 2
            && ball.getPosition().x < pong1.getPosition().x + xSize + 2
            && ball.getPosition().y > pong1.getPosition().y 
            && ball.getPosition().y < pong1.getPosition().y + ySize ){
                xVel *= -1; }
                // std::cout << "Y Ball Position " << ball.getPosition().y << std::endl << "Paddle Position Start: " << rect.getPosition().y << "Paddle Position End: " << rect.getPosition().y + ySize << std::endl; 
            if (ball.getPosition().x == pong1.getPosition().x + xSize ){
                std::cout << "X position ball True";
            }
            if (ballPos.x + xSizeBall == opp.getPosition().x && ballPos.y > opp.getPosition().y && ballPos.y < opp.getPosition().y +ySize)
                xVel *= -1;                  
            ballPos.x += xVel;
            ballPos.y += yVel;
            ball.setPosition(ballPos);
            pong1.setPosition(pong1Pos);
            opp.setPosition(oppPos);
          
            my_text.setPosition(textPos);

            window.clear();
            window.draw(pong1);
            window.draw(opp);
            window.draw(ball);
            window.draw(my_text);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && homeStart.getGlobalBounds().contains(window.mapPixelToCoords({sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y}))) {
            
            start = true;
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && homeQuit.getGlobalBounds().contains(window.mapPixelToCoords({sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y}))) {
            window.close();
        }
        else if (!start){
        homeStart.setPosition(startPos);
        homeQuit.setPosition(quitPos);
        window.draw(homeStart);
        window.draw(homeQuit);
        }

        window.display();
    }
}