tetris:interface.o main.o Mino.o MinoI.o MinoT.o MinoJ.o MinoS.o MinoN.o MinoO.o MinoL.o generator.o timer.o recorder.o
	g++ -o tetris main.o interface.o Mino.o MinoI.o MinoT.o MinoJ.o MinoS.o MinoN.o MinoO.o MinoL.o generator.o timer.o recorder.o -lncurses

interface.o:interface.cpp interface.h timer.cpp timer.h
	g++ -c interface.cpp timer.cpp -lncurses
	
main.o:main.cpp interface.h
	g++ -c main.cpp -lncurses

Mino.o:Mino.cpp Mino.h coordinate.h
	g++ -c Mino.cpp

MinoI.o:MinoI.cpp Mino.h MinoI.h
	g++ -c MinoI.cpp
	
MinoN.o:MinoN.cpp
	g++ -c MinoN.cpp

MinoS.o:MinoS.cpp
	g++ -c MinoS.cpp

MinoL.o:MinoL.cpp
	g++ -c MinoL.cpp

MinoJ.o:MinoJ.cpp
	g++ -c MinoJ.cpp

MinoO.o:MinoO.cpp
	g++ -c MinoO.cpp

MinoT.o:MinoO.cpp
	g++ -c MinoT.cpp

generator.o:generator.cpp
	g++ -c generator.cpp -lncurses

timer.o:timer.cpp
	g++ -c timer.cpp 

recorder.o:recorder.cpp recorder.h
	g++ -c recorder.cpp -lncurses

