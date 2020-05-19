#include <math.h>
#include <GL/glut.h>
#include "glm.h"
#include "imageloader.h"

static int RightShoulder = 0, RightElbow = 0, RightFingerBase = 0, RightFingerUp = 0 , RightHip =0,RightKnee=0,RightAnkle=0, LeftShoulder = 0, LeftElbow = 0, LeftFingerBase = 0, LeftFingerUp = 0 , LeftHip =0,LeftKnee=0,LeftAnkle=0,neck=0;
int windowWidth = 10000;
int windowHeight = 10000;
float aspect = float(windowWidth) / float(windowHeight);

double look_vector[] = {0,0,0};
double New_Vector[] = { 0,0,0};
double normalized[] = {0,0,0};
double RAngle1 = 0;
double RAngle2 = 0;
double UpAngle = 0;
double DownAngle = 0;
double speed = 0.1;

double eye[] = { 0, 0, 0 };
double center[] = { 0, 0, -1 };
double up[] = { 0, 1, 0 };

GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5,1.0 };
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0 };
// x , y, z, w
GLfloat light_position[] = {0.5,5.0, 0.0, 1.0 };
GLfloat lightPos1[] = {-0.5,-5.0,-2.0, 1.0 };
// Material Properties
GLfloat mat_amb_diff[] = {0.643, 0.753, 0.934, 1.0 };
GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat shininess[] = {100.0 };

GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture
GLuint _textureId1; //The id of the texture



void initRendering() {
    Image* image = loadBMP("floorA.bmp");
    _textureId = loadTexture(image);
    delete image;
    // Turn on the power
    glEnable(GL_LIGHTING);
    // Flip light switch
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    // assign light parameters
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    // Material Properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    GLfloat lightColor1[] = {1.0f, 1.0f,  1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
    glEnable(GL_NORMALIZE);
    //Enable smooth shading
    glShadeModel(GL_SMOOTH);
    // Enable Depth buffer
    glEnable(GL_DEPTH_TEST);
}
void screen_menu(int value)
{
    char* name = 0;

    switch (value) {
        case 'a':
            name = "floorA.bmp";
            break;
        case 'b':
            name = "floorB.bmp";
            break;
        case 'c':
            name = "floorC.bmp";
            break;
        case 'd':
            name = "floorD.bmp";
            break;

    }

    if (name) {
        Image* img = loadBMP(name);
        _textureId = loadTexture(img);
        delete img;
        glEnable(GL_LIGHTING);
        // Flip light switch
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        // assign light parameters
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
        // Material Properties
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
        GLfloat lightColor1[] = {1.0f, 1.0f,  1.0f, 1.0f };
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
        glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
        glEnable(GL_NORMALIZE);
        //Enable smooth shading
        glShadeModel(GL_SMOOTH);
        // Enable Depth buffer
        glEnable(GL_DEPTH_TEST);

    }

    glutPostRedisplay();
}


void display(void)
{


    glClearColor(0.0, 0.0, 0.0, 0.0);
    // Clear Depth and Color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
    glPushMatrix();
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
    //materials properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glPushMatrix();



    //floor
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
    glNormal3f(0.0,-1.0,0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.5,-0.25,2);
    glTexCoord2f(5.0f,  0.0f);
    glVertex3f(1.5,-0.25,2);
    glTexCoord2f(5.0f,  20.0f);
    glVertex3f(1.5,-0.25,-2);
    glTexCoord2f(0.0f, 20.0f);
    glVertex3f(-1.5,-0.25,-2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}



int main (int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("ROOM");
    initRendering();

    glMatrixMode(GL_PROJECTION);
    gluPerspective(60, aspect,0.1, 10);

    glutDisplayFunc(display);
    glutCreateMenu(screen_menu);
    glutAddMenuEntry("Textures", 0);
    glutAddMenuEntry("", 0);
    glutAddMenuEntry("floor_1", 'a');
    glutAddMenuEntry("floor_2", 'b');
    glutAddMenuEntry("floor_3", 'c');
    glutAddMenuEntry("floor_4", 'd');
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;

}
