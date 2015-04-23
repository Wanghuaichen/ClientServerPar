#ifndef ParasolidDoc_H
#define ParasolidDoc_H
#include <QTextDocument> 


class ParasolidDoc : public QTextDocument 
{
public:
	
	/*int m_nparts;
	PK_PART_t* m_parts;
	int m_ngeoms;
	PK_GEOM_t* m_geoms;*/
	//GLWidget *w ;


	void OnOpenFile (); 

};

#endif 