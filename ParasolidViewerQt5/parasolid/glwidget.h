

#ifndef GLWIDGET_H
#define GLWIDGET_H
#include "parasolid_kernel.h"
#include "ParasolidDoc.h"
#include <Session.h>
#include <Client.h>



#include <QGLWidget> // подключаем класс QGLWidget
struct coord
{
	double x;
	double y;
	double z;
};
struct cub
{
	coord st[4];
};
class GLWidget : public QGLWidget // класс Scene3D наследует встроенный класс QGLWidget
{ 
   private: 
      GLfloat xRot; // переменная хранит угол поворота вокруг оси X
      GLfloat yRot; // переменная хранит угол поворота вокруг оси Y   
      GLfloat zRot; // переменная хранит угол поворота вокруг оси Z
      GLfloat zTra; // переменная хранит величину трансляции оси Z 
      GLfloat nSca; // переменная отвечает за масштабирование объекта
	  cub allcub[6];
	  GLfloat m_scaleValue;
	   PK_SESSION_frustrum_t m_frustrum;
	   PK_SESSION_frustrum_t m_oldfrustrum;

	   int m_nparts;
	PK_PART_t* m_parts;
	int m_ngeoms;
	PK_GEOM_t* m_geoms;
      
      QPoint ptrMousePosition; // координата указателя мыши
      
      void scale_plus();     // приблизить сцену
      void scale_minus();    // удалиться от сцены  
      void rotate_up();      // повернуть сцену вверх
      void rotate_down();    // повернуть сцену вниз
      void rotate_left();    // повернуть сцену влево
      void rotate_right();   // повернуть сцену вправо
      void translate_down(); // транслировать сцену вниз
      void translate_up();   // транслировать сцену вверх      
      void defaultScene();   // наблюдение сцены по умолчанию      
      
      void drawAxis();       // построить оси координат

	  
        
   protected:
      // метод для проведения инициализаций, связанных с OpenGL 
      /*virtual*/ void initializeGL();         
      // метод вызывается при изменении размеров окна виджета            
      /*virtual*/ void resizeGL(int nWidth, int nHeight);  
      // метод, чтобы заново перерисовать содержимое виджета  
      /*virtual*/ void paintGL();                          
       
      // метод обработки события мыши при нажатии клавиши мыши
      /*virtual*/ void mousePressEvent(QMouseEvent* pe); 
      // метод обработки события мыши при перемещении мыши  
      /*virtual*/ void mouseMoveEvent(QMouseEvent* pe);  
      // метод обработки событий мыши при отжатии клавиши мыши  
      /*virtual*/ void mouseReleaseEvent(QMouseEvent* pe); 
      // метод обработки событий колесика мыши 
      /*virtual*/ void wheelEvent(QWheelEvent* pe);  
      // методы обработки события при нажатии определенной клавиши       
      /*virtual*/ void keyPressEvent(QKeyEvent* pe);       
      
   public: 
	  CSession m_session;
	  Client *cl;
      GLWidget(QWidget* parent = 0); // конструктор класса
	  void OnDraw();
	  void OnDrawEdge();
	  void SetVertex(int fac, int index, double x, double y, double z);
	  void OnOpenFile (); 
	  int check;
	  void drawOrigin();
}; 

#endif
