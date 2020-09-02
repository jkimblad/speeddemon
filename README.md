# speeddemon
Small framework to do timing measurements on c++ code with the purpose to find where time is best spent trying to optimize code.

## Build instructions

```
mkdir bin
cd bin
cmake ..
make
```
## Usage

Speeddemon works by the user adding timestamps throughout the code. Speeddemon uses this to build a control flow graph (CFG) keeping track of the execution times between each node.

Example:
```
Speeddemon s = Speeddemon();
s.init();

while(true) {
  s.time_stamp();
  // Code block 1

  s.time_stamp();
  // Code block 2

  s.time_stamp();
  // Code block 3
}
```

The speedemon object traps any kill signals sent to the program and prints the results before exiting when a SIGINT is sent (ctrl+c).

