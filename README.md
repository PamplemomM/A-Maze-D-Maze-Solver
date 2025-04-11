# **A-Maze-d**

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
_In case you are missing maze layout files of your own, you can find sample files inside of the `scripts` folder._

## 💰 **Bonuses** 💰

**This repository comes with many bonuses!**

---------------------------------------------------------------------------

### **Viewer**

The viewer acts as a visualizer for the A-Maze-d program, and reads its input data the exact same way as its counterpart.
This program and its source files are located inside of the `bonus` directory, but moving to this directory is not necessary.

To compile the viewer, make sure you are at the root of the project's repository, then run this command:
```bash
make viewer
```
This rule automatically moves the viewer's compiled binary (as well as a symbolic link to its `assets` directory) outside of the `bonus` directory.

Then, to execute the viewer, you can send your maze layout to it through the A-Maze-d program, like so:
```bash
./amazed < [FILE] | ./viewer
```

The viewer's usage can be displayed by executing it with the `-h` option:
```bash
./viewer -h
```

### **Maker**

The maker is an extension of the viewer, in which you get to build and export your own maze, using the beautiful graphical interface of the viewer.

To execute the maker, simply compile the viewer (as shown above), and use the `-m` option:
```bash
./viewer -m
```
_The controls for the maker are also documented in the viewer's usage_

---------------------------------------------------------------------------

### **Generator**

The *gen.sh* script, located at the root of the repository, lets you generate a new maze with however many robots and rooms you wish for.

To use it, execute the following command:
```bash
./gen.sh [NB_ROBOTS] [NB_ROOMS]
```
The script writes its result on the standard output, which makes it super easy to send it to the A-Maze-d program!

To do so, simply execute it as follows:
```bash
./gen.sh [NB_ROBOTS] [NB_ROOMS] | ./amazed
```

You can even pair this with the viewer, if you have it compiled:
```bash
./gen.sh [NB_ROBOTS] [NB_ROOMS] | ./amazed | ./viewer
```

---------------------------------------------------------------------------

## 🔎 **Tester** 🔎

Many tests were created for this project, ranging from unit tests to functional tests.

To compile and run the unit tests, simply use this command, at the root of the repository:
```bash
make test_run
```

For the functional tests, you can execute this bash script:
```bash
./tester.sh
```
_The output of the **error values tests** is stored in `tests/testerEresult`, and the **success values tests**' in `tests/testerSresult`, if you'd like to take a closer look._


## 🧹 **Cleaner** 🧹

After all those tests and compilations... The repository is looking like quite a mess, isn't it?

**Here comes the Super-Bash-Cleaner™!**

To cleanse this repository of all of its useless files, just execute the `clean.sh` script, located at the root of the repository:
```bash
./clean.sh
```
And your repository will be squeaky-clean in seconds!

<sup>📝 EPITECH project developed as part of the B-CPE-200 module by AntothP, Pathie and PamplemomM.</sup>
