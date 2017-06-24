CLIBS= 		-lm -lglut -lGL -lGLU -lX11 # 2014
#CPATHS=	-L/usr/X11R6/lib -I/usr/X11R6/include # 2011
CPATHS=		-I/usr/include -L/usr/lib # 2014
CFLAGS=		$(CPATHS)$(CLIBS)


helloclass:	helloclass.cpp
		g++ helloclass.cpp -o helloclass $(CFLAGS)

square:	square.cpp
		g++ square.cpp -o square $(CFLAGS)

box:	box.cpp
		g++ box.cpp -o box $(CFLAGS)

tryCircle:	tryCircle.cpp
		g++ tryCircle.cpp -o tryCircle $(CFLAGS)
		
circle:	circle.cpp
		g++ circle.cpp -o circle $(CFLAGS)

colorFun:	colorFun.cpp
		g++ colorFun.cpp -o colorFun $(CFLAGS)


cylinder:	cylinder.cpp
		g++ cylinder.cpp -o cylinder $(CFLAGS)

text:	text.cpp
		g++ text.cpp -o text $(CFLAGS)

lightAndMaterial1:	lightAndMaterial1.cpp
		g++ lightAndMaterial1.cpp -o lightAndMaterial1 $(CFLAGS)

lightAndMaterial2:	lightAndMaterial2.cpp
		g++ lightAndMaterial2.cpp -o lightAndMaterial2 $(CFLAGS)

hermiteCubic:	hermiteCubic.cpp
		g++ hermiteCubic.cpp -o hermiteCubic $(CFLAGS)

G4:	G4.cpp
		g++ G4.cpp -o G4 $(CFLAGS)

twoViewports:	twoViewports.cpp
		g++ twoViewports.cpp -o twoViewports $(CFLAGS)

map:	map.cpp
		g++ map.cpp -o map $(CFLAGS)

myanimate:	myanimate.cpp
		g++ myanimate.cpp -o myanimate $(CFLAGS)

merinG1:	merinG1.cpp
		g++ merinG1.cpp -o merinG1 $(CFLAGS)

merinG2:	merinG2.cpp
		g++ merinG2.cpp -o merinG2 $(CFLAGS)

merinG3:	merinG3.cpp
		g++ merinG3.cpp -o merinG3 $(CFLAGS)

squareOfWalls:	squareOfWalls.cpp
		g++ squareOfWalls.cpp -o squareOfWalls $(CFLAGS)

sphereInBox1:	sphereInBox1.cpp
		g++ sphereInBox1.cpp -o sphereInBox1 $(CFLAGS)

fonts:	fonts.cpp
		g++ fonts.cpp -o fonts $(CFLAGS)

myFonts:	myFonts.cpp
		g++ myFonts.cpp -o myFonts $(CFLAGS)

perspect1:	perspect1.cpp
		g++ perspect1.cpp -o perspect1 $(CFLAGS)

windows:	windows.cpp
		g++ windows.cpp -o windows $(CFLAGS)

menu:		menu.cpp
		g++ menu.cpp -o menu $(CFLAGS)

clean:
		rm *.o
