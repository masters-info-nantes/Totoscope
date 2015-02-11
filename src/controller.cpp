#include "controller.h"

Controller::Controller()
{
    this->decomposer = new VideoDecomposer("Generique.MOV",8);
    //decomposer->startProcessing();

}
