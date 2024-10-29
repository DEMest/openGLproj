#ifndef DISPLAY_H
#define DISPLAY_H

extern float x_angle, y_angle, x_translate, y_translate, z_translate;
extern bool show_grid, show_edges, show_polygons, smooth_shading, reset_pos;

void display();
void updateRotation();
void init();
void drawCube();
void drawSphere();
void setupLighting();

#endif