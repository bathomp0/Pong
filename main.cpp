#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{

    unsigned int xWindow = 720;
    unsigned int yWindow = 1280;    
    unsigned int xSize = 20;
    unsigned int ySize = 150;
    unsigned int xSizeBall = 20;
    unsigned int ySizeBall = 20;
    unsigned int p1Points = 0;
    unsigned int p2Points = 0;

    enum GameState { Title, Playing, PointScored, GameOver };
    GameState gameState = Title;

    sf::RenderWindow window(sf::VideoMode({xWindow, yWindow}), "Pong");
    window.setFramerateLimit(60);

    sf::RectangleShape pong1;
    sf::RectangleShape opp;
    sf::RectangleShape ball;
    
    sf::Vector2f pong1Pos(45, window.getSize().y/2);
    sf::Vector2f oppPos(window.getSize().x - 45, window.getSize().y/2);
    sf::Vector2f pong1PosReset(45, window.getSize().y/2);
    sf::Vector2f oppPosReset(window.getSize().x - 45, window.getSize().y/2);    
    sf::Vector2f ballPos(window.getSize().x/2 , window.getSize().y/2 + (ySize/2)); // Added the half so it's in the vertical  middle of the pong1
    sf::Vector2f ballPosReset(window.getSize().x/2 , window.getSize().y/2 + (ySize/2)); // Added the half so it's in the vertical  middle of the pong1    
    sf::Vector2f textPos(window.getSize().x/2 , 40);
    sf::Vector2f textPauseContinuePos(window.getSize().x/2 , 90);
    sf::Vector2f startPos(window.getSize().x/2 -100 , window.getSize().y/2);
    sf::Vector2f quitPos(window.getSize().x/2 +100 , window.getSize().y/2);
    sf::Vector2f p1ScorePos(50 , 40);  // 50 pixels from left end
    sf::Vector2f p2ScorePos(window.getSize().x - 50, 40); // 50 pixels from right end

    pong1.setPosition(pong1Pos);
    opp.setPosition(oppPos);
    ball.setPosition(ballPos);

    pong1.setFillColor(sf::Color::White);
    opp.setFillColor(sf::Color::White);
    ball.setFillColor(sf::Color::White);
    
    pong1.setSize(sf::Vector2f(xSize, ySize));
    opp.setSize(sf::Vector2f(xSize, ySize));
    ball.setSize(sf::Vector2f(xSizeBall, ySizeBall));

    float xVel = 3.5;
    float yVel = 3.5;
    sf::Font font;
    font.openFromFile("Pong\\Font\\Roboto-Black.ttf");

    sf::Text my_text(font, sf::String("Test")); 
    sf::Text homeStart(font, sf::String("Start"), 50); // Home page's Start & Quit
    sf::Text homeQuit(font, sf::String("Quit"), 50);  
    sf::Text pauseContinue(font, sf::String("Press Spacebar to continue"), 50);  // Text Object: Asks user to press Spacebar to continue
    sf::Text p1Score(font, sf::String(std::to_string(p1Points)), 50);
    sf::Text p2Score(font, sf::String(std::to_string(p2Points)), 50); 

    // my_text.setFont(font);
    my_text.setFillColor(sf::Color::White);
    bool start = false;
    bool active = true;

    pong1.setPosition(pong1Pos);
    opp.setPosition(oppPos);  

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();
        }
        
            switch (gameState) {
                case Title:
                    // std::cout << gameState;
                    homeStart.setPosition(startPos);
                    homeQuit.setPosition(quitPos);
                    window.draw(homeStart);
                    window.draw(homeQuit);
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && homeStart.getGlobalBounds().contains(window.mapPixelToCoords({sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y}))) {
                        gameState = Playing;
                    }
                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && homeQuit.getGlobalBounds().contains(window.mapPixelToCoords({sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y}))) {
                        window.close();

                    }
                    break;

                case Playing:

                    my_text.setPosition(textPos);
        

                    ballPos.x += xVel;
                    ballPos.y += yVel;
                    ball.setPosition(ballPos);  

                    if (ball.getGlobalBounds().findIntersection(pong1.getGlobalBounds())) { // Collision for P1
                        xVel *= -1; 
                    }
                    else if (ball.getGlobalBounds().findIntersection(opp.getGlobalBounds())) { // Collision for P2
                        xVel *= -1; 
                    }                  

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && pong1Pos.y > 0)
                        pong1Pos.y -= 5;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && oppPos.y > 0)
                        oppPos.y -= 5;            
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && pong1Pos.y <  window.getSize().y - ySize){
                        pong1Pos.y += 5;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && oppPos.y <  window.getSize().y - ySize){
                        oppPos.y += 5;
                    }
                    if (ballPos.x <= 0) {
                        p2Points++;
                        p2Score.setString(std::to_string(p2Points));
                        gameState = PointScored;

                    }
                    else if (ballPos.x >= window.getSize().x - xSizeBall){
                        p1Points++;
                        p1Score.setString(std::to_string(p1Points));
                        gameState = PointScored;
                    }
                    else if (ballPos.y >= window.getSize().y - ySizeBall){  // Collision detection for top & bottom of window
                        yVel *= -1;
                    }
                    else if (ballPos.y <= 0){
                        yVel *= -1;
                    }                          
                    my_text.setPosition(textPos);  // TODO: Dupllicate, need to clean up
                    p1Score.setPosition(p1ScorePos);
                    p2Score.setPosition(p2ScorePos);
                    pong1.setPosition(pong1Pos);
                    opp.setPosition(oppPos);                    

                    window.clear();
                    window.draw(pong1);
                    window.draw(opp);
                    window.draw(ball);
                    window.draw(my_text);
                    window.draw(p1Score);
                    window.draw(p2Score);
                    
                    break;
                
                case PointScored:

                    // std::cout << gameState;
                    ballPos = ballPosReset;  // Could also set this at the end of Playing case
                    pong1Pos = pong1PosReset;
                    oppPos = oppPosReset;
                    ball.setPosition(ballPos);
                    pong1.setPosition(pong1Pos);
                    opp.setPosition(oppPos);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
                        gameState = Playing;
                    }
                    window.clear();
                    window.draw(pong1);
                    window.draw(opp);
                    window.draw(ball);
                    window.draw(my_text);
                    window.draw(p1Score);
                    window.draw(p2Score);
                    window.draw(pauseContinue);
                    break;
            
            
            pong1.setPosition(pong1Pos);
            opp.setPosition(oppPos);

            my_text.setPosition(textPos);
            p1Score.setPosition(p1ScorePos);
            p2Score.setPosition(p2ScorePos);


            window.clear();
            window.draw(pong1);
            window.draw(opp);
            window.draw(ball);
            window.draw(my_text);
            window.draw(p1Score);
            window.draw(p2Score);
        } 
        // if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && homeStart.getGlobalBounds().contains(window.mapPixelToCoords({sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y}))) {
            
        //     start = true;
        // }
        // else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && homeQuit.getGlobalBounds().contains(window.mapPixelToCoords({sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y}))) {
        //     window.close();
        // }
        // else if (!start){
        
        // window.draw(homeStart);
        // window.draw(homeQuit);
        // }

        window.display();
    }
}