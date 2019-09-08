# 3D Game - Snake

The objective of this app is to develop a variant of 3D Snake game. This game was released in the mid-70s, originally developed for the "Blockade" game console. In the game, the player leads a snake through a board or maze in search of food while having to dodge certain obstacles. Among other things, the game has the following features: 

- Multiple levels, easily customizable 

- Collision management 

- Event management and lighting

- Possibility to rotate the camera to change the observation point of view

- Makes use of 3D models and textures

![ezgif com-optimize (1)](https://user-images.githubusercontent.com/54251435/64484763-ced2d280-d1cb-11e9-953e-58f801f5278e.gif)


## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development.

### Prerequisites
Before you run the app make sure you are in a windows device and have the following installed:
 - MinGW (make sure to add `C:\MinGW\bin` to the path env variable). 

### Installing

A step by step series of examples that tell you how to get a development env running

Once you've cloned or downloaded the project, go to the project's folder and run the following commands:

```
$ make
```
By now the executable file (snake.exe) should have been created and you will have everything you need to run the app

> **NOTE:** The repo comes with a generated `snake.exe` file so you should be able to play the game as soon as you clone the repo. In case you change any file, then you should re compile the game runing the `make` command.

### Running

Since all the dynamic libraries are included in the repo, you should be able to run it simply by making double click in the `snake.exe` file
