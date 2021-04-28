#include "MyGLWidget.h"
#include "ext/matrix_transform.hpp"
#include "fwd.hpp"
#include "qnamespace.h"
#include "trigonometric.hpp"
#include "vector_relational.hpp"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
    setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
    scale = 1.0;
    xMove = 0;
    yMove = 0;
    deltaA = M_PI / 180;
}

MyGLWidget::~MyGLWidget ()
{
    if (program != NULL)
        delete program;
}

void MyGLWidget::initializeGL ()
{
    // Cal inicialitzar l'ús de les funcions d'OpenGL
    initializeOpenGLFunctions();  
    glEnable (GL_DEPTH_TEST);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
    carregaShaders();
    creaBuffers();
    carregaBuffers();

    init_camera();

    projectTransform();
    viewTransform();
}

void MyGLWidget::init_camera(){

    glm::vec3 min (-2.5,0,-2.5);
    glm::vec3 max (2.5,4,2.5);
    
    radi = distance(min, max) / 2;
    
    centre = (max + min) / 2.0f; //**

    fovini = fov = M_PI/3;

    znear = radi;
    zfar  = radi*3;
    raw   = (float) width()/height();

    // perspectiva
    OBS = centre + glm::vec3(0,0, radi*2);
    VRP = centre;
    UP  = glm::vec3(0,1,0);

    // ortho
    top    = radi;
    bottom = -radi;
    right  = radi;        
    left   = -radi;        


    // euler
    psi   = 0;
    phi   = 0;
    theta = 0;
}

void MyGLWidget::paintGL () 
    {
        // Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
    GLint vp[4];
    glGetIntegerv (GL_VIEWPORT, vp);
    ample = vp[2];
    alt = vp[3];
#endif

    // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
    // useu els paràmetres que considereu (els que hi ha són els de per defecte)
    glViewport (0, 0, ample, alt);

    // Esborrem el frame-buffer
    glClear (GL_COLOR_BUFFER_BIT);


    // Activem el VAO per a pintar la caseta 
    modelTransformTerra();
    glBindVertexArray (VAO_terra);
    glDrawArrays(GL_TRIANGLES, 0, 9);

    modelTransformHomer();
    glBindVertexArray(VAO_Homer);
    glDrawArrays(GL_TRIANGLES, 0, m.faces().size()*3);

}

void MyGLWidget::modelTransformTerra () 
{
    glm::mat4 transform (1.0f);
    transform = glm::scale(transform, glm::vec3(scale));
    transform = glm::scale(transform, glm::vec3(2.5));
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(1,0,0));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
    glBindVertexArray (0);

}

void MyGLWidget::modelTransformHomer () 
{
    // Matriu de transformació de model
    glm::mat4 transform (1.0f);
    transform = glm::rotate(transform, glm::radians(rotate), glm::vec3(0.0, 1.0, 0.0));
    transform = glm::scale(transform, glm::vec3(scale));

    transform = glm::scale(transform, glm::vec3(4/(PmaxP.y-PminP.y),4/(PmaxP.y-PminP.y),4/(PmaxP.y-PminP.y)));
    transform = glm::translate(transform, glm::vec3(-((PminP.x+PmaxP.x)/2), -(PminP.y), -((PminP.z+PmaxP.z)/2)));

    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
    glBindVertexArray (0);
}

void MyGLWidget::resizeGL (int w, int h) 
{
    ample = w;
    alt = h;
    raw = float(w) / float(h);

    if ( not ortho ){

        if (raw < 1.0)
            fov = 2.0*atan( tan(fovini/2) / raw );
        else
            fov = fovini;

    } else { 
        if (raw < 1.0)
        {
            top = radi / raw;
            bottom = -radi / raw ;
        }
        else {
            left = -radi * raw;
            right = radi * raw;
        }
    }

    projectTransform();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
    makeCurrent();
    switch (event->key()) {
        case Qt::Key_S:  // escalar a més gran
            scale += 0.05;
            break;
                        
        case Qt::Key_D:  // escalar a més petit
            scale -= 0.05;
            break;
                        
        case Qt::Key_R:  // escalar a més petit
            rotate += 45;
            break;

        case Qt::Key_O:  // escalar a més petit
            if (ortho) ortho = false;
            else ortho = true;
            break;

        case Qt::Key_Z:  // zoomin
            //fov -= 0.05;
            top -= 0.05;
            right -= 0.05;
            left  += 0.05;
            bottom += 0.05;
            break;
        case Qt::Key_X:  // zoomout
            //fov += 0.05;
            top += 0.05;
            right += 0.05;
            left  -= 0.05;
            bottom -= 0.05;
            break;
        default:
            event->ignore();
            break;
    }
    update();
    projectTransform();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    makeCurrent();
    
    if (e->buttons() == Qt::LeftButton){ 
        if (!( e->modifiers() & ( Qt::ShiftModifier | Qt::AltModifier | Qt::ControlModifier ))){
            if (e->x() > xMove){
                std::cout << "left to right" <<std::endl;
                psi -= 0.1;
            }
            if (e->x() < xMove){
                std::cout << "right to left" <<std::endl;
                psi += 0.1;
            }
            if (e->y() > yMove){
                std::cout << "bottom to top" <<std::endl;
                theta += 0.1;
            }
            if (e->y() < yMove){
                std::cout << "top to bottom" <<std::endl;
                theta -= 0.1;
            }
            
        }
        if (e->modifiers() & (Qt::ShiftModifier))
        {
            if (e->y() > yMove){
                std::cout << "zoomin" <<std::endl;
                top -= 0.1;
                right -= 0.1;
                left  += 0.1;
                bottom += 0.1;
            }
            if (e->y() < yMove){
                std::cout << "zoomout" <<std::endl;
                top += 0.1;
                right += 0.1;
                left  -= 0.1;
                bottom -= 0.1;
            }
        }
        xMove = e->x();
        yMove = e->y();
        viewTransform();
        projectTransform();
        update();
    }
}


void MyGLWidget::carregaBuffers()
{
    glGenVertexArrays(1, &VAO_Homer);
    glBindVertexArray(VAO_Homer); 

    m.load("../models/Patricio.obj");

    float xmax, xmin, ymax, ymin, zmax, zmin;
    xmax = xmin = m.vertices()[0];
    ymax = ymin = m.vertices()[1];
    zmax = zmin = m.vertices()[2];

    for (unsigned int i = 3; i < m.vertices().size(); i+=3) {

        if( m.vertices()[i] < xmin )
        {
            xmin = m.vertices()[i];

        }
        if( m.vertices()[i] > xmax )
        {
            xmax = m.vertices()[i];

        } 
        if( m.vertices()[i+1] < ymin )
        {
            ymin = m.vertices()[i+1];

        }
        if( m.vertices()[i+1] > ymax )
        {
            ymax = m.vertices()[i+1];

        }
        if( m.vertices()[i+2] < zmin )
        {
            zmin = m.vertices()[i+2];

        }
        if( m.vertices()[i+2] > zmax )
        {
            zmax = m.vertices()[i+2];

        }
    }

    PmaxP = glm::vec3(xmax, ymax, zmax);
    PminP = glm::vec3(xmin, ymin, zmin);

    std::cout<<"PminP: "<<PminP.x<<" , "<<PminP.y<<" , "<<PminP.z<<std::endl;
    std::cout<<"PmaxP: "<<PmaxP.x<<" , "<<PmaxP.y<<" , "<<PmaxP.z<<std::endl;
    std::cout<<"Patricio's Size: "<<PmaxP.y-PminP.y<<std::endl;

    GLuint VBO_Homer;
    glGenBuffers(1, &VBO_Homer);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m.faces().size()*3*3, m.VBO_vertices(), GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    GLuint VBO_Homer_color;
    glGenBuffers(1, &VBO_Homer_color);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer_color);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m.faces().size()*3*3, m.VBO_matdiff(), GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);
}

void MyGLWidget::creaBuffers () 
{
    // Dades de la caseta
    // Dos VBOs, un amb posició i l'altre amb color
    glm::vec3 posicio[6] = {
        glm::vec3(-1.0, 1.0, 0),
    	glm::vec3(1.0, -1.0, 0),
    	glm::vec3(1.0, 1.0, 0),
    	glm::vec3(-1.0, -1.0, 0),
    	glm::vec3(1, -1, 0),
    	glm::vec3(-1, 1, 0)
    }; 

    glm::vec3 color[6] = {
        glm::vec3(0.4,0.4,0),
        glm::vec3(0.4,0.4,0),
        glm::vec3(0.4,0.4,0),
        glm::vec3(0.4,0.4,0),
        glm::vec3(0.4,0.4,0),
        glm::vec3(0.4,0.4,0)
    };

    // Creació del Vertex Array Object per pintar
    glGenVertexArrays(1, &VAO_terra);
    glBindVertexArray(VAO_terra);

    GLuint VBO_terra[2];
    glGenBuffers(2, VBO_terra);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_terra[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(posicio), posicio, GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_terra[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

    // Activem l'atribut colorLoc
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    glBindVertexArray (0);
}



void MyGLWidget::projectTransform () {
    // glm::perspective (FOV en radians, ra window, znear, zfar)
    //printf("%f\n", fov);
    //printf("%f\n", raw);
    //printf("%f\n", znear);
    //printf("%f\n", zfar);
    if (not ortho)
    {
        glm::mat4 Proj = glm::perspective (fov, raw, znear, zfar);
        glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);

    } else { 
        glm::mat4 Proj = glm::ortho (left, right, bottom, top, znear, zfar);
        glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
    }
}

void MyGLWidget::viewTransform () {
    // glm::lookAt (OBS, VRP, UP)
    // glm::mat4 View = glm::lookAt (OBS, VRP, UP);
    glm::mat4 View(1.0f);
    View = glm::translate(View, glm::vec3(0.0, 0.0, -(2*radi)));
    View = glm::rotate(View, -phi, glm::vec3(0.0, 0.0, 1.0)); // no sempre s'usa
    View = glm::rotate(View, theta, glm::vec3(1.0, 0.0, 0.0));
    View = glm::rotate(View, -psi, glm::vec3(0.0, 1.0, 0.0));

    View = glm::translate(View, -VRP);
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::carregaShaders()
{
    // Creem els shaders per al fragment shader i el vertex shader
    QOpenGLShader fs (QOpenGLShader::Fragment, this);
    QOpenGLShader vs (QOpenGLShader::Vertex, this);
    // Carreguem el codi dels fitxers i els compilem
    fs.compileSourceFile("shaders/basicShader.frag");
    vs.compileSourceFile("shaders/basicShader.vert");
    // Creem el program
    program = new QOpenGLShaderProgram(this);
    // Li afegim els shaders corresponents
    program->addShader(&fs);
    program->addShader(&vs);
    // Linkem el program
    program->link();
    // Indiquem que aquest és el program que volem usar
    program->bind();

    // Obtenim identificador per a l'atribut “vertex" del vertex shader
    vertexLoc = glGetAttribLocation (program->programId(), "vertex");
    // Obtenim identificador per a l'atribut “color" del vertex shader
    colorLoc = glGetAttribLocation (program->programId(), "color");
    // Uniform locations
    transLoc = glGetUniformLocation(program->programId(), "TG");

    projLoc = glGetUniformLocation (program->programId(), "proj");

    viewLoc = glGetUniformLocation (program->programId(), "view");
}
