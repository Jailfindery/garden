## garden Readme

### Introduction
`garden` is a control program for DotSlashGarden, an automated gardening project. The goal of DotSlashGarden is to create an indoor hydrogarden that requires little to no human intervention. `garden` allows for the control and customization of the automated systems (e.g. lighting, aeration pumps, pH monitoring).

### dnc (Double New Curses)
`dnc` is a sub-project of `garden` which provides a text user interface for `garden`'s menu system. It is an object-oriented reimplementation of `ncurses`. For more information on `dnc`, see the [dnc Overview](https://github.com/Jailfindery/garden/wiki/Using-dnc).

### jailket (Jailfindery's Socket Implementation)
`jailket` is another sub-project of garden which provides an implementation for socket communication. It is a wrapper for the Berkeley sockets API. For more information on `jailket`, see the [jailket Overview](https://github.com/Jailfindery/garden/wiki/jailket-Overview).

### Prerequisites
Prerequisites to compile and run `garden` include:
* GNU/Linux-based operating system (specifically [Raspbian](http://raspbian.org/))
* A compiler which supports C++11
* `ncurses` libraries
* Berkeley sockets API
* `dnc` shared library (see [Including dnc](https://github.com/Jailfindery/garden/wiki/Using-dnc#including-dnc) for more information)

### Documentation
Documentation for `garden` can be found at the [garden Wiki](https://github.com/Jailfindery/garden/wiki).

### Project Information
DotSlashGarden was started on July 2012. The blog for DotSlashGarden, which includes more information about `garden`, can be found at [dotslashgarden.blogspot.ca](http://dotslashgarden.blogspot.ca).

### Licensing
`garden` is licensed under the GNU General Public License v3.

`garden` also contains source code from `bottlerocket`, which is licensed under the GNU Lesser General Public License v2.

More licensing information can be found in the respective source code files.

### Author
This software was written by Joshua Schell <joshua.g.schell@gmail.com>.

