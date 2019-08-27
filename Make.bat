@echo off
title My Game
cls

echo ===================================
echo =                                 =
echo =          THE PRO SNAKE          =
echo =                                 =
echo ===================================
echo.

::Specify compiling path
echo Getting thing ready . . . 
echo.
cd C:\Users\Joaco\Desktop\Juego

::Removes old files
echo Removing old files . . . 
echo.
if exist build/Apple.o del build\Apple.o
if exist build/LoadObjects.o del build\LoadObjects.o
if exist build/Definitions.o del build\Definitions.o
if exist build/EstadoJuego.o del build\EstadoJuego.o
if exist build/Shape.o del build\Shape.o
if exist build/ShapeSphere.o del build\ShapeSphere.o
if exist build/main.o del build\main.o
if exist build/Menu.o del build\Menu.o
if exist build/EventsEngine.o del build\EventsEngine.o
if exist build/GraphicEngine.o del build\GraphicEngine.o
if exist build/GameEngine.o del build\GameEngine.o
if exist build/ScreenEngine.o del build\ScreenEngine.o
if exist build/Objeto.o del build\Objeto.o
if exist build/Snake.o del build\Snake.o
if exist build/tinystr.o del build\tinystr.o
if exist build/tinyxml.o del build\tinyxml.o
if exist build/tinyxmlerror.o del build\tinyxmlerror.o
if exist build/tinyxmlparser.o del build\tinyxmlparser.o
if exist build/Snake.exe del build\Snake.exe
if exist build/Earth.o del build\Earth.o
if exist build/Moon.o del buil\Moon.o
if exist build/Sun.o del build\Sun.o
if exist build/Mercury.o del build\Mercury.o
if exist build/Mars.o del build\Mars.o
if exist build/Jupiter.o del build\Jupiter.o
if exist build/Venus.o del buil\Venus.o
if exist build/Neptuno.o del build\Neptuno.o

::Build the game
echo Compiling Game . . . 

@echo on
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/Apple.cpp -o build/Apple.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/Earth.cpp -o build/Earth.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c  src/Moon.cpp -o  build/Moon.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c  src/Sun.cpp -o  build/Sun.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c  src/Mercury.cpp -o  build/Mercury.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c  src/Jupiter.cpp -o build/Jupiter.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c  src/Mars.cpp -o  build/Mars.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c  src/Venus.cpp -o  build/Venus.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c  src/Neptuno.cpp -o  build/Neptuno.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/LoadObjects.cpp -o build/LoadObjects.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/Definitions.cpp -o build/Definitions.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/GameState.cpp -o build/GameState.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/Shape.cpp -o build/Shape.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/ShapeSphere.cpp -o build/ShapeSphere.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/main.cpp -o build/main.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/Menu.cpp -o build/Menu.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/EventsEngine.cpp -o build/EventsEngine.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/GraphicEngine.cpp -o build/GraphicEngine.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/GameEngine.cpp -o build/GameEngine.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/ScreenEngine.cpp -o build/ScreenEngine.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/Objeto.cpp -o build/Objeto.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/Snake.cpp -o build/Snake.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/tinystr.cpp -o build/tinystr.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/tinyxml.cpp -o build/tinyxml.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/tinyxmlerror.cpp -o build/tinyxmlerror.o
g++ -Wextra -w -Wall -Ilib\SDL-1.2.15\include -Ilib\glut -Ilib\FreeImage -c src/tinyxmlparser.cpp -o build/tinyxmlparser.o
g++ -Llib\SDL-1.2.15\lib -Llib\glut -Llib\FreeImage -o Snake.exe build/Apple.o build/Earth.o build/Moon.o build/Sun.o build/Mercury.o build/Neptuno.o  build/Venus.o  build/Mars.o build/Jupiter.o build/LoadObjects.o build/Definitions.o build/GameState.o build/Shape.o build/ShapeSphere.o build/main.o build/Menu.o build/EventsEngine.o build/GraphicEngine.o build/GameEngine.o build/ScreenEngine.o build/Objeto.o build/Snake.o build/tinystr.o build/tinyxml.o build/tinyxmlerror.o build/tinyxmlparser.o -lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32 -lglut32 lib\SDL-1.2.15\lib\libSDLmain.a lib\SDL-1.2.15\lib\SDL_ttf.lib lib\SDL-1.2.15\lib\SDL_image.lib lib\SDL-1.2.15\lib\libSDL.dll.a lib\FreeImage\FreeImage.lib -mwindows
@echo off
echo.

if exist Snake.exe (
	echo Compiling successfully.
) else (
	echo Compiling failure.
)

::Pause
pause

::Exit
exit