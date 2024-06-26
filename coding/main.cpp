#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

sf::RenderWindow window(sf::VideoMode(800, 600), "CyberFighter");
sf::Music menuMusic;
sf::Music gameplayMusic;
sf::Clock textClock;
sf::Texture menuTexture2, menuTexture3;
sf::Clock menuClock;
sf::Text pressEnterText;
sf::Font font;
sf::Texture backgroundTexture;
sf::Texture characterTexture;
sf::Texture characterTexture2;
sf::Texture lifebarTexture;
sf::Text Lifetext;
sf::Font lifefont;
sf::Texture lifebarTexture2;
sf::Text Lifetext2;
sf::Font lifefont2;
sf::Event event;
sf::Time animationTime;
sf::Clock attackClock;
sf::Clock attackCooldown;
sf::Time animationTime2;
sf::Clock attackCooldown2;
sf::Clock attackClock2;

int frame = 0;
int frame2 = 0;
int countdown = 3;
int animationFrame = 0;
bool textVisible = true;
bool Movement = false;
int lifeValue = 100;
int lifeValue2 = 100;

float characterPosX = window.getSize().x / 5;
float character2PosX = window.getSize().x / 1.2;
float characterPosY = window.getSize().y / 1.34;
float character2PosY = window.getSize().y / 1.27;



enum GameState
{
    MainMenu,
    PreGameplay,
    Gameplay
};



int main()
{
    //------------------------------------------------------------------------------------

    // Window
    window.setVerticalSyncEnabled(true);

    //------------------------------------------------------------------------------------

    // Game state
    GameState gameState = MainMenu;

    // Menu music
    if (!menuMusic.openFromFile("sounds/menumusic.wav"))
    {
        // handle error
    }
    menuMusic.setLoop(true);

    // Gameplay music
    if (!gameplayMusic.openFromFile("sounds/battlemusic.wav"))
    {
        // handle error
    }
    gameplayMusic.setLoop(true);

    //------------------------------------------------------------------------------------

    // Menu
    if (!menuTexture2.loadFromFile("img/background/backgroundmenu2.png")) return 1;
    if (!menuTexture3.loadFromFile("img/background/backgroundmenu3.png")) return 1;
    sf::Sprite spritemenu(menuTexture2);
    spritemenu.scale(0.5, 0.6);

    //------------------------------------------------------------------------------------

    // Menu text

    if (!font.loadFromFile("fonts/pixelletters-font/Pixellettersfull-BnJ5.ttf")) return 1;
    pressEnterText.setFont(font);
    pressEnterText.setString("Press 'Enter' to start");
    pressEnterText.setCharacterSize(24);
    pressEnterText.setFillColor(sf::Color::White);
    pressEnterText.setPosition(window.getSize().x / 2 - 80, window.getSize().y / 1.5);


        // Countdown text
    sf::Clock countdownClock;
    sf::Text countdownText;
    countdownText.setFont(font);
    countdownText.setCharacterSize(70);
    countdownText.setFillColor(sf::Color::White);
    countdownText.setPosition(window.getSize().x / 2 - 20, window.getSize().y / 2);

    //------------------------------------------------------------------------------------

    // Background
    if (!backgroundTexture.loadFromFile("img/background/cybercity.png")) return 1;
    sf::Sprite spritebackground(backgroundTexture);
    spritebackground.scale(1.17, 2.2);


    //------------------------------------------------------------------------------------

    // Character
    if (!characterTexture.loadFromFile("img/characters/idle/bobidle.png")) return 1;
    sf::Sprite characterSprite(characterTexture);
    characterSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
    sf::Clock clock;

    //------------------------------------------------------------------------------------

    // Character 2
    if (!characterTexture2.loadFromFile("img/characters/idle/HDD69idle.png")) return 1;
    sf::Sprite characterSprite2(characterTexture2);
    characterSprite2.setTextureRect(sf::IntRect(0, 0, 48, 48));
    sf::Clock clock2;

    //------------------------------------------------------------------------------------

    // Lifebar

    if (!lifebarTexture.loadFromFile("img/life/lifebar1.png")) return 1;
    sf::Sprite lifebarSprite(lifebarTexture);
    lifebarSprite.setPosition(10, 10); // top-left corner
    lifebarSprite.setScale(0.06f, 0.06f); // original size

    if (!lifefont.loadFromFile("fonts/pixelletters-font/Pixellettersfull-BnJ5.ttf")) return 1;
    Lifetext.setFont(lifefont);
    Lifetext.Bold;
    Lifetext.setString("100");
    Lifetext.setCharacterSize(34);
    Lifetext.setFillColor(sf::Color::White);
    Lifetext.setPosition(30, 20);

    //------------------------------------------------------------------------------------

    // Lifebar 2

    if (!lifebarTexture2.loadFromFile("img/life/lifebar1.png")) return 1;
    sf::Sprite lifebarSprite2(lifebarTexture2);
    float lifebarWidth = lifebarTexture2.getSize().x * 0.06f;
    lifebarSprite2.setPosition(window.getSize().x - lifebarWidth, 10);
    lifebarSprite2.setScale(0.06f, 0.06f);

    if (!lifefont2.loadFromFile("fonts/pixelletters-font/Pixellettersfull-BnJ5.ttf")) return 1;
    Lifetext2.setFont(lifefont2);
    Lifetext2.Bold;
    Lifetext2.setString("100");
    Lifetext2.setCharacterSize(34);
    Lifetext2.setFillColor(sf::Color::White);
    float lifebarCenter = window.getSize().x - lifebarWidth / 2;
    float Lifetext2Center = Lifetext2.getGlobalBounds().width / 1.8;
    Lifetext2.setPosition(lifebarCenter - Lifetext2Center, 20);
    

    //------------------------------------------------------------------------------------

    // Character position/size
    characterSprite.setOrigin(48 / 2, 48 / 2);
    characterSprite.setPosition(characterPosX, characterPosY);
    characterSprite.scale(5, 5);

    //------------------------------------------------------------------------------------

    // Character 2 position/size

    characterSprite2.setOrigin(48 / 2, 48 / 2);
    characterSprite2.setPosition(window.getSize().x / 1.2, window.getSize().y / 1.27);
    characterSprite2.scale(4, 4);

    //------------------------------------------------------------------------------------

    while (window.isOpen())
    {        
        //------------------------------------------------------------------------------------
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            // Exit first menu

            if (gameState == MainMenu && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                gameState = PreGameplay; // start the game when enter pressed
            }

        
            //------------------------------------------------------------------------------------

            if (gameState == Gameplay)
            {
                // Bob movement
                if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left))
                {
                    Movement = true;
                }
                if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left))
                {
                    Movement = false;
                    characterTexture.loadFromFile("img/characters/idle/bobidle.png");
                }

                // HDD69 movement

                if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::D))
                {
                    Movement = true;
                }
                if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::D))
                {
                    Movement = false;
                    characterTexture2.loadFromFile("img/characters/idle/HDD69idle.png");
                }
            }
        }

        //------------------------------------------------------------------------------------

        window.clear();
 
        //------------------------------------------------------------------------------------

        if (gameState == MainMenu)
        {
            //------------------------------------------------------------------------------------

            // Menu music
            if (menuMusic.getStatus() != sf::Music::Playing)
            {
                menuMusic.play();
            }

            // Gameplay music
            if (gameplayMusic.getStatus() == sf::Music::Playing)
            {
                gameplayMusic.stop();
            }

            //------------------------------------------------------------------------------------

            // Menu
            if (menuClock.getElapsedTime().asSeconds() > 3.0f)
            {
                animationFrame = (animationFrame + 1) % 2;
                switch (animationFrame)
                {
                case 0:
                    spritemenu.setTexture(menuTexture2);
                    break;
                case 1:
                    spritemenu.setTexture(menuTexture3);
                    break;
                }
                menuClock.restart();
            }

            //------------------------------------------------------------------------------------

            // Menu enterText
            window.draw(spritemenu);

            if (textClock.getElapsedTime().asSeconds() > 0.5f)
            {
                textVisible = !textVisible;
                textClock.restart();
            }

            if (textVisible)
            {
                window.draw(pressEnterText);
            }

            //------------------------------------------------------------------------------------
            
        }

        
       if (gameState == PreGameplay)
        {
            // Countdown
            for (int i = 0; i < 3; i++)
            {  


                countdownText.setString(std::to_string(countdown - i));

                // Center the text
                sf::FloatRect textRect = countdownText.getLocalBounds();
                sf::RectangleShape highlight(sf::Vector2f(countdownText.getGlobalBounds().width + 10, countdownText.getGlobalBounds().height + 10));
                highlight.setFillColor(sf::Color(255, 0, 0, 255)); 
                highlight.setPosition(countdownText.getPosition().x -5, (countdownText.getPosition().y + countdownText.getGlobalBounds().height) - 5);

                // Draw the game
                window.clear();
                window.draw(spritebackground);
                window.draw(characterSprite);
                window.draw(characterSprite2);
                window.draw(lifebarSprite);
                window.draw(lifebarSprite2);
                window.draw(Lifetext);
                window.draw(Lifetext2);
                window.draw(highlight);
                window.draw(countdownText);
                window.display();
                window.draw(countdownText);
                window.display();

                sf::sleep(sf::seconds(1.3));
            }
        
            gameState = Gameplay;
        }

        else if (gameState == Gameplay)
        {
            //------------------------------------------------------------------------------------

            // Menu music
            if (menuMusic.getStatus() == sf::Music::Playing)
            {
                menuMusic.stop();
            }

            // Gameplay music
            if (gameplayMusic.getStatus() != sf::Music::Playing)
            {
                gameplayMusic.play();
            }

            //------------------------------------------------------------------------------------

            window.draw(spritebackground);

            //------------------------------------------------------------------------------------
        
            // Movement
            if (Movement)
            {
                // Movement Bob
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    if (characterSprite.getPosition().x + characterSprite.getGlobalBounds().width < window.getSize().x)
                    {
                        characterSprite.move(1, 0);
                        characterTexture.loadFromFile("img/characters/walk/bobwalk.png");
                    }
                }
                
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    if (characterSprite.getPosition().x > 0)
                    {
                        characterSprite.move(-1, 0);
                        characterTexture.loadFromFile("img/characters/walk/bobwalk2.png");
                    }
                }

    //------------------------------------------------------------------------------------

                // Movement HDD69
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    if (characterSprite2.getPosition().x + characterSprite2.getGlobalBounds().width < window.getSize().x)
                    {
                        characterSprite2.move(1, 0);
                        characterTexture2.loadFromFile("img/characters/walk/HDD69walk.png");
                    }
                }
    
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                {
                    if (characterSprite2.getPosition().x > 0)
                    {
                        characterSprite2.move(-1, 0);
                        characterTexture2.loadFromFile("img/characters/walk/HDD69walk.png");
                    }
                }
            }

            //------------------------------------------------------------------------------------

            // Attack Bob

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                characterTexture.loadFromFile("img/characters/attack/bobattack.png");
                int frameTime = 10.0f;
                animationTime = sf::seconds(frameTime);

                if (attackClock.getElapsedTime().asMilliseconds() > animationTime.asMilliseconds())
                {
                    frame = (frame + 1) % 6;
                    characterSprite.setTextureRect(sf::IntRect(frame * 48, 0, 48, 48));
                    attackClock.restart();
                }
                lifeValue2 -=10;
                Lifetext2.setString(std::to_string(lifeValue2));
                if (lifeValue2 <= 0)
                {
                    characterTexture2.loadFromFile("img/characters/death/HDD69death.png");
                    lifeValue2 = 100;
                }
            }

            //------------------------------------------------------------------------------------

            // Attack HDD

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {
                characterTexture2.loadFromFile("img/characters/attack/HDD69attack.png");
                int frameTime2 = 10.0f;
                animationTime2 = sf::seconds(frameTime2);

                if (attackClock2.getElapsedTime().asMilliseconds() > animationTime2.asMilliseconds())
                {
                    frame2 = (frame2 + 1) % 8;
                    characterSprite2.setTextureRect(sf::IntRect(frame2 * 48, 0, 48, 48));
                    attackClock2.restart();
                }

                lifeValue -=10;
                Lifetext.setString(std::to_string(lifeValue));
                if (lifeValue <= 0)
                {
                    characterTexture.loadFromFile("img/characters/death/bobdeath.png");
                    lifeValue = 100;
                }
            }

            //------------------------------------------------------------------------------------

            // Frame clock
            if (clock.getElapsedTime().asSeconds() > 0.15f)
            {
                frame = (frame + 1) % 4;
                characterSprite.setTextureRect(sf::IntRect(frame * 48, 0, 48, 48));
                clock.restart();
            }

            if (clock2.getElapsedTime().asSeconds() > 0.15f)
            {
                frame2 = (frame2 + 1) % 4;
                characterSprite2.setTextureRect(sf::IntRect(frame2 * 48, 0, 48, 48));
                clock2.restart();
            }

            //------------------------------------------------------------------------------------

            lifebarSprite.setTexture(lifebarTexture);
            lifebarSprite2.setTexture(lifebarTexture2);
            window.draw(characterSprite);
            window.draw(characterSprite2);
            window.draw(lifebarSprite);
            window.draw(lifebarSprite2);
            window.draw(Lifetext);
            window.draw(Lifetext2);
        }
        window.display();
    }

    return 0;
}