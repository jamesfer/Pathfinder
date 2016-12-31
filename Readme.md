# Pathfinder
Pathfinder is a library that gives you access to a range of discrete path finding algorithms such as breadth-first, depth-first and A-star that can be easily integrated into your project. __Note: Pathfinder is a discrete path finding library. This means it is designed to find paths through a graph of nodes, not around free-form obstacles such as those found in video games.__

## Installation
Pathfinder is a header only library so simply clone the repository and then add the `Source` folder to your projects include paths.

## Concepts
### State
A state represents a particular arrangement of an object. A state can really be anything you need such as a City on a map, or an arrangement of a chessboard. As long as it is unique and you can identify neighbouring states that could be reached by an `Action`, then it can be a state.

### Action
An action is a move that links two states. If an object is in one state, then the action would cause it to transition to a new state. For instance, if I was standing in `CityA` then an action might be to `DriveToCityB` which would result in me being in `CityB`. In theory, each possible state would have a list of actions that can be performed, each of which would link to a new state; this is how the graph is formed. An action can have a particular cost associated with it which represents how much energy it would take to perform that action. Again, this can take many forms such as the distance between two cities, or the time taken to perform the action. The action cost is used by some algorithms to better estimate whether an action is desirable.

### Node
A node is a graphing term and you shouldn't really need to use it in code, but I include it hear because it is possible that I will mention a few times. In the library, nodes are used to keep track of a series of actions that resulted in a particular state and calculate things such as the path cost so far and the number of actions that were taken. Each node is paired with a state that represent the result of the series of actions.

## Using the library
When using the library with your own code, there are a few things that you will need to use. The first thing to do is to create your state class.

### Creating a state class
A state has 4 requirements:

### Creating an action class

### Using the searcher class

## Contributing
If you'd like to contribute simply create a pull request with your changes and I'll have a look at it.

## License
The contents of this repository is licensed under the MIT license.
