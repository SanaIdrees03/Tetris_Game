/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR SPRING 2024 BS(SE)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * 
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;
int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(450, 565), title);
            //FONT
            Font font;
    font.loadFromFile("font/font1.ttf");//
           //
           
           
    Texture obj1, obj2, obj3,obj4 ,obj5, obj6;
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/tetris.png");
    obj3.loadFromFile("img/frame.png");
          
          
          //
    obj4.loadFromFile("img/shadows.png");
    obj5.loadFromFile("img/gover.png");
    obj6.loadFromFile("img/menu.png");
          //
          
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */
    Sprite sprite(obj1), background(obj2), frame(obj3),
    
                      //
     shadow(obj4) , game_over(obj5), menu(obj6);
                     //
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("audio/cruising-down.mp3"))
    {       
        return 1;
    }

    // Play the background music (looped)
    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    
                    
    int delta_x=0, colorNum=1 
    ,scr=0, //for score
    trans=0,//for menu/game/gameover
    points=0;//to check the score
    float timer=0, delay=0.9;
    bool rotate=0, 
    down=0,//to verify if spacebar is pressed
    over=0;//to verify if game is over
    Clock clock;


    while (window.isOpen()){
      if(trans==0)  //0 is for menu 
       {
    
      window.draw(menu);
      window.display();
    
    
      Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::S)            //Check if the other key pressed is S key
                {
                    sf::SoundBuffer buffer;
                    buffer.loadFromFile("audio/mouse-click.wav");

                    // Play the loaded audio
                    sf::Sound sound;
                    sound.setBuffer(buffer);
                    sound.play();

                    // Keep the program running to hear the audio
                    while (sound.getStatus() == sf::Sound::Playing) 
                    {}


                    trans = 1;                         //goes to main game

                }

                else if (e.key.code == Keyboard::C)    //Check if the other key pressed is X key
                {
                    sf::SoundBuffer buffer;
                    buffer.loadFromFile("audio/mouse-click.wav");

                    // Play the loaded audio
                    sf::Sound sound;
                    sound.setBuffer(buffer);
                    sound.play();

                    // Keep the program running to hear the audio
                    while (sound.getStatus() == sf::Sound::Playing)
                    {
                    }

                    readFile(scr); // Read and print data from the file
                    displayScoresFromFile(); // Display scores from the file
                }

                else if (e.key.code == Keyboard::X)    //Check if the other key pressed is X key
                {

                    sf::SoundBuffer buffer;
                    buffer.loadFromFile("audio/mouse-click.wav");

                    // Play the loaded audio
                    sf::Sound sound;
                    sound.setBuffer(buffer);
                    sound.play();

                    // Keep the program running to hear the audio
                    while (sound.getStatus() == sf::Sound::Playing)
                    {}
                  

                    over = 1;                           //Exits the game X=exit
                }
             }}}
    
    
        if(over)
        window.close();
        
        //////////////////////////////////////////////////////////////////////
        //game over
         if(trans==2)
         {
           window.draw(game_over);
           Text go;
           go.setFont(font);
           go.setCharacterSize(29);
           go.setString("RESTART (R)");
           go.setFillColor (Color::White);
           go.setPosition(125,390);
           window.draw(go);
           const int M = 20, N = 10;
           for (int i = 0; i < M; ++i) {
               for (int j = 0; j < N; ++j) {
                   gameGrid[i][j] = 0; // Reset each element of the game grid to zero
               }
           }
           
           Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {            //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::R)            //Check if the other key pressed is R key
                {

                    sf::SoundBuffer buffer;
                    buffer.loadFromFile("audio/mouse-click.wav");

                    // Play the loaded audio
                    sf::Sound sound;
                    sound.setBuffer(buffer);
                    sound.play();

                    // Keep the program running to hear the audio
                    while (sound.getStatus() == sf::Sound::Playing)
                    {
                    }
                    trans = 0;

                }
                    
                    window.display();         
         }}}       
         
        
        
        /////////////////////////////////////////////////////////////////
        //MAIN GAME//
         if(trans==1)
        {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        float t1=timer;
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive 
                
                
                
                
                else if (e.key.code == Keyboard::H)    //Check if the other key pressed is H key
                {

                    sf::SoundBuffer buffer;
                    buffer.loadFromFile("audio/mouse-click.wav");

                    // Play the loaded audio
                    sf::Sound sound;
                    sound.setBuffer(buffer);
                    sound.play();

                    // Keep the program running to hear the audio
                    while (sound.getStatus() == sf::Sound::Playing)
                    { }
                    trans = 0;
                }
                   
            
            
                  else if (Keyboard::isKeyPressed(Keyboard::Space))   
                        down=1;
            }
        }
       
       
            
      
           
        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        
       int n;
       fallingPiece(timer, delay,colorNum,n);               //Example: fallingPiece() function is called here
      
       //////////////////////////////////////////////////
       //  checks condition if bomb is coming . it does not allow the movement function to work on it
        if(n!=7)
        {
          if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.05;                             //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
        }
       
       
       //If DOWN key is stopped being pressed, delay in falling piece chnages back to 0.3
       if (!(Keyboard::isKeyPressed(Keyboard::Down))) 
            delay=0.3; 
        
        ////////////////////////////////////////////////////
        
       //for left and right movement of the blocks
       //it intakes :
       //t1 for time delay(t1 as time becomes 0 after the falling function is called)
       //delay 
       //delta_x to know which key was pressed
       //n to check if it was the bomb shape
       movement(t1, delay,delta_x,n);
       
       /////////////////////////////////////////////////////
       //checks if key is pressed or not 
       
       if(rotate)
       { 
         if(delta_x==1)
           r_left(rotate,delta_x);   //for left rotation , takes x as input as well to check if left key is pressed or not. left rotation(up + left key)
         else if(delta_x==-1)
           r_right(rotate,delta_x); //for right rotation , takes x as input as well to check if right key is pressed or not. right rotation(up + right key)
       }
      
      ///////////////////////////////////////////////////
      //checks if space is pressed or not
      
       if(down)
       {space(down,n);//n to check if it was the bomb shape //down to know if the space was pressed
       }
       
      //////////////////////////////////////////////////
      //initally score is zero
      //
       points=0;
       check(points);
       scr=scr+points;
       writeFile(scr); // Write some data to the file
       
       
       ////////////////////////////////////////////
       
       shadows();
       
       ////////////////////////////////////////////////
       
       if(gameover())
        {
          trans=2;
        }
       
        
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////


        window.clear(Color::White);
        window.draw(background);
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
          
          //////////////SHADOWSSS///////////////////////////
          

            for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                shadow.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                shadow.setPosition(j*18,i*18);
                shadow.move(800,800); //offset
                window.draw(shadow);
            }
        }
        for (int i=0; i<4; i++){
            shadow.setTextureRect(IntRect(colorNum*18,0,18,18));
            shadow.setPosition(point_3[i][0]*18,point_3[i][1]*18);
            shadow.move(28,31);
            window.draw(shadow);
          }
          
        ///////////////////////////////////////////////////////////////////////////////////////
         
        

//SFML TO PRINT  

Text s;
s.setFont(font);
s.setCharacterSize(20);
s.setString(std::to_string(scr));
s.setFillColor (Color::Cyan);
s.setPosition(150,425);

Text t;
t.setFont(font);
t.setCharacterSize(25);
t.setString("SCORE : ");
t.setFillColor (Color::Black);
t.setPosition(50,420);

Text h;
h.setFont(font);
h.setCharacterSize(25);
h.setString("PAUSE (H) ");
h.setFillColor (Color::Black);
h.setPosition(50,450);
        
        
        
        
        
        window.draw (h);
        window.draw (s);
        window.draw (t);
       // window.draw (score);
        //window.draw (t3);
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
        
  }}

  backgroundMusic.stop();   
  readFile(scr); // Read and print data from the file  


    return 0;
}
