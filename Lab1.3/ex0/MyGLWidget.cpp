//#include <GL/glew.h>
#include "MyGLWidget.h"
#include "qnamespace.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
    setFocusPolicy(Qt::StrongFocus);	// per rebre events de teclat
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

    scl = 0.5; // size of elements of the form * scl

    glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
    carregaShaders();
    creaBuffers();
}

void MyGLWidget::paintGL ()
{
    // Aquest codi és necessari únicament per a MACs amb pantalla retna.
#ifdef __APPLE__
    GLint vp[4];
    glGetIntegerv (GL_VIEWPORT, vp);
    ample = vp[2];
    alt = vp[3];
#endif

    // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
    // useu els paràmetres que considereu (els que hi ha són els de per defecte)
    //	glViewport (0, 0, ample, alt);

    glClear (GL_COLOR_BUFFER_BIT);	// Esborrem el frame-buffer

    modelTransform();

    // Activem l'Array a pintar
    glBindVertexArray(VAO1);

    // Pintem l'escena
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Desactivem el VAO
    glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
    ample = w;
    alt = h;

    glUniform1f(glGetUniformLocation(program->programId(),"x00"), ample/2.0);
    glUniform1f(glGetUniformLocation(program->programId(),"y00"), alt/2.0);
    glUniform1f(varLoc, scl);
}

void MyGLWidget::creaBuffers ()
{
    glm::vec3 Vertices[3];	// Tres vèrtexs amb X, Y i Z
    Vertices[0] = glm::vec3(1, -1, 0);
    Vertices[1] = glm::vec3(-1, -1, 0);
    Vertices[2] = glm::vec3(0, 1, 0);


    // Creació del Vertex Array Object (VAO) que usarem per pintar
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    // Creació del buffer amb les dades dels vèrtexs
    GLuint VBO1;
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    // Desactivem el VAO
    glBindVertexArray(0);
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

    // Obtenim identificador per a l'atribut “vertex” del vertex shader
    vertexLoc = glGetAttribLocation (program->programId(), "vertex");
    varLoc = glGetUniformLocation(program->programId(),"val");
    transLoc = glGetUniformLocation(program->programId(), "TG");
}

void MyGLWidget::modelTransform() {
    // Matriu de transformació, inicialment identitat (I)
    glm::mat4 TG(1); 
    TG=glm::translate(TG, glm::vec3 (matx, maty, matz));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]); 
                                                //   ^ glm::value_ptr(TG))
}

void MyGLWidget::keyPressEvent(QKeyEvent*e){
    makeCurrent();
    switch(e->key()){
        case Qt::Key_S:
            scl+=0.1;
            glUniform1f(varLoc,scl);
            break;
        case Qt::Key_D:
            scl-=0.1;
            glUniform1f(varLoc,scl);
            break;
        case Qt::Key_Up:
            maty += 0.1;
            modelTransform();
            break; 
        case Qt::Key_Down:
            maty -= 0.1;
            modelTransform();
            break; 
        case Qt::Key_Left:
            matx -= 0.1;
            modelTransform();
            break; 
        case Qt::Key_Right:
            matx += 0.1;
            modelTransform();
            break; 
        default:
            e->ignore();//propagaralpare
    }
    update();
}
