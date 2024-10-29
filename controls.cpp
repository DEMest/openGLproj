#include "controls.h"
#include "display.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <map>
#include <string>

bool wasdUD[6] = {false, false, false, false};
bool show_grid = true;
bool show_edges = false;
bool show_polygons = false;
bool smooth_shading = false;
bool reset_pos = false;

float camera_x = 0.0f;
float camera_y = 0.0f;

float maxSpeed = 0.3f;
float acceleration = 0.002f;
float currentSpeed = 0.0f;

std::map<char, std::string> hotkeyActions;

void moveCamera() {
    if (wasdUD[0] || wasdUD[1] || wasdUD[2] || wasdUD[3]) {
        while (currentSpeed < maxSpeed) {
            currentSpeed += acceleration;
        }
    }
    if (wasdUD[0]) {
        y_translate -= currentSpeed;
    }
    if (wasdUD[2]) {
        y_translate += currentSpeed;
    }
    if (wasdUD[1]) {
        x_translate += currentSpeed;
    }
    if (wasdUD[3]) { 
        x_translate -= currentSpeed;
    }
}

//void motion(int x, int y) {
//    if (last_x == -1 || last_y == -1) {
//        // Инициализация предыдущей позиции мыши
//        last_x = x;
//        last_y = y;
//    }
//
//    // Рассчитываем смещение курсора
//    int dx = x - last_x;
//    int dy = y - last_y;
//
//    // Обновляем углы поворота камеры с учётом чувствительности
//    y_angle += dx * sensitivity;
//    x_angle += dy * sensitivity;
//
//    // Обновляем последнюю позицию мыши
//    last_x = x;
//    last_y = y;
//
//    glutPostRedisplay();
//}
//
//// Обработка нажатия мыши (при необходимости)
//void mouse(int button, int state, int x, int y) {
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        glutSetCursor(GLUT_CURSOR_NONE);  // Скрываем курсор
//    }
//}

//void mouse_callback(int xpos, int ypos) {
//    static bool firstMouse = true;
//    if (firstMouse) {
//        last_x = xpos;
//        last_y = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - last_x;
//    float yoffset = last_y - ypos; // Перевёрнутое значение для Y
//    last_x = xpos;
//    last_y = ypos;
//
//    float sensitivity = 0.1f; // Скорость мыши
//    xoffset *= sensitivity;
//    yoffset *= sensitivity;
//
//    camera_yaw += xoffset;
//    camera_pitch += yoffset;
//
//    // Ограничение по углу наклона
//    if (camera_pitch > 89.0f)
//        camera_pitch = 89.0f;
//    if (camera_pitch < -89.0f)
//        camera_pitch = -89.0f;
//
//    // Обновляем вектор направления камеры
//    float frontX = cos(radians(camera_yaw)) * cos(radians(camera_pitch));
//    float frontY = sin(radians(camera_pitch));
//    float frontZ = sin(radians(camera_yaw)) * cos(radians(camera_pitch));
//    cameraFront = normalize(vec3(frontX, frontY, frontZ));
//}

void keyboard(unsigned char key, int x, int y) {
    key = toupper(key);

    if (hotkeyActions.find(key) != hotkeyActions.end()) {
        std::string action = hotkeyActions[key];

        if (action == "MOVE_FORWARD") {
            wasdUD[0] = true;
            acceleration = 0.002f;
        }
        else if (action == "MOVE_BACKWARD") {
            wasdUD[2] = true;
        }
        else if (action == "MOVE_LEFT") {
            wasdUD[1] = true;
        }
        else if (action == "MOVE_RIGHT") {
            wasdUD[3] = true;
        }
        else if (action == "TOGGLE_GRID") {
            show_grid = !show_grid;
        }
        else if (action == "TOGGLE_EDGES") {
            show_edges = !show_edges;
        }
        else if (action == "TOGGLE_POLYGON_VIEW") {
            show_polygons = !show_polygons;
            if (show_polygons) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }
        else if (action == "TOGGLE_SMOOTH_SHADING") {
            smooth_shading = !smooth_shading;
            if (smooth_shading) {
                glShadeModel(GL_SMOOTH);
            }
            else {
                glShadeModel(GL_FLAT);
            }
        }
        else if (action == "TOGGLE_RAY_TRACING") {
            
        }
        else if (action == "RESET_POSITION") {
            reset_pos = true;
        }
    }
    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y) {
    key = toupper(key);

    if (hotkeyActions.find(key) != hotkeyActions.end()) {
        std::string action = hotkeyActions[key];
        if (action == "MOVE_FORWARD") wasdUD[0] = false;
        else if (action == "MOVE_BACKWARD") wasdUD[2] = false;
        else if (action == "MOVE_LEFT") wasdUD[1] = false;
        else if (action == "MOVE_RIGHT") wasdUD[3] = false;
        else if (action == "RESET_POSITION")  reset_pos = false;
    }
}
