#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

sf::Clock textClock;
bool textVisible = true;
bool Movement = false;

enum GameState
{
    MainMenu,
    Gameplay,
    Selecperso
};


int main()
{
    //------------------------------------------------------------------------------------

    // Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "THE D");
    window.setVerticalSyncEnabled(true);

    //------------------------------------------------------------------------------------

    // Game state
    GameState gameState = MainMenu;

    // Menu music
    sf::Music menuMusic;
    if (!menuMusic.openFromFile("sounds/menumusic.wav"))
    {
        // handle error
    }
    menuMusic.setLoop(true); // to loop the music

    //------------------------------------------------------------------------------------

    // Menu
    sf::Texture menuTexture2, menuTexture3;
    if (!menuTexture2.loadFromFile("img/background/testas2.png")) return 1;
    if (!menuTexture3.loadFromFile("img/background/testas3.png")) return 1;
    sf::Sprite spritemenu(menuTexture2);
    spritemenu.scale(0.5, 0.6);

    sf::Clock menuClock;
    int animationFrame = 0;

    //------------------------------------------------------------------------------------

    // Menu text

    sf::Text pressEnterText;
    sf::Font font;
    if (!font.loadFromFile("fonts/pixelletters-font/Pixellettersfull-BnJ5.ttf")) return 1;
    pressEnterText.setFont(font);
    pressEnterText.setString("Press 'Enter' to start");
    pressEnterText.setCharacterSize(24);
    pressEnterText.setFillColor(sf::Color::White);
    pressEnterText.setPosition(window.getSize().x / 2 - 80, window.getSize().y / 1.5);

    //------------------------------------------------------------------------------------

    // Background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("img/background/cybercity.png")) return 1;
    sf::Sprite spritebackground(backgroundTexture);
    spritebackground.scale(1.17, 2.2);


    //------------------------------------------------------------------------------------

    // Character
    sf::Texture characterTexture;
    if (!characterTexture.loadFromFile("img/characters/idle/bobidle.png")) return 1;
    sf::Sprite characterSprite(characterTexture);
    characterSprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
    int frame = 0;
    sf::Clock clock;

    //------------------------------------------------------------------------------------

    // Character position/size
    characterSprite.setOrigin(48 / 2, 48 / 2);
    characterSprite.setPosition(window.getSize().x / 5, window.getSize().y / 1.3);
    characterSprite.scale(5, 5);

    //------------------------------------------------------------------------------------

    while (window.isOpen())
    {        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            // Exit first menu

            if (gameState == MainMenu && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                gameState = Gameplay; // start the game when enter pressed
            }

            //------------------------------------------------------------------------------------

            if (gameState == Gameplay)
            {
                if (event.type == sf::Event::KeyPressed && 
                    (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left))
                {
                    Movement = true;
                }
                if (event.type == sf::Event::KeyReleased && 
                    (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left))
                {
                    Movement = false;
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

            //------------------------------------------------------------------------------------

            // Menu
            if (menuClock.getElapsedTime().asSeconds() > 3.0f) // change frame every 0.5 seconds
            {
                animationFrame = (animationFrame + 1) % 2; // cycle through 3 frames
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

        else if (gameState == Gameplay)
        {
            //------------------------------------------------------------------------------------

            if (menuMusic.getStatus() == sf::Music::Playing)
            {
                menuMusic.stop();
            }

            // draw the game
            window.draw(spritebackground);

            //------------------------------------------------------------------------------------

            // Movement
            if (Movement)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    characterSprite.move(1, 0);
                }
                
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    characterSprite.move(-1, 0);
                }

                characterTexture.loadFromFile("img/characters/walk/bobwalk.png");

                if (characterSprite.getPosition().x > window.getSize().x)
                {
                    characterSprite.setPosition(0, characterSprite.getPosition().y);
                }
            }

            else
            {
                characterTexture.loadFromFile("img/characters/idle/bobidle.png");
            }

            //------------------------------------------------------------------------------------

            // Attack
            sf::Time animationTime;
            sf::Clock attackClock;
            sf::Clock attackCooldown;

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
            }

            if (attackCooldown.getElapsedTime().asSeconds() > 4.0f)
            {
                characterTexture.loadFromFile("img/characters/idle/bobidle.png");
            }

            //------------------------------------------------------------------------------------

            // Frame clock
            if (clock.getElapsedTime().asSeconds() > 0.15f)
            {
                frame = (frame + 1) % 4;
                characterSprite.setTextureRect(sf::IntRect(frame * 48, 0, 48, 48));
                clock.restart();
            }

            window.draw(characterSprite);

        }
        window.display();
    }

    return 0;
}