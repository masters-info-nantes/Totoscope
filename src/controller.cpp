#include "controller.h"

Controller::Controller()
{
    this->decomposer = new VideoDecomposer("Generique.mpeg",8);
    //decomposer->startProcessing();

}
