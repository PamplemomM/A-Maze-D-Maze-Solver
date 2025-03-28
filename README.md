# **A-maze-d**

## ✨ **Description** ✨
**The A-Maze-d project consists in moving a set of robots through a maze, from its entrance to its exit.**

It reads data representing the layout of a maze: the disposition of its rooms, the number of robots in it, and the tunnels linking the rooms together.
After this, a pathfinding algorithm is ran through the maze in order to guide each robot to the end room efficiently.
Once all robots have reached the exit, the results are displayed, showing each set of moves that were executed, in their respective order.

## 🛠️ **Usage** 🛠️
To compile the program, open a terminal at the root of the project's repository, and type in this command:
```bash
make re
```

Then, to execute the program, you must send your maze layout as follows:
```bash
./amazed < [FILE]
```
*In case you are missing maze layout files of your own, you can find sample files inside of the `scripts` folder.*

## 💰 **Bonus** 💰
**This repository comes with a bonus viewer!**

It acts as a visualizer for the A-Maze-d program, and reads its input data the exact same way as its counterpart.
This viewer and its source files are located inside of the `bonus` directory, but moving to this directory is not necessary.

To compile the viewer, make sure you are at the root of the project's repository, then run this command:
```bash
make viewer
```
This rule automatically moves the viewer's compiled binary (as well as a symbolic link to its `assets` directory) outside of the `bonus` directory.

Then, to execute the viewer, you can send your maze layout to it through the A-Maze-d program, like so:
```bash
./amazed < [FILE] | ./viewer
```

Furthermore, the viewer's usage can be displayed by executing it with the `-h` option:
```bash
./viewer -h
```

<sup>📝 EPITECH project developed as part of the B-CPE-200 module by AntothP, Pathie and PamplemomM.</sup>
