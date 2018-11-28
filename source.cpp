#include <iostream>
#include <vector>
#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

//define variables for viewport setup
GLint WIDTH = 800;
GLint HEIGHT = 800;
GLfloat fov = 90.0f;
GLfloat aspect = WIDTH/HEIGHT;
GLfloat near = 0.1f;
GLfloat far = 500.0f;

GLfloat viewPos = 20.0f;

GLfloat rot = 0;

//setup struct to hold vertex data
struct Vertex
{

    GLfloat vert[3];
    GLfloat norm[3];

};

//DrawShape will draw the vertices of one shape depending on the type provided
void DrawShape(int type, int latDiv, int longDiv)
{

    vector<Vertex> vertices;

    switch(type)
    {
        case(0): //cube
        {
            for( int i = 0; i < 24; i++)
            {
               vertices.push_back(Vertex());
            }

            //define the needed vertices for a cube
            vertices[0].vert[0] = -0.5; vertices[0].vert[1] = -0.5; vertices[0].vert[2] = -0.5;
            vertices[1].vert[0] = -0.5; vertices[1].vert[1] = -0.5; vertices[1].vert[2] = 0.5;
            vertices[2].vert[0] = -0.5; vertices[2].vert[1] = 0.5; vertices[2].vert[2] = 0.5;
            vertices[3].vert[0] = -0.5; vertices[3].vert[1] = 0.5; vertices[3].vert[2] = -0.5;
            vertices[4].vert[0] = 0.5; vertices[4].vert[1] = -0.5; vertices[4].vert[2] = -0.5;
            vertices[5].vert[0] = 0.5; vertices[5].vert[1] = -0.5; vertices[5].vert[2] = 0.5;
            vertices[6].vert[0] = 0.5; vertices[6].vert[1] = 0.5; vertices[6].vert[2] = 0.5;
            vertices[7].vert[0] = 0.5; vertices[7].vert[1] = 0.5; vertices[7].vert[2] = -0.5;

            //draw each side of the cube using the defined vertices
            glBegin(GL_QUADS);

            glColor3f( 0.6f, 0.6f, 0.6f );

            glNormal3f( -1.0f, 0.0f, 0.0f);            
            glVertex3fv( vertices[0].vert );//left
            glNormal3f( -1.0f, 0.0f, 0.0f); 
            glVertex3fv( vertices[1].vert );
            glNormal3f( -1.0f, 0.0f, 0.0f);  
            glVertex3fv( vertices[2].vert );
            glNormal3f( -1.0f, 0.0f, 0.0f); 
            glVertex3fv( vertices[3].vert );

            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3fv( vertices[4].vert );//right
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3fv( vertices[5].vert );
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3fv( vertices[6].vert );
            glNormal3f(1.0f, 0.0f, 0.0f);
            glVertex3fv( vertices[7].vert );

            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3fv( vertices[0].vert );//back
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3fv( vertices[4].vert );
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3fv( vertices[7].vert );
            glNormal3f(0.0f, 0.0f, -1.0f);
            glVertex3fv( vertices[3].vert );

            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3fv( vertices[1].vert );//front
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3fv( vertices[2].vert );
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3fv( vertices[6].vert );
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3fv( vertices[5].vert );

            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3fv( vertices[2].vert );//top
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3fv( vertices[3].vert );
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3fv( vertices[7].vert );
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3fv( vertices[6].vert );

            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3fv( vertices[0].vert );//bottom
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3fv( vertices[1].vert );
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3fv( vertices[5].vert );
            glNormal3f(0.0f, -1.0f, 0.0f);
            glVertex3fv( vertices[4].vert );

            glEnd();

            break;
        }

        case(1): //sphere
        {

            int vertCount = (latDiv - 1) * longDiv;

            for( int l = 0; l < vertCount; l++)
            {
                vertices.push_back(Vertex());
            }

            GLfloat curRadius, curTheta, curRho, deltaTheta, deltaRho, curX, curY, curZ;
            int curVert = 0;
            
            vertices[0].vert[0] = 0.0f; vertices[0].vert[1] = 1.0f; vertices[0].vert[2] = 0.0f;
            vertices[0].norm[0] = 0.0f; vertices[0].norm[1] = 1.0f; vertices[0].norm[2] = 0.0f;

            deltaTheta = (2.0f * 3.14159f) / latDiv;
            deltaRho = 3.14159f / longDiv;

            for( int i = 1; i < longDiv; i++ ){
                
                curRho = (3.14159f/2.0f) - i*deltaRho;
                curY = sin(curRho);
                curRadius = cos(curRho);

                for( int j = 1; j < latDiv; j++ ){

                    curTheta = j * deltaTheta;
                    curX = curRadius * cos(curTheta);
                    curZ = -curRadius * sin(curTheta);

                    vertices[curVert++].vert[0] = curX; vertices[curVert].vert[1] = curY; vertices[curVert].vert[2] = curZ;
                    vertices[curVert].norm[0] = curX; vertices[curVert].norm[1] = curY; vertices[curVert].norm[2] = curZ;

                }
            }

            vertices[vertCount].vert[0] = 0.0f; vertices[vertCount].vert[1] = -1.0f; vertices[vertCount].vert[2] = 0.0f;
            vertices[vertCount].norm[0] = 0.0f; vertices[vertCount].norm[1] = -1.0f; vertices[vertCount].norm[2] = 0.0f;

            glBegin(GL_TRIANGLE_FAN);
                glNormal3fv(vertices[0].norm);
                glVertex3fv(vertices[0].vert);
                for( int t = 0; t < latDiv; t++ ){
                    glNormal3fv( vertices[t].norm );
                    glVertex3fv( vertices[t].vert );

                }
            glEnd();

            int vertIndex;
            for ( int k = 0; k < longDiv - 2; k++){

                vertIndex = k * latDiv;
                glBegin(GL_QUAD_STRIP);
                    for(int n = 0; n < latDiv; n++){
                        
                        glNormal3fv(vertices[vertIndex+n].norm);
                        glVertex3fv(vertices[vertIndex+n].vert);

                        glNormal3fv(vertices[vertIndex+latDiv+n].norm);
                        glVertex3fv(vertices[vertIndex+latDiv+n].vert);

                    }

                    glNormal3fv(vertices[vertIndex].norm);
                    glVertex3fv(vertices[vertIndex].vert);

                    glNormal3fv(vertices[vertIndex+latDiv].norm);
                    glVertex3fv(vertices[vertIndex+latDiv].vert);
                glEnd();
            }
 
            glBegin(GL_TRIANGLE_FAN);
                glNormal3fv(vertices[vertCount].norm);
                glVertex3fv(vertices[vertCount].vert);
                for( int m = 0; m < latDiv; m++){
                    glNormal3fv(vertices[vertCount - m].norm);
                    glVertex3fv(vertices[vertCount - m].vert);
                }

                glNormal3fv(vertices[vertCount - 1].norm);
                glVertex3fv(vertices[vertCount - 1].vert);
            glEnd();

            break;
        }

        case(2): //cylinder
        {
            int vertCount = (latDiv - 1) * longDiv;

            for(int i = 0; i < vertCount; i++){
                vertices.push_back(Vertex());
            }

            vertices[0].norm[0] = 0.0f; vertices[0].norm[1] = 1.0f; vertices[0].norm[2] = 0.0f;
            vertices[0].vert[0] = 0.0f; vertices[0].vert[1] = 1.0f; vertices[0].vert[2] = 0.0f;

            vertices[1].norm[0] = 0.0f; vertices[1].norm[1] = -1.0f; vertices[1].norm[2] = 0.0f;
            vertices[1].vert[0] = 0.0f; vertices[1].vert[1] = -1.0f; vertices[1].vert[2] = 0.0f;

            for(int j = 2; j < vertCount; j = j+2){
                vertices[j].norm[0] = cos( (j-2)*2.0f*3.14159f/(vertCount/2));
                vertices[j].norm[1] = 0.0f;
                vertices[j].norm[2] = sin( (j-2)*2.0f*3.14159f/(vertCount/2));

                vertices[j].vert[0] = vertices[j].norm[0];
                vertices[j].vert[2] = vertices[j].norm[2];
                vertices[j].vert[1] = 1.0f;

                vertices[j+1].norm[0] = vertices[j].norm[0];
                vertices[j+1].norm[2] = vertices[j].norm[2];
                vertices[j+1].norm[1] = 0.0f;

                vertices[j+1].vert[0] = vertices[j].vert[0];
                vertices[j+1].vert[2] = vertices[j].vert[2];
                vertices[j+1].vert[1] = -1.0f;
            }

            glBegin(GL_TRIANGLE_FAN);
                glNormal3fv(vertices[0].norm);
                glVertex3fv(vertices[0].vert);

                for( int k = 2; k < vertCount; k= k+2){
                    glNormal3fv(vertices[k].norm);
                    glVertex3fv(vertices[k].vert);
                }
            glEnd();

            glBegin(GL_TRIANGLE_FAN);
                glNormal3fv(vertices[1].norm);
                glVertex3fv(vertices[1].vert);

                for( int k = 3; k < vertCount; k= k+2){
                    glNormal3fv(vertices[k].norm);
                    glVertex3fv(vertices[k].vert);
                }
            glEnd();

            glBegin(GL_TRIANGLE_STRIP);
                for( int l = 2; l < vertCount; l++){
                    glNormal3fv(vertices[l].norm);
                    glVertex3fv(vertices[l].vert);
                }
            glEnd();

            break;
        }

        case(3): //cone
        {

            int vertCount = (latDiv - 1) * longDiv;

            for(int i = 0; i < vertCount; i++){
                vertices.push_back(Vertex());
            }

            vertices[0].norm[0] = 0.0f; vertices[0].norm[1] = 1.0f; vertices[0].norm[2] = 0.0f;
            vertices[0].vert[0] = 0.0f; vertices[0].vert[1] = 1.0f; vertices[0].vert[2] = 0.0f;

            vertices[1].norm[0] = 0.0f; vertices[1].norm[1] = -1.0f; vertices[1].norm[2] = 0.0f;
            vertices[1].vert[0] = 0.0f; vertices[1].vert[1] = -1.0f; vertices[1].vert[2] = 0.0f;

            for(int j = 2; j < vertCount; j++){
                vertices[j].norm[0] = cos( (j-2)*2.0f*3.14159f/(vertCount));
                vertices[j].norm[1] = 0.0f;
                vertices[j].norm[2] = sin( (j-2)*2.0f*3.14159f/(vertCount));

                vertices[j].vert[0] = vertices[j].norm[0];
                vertices[j].vert[1] = -1.0f;
                vertices[j].vert[2] = vertices[j].norm[2];
            }

            glBegin(GL_TRIANGLE_FAN);
                glNormal3fv(vertices[0].norm);
                glVertex3fv(vertices[0].vert);

                for(int k = 2; k < vertCount; k++){
                    glNormal3fv(vertices[k].norm);
                    glVertex3fv(vertices[k].vert);

                }
            glEnd();

            glBegin(GL_TRIANGLE_FAN);
                glNormal3fv(vertices[1].norm);
                glVertex3fv(vertices[1].vert);

                for(int k = 2; k < vertCount; k++){
                    glNormal3fv(vertices[k].norm);
                    glVertex3fv(vertices[k].vert);

                }
            glEnd();

            break;
        }

    }

}

void DrawWalls(){

    //Floor
    glPushMatrix();
    glScalef(20.0f, 20.0f, 1.0f);
    glTranslatef(0.0f, 0.5f, -10.5f);
    DrawShape(0, 1, 1);
    glPopMatrix();

    //Left wall
    glPushMatrix();
    glScalef(1.0f, 20.0f, 20.0f);
    glTranslatef(-10.5f, 0.5f, 0.0f);
    DrawShape(0, 1, 1);
    glPopMatrix();

    //Right wall
    glPushMatrix();
    glScalef(20.0f, 1.0f, 20.0f);
    glTranslatef(0.0f, 0.5f, 0.0f);
    DrawShape(0, 1, 1);
    glPopMatrix();
}

void DrawBed(){

    //Draw
    glPushMatrix();
    glScalef(6.0f, 1.0f, 10.0f);
    glTranslatef(0.0f, 3.0f, 0.0f);
    DrawShape(0, 1, 1);
    glPopMatrix();

    //Draw
    glPushMatrix();
    glScalef(6.0f, 2.0f, 11.0f);
    glTranslatef( 0.0f, 1.0f, 0.0f );
    DrawShape(0, 1, 1);
    glPopMatrix();

    //Draw
    glPushMatrix();
    glScalef(6.0f, 4.0f, 1.0f);
    glTranslatef(0.0f, 1.0f, -4.5f);
    DrawShape(0, 1, 1);
    glPopMatrix();
}

void DrawStand(){

    //Draw legs
    glPushMatrix();
    glTranslatef(1.5f, 2.5f, 1.5f);
    glScalef(0.2f, 3.0f, 0.2f);
    DrawShape(2, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5f, 2.5f, 1.5f);
    glScalef(0.2f, 3.0f, 0.2f);
    DrawShape(2, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5f, 2.5f, -1.5f);
    glScalef(0.2f, 3.0f, 0.2f);
    DrawShape(2, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5f, 2.5f, -1.5f);
    glScalef(0.2f, 3.0f, 0.2f);
    DrawShape(2, 100, 100);
    glPopMatrix();

    //Draw top
    glPushMatrix();
    glTranslatef(0.0f, 5.0f, 0.0f);
    glScalef(3.0f, 0.25f, 3.0f);
    DrawShape(0, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);
    glScalef(3.0f, 0.25f, 3.0f);
    DrawShape(0, 1, 1);
    glPopMatrix();
}

void DrawFan(){

    //Draw base
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, 0.0f);
    glScalef(0.25f, 3.0f, 0.25f);
    DrawShape(2, 100, 100);
    glPopMatrix();

    //Draw stand
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glScalef(1.0f, 0.5f, 1.0f);
    DrawShape(2, 100, 100);
    glPopMatrix();

    //Draw blade mount
    glPushMatrix();
    glTranslatef(0.0f, 6.0f, 0.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    DrawShape(1, 200, 200);
    glPopMatrix();



}

void DrawBlades(){

    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    glScalef(0.1f, 1.0f, 0.2f);
    DrawShape( 1, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
    glScalef(0.1f, 1.0f, 0.2f);
    DrawShape( 1, 100, 100);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);
    glScalef(0.1f, 0.2f, 1.0f);
    DrawShape( 1, 100, 100);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1.0f);
    glScalef(0.1f, 0.2f, 1.0f);
    DrawShape( 1, 100, 100);
    glPopMatrix();

}

void DrawDrawers(){

    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f);
    glScalef(3.0f, 4.0f, 2.0f);
    DrawShape(0, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);
    glScalef(1.9f, 0.66666666667f, 2.1f);
    DrawShape(0, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);
    glScalef(1.9f, 1.33333333333f, 2.1f);
    DrawShape(0, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);
    glScalef(1.9f, 2.0f, 2.1f);
    DrawShape(0, 1, 1);
    glPopMatrix();
}

void DrawLamp(){

    //Draw base
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    glScalef(0.2f, 2.0f, 0.2f);
    DrawShape(2, 100, 100);
    glPopMatrix();

    //Draw lampshade
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, 0.0f);
    glScalef(1.0f, 1.0f, 1.0f);
    DrawShape(3, 100, 100);
    glPopMatrix();

    //Draw stand
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.0f);
    glScalef(1.0f, 0.2f, 1.0f);
    DrawShape(2, 100, 100);
    glPopMatrix();


}

void init(){
    //Initialize render options
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    //define materials properties
    GLfloat mat_ambient [] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat mat_diffuse [] = {0.6f, 0.6f, 0.6f, 1.0f};
    GLfloat mat_specular [] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess [] = {50.0f};

    //Bind material properties to pipeline
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    //Define scene lighting
    GLfloat lightIntensity [] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat light_position [] = {0.0f, 6.0f, 6.0f, 0.0f};
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, lightIntensity);

}
void display()
{   

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspect, near, far);
    gluLookAt(viewPos, viewPos, viewPos, -10.0f, 0.0f, -10.0f, 0.0f, 1.0f, 0.0f);



    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();    

    //Use draw functions to draw room scene
    glPushMatrix();
    //glRotatef(rot, 0.0f, 1.0f, 0.0f); 
    //DrawShape(2, 200, 200);
    //glutSolidTeapot(1.0f); //This is strictly for testing lighting and scene
    DrawWalls();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.0f, 0.0f, -5.5f);
    DrawBed();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -8.5f);
    DrawStand();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.0f, 0.0f, -9.0f);
    DrawDrawers();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 5.0f, -8.5f);
    DrawLamp();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.0f, 0.0f, 7.0f);
    DrawFan();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.75f, 6.0f, 7.0f);
    glRotatef(rot, -1.0f, 0.0f, 0.0f);
    DrawBlades();
    glPopMatrix();


    glutSwapBuffers();

    //Increment rotation variable for fan blades
    if( rot >= 360.0f )
        rot = 0.0f;

    rot+=5.0f;
}

void myMouse(int button, int state, int x, int y)
{
  switch (button) {
     //On left click, zoom out
     case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            viewPos -= 2.0f;
            glutPostRedisplay(); // draw it again
        }
        break;
     //On middle click, zoom in
     case GLUT_MIDDLE_BUTTON:
        if (state == GLUT_DOWN) {
            viewPos += 2.0f;
            glutPostRedisplay(); // draw it again
        }
        break;
     //On right click, exit program
     case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
           exit (-1);
        break;
     default:
        break;
  }
}



int main(int argc, char **argv)
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( WIDTH, HEIGHT );
    glutCreateWindow( "Bedroom Scene" );
    init();
    glutDisplayFunc( display );
    glutIdleFunc( display);
    glutMouseFunc( myMouse );
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glutMainLoop();

    return 0;

}
