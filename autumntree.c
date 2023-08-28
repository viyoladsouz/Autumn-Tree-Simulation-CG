#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846

typedef struct {
    float x;
    float y;
    float size;
    float speed;
} FallingLeaf;
float boatX = 300.0f; // Initial X position of the boat
float boatSpeed = 2.0f; // Speed of the boat

#define MAX_LEAVES 50
FallingLeaf leaves[MAX_LEAVES];

float birdPositionX = 0.0f;  // X position of the bird
float wingAngle = 0.0f;      // Angle for wing movement

void drawBird(float birdX, float birdY) {
    // Draw the bird
    glColor3f(0.2f, 0.2f, 0.2f); // Set color to black

    // Bird body
    glBegin(GL_TRIANGLES);
    glVertex2f(birdX - 10.0f, birdY + 10.0f);  // Top vertex
    glVertex2f(birdX, birdY + 20.0f);          // Bottom left vertex
    glVertex2f(birdX + 10.0f, birdY + 10.0f);  // Bottom right vertex
    glEnd();

    // Bird wings
    glBegin(GL_TRIANGLES);
    glVertex2f(birdX, birdY + 10.0f);                  // Top vertex
    glVertex2f(birdX - 20.0f, birdY - wingAngle);      // Bottom left vertex
    glVertex2f(birdX + 20.0f, birdY - wingAngle);      // Bottom right vertex
    glEnd();
}

void drawBirds() {
    int numBirds = 4;
    float birdSpacing = 200.0f;

    for (int i = 0; i < numBirds; i++) {
        float birdX = birdPositionX + i * birdSpacing;
        drawBird(birdX, 100.0f);
    }
}

void updateWingAngle() {
    float wingSpeed = 5.0f;  // Adjust the speed of wing movement
    wingAngle = sin(birdPositionX * wingSpeed) * 20.0f;
}

void update() {
    // Update bird position
    birdPositionX += 1.0f;  // Adjust the bird's horizontal movement speed

    // Update wing angle for wing movement
    updateWingAngle();
}

// Function to draw a falling leaf
void drawLeaf(float x, float y, float size) {
    // Draw leaf as a pentagon
    glColor3f(0.8f, 0.7f, 0.0f); // Set color to orange

    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glBegin(GL_POLYGON);
    float angle = 72.0f; // Angle between each vertex of the pentagon
    float radius = size; // Calculate radius based on size

    for (int i = 0; i < 5; i++) {
        float theta = i * angle * (M_PI / 180.0f); // Convert degrees to radians
        float px = radius * cos(theta);
        float py = radius * sin(theta);
        glVertex2f(px, py);
    }
    glEnd();
    glPopMatrix();
}

void initFallingLeaves() {
    // Initialize the falling leaves at random positions and speeds
    for (int i = 0; i < MAX_LEAVES; i++) {
        leaves[i].x = (rand() % 600) - 500;
        leaves[i].y = 100.0f; // Adjusted initial y position to 0.0f
        leaves[i].size = (rand() % 10) + 5;
        leaves[i].speed = (rand() % 5) + 1;
    }
}

void drawFallingLeaves() {
    for (int i = 0; i < MAX_LEAVES; i++) {
        if (leaves[i].y < -400.0f) {
            // If a leaf has fallen below the ground, reset its position
            leaves[i].x = (rand() % 600) - 500;
            leaves[i].y = 100.0f; // Adjusted reset position to 0.0f
        }
        // Update the leaf's position based on its speed
        leaves[i].y -= leaves[i].speed;

        // Draw the leaf
        drawLeaf(leaves[i].x, leaves[i].y, leaves[i].size);
    }
}

float cloudPositionX = -200.0f; // Initial X position of the clouds

void drawCloud(float x, float y, float size) {
    // Draw cloud with white color
    glColor3f(1.0f, 1.0f, 1.0f);
    float radius = size / 2.0f; // Calculate radius based on size

    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 30) {
        float theta = i * (M_PI / 180.0f); // Convert degrees to radians
        float px = radius * cos(theta);
        float py = radius * sin(theta);
        glVertex2f(px, py);
    }
    glEnd();
    glPopMatrix();
}

void drawClouds() {
    float cloudSize = 80.0f;
    float cloudSpacing = 200.0f;
    float cloudY = 100.0f; // Adjust Y position of the clouds
    int numClouds = 4;

    // Calculate the initial X position for the first cloud in the straight line
    float startX = cloudPositionX - (cloudSpacing * (numClouds - 1) / 2);

    for (int i = 0; i < numClouds; i++) {
        float cloudX = startX + i * cloudSpacing;
        drawCloud(cloudX, cloudY, cloudSize);
    }

}

void drawPentagon(float x, float y, float size) {
    // Draw pentagon with green color
    glColor3f(1.0f, 0.5f, 0.1f);
    float angle = 72.0f; // Angle between each vertex of the pentagon
    float radius = 20;// Calculate radius based on size

    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 5; i++) {
        float theta = i * angle * (M_PI / 180.0f); // Convert degrees to radians
        float px = radius * cos(theta);
        float py = radius * sin(theta);
        glVertex2f(px, py);
    }
    glEnd();
    glPopMatrix();
}

void makeTree(float x, float y, float length, float angle, float width) {
    if (length < 1) {
        return;
    }

    glColor3f(0.5f, 0.35f, 0.05f);

    // Draw trunk
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y + length);
    glEnd();

    float newX = x;
    float newY = y + length;
    float newLength = length * 0.7f; // Reduce branch length

    glPushMatrix();
    glTranslatef(newX, newY, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    makeTree(0.0f, 0.0f, newLength, angle - 5, width * 0.9f); // Reduce branch width
    glPopMatrix();

    glPushMatrix();
    glTranslatef(newX, newY, 0.0f);
    glRotatef(-angle, 0.0f, 0.0f, 1.0f);
    makeTree(0.0f, 0.0f, newLength, angle - 5, width * 0.9f); // Reduce branch width
    glPopMatrix();

    // Draw pentagon at the end of the branch
    drawPentagon(newX, newY + newLength, width * 2.5f);
}

static void resize(int width, int height) {
    const float ar = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-400.0 * ar, 400.0 * ar, -400.0, 400.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            boatX -= boatSpeed; // Move the boat to the left
            break;
        case GLUT_KEY_RIGHT:
            boatX += boatSpeed; // Move the boat to the right
            break;
    }

    // Limit the boat's position within the window
    if (boatX < 175.0f)
        boatX = 175.0f;
    else if (boatX > 800.0f)
        boatX = 800.0f;

    glutPostRedisplay(); // Notify GLUT that the display needs to be redrawn
}
void drawBench(float x, float y, float width, float height) {
    // Draw the bench seat
    glColor3f(0.5f, 0.5f, 0.5f); // Set color to gray
    glRectf(x, y, x + width, y + height);

    // Draw the bench legs
    glColor3f(0.2f, 0.2f, 0.2f); // Set color to black
    glRectf(x - 5.0f, y, x, y + height);
    glRectf(x + width, y, x + width + 5.0f, y + height);
    glRectf(x, y - 5.0f, x + width, y);

    float legWidth = 10.0f;
    float legHeight = 30.0f;
    
    glColor3f(0.2f, 0.2f, 0.2f); // Set color to black
    glRectf(x - legWidth, y - legHeight, x, y);
    glRectf(x + width, y - legHeight, x + width + legWidth, y);
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Set the viewport to the bottom one-fourth part of the window
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    int quarterHeight = windowHeight / 4;
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), quarterHeight);

    // Draw grassy ground
    glColor3f(0.5f, 0.6f, 0.15f); // Set color to green
    glBegin(GL_QUADS);
    glVertex2f(-800.0f, 400.0f); // Bottom-left corner
    glVertex2f(800.0f, 400.0f); // Bottom-right corner
    glVertex2f(800.0f, -400.0f); // Top-right corner
    glVertex2f(-800.0f, -800.0f); // Top-left corner
    glEnd();


    // Draw pond
    glColor3f(0.3f, 0.3f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 400.0f); // Bottom-left corner
    glVertex2f(1000.0f, 600.0f); // Bottom-right corner
    glVertex2f(1000.0f, -800.0f); // Top-right corner
    glVertex2f(0.0f, -800.0f); // Top-left corner
    glEnd();

    glColor3f(0.5f, 0.6f, 0.15f); // Set color to green
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, -800.0f); // Bottom-left corner
    glVertex2f(300.0f, 400.0f); // Bottom-right corner
    glVertex2f(0.0f, 400.0f);
    glEnd();

     glBegin(GL_TRIANGLES);
    glVertex2f(0.9f, -200.0f); // Bottom-left corner
    glVertex2f(450.0f, 400.0f); // Bottom-right corner
    glVertex2f(0.0f, 400.0f);
    glEnd();


    // Reset the viewport to the full window
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

    // Draw tree
    glPushMatrix();
    glTranslatef(0.0f, -300.0f, 0.0f);
    makeTree(-195.5f,-50.0f, 170.0f, 30.0f, 10.0f); // Adjust length and width
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -300.0f, 0.0f);
    makeTree(-185.5f,-50.0f, 170.0f, 30.0f, 10.0f); // Adjust length and width
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -300.0f, 0.0f);
    makeTree(-190.5f,-50.0f, 170.0f, 30.0f, 10.0f); // Adjust length and width
    glPopMatrix();


    // Draw clouds
    glPushMatrix();
    glTranslatef(cloudPositionX, quarterHeight, 0.0f); // Move to the top one-fourth part of the window
    drawClouds();
    glPopMatrix();

    // Draw birds
    drawBirds();

    //Draw boat
    glPushMatrix();
   glTranslatef(boatX, -380.0f, 0.0f);

    glColor3f(0.5f,0.3f, 0.05f); 
    glBegin(GL_QUADS);
    glVertex2f(-45.0f, 0.0f); // Bottom-left corner
    glVertex2f(45.0f, 0.0f); // Bottom-right corner
    glVertex2f(85.0f, 50.0f); // Top-right corner
    glVertex2f(-85.0f, 50.0f); // Top-left corner
    glEnd();



    glColor3f(1.0f, 1.0f, 1.0f); // Set color to red
        glBegin(GL_TRIANGLES);
        glVertex2f(-45.0f, 45.0f); // Top-left corner
        glVertex2f(45.0f, 45.0f); // Top-right corner
        glVertex2f(0.0f, 120.0f); // Bottom center
        glEnd();

        glColor3f(0.5f, 0.3f, 0.1f); // Set color to brown
        glBegin(GL_LINES);
        glVertex2f(-45.0f, 60.0f); // Line start point
        glVertex2f(45.0f, 60.0f); // Line end point
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(0.0f, 40.0f); // Line start point (middle top of triangle)
        glVertex2f(0.0f, 120.0f); // Line end point (bottom center of triangle)
    glEnd();
 
    glPopMatrix();

    drawFallingLeaves();
    // Draw the bench
    drawBench(-700.0f, -300.0f, 200.0f, 50.0f);
    

    glutSwapBuffers();
    glFlush();
}

void idle() {
    update();
    glutPostRedisplay();
}

void updateCloudPosition(int value) {
    cloudPositionX += 4.0f; // Update cloud position

    // Reset cloud position when it reaches the right edge of the window
    if (cloudPositionX > 400.0f) {
        cloudPositionX = -400.0f;
    }

    glutPostRedisplay(); // Notify GLUT that the display needs to be redrawn
    glutTimerFunc(1, updateCloudPosition, 0); // Schedule the next update
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Autumn Tree");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutSpecialFunc(keyboard);

    glClearColor(0.6f, 0.9f, 1.50f, 1.0f); // Set background color to sky blue


    // Start updating cloud position
    glutTimerFunc(1, updateCloudPosition, 0);
    initFallingLeaves();
    glutMainLoop();

    return 0;
}
