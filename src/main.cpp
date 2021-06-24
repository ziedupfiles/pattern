#include "include/basicinteraction.h"

int main (int argc, char** argv)
{
    Basic* manager = new Basic();
    manager->setValues();
    manager->spin();

}
