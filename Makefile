all:
    g++ main.cpp libraries/src/glad.c -o main.exe -I libraries/include -L libraries/lib -lglfw3 -lgdi32 -lopengl32