#include "Example2.h"
void Example2::Update(sf::RenderWindow *window, float deltaTime)
{
    auto example1 = (Example1 *)FindObject("example1");
    SetActive(example1, 0);
    DestroyObject(example1);
}
auto Example2InstantiateAtStart = new Example2;