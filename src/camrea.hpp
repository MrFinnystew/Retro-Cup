#pragma once

#include "printing.hpp"

class Camrea {
public:
    double zoom = 1;
    double x = 0;
    double y = 0;
    
    void zoomIn(float amount) {
        importantInfo("Increasing zoom by: " + std::to_string(amount) + "\n");
        zoom += amount;
        importantInfo("Zoom is now: " + std::to_string(zoom) + "\n");
    }
    
    void zoomOut(float amount) {
        importantInfo("Decreasing zoom by: " + std::to_string(amount) + "\n");
        zoom -= amount;
        importantInfo("Zoom is now: " + std::to_string(zoom) + "\n");
    }
};
