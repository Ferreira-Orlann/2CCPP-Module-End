// Porjet Fin Module.cpp : définit le point d'entrée de l'application.


#include <iostream>
#include "visual.hpp"

using namespace std;

int main() {
	cout << "Hello CMake." << sizeof(LayingGrass::CollisionEngine) << endl;
	LayingGrass::LayingGrassVisual visual = LayingGrass::LayingGrassVisual();
	while (visual.ShouldRender())
	{
		visual.ProcessInputs();
		visual.Render();
	}
	return 0;
}
