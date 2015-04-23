

#ifndef GLWIDGET_H
#define GLWIDGET_H
#include "parasolid_kernel.h"
#include "ParasolidDoc.h"
#include <Session.h>
#include <Client.h>



#include <QGLWidget> // ���������� ����� QGLWidget
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
class GLWidget : public QGLWidget // ����� Scene3D ��������� ���������� ����� QGLWidget
{ 
   private: 
      GLfloat xRot; // ���������� ������ ���� �������� ������ ��� X
      GLfloat yRot; // ���������� ������ ���� �������� ������ ��� Y   
      GLfloat zRot; // ���������� ������ ���� �������� ������ ��� Z
      GLfloat zTra; // ���������� ������ �������� ���������� ��� Z 
      GLfloat nSca; // ���������� �������� �� ��������������� �������
	  cub allcub[6];
	  GLfloat m_scaleValue;
	   PK_SESSION_frustrum_t m_frustrum;
	   PK_SESSION_frustrum_t m_oldfrustrum;

	   int m_nparts;
	PK_PART_t* m_parts;
	int m_ngeoms;
	PK_GEOM_t* m_geoms;
      
      QPoint ptrMousePosition; // ���������� ��������� ����
      
      void scale_plus();     // ���������� �����
      void scale_minus();    // ��������� �� �����  
      void rotate_up();      // ��������� ����� �����
      void rotate_down();    // ��������� ����� ����
      void rotate_left();    // ��������� ����� �����
      void rotate_right();   // ��������� ����� ������
      void translate_down(); // ������������� ����� ����
      void translate_up();   // ������������� ����� �����      
      void defaultScene();   // ���������� ����� �� ���������      
      
      void drawAxis();       // ��������� ��� ���������

	  
        
   protected:
      // ����� ��� ���������� �������������, ��������� � OpenGL 
      /*virtual*/ void initializeGL();         
      // ����� ���������� ��� ��������� �������� ���� �������            
      /*virtual*/ void resizeGL(int nWidth, int nHeight);  
      // �����, ����� ������ ������������ ���������� �������  
      /*virtual*/ void paintGL();                          
       
      // ����� ��������� ������� ���� ��� ������� ������� ����
      /*virtual*/ void mousePressEvent(QMouseEvent* pe); 
      // ����� ��������� ������� ���� ��� ����������� ����  
      /*virtual*/ void mouseMoveEvent(QMouseEvent* pe);  
      // ����� ��������� ������� ���� ��� ������� ������� ����  
      /*virtual*/ void mouseReleaseEvent(QMouseEvent* pe); 
      // ����� ��������� ������� �������� ���� 
      /*virtual*/ void wheelEvent(QWheelEvent* pe);  
      // ������ ��������� ������� ��� ������� ������������ �������       
      /*virtual*/ void keyPressEvent(QKeyEvent* pe);       
      
   public: 
	  CSession m_session;
	  Client *cl;
      GLWidget(QWidget* parent = 0); // ����������� ������
	  void OnDraw();
	  void OnDrawEdge();
	  void SetVertex(int fac, int index, double x, double y, double z);
	  void OnOpenFile (); 
	  int check;
	  void drawOrigin();
}; 

#endif
