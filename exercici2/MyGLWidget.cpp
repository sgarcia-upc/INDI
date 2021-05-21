#include "MyGLWidget.h"
#include "ext/matrix_transform.hpp"
#include "fwd.hpp"
#include "trigonometric.hpp"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
    setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
    phi = 0;
    psi = M_PI/9.0;
    theta = M_PI/9.0;
    patricioRotation1 = 0;
    patricioRotation2 = 0;
    patRot1 = 1;
    patRot2 = 1;
    secondCamera = false;
}

void MyGLWidget::principalCamera(){
    makeCurrent();
    secondCamera = false;
    viewTransform ();
    update();
}

void MyGLWidget::secondaryCamera(){
    makeCurrent();
    secondCamera = true;
    viewTransform ();
    update();
}

void MyGLWidget::resetEscena(){
    makeCurrent();
    emit (cameraPrincipalRadio(true));
    emit (cameraSecondariaRadio(false));
    phi = 0;
    psi = M_PI/9.0;
    theta = M_PI/9.0;
    patricioRotation1 = 0;
    patricioRotation2 = 0;
    secondCamera = false;
    patRot1 = 1;
    patRot2 = 1;
    emit(dialpatri1(patRot1));
    emit(dialpatri2(patRot2));
    viewTransform ();
    update();
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

    glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
    glEnable(GL_DEPTH_TEST);
    carregaShaders();
    iniEscena ();
    iniCamera ();
}

void MyGLWidget::rotpat1(int n){
    makeCurrent();
    patricioRotation1 = (M_PI/6)*n;
    patRot1 = n;
    update();
}

void MyGLWidget::rotpat2(int n){
    makeCurrent();
    patricioRotation2 = (M_PI/6)*n;
    patRot2 = n;
    update();

}

void MyGLWidget::iniEscena ()
{
    creaBuffersTerra();
    creaBuffersCub();
    creaBuffersPatricio();

    centreEsc = glm::vec3(2,2,2);
    centreEscSecondaria = glm::vec3(0,0,0);

    glm::vec3 min (-20,4,-20);
    glm::vec3 max (20,0,20);

    radiEsc = distance(min, max) / 2;
}

void MyGLWidget::iniCamera ()
{
    angleY = angleX = 0.0;
    obs = centreEsc + glm::vec3(0, 2, 2*radiEsc);
    vrp = centreEsc;
    up = glm::vec3(0,1,0);
    ra = 1.0;
    fov = fovini = M_PI/3.0;
    zn = radiEsc;
    zf = 3.0*radiEsc;

    projectTransform ();
    viewTransform ();
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
    //  glViewport (0, 0, ample, alt);

    // Esborrem el frame-buffer i el depth-buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Activem el VAO per a pintar el Terra
    glBindVertexArray (VAO_Terra);
    modelTransformTerra ();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Activem el VAO per a pintar la Cub
    glBindVertexArray (VAO_Cub);
    modelTransformParet ();
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Activem el VAO per a pintar el Patricio
    glBindVertexArray (VAO_Patricio);
    modelTransformPatricio1 ();
    glDrawArrays(GL_TRIANGLES, 0, Patricio.faces().size()*3);

    glBindVertexArray (VAO_Patricio);
    modelTransformPatricio2 ();
    glDrawArrays(GL_TRIANGLES, 0, Patricio.faces().size()*3);
    glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
    ample = w;
    alt = h;

    ra = float(ample)/float(alt);

    if (ra < 1.0)
        fov = 2.0*atan( tan(fovini/2) / ra );
    else
        fov = fovini;

    projectTransform ();
}
//
void MyGLWidget::modelTransformPatricio1 ()
{
    glm::vec3 x;
    float escala;
    calculaCapsaModel (Patricio, escala, x);
    escala *= 4;

    glm::mat4 TG(1.f);  // Matriu de transformació

    TG = glm::translate(TG, glm::vec3 (10, 0, 10));
    TG = glm::rotate(TG, -patricioRotation1, glm::vec3(0,1,0));
    TG = glm::translate(TG, glm::vec3 (5, 0, 5));

    TG = glm::rotate(TG, glm::radians(45.0f), glm::vec3(0,1,0));
    TG = glm::scale(TG, glm::vec3(escala));
    TG = glm::translate(TG, glm::vec3(-x));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPatricio2()
{
    glm::vec3 x;
    float escala;
    calculaCapsaModel (Patricio, escala, x);
    escala *= 4;

    glm::mat4 TG(1.f);  // Matriu de transformació

    TG = glm::translate(TG, glm::vec3 (-10, 0, -10));
    TG = glm::rotate(TG, patricioRotation2, glm::vec3(0,1,0));
    TG = glm::translate(TG, glm::vec3 (-5, 0, -5));

    TG = glm::rotate(TG, glm::radians(45.0f), glm::vec3(0,1,0));
    TG = glm::scale(TG, glm::vec3(escala));
    TG = glm::translate(TG, glm::vec3(-x));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformParet ()  // Cal modificar aquesta funció...
{
    glm::mat4 TG(1.f);  // Matriu de transformació
    TG = glm::scale(TG, glm::vec3(0.6,2,40));

    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformTerra ()
{
    glm::mat4 TG(1.f);  // Matriu de transformació

    // crece el doble
    TG = glm::scale(TG, glm::vec3(2,0,2));
    // ponemos la tierra de 20x20 en el centro
    TG = glm::translate (TG, glm::vec3(-10,0,-10));

    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::projectTransform () // Cal modificar aquesta funció...
{
    glm::mat4 Proj;  // Matriu de projecció

    Proj = glm::perspective(fov, ra, zn, zf);

    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform () // Cal modificar aquesta funció...
{
    glm::mat4 View(1.0f);
    if (secondCamera){
        View = glm::lookAt(glm::vec3(0,40,0),centreEscSecondaria, glm::vec3(-1,0,0));
    } else {
        View = glm::translate(View, glm::vec3(0.0, 0.0, -(2*radiEsc)));
        View = glm::rotate(View, -phi, glm::vec3(0.0, 0.0, 1.0)); // no sempre s'usa
        View = glm::rotate(View, theta, glm::vec3(1.0, 0.0, 0.0));
        View = glm::rotate(View, -psi, glm::vec3(0.0, 1.0, 0.0));

        View = glm::translate(View, -vrp);
    }
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)  // Cal modificar aquesta funció...
{
    makeCurrent();
    switch (event->key()) {
        case Qt::Key_R:
            patricioRotation1 += M_PI/6;
            patRot1++;
            if (patRot1 == 13) patRot1 = 1;
            emit(dialpatri1(patRot1));
            break;

        case Qt::Key_T:
            patricioRotation2 += M_PI/6;
            patRot2++;
            if (patRot2 == 13) patRot2 = 1;
            emit(dialpatri2(patRot2));
            break;

        case Qt::Key_C:
            if (not secondCamera){
                secondCamera = true;
                emit (cameraPrincipalRadio(false));
                emit (cameraSecondariaRadio(true));
            }
            else {
                secondCamera = false;
                emit (cameraPrincipalRadio(true));
                emit (cameraSecondariaRadio(false));
            }
            viewTransform();
            break;
        case Qt::Key_I:
            resetEscena();
            break;

        default: event->ignore(); break;
    }

    update();
}

void MyGLWidget::mousePressEvent (QMouseEvent *e)
{
    xClick = e->x();
    yClick = e->y();

    if (e->button() & Qt::LeftButton &&
            ! (e->modifiers() & (Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
    {
        if (not secondCamera)
            DoingInteractive = ROTATE;
    }
}

void MyGLWidget::mouseReleaseEvent( QMouseEvent *)
{
    DoingInteractive = NONE;
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    makeCurrent();
    if (DoingInteractive == ROTATE)
    {
        // Aquí cal completar per fer la rotació...
        if (e->x() > xClick){
            psi -= 0.1;
        }
        if (e->x() < xClick){
            psi += 0.1;
        }
        if (e->y() > yClick){
            theta += 0.1;
        }
        if (e->y() < yClick){
            theta -= 0.1;
        }

        viewTransform ();
    }

    xClick = e->x();
    yClick = e->y();

    update ();
}

void MyGLWidget::calculaCapsaModel (Model &p, float &escala, glm::vec3 &centreBase)
{
    // Càlcul capsa contenidora i valors transformacions inicials
    float minx, miny, minz, maxx, maxy, maxz;
    minx = maxx = p.vertices()[0];
    miny = maxy = p.vertices()[1];
    minz = maxz = p.vertices()[2];
    for (unsigned int i = 3; i < p.vertices().size(); i+=3)
    {
        if (p.vertices()[i+0] < minx)
            minx = p.vertices()[i+0];
        if (p.vertices()[i+0] > maxx)
            maxx = p.vertices()[i+0];
        if (p.vertices()[i+1] < miny)
            miny = p.vertices()[i+1];
        if (p.vertices()[i+1] > maxy)
            maxy = p.vertices()[i+1];
        if (p.vertices()[i+2] < minz)
            minz = p.vertices()[i+2];
        if (p.vertices()[i+2] > maxz)
            maxz = p.vertices()[i+2];
    }
    escala = 1.0/(maxy-miny);
    centreBase[0] = (minx+maxx)/2.0;
    centreBase[1] = miny;
    centreBase[2] = (minz+maxz)/2.0;
}

void MyGLWidget::creaBuffersCub ()
{
    // Dades del cub
    // Vèrtexs del cub
    glm::vec3 vertexs[8] = {
        /* 0*/ glm::vec3( -0.5, 0.0, -0.5),  /* 1*/ glm::vec3( 0.5, 0.0, -0.5),
        /* 2*/ glm::vec3( -0.5, 1.0, -0.5),  /* 3*/ glm::vec3( 0.5, 1.0, -0.5),
        /* 4*/ glm::vec3( -0.5, 0.0, 0.5),  /* 5*/ glm::vec3( 0.5, 0.0, 0.5),
        /* 6*/ glm::vec3( -0.5, 1.0, 0.5),  /* 7*/ glm::vec3( 0.5, 1.0, 0.5)
    };

    // VBO amb la posició dels vèrtexs
    glm::vec3 poscub[36] = {  // 12 triangles
        vertexs[0], vertexs[2], vertexs[1],
        vertexs[1], vertexs[2], vertexs[3],
        vertexs[5], vertexs[1], vertexs[7],
        vertexs[1], vertexs[3], vertexs[7],
        vertexs[2], vertexs[6], vertexs[3],
        vertexs[3], vertexs[6], vertexs[7],
        vertexs[0], vertexs[4], vertexs[6],
        vertexs[0], vertexs[6], vertexs[2],
        vertexs[0], vertexs[1], vertexs[4],
        vertexs[1], vertexs[5], vertexs[4],
        vertexs[4], vertexs[5], vertexs[6],
        vertexs[5], vertexs[7], vertexs[6]
    };

    glm::vec3 color(0, 0, 1.0);

    glm::vec3 colorcub[36] = {
        color, color, color, color, color, color,
        color, color, color, color, color, color,
        color, color, color, color, color, color,
        color, color, color, color, color, color,
        color, color, color, color, color, color,
        color, color, color, color, color, color
    };

    // Creació del Vertex Array Object del cub
    glGenVertexArrays(1, &VAO_Cub);
    glBindVertexArray(VAO_Cub);

    GLuint VBO_Cub[2];
    glGenBuffers(2, VBO_Cub);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cub[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(poscub), poscub, GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Cub[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorcub), colorcub, GL_STATIC_DRAW);

    // Activem l'atribut normalLoc
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    glBindVertexArray(0);
}

void MyGLWidget::creaBuffersPatricio ()
{
    // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
    Patricio.load("./models/Patricio.obj");

    // Creació del Vertex Array Object del Patricio
    glGenVertexArrays(1, &VAO_Patricio);
    glBindVertexArray(VAO_Patricio);

    // Creació dels buffers del model
    GLuint VBO_Patricio[2];
    // Buffer de posicions
    glGenBuffers(2, VBO_Patricio);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*Patricio.faces().size()*3*3, Patricio.VBO_vertices(), GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    // Buffer de component difusa usada com a color
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*Patricio.faces().size()*3*3, Patricio.VBO_matdiff(), GL_STATIC_DRAW);

    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    glBindVertexArray(0);
}




void MyGLWidget::creaBuffersTerra ()
{
    // Dades del terra
    // VBO amb la posició dels vèrtexs
    glm::vec3 posterra[4] = {
        glm::vec3(0.0, 0.0, 20.0),
        glm::vec3(20.0, 0.0, 20.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(20.0, 0.0, 0.0),
    };

    glm::vec3 color(0.6,0.6,0.0);

    // Fem que aquest material afecti a tots els vèrtexs per igual
    glm::vec3 colterra[4] = {
        color, color, color, color
    };

    // Creació del Vertex Array Object del terra
    glGenVertexArrays(1, &VAO_Terra);
    glBindVertexArray(VAO_Terra);

    GLuint VBO_Terra[2];
    glGenBuffers(2, VBO_Terra);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(posterra), posterra, GL_STATIC_DRAW);

    // Activem l'atribut vertexLoc
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colterra), colterra, GL_STATIC_DRAW);

    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

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
    // Obtenim identificador per a l'atribut “color” del vertex shader
    colorLoc = glGetAttribLocation (program->programId(), "color");

    // Demanem identificadors per als uniforms del vertex shader
    transLoc = glGetUniformLocation (program->programId(), "TG");
    projLoc = glGetUniformLocation (program->programId(), "proj");
    viewLoc = glGetUniformLocation (program->programId(), "view");
}

