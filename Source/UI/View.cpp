#include "View.h"
#include <iostream>

using namespace std;

View::View() {

}

void View::update(double dt) {
    cout << "View update: " << dt << endl;
}
