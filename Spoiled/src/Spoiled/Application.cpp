#include <iostream>
#include <Spyen/Spyen.h>

int main() {
	Spyen::Window window;
	window.Init("Spyen", 800, 600);

	while(window.IsOpen()){
		// Do stuff
	}
	window.Destroy();
    return 0;
}