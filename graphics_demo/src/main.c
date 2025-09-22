#include <stm32f031x6.h>
#include "display.h"
#include <stdint.h>
#include <stdio.h>
#include "serial.h"

void initClock(void);
void initSysTick(void);
void SysTick_Handler(void);
void delay(volatile uint32_t dly);
void setupIO();
int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py);
void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber);
void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode);
void movingBarrels(uint16_t startY, uint16_t endY, const uint16_t *image, int x, int y);
void movingBarrelsX2(uint16_t startY, uint16_t endY, const uint16_t *image, int x, int y);
void movingBarrelsLeft(uint16_t startY, uint16_t endY, const uint16_t *image, int x, int y);
void movingBarrelsLeftX2(uint16_t startY, uint16_t endY, const uint16_t *image, int x, int y);
void background();
void background2();
void background3();
void background4();
void red1On();
void red1Off();
void red2On();
void red2Off();
void red3On();
void red3Off();
void initSound(void);
void jumpCharacter();


volatile uint32_t milliseconds;

//main character 
const uint16_t deco1blue[]=  
{
0,0,40224,40224,40224,40224,40224,0,0,0,0,0,0,0,40224,40224,40224,40224,40224,40224,40224,0,0,0,0,0,40375,40375,40375,9293,40375,0,0,0,0,0,0,0,40375,40375,40375,40375,40375,57293,0,0,0,0,0,0,40375,40375,40375,4368,4368,0,0,0,0,0,0,0,0,40375,40375,40375,0,0,0,0,0,0,0,0,0,1994,1994,1994,0,0,0,0,0,0,0,0,1994,1994,65535,1994,0,0,0,0,0,0,0,0,1994,1994,65535,1994,1994,1994,1994,0,0,0,0,0,1994,1994,65535,65535,65535,65535,1994,0,0,0,0,0,1994,1994,1994,1994,1994,1994,1994,0,0,0,0,0,1994,1994,1994,1994,0,0,0,0,0,0,0,0,0,1994,65535,1994,0,0,0,0,0,0,0,0,0,1994,65535,1994,0,0,0,0,0,0,0,0,0,1994,65535,1994,0,0,0,0,0,0,0,0,0,22355,22355,22355,22355,0,0,0,0,0,
};

//top head of character
const uint16_t deco3[]= 
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,40224,40224,40224,40224,0,0,0,0,0,0,0,40224,40224,40224,40224,40224,40224,0,0,0,0,1994,1994,40224,40224,40224,40224,40224,40224,1994,1994,0,0,65535,65535,40224,40224,40224,40224,40224,40224,65535,65535,0,0,1994,1994,40224,40224,40224,40224,40224,40224,1994,1994,0,0,0,0,40224,40224,40224,40224,40224,40224,0,0,0,0,0,0,0,40224,40224,40224,40224,0,0,0,0,0,0,0,0,40224,40224,40224,40224,0,0,0,0,0,0,0,0,40224,40224,40224,40224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

//heart for lives
const uint16_t heart[]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,57293,57293,0,0,57293,57293,0,0,0,0,0,57293,57293,57293,57293,57293,57293,57293,57293,0,0,0,57293,57293,57293,57293,57293,57293,57293,57293,57293,57293,0,0,57293,57293,57293,57293,57293,57293,57293,57293,57293,57293,0,0,0,57293,57293,57293,57293,57293,57293,57293,57293,0,0,0,0,0,57293,57293,57293,57293,57293,57293,0,0,0,0,0,0,0,57293,57293,57293,57293,0,0,0,0,0,0,0,0,0,57293,57293,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

//ladder image
const uint16_t ladder[]=
{
	0,16621,16621,16621,16621,16621,16621,16621,16621,16621,16621,0,0,16621,16621,0,0,0,0,0,0,16621,16621,0,0,16621,16621,0,0,0,0,0,0,16621,16621,0,0,16621,16621,16621,16621,16621,16621,16621,16621,16621,16621,0,0,16621,16621,16621,16621,16621,16621,16621,16621,16621,16621,0,0,16621,16621,0,0,0,0,0,0,16621,16621,0,0,16621,16621,0,0,0,0,0,0,16621,16621,0,0,16621,16621,16621,16621,16621,16621,16621,16621,16621,16621,0,0,16621,16621,16621,16621,16621,16621,16621,16621,16621,16621,0,0,16621,16621,0,0,0,0,0,0,16621,16621,0,0,16621,16621,0,0,0,0,0,0,16621,16621,0,0,16621,16621,16621,16621,16621,16621,16621,16621,16621,16621,0,0,16621,16621,16621,16621,16621,16621,16621,16621,16621,16621,0,0,16621,16621,0,0,0,0,0,0,16621,16621,0,0,16621,16621,0,0,0,0,0,0,16621,16621,0,0,16621,16621,16621,16621,16621,16621,16621,16621,16621,16621,0,
};

//standing barrel
const uint16_t barrel[] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,65315,65315,65315,0,0,0,0,0,0,0,0,65315,22355,22355,22355,65315,0,0,0,0,0,0,65315,22355,22355,1994,22355,22355,65315,0,0,0,0,0,65315,22355,1994,22355,22355,22355,65315,0,0,0,0,0,0,65315,22355,22355,22355,65315,0,0,0,0,0,0,0,0,65315,65315,65315,0,0,0,0,0,
};

//rolling barrel
const uint16_t barrelroll[] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,65315,65315,0,0,0,0,0,0,0,0,0,65315,22355,22355,65315,0,0,0,0,0,0,0,65315,22355,1994,22355,22355,65315,0,0,0,0,0,0,65315,22355,22355,1994,22355,65315,0,0,0,0,0,0,65315,22355,22355,22355,22355,65315,0,0,0,0,0,0,0,65315,22355,22355,65315,0,0,0,0,0,0,0,0,0,65315,65315,0,0,0,0,0,
};

//top of the barrel
const uint16_t topbarrel[] =
{
	0,0,0,65315,65315,22355,22355,65315,65315,0,0,0,0,0,1994,1994,1994,1994,1994,1994,1994,1994,0,0,0,65315,65315,16142,22355,22355,22355,22355,16142,65315,65315,0,65315,16142,16142,16142,22355,22355,22355,22355,16142,16142,16142,65315,65315,16142,16142,16142,22355,22355,22355,22355,16142,16142,16142,65315,65315,16142,16142,16142,22355,22355,22355,22355,16142,16142,16142,65315,65315,16142,16142,16142,22355,22355,22355,22355,16142,16142,16142,65315,65315,16142,16142,16142,22355,22355,22355,22355,16142,16142,16142,65315,65315,16142,16142,16142,22355,22355,22355,22355,16142,16142,16142,65315,65315,16142,16142,16142,22355,22355,22355,22355,16142,16142,16142,65315,65315,16142,16142,16142,22355,22355,22355,22355,16142,16142,16142,65315,65315,16142,16142,16142,22355,22355,22355,22355,16142,16142,16142,65315,65315,16142,16142,16142,22355,22355,22355,22355,16142,16142,16142,65315,0,65315,65315,16142,22355,22355,22355,22355,16142,65315,65315,0,0,0,1994,1994,1994,1994,1994,1994,1994,1994,0,0,0,0,0,65315,65315,22355,22355,65315,65315,0,0,0,
};

//character running
const uint16_t running[] =
{
	0,0,0,0,0,40224,40224,40224,40224,40224,0,0,0,0,0,0,0,40224,40224,40224,40224,40224,40224,40224,0,0,0,0,0,40375,40375,40375,9293,40375,0,0,0,0,0,0,0,40375,40375,40375,40375,40375,57293,0,0,0,0,0,0,40375,40375,40375,4096,4096,0,0,0,0,0,0,0,0,40375,40375,40375,0,0,0,0,0,0,0,0,1994,1994,1994,0,0,0,0,0,0,0,0,1994,1994,65535,1994,0,0,0,0,0,0,0,0,1994,1994,65535,1994,1994,1994,1994,0,0,0,0,0,1994,1994,65535,65535,65535,65535,1994,0,0,0,0,0,1994,1994,1994,1994,1994,1994,1994,0,0,0,0,0,1994,1994,1994,1994,0,0,0,0,0,0,0,0,0,1994,1994,65535,1994,0,0,0,0,0,0,0,1994,1994,1994,65535,1994,0,0,0,0,0,0,22355,1994,1994,1994,65535,1994,0,0,0,0,0,0,0,22355,0,22355,22355,22355,22355,0,0,
};

//character jumping
const uint16_t jumping[] = 
{
	0,57360,0,40375,40375,40375,40375,9293,0,0,0,0,0,0,0,40375,40375,40375,40375,40375,57293,0,0,0,0,0,0,40375,40375,40375,4368,4368,0,0,0,0,0,0,0,0,40375,40375,40375,40375,0,0,0,0,0,0,0,0,1994,1994,1994,0,0,0,0,0,1994,1994,1994,1994,1994,1994,1994,1994,1994,1994,0,0,1994,65535,65535,65535,65535,65535,65535,65535,65535,1994,0,0,1994,1994,1994,1994,65535,65535,1994,1994,1994,1994,0,0,0,0,0,1994,65535,65535,1994,0,0,0,0,0,0,0,0,1994,1994,1994,1994,0,0,0,22355,0,0,0,0,1994,1994,1994,1994,1994,1994,22355,22355,0,0,0,1994,1994,1994,1994,1994,1994,1994,22355,22355,0,0,22355,22355,1994,1994,1994,0,0,0,0,0,0,22355,22355,22355,1994,0,0,0,0,0,0,0,0,22355,22355,0,0,0,0,0,0,0,0,0,0,0,49192,0,0,0,0,0,0,0,0,0,0,
};

//crown to win
const uint16_t crown[] = 
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24327,24327,0,0,0,0,0,0,0,0,0,24327,65535,65535,24327,0,0,0,0,0,0,0,0,0,24327,24327,0,0,0,0,0,0,0,0,0,0,24327,24327,0,0,0,0,0,0,24327,24327,0,24327,40224,40224,24327,0,24327,24327,0,24327,40224,40224,24327,40224,40224,40224,40224,24327,40224,40224,24327,24327,40224,40224,24327,40224,40224,40224,40224,24327,40224,40224,24327,0,24327,40224,24327,40224,40224,40224,40224,24327,40224,24327,0,0,0,24327,24327,24327,24327,24327,24327,24327,24327,0,0,0,0,24327,24327,24327,24327,24327,24327,24327,24327,0,0,
};

int hinverted = 0;
int vinverted = 0;
int toggle = 0;
int hmoved = 0;
int vmoved = 0;
int jmoved = 0;
int screen = 0;

int main()
{
	uint16_t x = 15; //deco starting x value
	uint16_t y = 138; //deco starting y value
	uint16_t oldx = x;
	uint16_t oldy = y;

	initClock();
	initSysTick();
	setupIO();
	initSerial();
	

	while(1)
	{
		// Main Menu = screen = 0
		while(screen == 0) 
		{
			
			eputs("\r\n");
			
			

			x = 15; 
			y = 138;

			
			
			// Draw screen

			//Name of game
			printTextX2("CROWN", 37, 10, RGBToWord(255,255,255), 0);
			printTextX2("CLIMB", 37, 30, RGBToWord(255,255,255), 0);

			//Image of crown you have to get to win
			putImage(58,48,12,16, crown,hinverted,0);

			//Controls
			printText("Press 'Down'", 25, 70, RGBToWord(255,255,255), 0);
			printText("to start", 39, 80, RGBToWord(255,255,255), 0);
			printText("'Up' = Climb", 3, 100, RGBToWord(255,0,255), 0);
			printText("'Dowm' = Jump", 3, 110, RGBToWord(255,0,255), 0);
			printText("'Right' = Go Right", 3, 120, RGBToWord(255,0,255), 0);
			printText("'Left' = Go left",3, 130, RGBToWord(255,0,255), 0);

			// if "Down" pressed, start the game (screen set to 1)
			if ( (GPIOA->IDR & (1 << 11)) == 0) 
			{
				screen = 1;
				fillRectangle(0,0,128,160,0);
				eputs("Game started");//serial comms
			} // end if


		} // end while 

		while(screen == 1)
		{
			background(); //loads background

			//starts barrels moving left and right across screen X2 means twice as fast
			movingBarrels(139,14,barrel, x, y);
			movingBarrelsLeft(112,114,barrel, x, y);
			movingBarrelsX2(85,14,barrel, x ,y);
			movingBarrelsLeftX2(58,114,barrel, x ,y);

			hmoved = vmoved = 0;
			hinverted = vinverted = 0;
			

			if ((GPIOB->IDR & (1 << 4))==0) // right pressed
			{
				if (x < 110)
				{
					x = x + 1;
					hmoved = 1;
					hinverted = 0;
					eputs("Right\n");
				} //end if					
			} //end if


			if ((GPIOB->IDR & (1 << 5))==0) // left pressed
			{			
				if (x > 10)
				{
					x = x - 1;
					hmoved = 1;
					hinverted = 1;
					eputs("Left\n");
				} //end if		
			} //end if

			
			if ( (GPIOA->IDR & (1 << 11)) == 0) // down pressed
			{
				if (y < 140)
				{
					y = y - 7;
					jmoved = 1;
					eputs("Down\n");
    			} //end if
			} //end if

			
			

			if (isInside(108,140,12,27,x,y) || isInside(108,140,12,27,x+12,y) || isInside(108,140,12,27,x,y+27) || isInside(108,140,12,27,x+12,y+27) )
			{

				if ( (GPIOA->IDR & (1 << 8)) == 0) // up pressed
				{			
					if (y > 16)
					{
						y = y - 1;
						vmoved = 1;
						vinverted = 1;
						eputs("Up\n");
					} //end if
				} //end if

			} //end if


			if (isInside(5,112,12,27,x,y) || isInside(5,112,12,27,x+12,y) || isInside(5,112,12,27,x,y+27) || isInside(5,112,12,27,x+12,y+27) )
			{

				if ( (GPIOA->IDR & (1 << 8)) == 0) // up pressed
				{			
					if (y > 16)
					{
						y = y - 1;
						vmoved = 1;
						vinverted = 1;
						eputs("Up\n");
					} //end if
				} //end if

			} //end if

			if (isInside(104,86,12,27,x,y) || isInside(104,86,12,27,x+12,y) || isInside(104,86,12,27,x,y+27) || isInside(104,86,12,27,x+12,y+27) )
			{

				if ( (GPIOA->IDR & (1 << 8)) == 0) // up pressed
				{			
					if (y > 16)
					{
						y = y - 1;
						vmoved = 1;
						vinverted = 1;
						eputs("Up\n");
					} //end if
				} //end if

			} //end if
			

			if (isInside(7,58,12,27,x,y) || isInside(7,58,12,27,x+12,y) || isInside(7,58,12,27,x,y+27) || isInside(7,58,12,27,x+12,y+27) )
			{

				if ( (GPIOA->IDR & (1 << 8)) == 0) // up pressed
				{			
					if (y > 16)
					{
						y = y - 1;
						vmoved = 1;
						vinverted = 1;
						eputs("Up\n");
					} //end if
				} //end if

			} //end if

			if (isInside(59,32,12,27,x,y) || isInside(59,32,12,27,x+12,y) || isInside(59,32,12,27,x,y+27) || isInside(59,32,12,27,x+12,y+27) )
			{

				if ( (GPIOA->IDR & (1 << 8)) == 0) // up pressed
				{			
					if (y > 16)
					{
						y = y - 1;
						vmoved = 1;
						vinverted = 1;
						eputs("Up\n");
					} //end if
				} //end if

			} //end if

			



			if ((vmoved) || (hmoved) || (jmoved)) 
			{
				// only redraw if there has been some movement (reduces flicker)
				fillRectangle(oldx,oldy,12,16,0);
				
				oldx = x;
				oldy = y;
									
				if (hmoved)
				{
					if (toggle)
						putImage(x,y,12,16,deco1blue,hinverted,0);
					else
						putImage(x,y,12,16,running,hinverted,0);
				
					toggle = toggle ^ 1;
				} //end if
				
				if (vmoved)
				{
					putImage(x,y,12,16,deco3,0,vinverted);
				} //end else

				if (jmoved)
				{
					putImage(x,y,12,16,jumping,hinverted,0);
					//delay(200);
					jmoved = 0;
					y = y + 7;
				}
				

				// Now check for an overlap by checking to see if ANY of the 4 corners of deco are within the target area

				//if inside the crown game = won
				if (isInside(70,10,12,16,x,y) || isInside(70,10,12,16,x+12,y) || isInside(70,10,12,16,x,y+16) || isInside(70,10,12,16,x+12,y+16) )
				{
					screen = 2;
					fillRectangle(0,0,128,160,0);
				} //end if 

			} //end if		

			delay(50);
		} //end while

		while (screen == 2)
		{
			red2On();
			red1On();
			//you win the game
			printTextX2("WINNER!", 30, 50, RGBToWord(255,255,255), 0);
			printText("Score:1000", 35, 90, RGBToWord(255,255,255), 0);


			//press up to play again
			printText("Press 'Up' to", 20, 130, RGBToWord(255,255,255), 0);
			printText("Play again", 30, 145, RGBToWord(255,255,255), 0);

			// if "Up" pressed, restart the game (screen set to 0)
			if ( (GPIOA->IDR & (1 << 8)) == 0) // up pressed
			{			
				screen = 0;
				fillRectangle(0,0,128,160,0);
				eputs("Back to start screen\n");
			} //end if
		} //end while

		while (screen == 3)
		{
			red2On();
			red1On();
			//game = over
			printTextX2("GAME", 40, 40, RGBToWord(255,255,255), 0);
			printTextX2("OVER", 40, 60, RGBToWord(255,255,255), 0);	

			//press up to play again
			printText("Press 'Up' to", 20, 130, RGBToWord(255,255,255), 0);
			printText("Play again", 30, 145, RGBToWord(255,255,255), 0);

			printText("Score:0", 5, 1, RGBToWord(255,255,255), 0);


			// if "Up" pressed, restart the game (screen set to 1)
			if ( (GPIOA->IDR & (1 << 8)) == 0) // up pressed
			{			
				screen = 0;
				fillRectangle(0,0,128,160,0);
				x = 15;
				y = 138;
				eputs("Back to start screen\n");
			} //end if	
				
		} //end while

		
	} //end while
	return 0;
} //end int main

void initSysTick(void)
{
	SysTick->LOAD = 48000;
	SysTick->CTRL = 7;
	SysTick->VAL = 10;
	__asm(" cpsie i "); // enable interrupts
}

void SysTick_Handler(void)
{
	milliseconds++;
}

void initClock(void)
{
// This is potentially a dangerous function as it could
// result in a system with an invalid clock signal - result: a stuck system
        // Set the PLL up
        // First ensure PLL is disabled
        RCC->CR &= ~(1u<<24);
        while( (RCC->CR & (1 <<25))); // wait for PLL ready to be cleared
        
// Warning here: if system clock is greater than 24MHz then wait-state(s) need to be
// inserted into Flash memory interface
				
        FLASH->ACR |= (1 << 0);
        FLASH->ACR &=~((1u << 2) | (1u<<1));
        // Turn on FLASH prefetch buffer
        FLASH->ACR |= (1 << 4);
        // set PLL multiplier to 12 (yielding 48MHz)
        RCC->CFGR &= ~((1u<<21) | (1u<<20) | (1u<<19) | (1u<<18));
        RCC->CFGR |= ((1<<21) | (1<<19) ); 

        // Need to limit ADC clock to below 14MHz so will change ADC prescaler to 4
        RCC->CFGR |= (1<<14);

        // and turn the PLL back on again
        RCC->CR |= (1<<24);        
        // set PLL as system clock source 
        RCC->CFGR |= (1<<1);
}

void delay(volatile uint32_t dly)
{
	uint32_t end_time = dly + milliseconds;
	while(milliseconds != end_time)
		__asm(" wfi "); // sleep
}

void enablePullUp(GPIO_TypeDef *Port, uint32_t BitNumber)
{
	Port->PUPDR = Port->PUPDR &~(3u << BitNumber*2); // clear pull-up resistor bits
	Port->PUPDR = Port->PUPDR | (1u << BitNumber*2); // set pull-up bit
}

void pinMode(GPIO_TypeDef *Port, uint32_t BitNumber, uint32_t Mode)
{
	/*
	*/
	uint32_t mode_value = Port->MODER;
	Mode = Mode << (2 * BitNumber);
	mode_value = mode_value & ~(3u << (BitNumber * 2));
	mode_value = mode_value | Mode;
	Port->MODER = mode_value;
}

int isInside(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t px, uint16_t py)
{
	// checks to see if point px,py is within the rectange defined by x,y,w,h
	uint16_t x2,y2;
	x2 = x1+w;
	y2 = y1+h;
	int rvalue = 0;
	if ( (px >= x1) && (px <= x2))
	{
		// ok, x constraint met
		if ( (py >= y1) && (py <= y2))
			rvalue = 1;
	}
	return rvalue;
}

void setupIO()
{
	RCC->AHBENR |= (1 << 18) + (1 << 17); // enable Ports A and B
	display_begin();
	pinMode(GPIOB,4,0);
	pinMode(GPIOB,5,0);
	pinMode(GPIOA,8,0);
	pinMode(GPIOA,11,0);
	enablePullUp(GPIOB,4);
	enablePullUp(GPIOB,5);
	enablePullUp(GPIOA,11);
	enablePullUp(GPIOA,8);

	pinMode(GPIOB,3,1);
	enablePullUp(GPIOB,3);

	pinMode(GPIOA,0,1);
	enablePullUp(GPIOA,0);
}

//function for barrel moving right
void movingBarrels(uint16_t startY, uint16_t endY, const uint16_t *image, int x, int y)
{
	static uint16_t xPos = 40; //Starting x position of barrel
	static int direction = 1; //Movement direction 1 = right -1 = left
	uint16_t width = 12; //width of barrel
	int screen = 0;
	//int screen = 1;

	xPos += direction; //increment or decrement xPos based on direction

	if (xPos >= (98 - width) || xPos <= 14) //checks if barrel has reached boundary
	{
		direction *= -1;
	}

	putImage (xPos, startY, 12, 16, image, 0, 0);
	
	if (isInside(xPos,startY,8,8,x,y) || isInside(xPos,startY,8,8,x+8,y) || isInside(xPos,startY,8,8,x,y+8) || isInside(xPos,startY,8,8,x+8,y+8))
	{ 
		screen = 3;
		eputs("GAME OVER!\n"); 
	}

	return screen;
}

//fuction for barrel moving right at 2x speed
void movingBarrelsX2(uint16_t startY, uint16_t endY, const uint16_t *image, int x , int y)
{
	static uint16_t xPos = 14; //Current x position of barrel
	static int direction = 2; //Movement direction 1 = right -1 = left
	uint16_t width = 12; //width of barrel
	

	xPos += direction; //increment or decrement xPos based on direction

	if (xPos >= (94 - width) || xPos <= 14) //checks if barrel has reached boundary
	{
		direction *= -1;
	}

	putImage (xPos, startY, 12, 16, image, 0, 0);

	if (isInside(xPos,startY,8,8,x,y) || isInside(xPos,startY,8,8,x+8,y) || isInside(xPos,startY,8,8,x,y+8) || isInside(xPos,startY,8,8,x+8,y+8))
	{ 
		int screen = 3;
		eputs("GAME OVER!\n"); 
	}

	return screen;
}

//function for barrel moving left
void movingBarrelsLeft(uint16_t startY, uint16_t endY, const uint16_t *image, int x, int y)
{
	static uint16_t xPos = 102; //Current x position of barrel
	static int direction = -1; //Movement direction 1 = right -1 = left
	uint16_t width = 12; //width of barrel

	xPos += direction; //increment or decrement xPos based on direction

	if (xPos >= (114 - width) || xPos <= 28) //checks if barrel has reached boundary
	{
		direction *= -1;
	}

	putImage (xPos, startY, 12, 16, image, 0, 0);

	if (isInside(xPos,startY,8,8,x,y) || isInside(xPos,startY,8,8,x+8,y) || isInside(xPos,startY,8,8,x,y+8) || isInside(xPos,startY,8,8,x+8,y+8))
	{ 
		int screen = 3;
		eputs("GAME OVER!\n"); 
	}

	return screen;
}

//function for barrel moving left at 2x speed
void movingBarrelsLeftX2(uint16_t startY, uint16_t endY, const uint16_t *image, int x, int y)
{
	static uint16_t xPos = 102; //Current x position of barrel
	static int direction = -2; //Movement direction 1 = right -1 = left
	uint16_t width = 12; //width of barrel

	xPos += direction; //increment or decrement xPos based on direction

	if (xPos >= (114 - width) || xPos <= 32) //checks if barrel has reached boundary
	{
		direction *= -1;
	}

	putImage (xPos, startY, 12, 16, image, 0, 0);

	if (isInside(xPos,startY,8,8,x,y) || isInside(xPos,startY,8,8,x+8,y) || isInside(xPos,startY,8,8,x,y+8) || isInside(xPos,startY,8,8,x+8,y+8))
	{ 
		int screen = 3;
		eputs("GAME OVER!\n"); 
	}

	return screen;
}

//function that implements the background
void background()
{
	//lights on
	red1Off();
	red2Off();
	

	//Track lines
	drawLine(14, 155, 128, 155, RGBToWord(160,32,240));
	drawLine(1, 128, 114, 128, RGBToWord(160,32,240));
	drawLine(14, 101, 128, 101, RGBToWord(160,32,240));
	drawLine(1, 74, 114, 74, RGBToWord(160,32,240));
	drawLine(14, 47, 128, 47, RGBToWord(160,32,240));

	//bottom ladder right
	putImage(98,128,12,16,ladder,0,0);
	putImage(98,139,12,16,ladder,0,0);

	//ladder second from bottom on left
	putImage(16,112,12,16,ladder,0,0);
	putImage(16,101,12,16,ladder,0,0);

	//ladder third from bottom on right
	putImage(94,74,12,16,ladder,0,0);
	putImage(94,85,12,16,ladder,0,0);

	//ladder fourth from bottom on left
	putImage(18,47,12,16,ladder,0,0);
	putImage(18,58,12,16,ladder,0,0);

	//top ladder
	putImage(70,15,12,16,ladder,0,0);
	putImage(70,31,12,16,ladder,0,0);

	//hearts top left of screen
	putImage(1,1,12,16,heart,0,0);
	//putImage(14,1,12,16,heart,0,0);
	//putImage(27,1,12,16,heart,0,0);

	//crown
	putImage(70,-4,12,16,crown,0,0);

	//topbarrels
	putImage(114,30,12,16,topbarrel,0,0);
	putImage(101,30,12,16,topbarrel,0,0);
	putImage(114,14,12,16,topbarrel,0,0);
}

//functions for each light on/off
void red2On()
{
    GPIOA->ODR = GPIOA->ODR | (1 << 3);
}

void red2Off()
{
    GPIOA->ODR = GPIOA->ODR | (1 << 0);
}

void red1On()
{
    GPIOA->ODR = GPIOA->ODR | (1 << 0);
}

void red1Off()
{
    GPIOA->ODR = GPIOA->ODR &= ~(1 << 0);
}

