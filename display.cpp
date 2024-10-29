#include <GL/glut.h>
#include "display.h"
#include "controls.h"

// Определение переменных для вращения и перемещения куба
float x_angle = 30.0f, y_angle = 45.0f;
float z_translate = -7.0f, x_translate = 0.0f, y_translate = 0.0f;

void setColorFromHex(int hexValue) {
    float r = ((hexValue >> 16) & 0xFF) / 255.0f;  // Извлечение красного компонента
    float g = ((hexValue >> 8) & 0xFF) / 255.0f;   // Извлечение зелёного компонента
    float b = (hexValue & 0xFF) / 255.0f;          // Извлечение синего компонента

    glColor3f(r, g, b);  // Установка цвета для OpenGL
}

void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = { 2.0, 4.0, 1.0, 0.0 };  // Позиция источника света
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };   // Диффузный свет (рассеянный)
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };  // Спекулярный свет (блики)
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    GLfloat ambient_light[] = { 0.7f, 0.7f, 0.7f, 1.0f };  // Более яркий фоновый свет
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glEnable(GL_LIGHT1);
    GLfloat light1_position[] = { -2.0, 4.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

}


void setupMaterial() {
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };   // Диффузное отражение объекта
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  // Спекулярные блики
    GLfloat mat_shininess[] = { 50.0 };               // "Гладкость" объекта для бликов
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

// Инициализация OpenGL
void init() {
    glEnable(GL_DEPTH_TEST);   // Включение теста глубины
    glEnable(GL_LIGHTING);     // Включение освещения
    glEnable(GL_LIGHT0);       // Включение источника света 0
    GLfloat light_position[] = { 3.0, 4.0, 3.0, 0.0 }; // Позиция источника
    GLfloat light_color[] = { 1.0, 1.0, 1.0, 1.0 };   // Цвет света
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
}
void drawAxes(float length) {
    glLineWidth(2.0f);  // Устанавливаем толщину линий для осей

    glBegin(GL_LINES);

    // Ось X (красная)
    glColor3f(1.0f, 0.0f, 0.0f);  // Красный цвет для оси X
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(length, 0.0f, 0.0f);

    // Ось Y (зелёная)
    glColor3f(0.0f, 1.0f, 0.0f);  // Зелёный цвет для оси Y
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, length, 0.0f);

    // Ось Z (синяя)
    glColor3f(0.0f, 0.0f, 1.0f);  // Синий цвет для оси Z
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, length);

    glEnd();

    glLineWidth(1.0f);  // Возвращаем толщину линий по умолчанию
}

// Функция для отрисовки куба
void drawCube() {
    setColorFromHex(0x606060);
    glBegin(GL_QUADS);
    GLfloat cube_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat cube_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_ambient);
    // Передняя грань
    glNormal3f(0.0f, 0.0f, 1.0f);  // Нормаль передней грани
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // Задняя грань
    glNormal3f(0.0f, 0.0f, -1.0f);  // Нормаль задней грани
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    // Верхняя грань
    glNormal3f(0.0f, 1.0f, 0.0f);  // Нормаль верхней грани
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // Нижняя грань
    glNormal3f(0.0f, -1.0f, 0.0f);  // Нормаль нижней грани
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Правая грань
    glNormal3f(1.0f, 0.0f, 0.0f);  // Нормаль правой грани
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Левая грань
    glNormal3f(-1.0f, 0.0f, 0.0f);  // Нормаль левой грани
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    glEnd();
}

void drawSphere() {
    glPushMatrix();
    glTranslatef(4.0f, 0.0f, 0.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutSolidSphere(1.0f, 40, 40);
    glPopMatrix();
}

void drawFloor(float size) {
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex3f(-size, -1.1f, -size);
    glVertex3f(size, -1.1f, -size);
    glVertex3f(size, -1.1f, size);
    glVertex3f(-size, -1.1f, size);

    glEnd();
}


void drawGrid(float size, float step) {
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);

    for (float i = -size; i <= size; i += step) {
        glVertex3f(-size, 0.0f, i);
        glVertex3f(size, 0.0f, i);
    }

    for (float i = -size; i <= size; i += step) {
        glVertex3f(i, 0.0f, -size);
        glVertex3f(i, 0.0f, size);
    }

    glEnd();
}

float angleX = 0.0f;
float angleY = 0.0f;
float rotationSpeed = 0.5f;

void rotateCube() {
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);
}

void updateRotation() {
    angleX += rotationSpeed;
    angleY += rotationSpeed;
    if (angleX > 360.0f) angleX -= 360.0f;
    if (angleY > 360.0f) angleY -= 360.0f;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(x_translate, y_translate, z_translate);
    glRotatef(x_angle, 1.0f, 0.0f, 0.0f);
    glRotatef(y_angle, 0.0f, 1.0f, 0.0f);

    setupLighting();
    setupMaterial();
    drawFloor(10.0f);
    //drawCube();
    drawSphere();
    drawAxes(4.0f);
    drawGrid(100.0f, 1.0f);
    rotateCube();
    drawCube();
    if (reset_pos) {
        x_angle = 30.0f, y_angle = 45.0f;
        z_translate = -7.0f, x_translate = 0.0f, y_translate = 0.0f;
    }

    glutSwapBuffers();
}
