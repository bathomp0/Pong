#include <SFML/Graphics.hpp>
#include <iostream>

// class Text : public sf::Text {
//     Text()
// }
int main()
{
    unsigned int xSize = 20;
    unsigned int ySize = 150;
    unsigned int xSizeBall = 20;
    unsigned int ySizeBall = 20;

    unsigned int xWindow = 720;
    unsigned int yWindow = 1280;

    sf::RenderWindow window(sf::VideoMode({xWindow, yWindow}), "SFML works!");
    window.setFramerateLimit(60);

    sf::CircleShape shape(100.f);
    sf::RectangleShape rect;
    sf::RectangleShape opp;
    sf::RectangleShape ball;
    
    sf::Vector2f rectPos(45, window.getSize().y/2);
    sf::Vector2f oppPos(window.getSize().x - 45, window.getSize().y/2);
    sf::Vector2f ballPos(window.getSize().x/2 , window.getSize().y/2 + (ySize/2)); // Added the half so it's in the vertical  middle of the rect
    sf::Vector2f textPos(window.getSize().x/2 , 40);
    sf::Vector2f startPos(window.getSize().x/2 -100 , window.getSize().y/2);
    sf::Vector2f quitPos(window.getSize().x/2 +100 , window.getSize().y/2);

    rect.setPosition(rectPos);
    opp.setPosition(oppPos);
    ball.setPosition(ballPos);

    rect.setFillColor(sf::Color::White);
    opp.setFillColor(sf::Color::White);
    ball.setFillColor(sf::Color::White);
    
    rect.setSize(sf::Vector2f(xSize, ySize));
    opp.setSize(sf::Vector2f(xSize, ySize));
    ball.setSize(sf::Vector2f(xSizeBall, ySizeBall));


    float xVel = 3.5;
    float yVel = 3.5;
    sf::Font font;
    font.openFromFile("Pong\\Font\\Roboto-Black.ttf");
    // sf::String textString = "Test"; // Create an sf::String

    sf::Text my_text(font, sf::String("Test")); // Correct: Creating a temporary sf::String
    sf::Text homeStart(font, sf::String("Start"), 50); // Home page's Start button
    sf::Text homeQuit(font, sf::String("Quit"), 50); // Home page's Quit button

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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && rectPos.y > 0)
                rectPos.y -= 1;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && oppPos.y > 0)
                oppPos.y -= 1;            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && rectPos.y <  window.getSize().y - ySize){
                rectPos.y += 1;
                // std::cout << rect.getPosition().y;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && oppPos.y <  window.getSize().y - ySize){
                        oppPos.y += 1;
                        // std::cout << opp.getPosition().y;
                    }        
            if (ballPos.x <= 0 || ballPos.x >= window.getSize().x - xSizeBall) xVel *= -1;
            if (ballPos.y <= 0 || ballPos.y >= window.getSize().y - ySizeBall ) yVel *= -1;
            if (ballPos.x == rect.getPosition().x + xSize && ballPos.y > rect.getPosition().y && ballPos.y < rect.getPosition().y + ySize )
                xVel *= -1; 
            if (ballPos.x + xSizeBall == opp.getPosition().x && ballPos.y > opp.getPosition().y && ballPos.y < opp.getPosition().y +ySize)
                xVel *= -1;                  
            ballPos.x += xVel;
            ballPos.y += yVel;
            ball.setPosition(ballPos);
            rect.setPosition(rectPos);
            opp.setPosition(oppPos);
          
            my_text.setPosition(textPos);

            window.clear();
            window.draw(rect);
            window.draw(opp);
            window.draw(ball);
            window.draw(my_text);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && sf::Mouse::getPosition(window).x >= startPos.x && sf::Mouse::getPosition(window).x < startPos.x + homeStart.getLocalBounds().position.length() && sf::Mouse::getPosition(window).y >= startPos.y && sf::Mouse::getPosition(window).y < startPos.y + 50 ){
            
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

        std::cout << "Mouse X Coordinates" << sf::Mouse::getPosition(window).x << std::endl << "Mouse Y Coordinates" << sf::Mouse::getPosition(window).y << std::endl;
        std::cout << "Home Start Global" << homeStart.getGlobalBounds().contains(window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y})) << std::endl << "Home Start Local" << homeStart.getLocalBounds().position.length() << std::endl;
        window.display();
    }
}