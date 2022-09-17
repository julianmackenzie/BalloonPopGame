# BalloonPopGame
Command line Candy Crush clone

This was a project for CS211: Programming Practicum.

It was one of the harder projects I've ever had to do, not necessarily because the concepts we covered were too difficult, but
because there was a lot of confusion surrounding the makefile and how to properly put it together. Combined with some very poor
communication on the instructor's part and a project partner who was AWOL, I was pushed to my limits writing this game.

A lot of the framework was provided, the majority of my work was in bpop.c and bpgame.c. The complicated nature of it was threefold:
1. Working in C, which we had done very little of up to this point
2. Correctly implementing a method of navigating the linked lists, marking adjacent "balloons" in all four directions to be popped
  without overcounting (essentially a depth-first search, if I remember correctly)
3. Puzzling through the creation of the makefile, as the provided file was not functional, something that wasn't addressed by
  instructors until the project was nearly due (I mean it, the communication in that class was abysmal.)
  
Overall, it was a rewarding project that stretched me thin. While simply presented, it demonstrated my troubleshooting ability,
my tenacity in completing a group assignment on my own, and my understanding of char matrices.
