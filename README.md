# C++ Path-finding Algorithm

![GitHub](https://img.shields.io/github/license/HamishHamiltonSmith/Cpp-Pathfinder)

An evolutionary path-finding alogorithm and visualisation written in C++.
***This is an older repo of mine - the code may not be high quality***

+ [Installation](#installation)
+ [Dependencies](#dependencies)
+ [How it works and usage](#the-algorithm)
+ [Liscence](#liscence)



## Installation

To install first create a build directory in `src` using:

  `mkdir build`
  
Then move to it and build the project using cmake:

  `cmake ../` and then
  `make`

If you are using linux, [SFML](https://github.com/SFML/SFML) requires you to install **some [dependencies](#dependencies)**.
You can download them with your chosen package manager (eg: *apt*) - all common package managers should be fine.

You can run the program by **executing the path-finder executable that is created**.

## Dependencies

This project uses [SFML](https://github.com/SFML/SFML). CMake will handle the installation of that for you, but you are required to install a few small SFML dependencies. These can be found [here](https://github.com/SFML/SFML#external-libraries-used-by-sfml).


## The Algorithm

### Basic Usage

This project visualises a path-finding algorithm I have been working on, you can create diferent maps, and specify start and end positions and see a visualisation of the alorithm at work - determining optimal paths to get from point A to point B - this algorithm is built with speed in mind.

In order to create new maps you can modify the map stored in main.cpp - and expand it as you wish. **Remember** to specify startPos, endPos positions in respective variables aswell as adding them to the map. Here is the map key:

+ `0` - An empty space
+ `1` - A filled space
+ `2` - The endpoint
+ `3` - The startpoint

The algorithm I designed for this is particulary advantageous and efficient with larger areas - and is **progressive** meaning you can either sacrifice some speed for accuracy, or get paths which may be less optimal, but much faster than algorithms such as A*. The algorithm works best however with maze-like constricted maps.

For smaller, open maps - I don't recommend use.

There are many parameters you can tune in order to achieve diferent things, such as:

- The number of AIs that spawn
- The max number of steps an AI can take before a new generation is formed
- The distance gradient (see algorithm specification)
- Success weight influence
- Wave end options 


### How it works

Now let's get on to the insteresting stuff, how does the algorithm actually work?
It all starts with a weighting map - basically each point on the map has a weight - that
influences how likely an AI instance is to move to that square. This weights map is initially 
determined based **slightly** on **how far a given square is from the enpoint**. These weights
are fairly minor though as to ensure creative paths are also checked. On screen - you will be 
able to see the weights of the map through the colours of each square. 

At the start of each wave - a group of AI instances are spawned - they observe adjacent squares
and pick one at a non-uniform random distrubution based on each square's weights. Iniitally AI
movement is largely random - but if it nears the endpoint it will hone in exponentially. 
Note that an AI is very unlikely to visit a square it has already been on.

When an AI reaches the endpoint, all positions it was at have their weights increased - and a new
AI generation is spawned. After a positions weight is high enough; it turns an entirely new shade - 
to indicate it is an effecient waypoint - the highest shade is purple.

As this process repeats - more and more AIs follow sucessfull paths which can help to refine shortcuts,
since only the most sucesfully AI influences weights - only the best of the best routes stay prominent.
There are always however some AI that continue to move to other areas in search of alternitave roots.

You can also limit the amount of steps an AI can take if you want to enforce the most optimal path is 
taken, but I don't reccomend doing this. 

Those are the basics!


## Liscence

>   Licensed under the Apache License, Version 2.0 (the "License");
>   you may not use this file except in compliance with the License.
>   You may obtain a copy of the License at
>
>       http://www.apache.org/licenses/LICENSE-2.0
>
>   Unless required by applicable law or agreed to in writing, software
>   distributed under the License is distributed on an "AS IS" BASIS,
>   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
>   See the License for the specific language governing permissions and
>   limitations under the License.
