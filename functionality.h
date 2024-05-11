/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR SPRING 2024 BS(SE)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * 
*/

//---Piece Starts to Fall When Game Starts---//
#include <fstream>
#include <iostream>
void fallingPiece(float& timer, float& delay,int& colorNum,int& n1){
    if (timer>delay)
    {
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
        }
          
        if (!anamoly()){
            for(int i=0;i<4;i++)
                gameGrid[point_2[i][1]][point_2[i][0]]=colorNum;
                colorNum=1+rand()%7;
            int n=rand()%8;
                n1=n;
            //--- Un-Comment this Part When You Make BLOCKS array---//
            
                for (int i=0;i<4;i++){
                    point_1[i][0] = BLOCKS[n][i] % 2;
                    point_1[i][1] = BLOCKS[n][i] / 2;
                }
            
        }
        timer=0;
    }
}

/////////////////////////////////////////////
///*** CODING FUNTIONS STARTS HERE ***///
   
   //manages both left and right movements 
void movement(float& timer, float& delay,int& x,int n)
{ 
  if(n==7)
   return;
  if (timer>delay)
  {
   for (int i=0;i<4;i++)
     {
       point_2[i][0]=point_1[i][0];
       point_2[i][1]=point_1[i][1];
       point_1[i][0]+=x; //How much units left or right 
      
     }
  x=0;
   
  if(!anamoly())
   {
       for(int i=0;i<4;i++)
       { point_1[i][0]=point_2[i][0];
         point_1[i][1]=point_2[i][1];
       }
        
   }
  timer=0;
 }
 
}

///////////////////////////////////////////////

void r_left(bool& r,int& x)
{
    
    int p1,p2;
    for (int i=0;i<4;i++)
     {
       point_2[i][0]=point_1[i][0];
       point_2[i][1]=point_1[i][1];   
       p1=point_1[i][1]-point_1[1][1];
       p2=point_1[i][0]-point_1[1][0]; 
       point_1[i][0]=point_1[1][0]-p1;
       point_1[i][1]=point_1[1][1]+p2;
     }
    r=0; x=0;
   
	
     if(!anamoly())
   {
       for(int i=0;i<4;i++)
        { point_1[i][0]=point_2[i][0];
          point_1[i][1]=point_2[i][1];}
        
   }
}

////////////////////////////////////////////

void r_right(bool& r,int& x)
{
   
    int p1,p2;
    for (int i=0;i<4;i++)
     {
       point_2[i][0]=point_1[i][0];
       point_2[i][1]=point_1[i][1];   
       p1=point_1[i][1]-point_1[1][1];
       p2=point_1[i][0]-point_1[1][0]; 
       point_1[i][0]=point_1[1][0]+p1;
       point_1[i][1]=point_1[1][1]-p2;
     }
    r=0; x=0;
     if(!anamoly())
   {
       for(int i=0;i<4;i++)
        {point_1[i][0]=point_2[i][0];
         point_1[i][1]=point_2[i][1];}
        
   }

}

////////////////////////////////////////////////

void writeFile(int points)
{
    std::ofstream outputFile("log.bin"); // Create or open file in append mode in the same directory

    if (outputFile.is_open()) {
        outputFile << points << "\n"; // Write points to the file
        outputFile.close(); // Close the file
    }
    else {
        std::cout << "Error opening the file for writing.\n";
    }
}

void readFile(int& points) {
    std::ifstream inputFile("log.bin"); // Open file for reading

    if (inputFile.is_open()) {
        while (inputFile >> points) { // Read each integer from the file
            std::cout << "Points: " << points << "\n"; // Print the points to the console
        }
        inputFile.close(); // Close the file
    }
    else {
        std::cerr << "Error opening the file for reading.\n";
    }
}

void displayScoresFromFile() {
    std::ifstream inputFile("score.bin"); // Open file for reading

    if (inputFile.is_open()) {
        int score;
        std::cout << "Scores:\n";
        while (inputFile >> score) { // Read each integer from the file
            std::cout << score << "\n"; // Print the score to the console
        }
        inputFile.close(); // Close the file
    }
}

void space(bool& down,int n)
{    
  if(n==7)
   return;
   while(anamoly())
   {
    for (int i=0;i<4;i++)
     {
       point_2[i][0]=point_1[i][0];
       point_2[i][1]=point_1[i][1];  
       point_1[i][1]+=1;
     }
   }
  
  if(!anamoly())
   {
       for(int i=0;i<4;i++)
        {point_1[i][1]-=1;}
        
   }
   down=0;
}

////////////////////////////////////////////////

void clear(int i,int& score)
{
  for(int j=0;j<N;j++)
    {
      gameGrid[i][j]=gameGrid[i-1][j];
      score++;

    }
}

////////////////////////////////////////////////

void check(int& points) {
    const int M = 20, N = 10;
    int cnt = 0, score = 0;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (gameGrid[i][j] != 0) {
                cnt++;
            }
        }
        if (cnt == N) {
            clear(i, score);
        }
        cnt = 0;
    }

   switch(score)
  {
  case 1:
      points=10;
      writeFile(points);
     break;
  case 2:
      points=30;
      writeFile(points);
     break;
  case 3:
      points=60;
      writeFile(points);
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9: 
  case 10:
  case 11:
  case 12:
  case 13:
  case 14: 
  case 15:
  case 16:
  case 17:
  case 18:
  case 19:
  case 20:
      points=100;
      writeFile(points);
     break;
  }
  score=0;
  writeFile(points);
}


 //////////////////////////////////////////////////

bool gameover()
{
  const int N = 10;
   for(int j=0;j<N;j++)
    {
      if(gameGrid[1][j]!=0)
         return 1;

    }
  return 0;
}


////////////////////////////////////////////////////

void shadows()
{
 for (int i=0;i<4;i++)
     {
       point_3[i][0]=point_1[i][0];
       point_3[i][1]=point_1[i][1];
     }

while(anamoly_s())
   {
    for (int i=0;i<4;i++)
     {  
       point_3[i][1]+=1;
     }
   }
   if(!anamoly_s())
   {
       for(int i=0;i<4;i++)
         point_3[i][1]-=1;
   }
   
}

  
///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
