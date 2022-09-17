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


Some gameplay:
Basic coordinate functionality, pops clusters of balloons which are found using a depth-first search.
![bpop1](https://user-images.githubusercontent.com/113747039/190840824-c0ad0eb8-bcdd-481d-b39b-9236d859198e.png)
![bpop2](https://user-images.githubusercontent.com/113747039/190840825-13f786fd-0f1f-4e7e-8d33-d5d5f8242cc9.png)
![bpop3](https://user-images.githubusercontent.com/113747039/190840826-0bc9f042-cf85-4167-8ffa-2af815f8d413.png)

About to make a huge move!
![bpop4](https://user-images.githubusercontent.com/113747039/190840827-e8e8e57a-8d26-4168-a51c-b284477593b2.png)


After fixing SCORE code to display score instead of turn number:
![bpop5](https://user-images.githubusercontent.com/113747039/190840828-5c09d699-ab2d-45eb-8b13-eab8271a2af5.png)
