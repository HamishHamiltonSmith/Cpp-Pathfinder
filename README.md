# C++ Path-finding Algorithm


## What is it?

This is my take on a path-finding AI along with a graphical visualisation (SFML). Its goal is simple, find the shortest path from point A to point B. There are many effective and efficient path finding algorithms out there, this is not one of them. It can't necissarily determine the shortest path with 100% accuracy, however it mostly does (especially in mazes rather than open areas), and can do so much quicker than conventional algorithms. 

The idea is every tile on the map has a weight. Every AI "player" scans its adjacent (unocupied) squares and choses which to move to based on the ratio of these weights. In the begining the weights are initialised based on their distance from the endpoint, so if there is a simple path it will be found quickly. When an AI finds the endpoint, the generation is completed, the AI instance will then add to the weights of all tiles it used on its journey, making others more likely to follow in the next gen. ONLY the fastest AI to the end will have an effect, to encourage optimal routes. 

The map is stored as an array, which you can edit as you please to design your own maps, a word of warning - this was designed with mazes in mind - so open spaces can be problematic for the AI, whilst you will get strong results in the end it might take a little longer!


## Installation

To install please ensure that the SFML library is linked to the code. You can use CMake to build, or if you are using linux you can try installing SFML manually. If you chose to do this, the `comp.sh` build script can be used to link up the project and the code should work. 
