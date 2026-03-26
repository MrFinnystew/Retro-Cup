


SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;
int pixelsPerGamePixels = 0;
bool debugMode = true;
int loopNumber = 0;
double currentFPS = 0.0;
string operatingSystem;
vector<double> largestFPSlist = {};
bool updateRenderingOnResize = true;
bool muted = false;
Audio audio(&muted);
Camrea camrea;
rectangle screenSize;
