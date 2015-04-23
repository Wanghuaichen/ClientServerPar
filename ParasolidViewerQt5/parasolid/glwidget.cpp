

#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include "Session.h"
#include <math.h>
#include <GLU.H>


const static float pi=3.141593, k=pi/180; // глобальная переменная

GLfloat VertexArray[12][3]; // декларируем массив вершин
GLfloat ColorArray[12][3];  // декларируем массив цветов вершин
GLubyte IndexArray[20][3];  // декларируем массив индексов вершин

// конструктор класса Scene3D
GLWidget::GLWidget(QWidget* parent/*= 0*/) : QGLWidget(parent), m_scaleValue(1.0) 
{ 
   // setFormat(QGLFormat(QGL::DepthBuffer)); // использовать буфер глубины
                                              // установлено по умолчанию в контексте 
	cl = new Client();
	m_session.Start();
	
	//ParasolidDoc *doc = new ParasolidDoc();
	
   // начальные значения данных-членов класса
   xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1; 
  /* m_doc = new ParasolidDoc();
   m_doc -> CreateBlock();*/

   // передает дальше указатель на объект parent
} 

 void GLWidget::initializeGL() // инициализация
{
	
	
	PK_SESSION_ask_frustrum( &m_frustrum );
   // цвет для очистки буфера изображения - будет просто фон окна
	glClearColor(Qt::white, Qt::green, Qt::blue, Qt::red); 
   glEnable(GL_DEPTH_TEST);  // устанавливает режим проверки глубины пикселей
   glShadeModel(GL_FLAT);    // отключает режим сглаживания цветов 
   // устанавливаем режим, когда строятся только внешние поверхности 
   glEnable(GL_CULL_FACE);  
   
  
   
   glEnableClientState(GL_VERTEX_ARRAY); // активизация массива вершин
   glEnableClientState(GL_COLOR_ARRAY);  // активизация массива цветов вершин
}

void GLWidget::resizeGL(int nWidth, int nHeight) // окно виджета
{ 
   glMatrixMode(GL_PROJECTION); // устанавливает текущей проекционную матрицу
   glLoadIdentity();            // присваивает проекционной матрице единичную матрицу
 
   // отношение высоты окна виджета к его ширине
   GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;
   
   // мировое окно
   if (nWidth>=nHeight)
      // параметры видимости ортогональной проекции
      glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 1.0); 
   else
      glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 1.0);      
   // плоскости отсечения (левая, правая, верхняя, нижняя, передняя, задняя)
   
   // параметры видимости перспективной проекции
   // glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
   // плоскости отсечения (левая, правая, верхняя, нижняя, ближняя, дальняя)
  
   // поле просмотра
   glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void GLWidget::paintGL() // рисование
{ 
   // glClear(GL_COLOR_BUFFER_BIT); // окно виджета очищается текущим цветом очистки
   // очистка буфера изображения и глубины
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
   //glScalef(m_scaleValue, m_scaleValue, m_scaleValue);
   // устанавливаем положение и ориентацию матрице моделирования
   glMatrixMode(GL_MODELVIEW); 
  // загружаем единичную матрицу моделирования
   glLoadIdentity();           

   // последовательные преобразования
   glScalef(nSca, nSca, nSca);        // масштабирование
   glTranslatef(0.0f, zTra, 0.0f);    // трансляция     
   glRotatef(xRot, 1.0f, 0.0f, 0.0f); // поворот вокруг оси X         
   glRotatef(yRot, 0.0f, 1.0f, 0.0f); // поворот вокруг оси Y
   glRotatef(zRot, 0.0f, 0.0f, 1.0f); // поворот вокруг оси Z
 
   //drawAxis();   // рисование осей координат
   drawOrigin(); // нарисовать фигуру
   
   if(check == 1)
	   OnDraw();
   if(check == 2)
	   OnDrawEdge();
   
   
}  

void GLWidget::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
   // при нажатии пользователем кнопки мыши переменной ptrMousePosition 
   // будет присвоена координата указателя мыши 
   ptrMousePosition = pe->pos();  

   // ptrMousePosition = (*pe).pos(); // можно и так написать                          
} 

void GLWidget::mouseReleaseEvent(QMouseEvent* pe) // отжатие клавиши мыши
{ 
   // некоторые функции, которые должны выполняться при отжатии клавиши мыши            
} 

// изменение положения стрелки мыши
void GLWidget::mouseMoveEvent(QMouseEvent* pe) 
{   
   // вычисление углов поворота
   xRot += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height(); 
   zRot += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width(); 
   
   ptrMousePosition = pe->pos();
   
   updateGL(); // обновление изображения
}

// вращение колёсика мыши
void GLWidget::wheelEvent(QWheelEvent* pe) 
{ 
   if ((pe->delta())>0) 
   {scale_plus();
    m_scaleValue = m_scaleValue * 1.1;
   }
   else if ((pe->delta())<0) 
   {scale_minus();   
    m_scaleValue = m_scaleValue /1.1;
   }
    
   updateGL(); // обновление изображения          
}

// нажатие определенной клавиши
void GLWidget::keyPressEvent(QKeyEvent* pe) 
{  
   switch (pe->key())
   {         
      case Qt::Key_Plus:  
         scale_plus();     // приблизить сцену
      break;
         
      case Qt::Key_Equal:  
         scale_plus();     // приблизить сцену   
      break;
         
      case Qt::Key_Minus: 
         scale_minus();    // удалиться от сцены
      break;

      case Qt::Key_Up:  
         rotate_up();      // повернуть сцену вверх
      break;
         
      case Qt::Key_Down:  
         rotate_down();    // повернуть сцену вниз
      break;         
         
      case Qt::Key_Left:  
        rotate_left();     // повернуть сцену влево
      break;
         
      case Qt::Key_Right:  
         rotate_right();   // повернуть сцену вправо
      break;                           
         
      case Qt::Key_Z:
         translate_down(); // транслировать сцену вниз
      break;  
         
      case Qt::Key_X:
         translate_up();   // транслировать сцену вверх
      break; 
         
      case Qt::Key_Space:  // клавиша пробела
         defaultScene();   // возвращение значений по умолчанию
      break;
      
      case Qt::Key_Escape: // клавиша "эскейп"
         this->close();    // завершает приложение
      break;                                                           
   }
   
   updateGL(); // обновление изображения
}

void GLWidget::scale_plus() // приблизить сцену
{
   nSca = nSca*1.1;
}

void GLWidget::scale_minus() // удалиться от сцены 
{
   nSca = nSca/1.1;
}

void GLWidget::rotate_up() // повернуть сцену вверх
{
   xRot += 1.0;
}

void GLWidget::rotate_down() // повернуть сцену вниз
{
   xRot -= 1.0;
}

void GLWidget::rotate_left() // повернуть сцену влево
{
   zRot += 1.0;
}

void GLWidget::rotate_right() // повернуть сцену вправо
{
   zRot -= 1.0;
}

void GLWidget::translate_down() // транслировать сцену вниз
{
   zTra -= 0.05;
}

void GLWidget::translate_up() // транслировать сцену вверх
{
   zTra += 0.05;
}

void GLWidget::defaultScene() // наблюдение сцены по умолчанию
{
   xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1;
}

void GLWidget::drawAxis() // построить оси координат
{
   // устанавливаем ширину линии приближенно в пикселях
   glLineWidth(3.0f); 
   // до вызова команды ширина равна 1 пикселю по умолчанию
   
   // устанавливаем цвет последующих примитивов
   glColor4f(1.00f, 0.00f, 0.00f, 1.0f); 
   // ось x красного цвета
   glBegin(GL_LINES); // построение линии
      glVertex3f( 1.0f,  0.0f,  0.0f); // первая точка
      glVertex3f(-1.0f,  0.0f,  0.0f); // вторая точка
   glEnd();  
   
   QColor halfGreen(0, 128, 0, 255);
   qglColor(halfGreen);
   glBegin(GL_LINES);
      // ось y зеленого цвета
      glVertex3f( 0.0f,  1.0f,  0.0f);
      glVertex3f( 0.0f, -1.0f,  0.0f);
  
      glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
      // ось z синего цвета
      glVertex3f( 0.0f,  0.0f,  1.0f);
      glVertex3f( 0.0f,  0.0f, -1.0f);
   glEnd();
}
void GLWidget::SetVertex(int fac, int index, double x, double y, double z)
{
	allcub[fac].st[index].x = x;
	allcub[fac].st[index].y = y;
	allcub[fac].st[index].z = z;
}
void GLWidget::OnDraw()
{
	   
	 
	 PK_VECTOR_t vec_p;
	 PK_POINT_t p_p;
	 int count = 0;
	 PK_POINT_sf_t point_sp[3];
	 //QList<PK_VECTOR_t> *vertexList = new QList<PK_VECTOR_t>();
	 int ss = cl->vertexList->size();
	 if (cl->vertexList->size() == 0) return;
	 for(int i = 0; i<cl->vertexList->size(); i++)
	 {
		
		 //vec_p = cl->vertexList->value(i);
		 point_sp[count].position.coord[0] = cl->vertexList->value(i).coord[0];
		 point_sp[count].position.coord[1] = cl->vertexList->value(i).coord[1];
		 point_sp[count].position.coord[2] = cl->vertexList->value(i).coord[2];
		// << vec_p.coord[0] << "," << vec_p.coord[1]<< "," <<vec_p.coord[2] << "|";
		 count++;
		 if(count == 3)
		 {
			 glBegin(GL_TRIANGLES);
				glColor3f(0.0, 1.0, 0.0);
				glVertex3d(point_sp[0].position.coord[0],point_sp[0].position.coord[1],point_sp[0].position.coord[2]);
				glVertex3d(point_sp[1].position.coord[0],point_sp[1].position.coord[1],point_sp[1].position.coord[2]);
				glVertex3d(point_sp[2].position.coord[0],point_sp[2].position.coord[1],point_sp[2].position.coord[2]);
			  glEnd();
			  glLineWidth(2);
			  count = 0;
		 }
		 
	 }
	 //cl->vertexList->clear();
	
	// free(cl->vertexList);
	
	 
	 


	
}
void GLWidget::OnDrawEdge()
{
	 CSession m_session;
	   m_session.Start();
	   PK_PART_t *parts;
       int n_parts = 0;
       parts = NULL;
	   PK_MEMORY_free(parts);
       PK_ERROR_code_t err = PK_ERROR_no_errors;
	   PK_PART_receive_o_t receive_opts;
	   PK_PART_receive_o_m(receive_opts);
	   receive_opts.receive_user_fields = PK_LOGICAL_true;
	   receive_opts.transmit_format = PK_transmit_format_text_c;
       char *key = "D:\\bll.x_t";
       err = PK_PART_receive(key, &receive_opts, &n_parts, &parts);
	   int n_partitions;
	   PK_PART_t part = *parts; 
	   PK_CURVE_t *curve;
	   PK_POINT_t point;
	   PK_GEOM_t *geom;
	   PK_PARTITION_t  *pt;
	   PK_SESSION_ask_partitions(&n_partitions, &pt);
	   PK_BODY_t *bod;
	   int n_bod;
	   PK_PARTITION_ask_bodies(pt[0], &n_bod, &bod);
	   PK_EDGE_t *edge;
	   int n_edge;
	   PK_BODY_ask_edges(*bod, &n_edge, &edge);
	   PK_CLASS_t *class_curve;
	   PK_VERTEX_t vert[2];
	   PK_INTERVAL_t *interval;
	   PK_LOGICAL_t *l;
	   PK_POINT_sf_t point_s;
	   PK_POINT_sf_t point_sff[2];
	   PK_FACE_t *face;
	   int n_face;
	   //топология детали
	   PK_BODY_ask_topology_o_t ot ;
	   int n_topol;
	   PK_TOPOL_t *topol;
	   PK_CLASS_t *classtop;
	   int a, *b, *c;
	   PK_TOPOL_sense_t *sence;
	   
	   PK_BODY_ask_topology(*bod, &ot, &n_topol, &topol, &classtop, &a, &b, &c, &sence );
	   //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	   for(int i = 0; i<n_topol; i++)
	   {
		   //построение фейсов
		   if(classtop[i] == PK_CLASS_edge)
		   {
			
			   int num_vert;
			   
			   PK_EDGE_ask_vertices(topol[i],  vert);
			 
			   for(int j = 0; j<2; j++)
			   {
					PK_VERTEX_ask_point(vert[j], &point);
					PK_POINT_ask(point, &point_s);
					point_sff[j] = point_s;
			   }
			
			   glBegin(GL_LINES);
				glColor3f(0.0, 0.0, 1.0);
				glVertex3d(point_sff[0].position.coord[0],point_sff[0].position.coord[1],point_sff[0].position.coord[2]);
				glVertex3d(point_sff[1].position.coord[0],point_sff[1].position.coord[1],point_sff[1].position.coord[2]);
			  glEnd();
			   glLineWidth(2);
			   
		   }
	   }
	   glLineWidth(2);

}

void GLWidget::drawOrigin()
{
  float n_size = 5.0;//размер оси
  double n_rad = 0.12;//размер радиуса оси
  float rad_con = 2.0;//радиус конуса
  double h_con = 0.2;//высота конуса
  float angleRot = 90.0;//угол поворота
  float radCenter = 1.2;//радиус центральной точки
  float sizeAxis = n_size / (m_scaleValue * 20);// устанавливаем размер оси
  float radiusAxis = n_rad / (m_scaleValue * 20);// устанавливаем размер оси
  float accuracy = 10.0;//точность отрисовки координат

  glLineWidth(1.0f); // устанавливаем ширину оси

  GLUquadricObj *quadObj;
  quadObj = gluNewQuadric();

  GLfloat O_color[] = {255.0, 0.0, 0.0};
  glColor3f(0.0, 0.0, 1.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, O_color);
  gluSphere(quadObj, radCenter*radiusAxis, 10, 10);

  glRotated(-angleRot, 1.0, 0.0, 0.0);
  glRotated(-angleRot, 0.0, 0.0, 1.0);

  // отрисовка оси z
  GLfloat OZ_color[] = {0.0, 0.0, 1.0, 1.0};
  glColor3f(0.0, 0.0, 255.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, OZ_color);

  gluCylinder(quadObj, radiusAxis, radiusAxis, sizeAxis, accuracy, accuracy);
  glTranslated(0.0, 0.0, sizeAxis);
  gluDisk(quadObj, 0.0, rad_con*radiusAxis, accuracy, accuracy);
  gluCylinder(quadObj, rad_con*radiusAxis, 0.0, h_con*sizeAxis, accuracy, accuracy);

  glTranslated(0.0, 0.0, -sizeAxis);

  // отрисовка оси y
  GLfloat OY_color[] = {0.0, 1.0, 0.0, 1.0};
  glColor3f(0.0, 255.0, 0.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, OY_color);

  glRotated(-angleRot, 1.0, 0.0 ,0.0);
  gluCylinder(quadObj, radiusAxis, radiusAxis, sizeAxis, accuracy, accuracy);
  glTranslated(0.0, 0.0, sizeAxis);
  gluDisk(quadObj, 0.0, rad_con*radiusAxis, accuracy, accuracy);
  gluCylinder(quadObj, rad_con*radiusAxis, 0.0, h_con*sizeAxis, accuracy,accuracy );

  glTranslated(0.0, 0.0, -sizeAxis);

  // отрисовка оси x
  GLfloat OX_color[] = {1.0, 0.0, 0.0, 1.0};
  glColor3f(255.0, 0.0, 0.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, OX_color);

  glRotated(angleRot, 0.0, 1.0, 0.0);
  gluCylinder(quadObj, radiusAxis, radiusAxis, sizeAxis, accuracy, accuracy);
  glTranslated(0.0, 0.0, sizeAxis);
  gluDisk(quadObj, 0.0, rad_con*radiusAxis, accuracy, accuracy);
  gluCylinder(quadObj, rad_con*radiusAxis, 0.0, h_con*sizeAxis, accuracy, accuracy );
  glTranslated(0.0, 0.0, -sizeAxis);

}

void GLWidget :: OnOpenFile ()
{
		
	   QFile file("D:\\cylinder.x_t"); // создаем объект класса QFile
	   QByteArray data; // Создаем объект класса QByteArray, куда мы будем считывать данные
       if (!file.open(QIODevice::ReadOnly)) // Проверяем, возможно ли открыть наш файл для чтения
        return; // если это сделать невозможно, то завершаем функцию
	   data = file.readAll(); //считываем все данные с файла в объект data
	   
       char *key = "J:\\cylinder.x_t";
	   cl->PassFileToServer(QString(data));
      

}
