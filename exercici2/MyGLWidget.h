#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "model.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

 
  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();


  signals:
    void cameraSecondariaRadio(bool value);
    void cameraPrincipalRadio(bool value);
    void dialpatri1(int value);
    void dialpatri2(int value);

  public slots:
    void resetEscena();
    void principalCamera();
    void secondaryCamera();
    void rotpat1(int n);
    void rotpat2(int n);

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
    void creaBuffersTerra ();
    void creaBuffersCub ();
    void creaBuffersPatricio ();
    void carregaShaders ();
    void projectTransform ();
    void viewTransform ();
    void modelTransformTerra ();
    void modelTransformParet ();
    void modelTransformPatricio1 ();
    void modelTransformPatricio2 ();
    void calculaCapsaModel (Model &p, float &escala, glm::vec3 &centreBase);
    void iniEscena ();
    void iniCamera ();

    // VAO names
    GLuint VAO_Cub, VAO_Terra, VAO_Patricio;
    // Program
    QOpenGLShaderProgram *program;
    // uniform locations
    GLuint transLoc, projLoc, viewLoc;
    // attribute locations
    GLuint vertexLoc, colorLoc;

    GLint ample, alt;

    // model
    Model Patricio;
    // paràmetres calculats a partir de la capsa contenidora del model
    glm::vec3 posPatricio, centreBasePatricio;

    glm::vec3 centreEsc, centreEscSecondaria, obs, vrp, up;
    float radiEsc, ra, fov, zn, zf, psi, phi, theta, patricioRotation1, patricioRotation2, fovini;
    
    float angleX, angleY;
    bool secondCamera;

    typedef  enum {NONE, ROTATE} InteractiveAction;
    InteractiveAction DoingInteractive;
    int xClick, yClick, patRot1, patRot2;
};

