#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QMouseEvent>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "model.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();


  signals:
    void allOff(bool);
    void oneOn(bool);
    void twoOn(bool);
    void allOn(bool);
    void reactorSig(bool);

  public slots:
    void allOff();
    void oneOn();
    void twoOn();
    void allOn();
    void reactor(bool);

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ( );
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);
    // mouse{Press/Release/Move}Event - Són cridades quan es realitza l'event 
    // corresponent de ratolí
    virtual void mousePressEvent (QMouseEvent *event);
    virtual void mouseReleaseEvent (QMouseEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);

  private:

    void creaBuffersModel(Model &model, const char *fileName, GLuint *VAO, float &escala, glm::vec3 &centreBase);
    void creaBuffersHangar();
    void creaBuffersPersonatge();
    void creaBuffersTerra ();
    void carregaShaders ();
    void projectTransform ();
    void viewTransform ();
    void modelTransformTerra ();
    void modelTransformHangar ();
    void modelTransformAvio ();
    void calculaCapsaModel (Model &m, float &escala, glm::vec3 &centreBase);
    void iniEscena ();
    void iniCamera ();


    // VAO names
    GLuint VAO_avio, VAO_hangar, VAO_Terra ;
    // Program
    QOpenGLShaderProgram *program;
    // uniform locations
    GLuint transLoc, projLoc, viewLoc;
    // attribute locations
    GLuint vertexLoc, normalLoc, matambLoc, matdiffLoc, matspecLoc, matshinLoc, colFocusReactorLoc, colFocusLoc0, colFocusLoc1, colFocusLoc2, posFocusLoc0, posFocusLoc1, posFocusLoc2, ambFocusLoc, posFocusReactorLoc, avioLoc;
    GLint ample, alt;

    // model
    Model hangarModel, avioModel;
    // paràmetres calculats a partir de la capsa contenidora del model
    glm::vec3 centreBaseAvio, centreBaseHangar, defFocus, posFocus0, posFocus1, posFocus2, colFocusReactor, posFocusReactor, ambFocus;
    float escalaAvio, escalaArc;
    glm::vec3 centreEsc;
    float radiEsc, ra;

    glm::vec3 avioPos;


    typedef  enum {NONE, ROTATE} InteractiveAction;
    InteractiveAction DoingInteractive;
    int xClick, yClick;
    float angleX, angleY;
    bool reactorOn;

    glm::mat4 View;

};

