#include "Main.h"
class Example2 : Object
{
    std::string id = "example2";
    void Start(sf::RenderWindow *window)
    {
        // Pour activer/désactiver l'object (sans le détruire)
        // FindObject("example")->Active = true/false;
    }
};
Example2 *example2 = new Example2;