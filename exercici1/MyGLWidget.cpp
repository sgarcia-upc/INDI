#include "MyGLWidget.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
    setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
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

    // Activar el canal de transparència. (NEW!)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_SRC1_ALPHA);

    glClearColor (200/255.0, 220/255.0, 255/255.0, 1.0); // defineix color de fons (d'esborrat)
    carregaShaders();
    creaBuffers();

    // Inicialització de variables d'estat
    this->xPrimeraMuntanya = -1.0;
    this->xSegonaMuntanya = -0.5;
    this->anglePalanca = 0;
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

    glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

    pintaMuntanyes();
    pintaBaseGronxador();
    pintaGronxador();
    pintaPesos();

}


void MyGLWidget::resizeGL (int w, int h)
{
    ample = w;
    alt = h;
}


void MyGLWidget::pintaBaseGronxador(){
    transformacioBaseGronxador();
    glBindVertexArray(VAO_TRIANGLE);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
}


void MyGLWidget::pintaGronxador(){
    transformacioGronxador();
    glBindVertexArray(VAO_QUADRAT);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
}


void MyGLWidget::pintaPesos(){
    transformacioPes(+1);
    glBindVertexArray(VAO_QUADRAT);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    transformacioPes(-1);
    glBindVertexArray(VAO_QUADRAT);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
}


void MyGLWidget::pintaMuntanyes(){

    glBindVertexArray(VAO_MUNTANYA);

    transformacioMuntanya(0.7, this->xPrimeraMuntanya, 0.5);
    glDrawArrays(GL_TRIANGLE_FAN, 0, MUNTANYA_NUM_VERTEXS);

    transformacioMuntanya(1, this->xSegonaMuntanya, 1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, MUNTANYA_NUM_VERTEXS);


    glBindVertexArray(0);
}


void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
    makeCurrent();
    switch (event->key()) {
        case Qt::Key_A: 
            if (anglePalanca <30)
                anglePalanca +=5;
            break;
                        
        case Qt::Key_D: 
            if (anglePalanca >-30)
                anglePalanca -=5;
            break;
                        
        default:
            event->ignore();
            break;
    }
    update();
}


void MyGLWidget::transformacioMuntanya(double h, double xPos, float transparencia){

    // Codi per a la TG necessària
    glm::mat4 transform (1.0f);

    // movem al xPox
    transform = glm::translate(transform, glm::vec3(xPos, -1, 0));

    //// escalem
    transform = glm::scale(transform, glm::vec3(0.5, 1/(h*2.0), 1));

    // al centre de coordenades
    transform = glm::translate(transform, glm::vec3(1, 1, 0));

    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &transform[0][0]); 
    glUniform1f(transCol, transparencia);
}


void MyGLWidget::transformacioBaseGronxador(){

    // Codi per a la TG necessària
    glm::mat4 transform (1.0f);
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &transform[0][0]); 
}


void MyGLWidget::transformacioGronxador(){

    // Codi per a la TG necessària
    glm::mat4 transform (1.0f);

    transform = glm::translate(transform, glm::vec3(0, -0.8, 0));
    transform = glm::rotate(transform, glm::radians(anglePalanca), glm::vec3(0,0,1));
    transform = glm::translate(transform, glm::vec3(-0.4, -0.0, 0));
    transform = glm::scale(transform, glm::vec3(0.8, 0.1, 0));
    transform = glm::translate(transform, glm::vec3(0.5, 0.5, 0));
    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &transform[0][0]); 
}


void MyGLWidget::transformacioPes(int left){
    // Codi per a la TG necessària
    glm::mat4 transform (1.0f);

    transform = glm::translate(transform, glm::vec3(0, -0.8, 0));
    transform = glm::rotate(transform, glm::radians(anglePalanca), glm::vec3(0,0,1));
    
    transform = glm::translate(transform, glm::vec3(-0.4*left, 0.1, 0));
    transform = glm::scale(transform, glm::vec3(0.1, 0.1, 0));
    transform = glm::translate(transform, glm::vec3(0.5*left, 0.5, 0));

    glUniformMatrix4fv (transLoc, 1, GL_FALSE, &transform[0][0]); 
}


void MyGLWidget::creaBuffers (){
    creaBufferTriangle();
    creaBufferMuntanya();
    creaBufferQuadrat();
}


void MyGLWidget::creaBufferMuntanya(){
    double h1=0.4;
    double h2=0.5;
    int id=0;
    glm::vec3 Vertices[MUNTANYA_NUM_VERTEXS]= {
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(-1.0, -1.0, 0.0),
        glm::vec3(1.0, -1.0, 0.0),
        glm::vec3(h2/2, 1-h2, 0.0),
        glm::vec3(h1/4, 1-h1, 0.0),
        glm::vec3(0, 1-h2, 0.0),
        glm::vec3(-h1/4, 1-h1, 0.0),
        glm::vec3(-h2/2, 1-h2, 0.0)
    };


    glm::vec3 Colors[MUNTANYA_NUM_VERTEXS];
    for (int i=0;i<MUNTANYA_NUM_VERTEXS;i++) {
        if (i > 2){
            Colors[i] = glm::vec3(1.0, 1.0, 1.0);
        } else {
            Colors[i] = glm::vec3(155/255.0, 121/255.0, 61/255.0);
        }
    }

    // Creació del Vertex Array Object (VAO) que usarem per pintar
    glGenVertexArrays(1, &VAO_MUNTANYA);
    glBindVertexArray(VAO_MUNTANYA);

    // Creació del buffer amb les dades dels vèrtexs
    GLuint VBO[2];
    glGenBuffers(2, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    // Creació del buffer de colors
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);


    // Desactivem el VAO
    glBindVertexArray(0);

}


void MyGLWidget::creaBufferQuadrat(){

    glm::vec3 Vertices[4];  // Tres vèrtexs amb X, Y i Z
    Vertices[0] = glm::vec3(-0.5,  0.5, 0.0);
    Vertices[1] = glm::vec3(-0.5, -0.5, 0.0);
    Vertices[2] = glm::vec3( 0.5,  0.5, 0.0);
    Vertices[3] = glm::vec3( 0.5, -0.5, 0.0);

    // Creació del Vertex Array Object (VAO) que usarem per pintar
    glGenVertexArrays(1, &VAO_QUADRAT);
    glBindVertexArray(VAO_QUADRAT);

    glm::vec3 Colors[4];
    for(int i=0;i<4;i++) {
        Colors[i] = glm::vec3(1.0, 1.0, 1.0);
    }
    // Creació del buffer amb les dades dels vèrtexs
    GLuint VBO[2];
    glGenBuffers(2, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    // Creació del buffer de colors
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);


    // Desactivem el VAO
    glBindVertexArray(0);

}

void MyGLWidget::creaBufferTriangle ()
{
    float d=0.1;
    glm::vec3 Vertices[3];  // Tres vèrtexs amb X, Y i Z
    Vertices[0] = glm::vec3(-d, -1.0, 0.0);
    Vertices[1] = glm::vec3(+d, -1.0, 0.0);
    Vertices[2] = glm::vec3(0.0, -1+2*d, 0.0);

    glm::vec3 Colors[3];  // Tres vèrtexs amb X, Y i Z
    for(int i=0;i<3;i++) {
        Colors[i] = glm::vec3(0.0, 0.0, 0.0);
    }


    // Creació del Vertex Array Object (VAO) que usarem per pintar
    glGenVertexArrays(1, &VAO_TRIANGLE);
    glBindVertexArray(VAO_TRIANGLE);

    // Creació del buffer amb les dades dels vèrtexs
    GLuint VBO[2];
    glGenBuffers(2, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);


    // Creació del buffer de colors
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);


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
    colorLoc = glGetAttribLocation (program->programId(), "color");
    transLoc = glGetUniformLocation(program->programId(), "TG"); 
    transCol = glGetUniformLocation(program->programId(), "trans"); 
}
