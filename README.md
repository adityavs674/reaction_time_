# reaction_time_
One day I woke up to a thought - that I hadn't properly used arduino after 8th standard. So I decided to create this little game on arduino. 
A simple arduino powered reaction time game using pushbuttons and LEDs.

Made on a breadboard, It has total of 2 pushbuttons, 1 for each player and 1 blue LED that triggers the start of each round.
As soon as the blue LED lights up, each player has to press thier button faster than the other.
Whoever wins has thier side of green led lit up.
If someone presses thier button before the blue LED, thier side of red lights up.
If player 1 is winning, yellow LED is on, otherwise off.

Multiple rounds are triggered one after the other, without stopping until power off or reset (upon reset, the scores reset, and rounds start again)
The scores are displayed on the serial monitor if the arduino is connected to a pc and arduino IDE is opened.

I also created a buttondetect function which takes last 10 values of the digitalRead pushbutton and uses thier average value to check if the button is really pressed, or it is a glitched input.
I had to do this because the pushbuttons produce really glitchy results. The tradeoff is, if the buttons are pressed under ~25 milliseconds of time difference between each other, they are registered as a draw.
If it is not the case for you, you can replace all 8 function calls of buttondetect function with digitalRead, and everything will keep working.

Learnings -
Pushbuttons are glitchy as hell.
Use unsigned long data types whenever working with delay() or millis(), micros() etc.
analogRead on unconnected pin makes up for a fairly good randomSeed for random() fxn.
static variables dont change across different iterations of a loop.
use while loop with millis() instead of delay() as delay() is a blocking function.
