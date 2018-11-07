#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include <exception>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main(int argc, char *argv[])
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    throw std::exception();
  }

  SDL_Window *window = SDL_CreateWindow("Triangle",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  if(!SDL_GL_CreateContext(window))
  {
    throw std::exception();
  }

  if(glewInit() != GLEW_OK)
  {
    throw std::exception();
  }

  VertexBuffer *positions = new VertexBuffer();
  positions->add(glm::vec3(0.0f, 0.5f, 0.0f));
  positions->add(glm::vec3(-0.5f, -0.5f, 0.0f));
  positions->add(glm::vec3(0.5f, -0.5f, 0.0f));

  VertexBuffer *colors = new VertexBuffer();
  colors->add(glm::vec4(0.92f, 0.54f, 0.13f, 1.0f));
  colors->add(glm::vec4(0.96f, 0.68f, 0.16f, 1.0f));
  colors->add(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

  VertexArray *shape = new VertexArray();
  shape->SetBuffer("in_Position", positions);
  shape->SetBuffer("in_Color", colors);

  ShaderProgram *shaderProgram = new ShaderProgram("../shaders/simple.vert", "../shaders/simple.frag");
  float angle = 0.0f;
 // shaderProgram->SetUniformVec4("in_Projection", glm::perspective(glm::radians(45.0f),
 //	  (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f));

  bool quit = false;

  while(!quit)
  {
    SDL_Event event = {0};

    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        quit = true;
      }
    }

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	shaderProgram->draw(shape);

    SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}