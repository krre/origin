#include "Entity.h"
#include <chrono>

EntityId Entity::counter = 0;

Entity::Entity(EntityId id) {
    if (id) {
        this->id = id;
    } else {
        /*
        // Get id as nanoseconds count from Epoch
        using namespace std::chrono;
        auto now = high_resolution_clock::now();
        this->id = duration_cast<nanoseconds>(now.time_since_epoch()).count();
        */
        this->id = counter++; // TODO: Replace by hash
    }
}
