#include <stdio.h>

#include <obj/info.h>
#include <obj/load.h>

int main(int argc, char* argv[])
{
  Model model;

  load_model(&model, "cat.obj");
  print_model_info(&model);
  
  return 0;
}