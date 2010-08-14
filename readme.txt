ofxBoost
=========
Allows you to use boost in openFrameworks.

Compiling boost on Windows
==========================
You can use the precompiled libraries for mingw/code::blocks, but when you want
to build Boost yourself follow these steps

- download the boost source


- I tried to compile boost on two computers, on one I simply used the 
windows console (cmd) the other one I created using "bash" from a cygwin 
installation...
- in the root of boost, run: bootstrap.bat
- run:  
./bjam.exe toolset=gcc target-os=windows --layout=versioned install

This created C:\Boost\
  

Compiling boost on Mac OSX
===========================
- Download boost_1_43_0 (http://sourceforge.net/projects/boost/files/boost/1.43.0/boost_1_43_0.tar.bz2/download)
$ bunzip2 boost_1_43_0.tar.bz2
$ tar -xvf boost_1_43_0.tar
$ cd boost_1_43_0
$ ./boostrap.sh
$ ./bjam --build-type=minimal \
	--layout=versioned \
	--macosx-version=10.6 \
	--without-regex \
	--without-mpi \
	--without-wave \
	--without-test \
	--without-python \
	--without-graph \
	--without-graph_parallel \
	--without-serialization \
	--without-signals \
	toolset=darwin \
	target-os=darwin \
	architecture=combined \
	address-model=32_64 \
	stage

Installing on Mac OSX (XCode)
=============================
- make sure that you use:
#undef check 
before including any of the boost .hpp files where you need those

- Add this to your search paths: ../../../addons_diederick/ofxBoost/src/lib/
- Add the static libs form the ofxBoost/lib/mac dir to your project by dragging
them on your project.


  