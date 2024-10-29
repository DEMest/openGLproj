#ifndef CONTROLS_H
#define CONTROLS_H

extern int last_x;
extern int last_y;

extern float camera_x;
extern float camera_y;
extern float camera_z;

extern float camera_yaw;
extern float camera_pitch;

extern float speed;

extern bool show_grid;
extern bool show_edges;
extern bool show_polygons;

#define M_PI 3.14159265358979323846

// config.h
#include <string>
#include <map>

extern std::map<char, std::string> hotkeyActions;

void parseConfig(const std::string& filename);
// config.h


void mouse_callback(int xpos, int ypos);
void moveCamera();
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);

#endif // CONTROLS_H
