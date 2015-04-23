#include "PsServer.h"

PsServer::PsServer(QWidget *widget, QObject *parent) :QTcpServer(parent)
{
    _widget = widget;
}

bool PsServer::doStartServer(QHostAddress addr, qint16 port)
{
    if (!listen(addr, port))
    {
        qDebug() << "Server not started at" << addr << ":" << port;
        return false;
    }
    qDebug() << "Server started at" << addr << ":" << port;
    return true;
}

void PsServer::doSendToAllUserJoin(QString name)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    //??????????? ????? ??? ?????? ?????
    out << (quint16)0 << PsClient::comUserJoin << name;
    //????? ?? ????????????????? ????? ?????? ?????
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    //?????????? ???? ??????????????, ????? ????, ??? ?????
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getName() != name && _clients.at(i)->getAutched())
            _clients.at(i)->_sok->write(block);
}

void PsServer::doSendToAllUserLeft(QString name)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << PsClient::comUserLeft << name;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getName() != name && _clients.at(i)->getAutched())
            _clients.at(i)->_sok->write(block);
}

void PsServer::doSendToAllMessage(QString message, QString fromUsername)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << PsClient::comMessageToAll << fromUsername << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    for (int i = 0; i < _clients.length(); ++i)
        if (_clients.at(i)->getAutched())
            _clients.at(i)->_sok->write(block);
}

void  PsServer::doQueryToServer(QString message, QString fromUsername)
{
    QString str = "0,0.1,0.08,|0.0153073,0.1,0.116955,|0.0282843,0.1,0.108284,|0.0282843,0.1,0.108284,|0.0369552,0.1,0.0953073,|0,0.1,0.08,|0.0369552,0.1,0.0953073,|0.04,0.1,0.08,|0,0.1,0.08,|0.04,0.1,0.08,|0.0369552,0.1,0.0646927,|0,0.1,0.08,|0.0369552,0.1,0.0646927,|0.0282843,0.1,0.0517157,|0,0.1,0.08,|0.0282843,0.1,0.0517157,|0.0153073,0.1,0.0430448,|0,0.1,0.08,|0.0153073,0.1,0.0430448,|0,0.1,0.04,|0,0.1,0.08,|0,0.1,0.04,|-0.0153073,0.1,0.0430448,|0,0.1,0.08,|-0.0153073,0.1,0.0430448,|-0.0282843,0.1,0.0517157,|0,0.1,0.08,|-0.0282843,0.1,0.0517157,|-0.0369552,0.1,0.0646927,|0,0.1,0.08,|-0.0369552,0.1,0.0646927,|-0.04,0.1,0.08,|0,0.1,0.08,|-0.04,0.1,0.08,|-0.0369552,0.1,0.0953073,|0,0.1,0.08,|-0.0369552,0.1,0.0953073,|-0.0282843,0.1,0.108284,|0,0.1,0.08,|-0.0282843,0.1,0.108284,|-0.0153073,0.1,0.116955,|0,0.1,0.08,|-0.0153073,0.1,0.116955,|1.46958e-17,0.1,0.12,|0,0.1,0.08,|1.46958e-17,0.1,0.12,|0.0153073,0.1,0.116955,|0,0.1,0.08,|0,0,0.04,|0,0.1,0.04,|0.0153073,0.1,0.0430448,|0.0153073,0,0.0430448,|0.0153073,0.1,0.0430448,|0.0282843,0.1,0.0517157,|0.0282843,0,0.0517157,|0.0282843,0.1,0.0517157,|0.0369552,0.1,0.0646927,|0.0369552,0,0.0646927,|0.0369552,0.1,0.0646927,|0.04,0.1,0.08,|0.04,0,0.08,|0.04,0.1,0.08,|0.0369552,0.1,0.0953073,|0.0369552,0,0.0953073,|0.0369552,0.1,0.0953073,|0.0282843,0.1,0.108284,|0.0282843,0,0.108284,|0.0282843,0.1,0.108284,|0.0153073,0.1,0.116955,|0.0153073,0,0.116955,|0.0153073,0.1,0.116955,|1.46958e-17,0.1,0.12,|4.89859e-18,0,0.12,|1.46958e-17,0.1,0.12,|-0.0153073,0.1,0.116955,|-0.0153073,0,0.116955,|-0.0153073,0.1,0.116955,|-0.0282843,0.1,0.108284,|-0.0282843,0,0.108284,|-0.0282843,0.1,0.108284,|-0.0369552,0.1,0.0953073,|-0.0369552,0,0.0953073,|-0.0369552,0.1,0.0953073,|-0.04,0.1,0.08,|-0.04,0,0.08,|-0.04,0.1,0.08,|-0.0369552,0.1,0.0646927,|-0.0369552,0,0.0646927,|-0.0369552,0.1,0.0646927,|-0.0282843,0.1,0.0517157,|-0.0282843,0,0.0517157,|-0.0282843,0.1,0.0517157,|-0.0153073,0.1,0.0430448,|-0.0153073,0,0.0430448,|-0.0153073,0.1,0.0430448,|0,0.1,0.04,|0,0.1,0.04,|0,0,0.04,|-0.0153073,0,0.0430448,|-0.0153073,0.1,0.0430448,|-0.0153073,0,0.0430448,|-0.0282843,0,0.0517157,|-0.0282843,0.1,0.0517157,|-0.0282843,0,0.0517157,|-0.0369552,0,0.0646927,|-0.0369552,0.1,0.0646927,|-0.0369552,0,0.0646927,|-0.04,0,0.08,|-0.04,0.1,0.08,|-0.04,0,0.08,|-0.0369552,0,0.0953073,|-0.0369552,0.1,0.0953073,|-0.0369552,0,0.0953073,|-0.0282843,0,0.108284,|-0.0282843,0.1,0.108284,|-0.0282843,0,0.108284,|-0.0153073,0,0.116955,|-0.0153073,0.1,0.116955,|-0.0153073,0,0.116955,|4.89859e-18,0,0.12,|1.46958e-17,0.1,0.12,|4.89859e-18,0,0.12,|0.0153073,0,0.116955,|0.0153073,0.1,0.116955,|0.0153073,0,0.116955,|0.0282843,0,0.108284,|0.0282843,0.1,0.108284,|0.0282843,0,0.108284,|0.0369552,0,0.0953073,|0.0369552,0.1,0.0953073,|0.0369552,0,0.0953073,|0.04,0,0.08,|0.04,0.1,0.08,|0.04,0,0.08,|0.0369552,0,0.0646927,|0.0369552,0.1,0.0646927,|0.0369552,0,0.0646927,|0.0282843,0,0.0517157,|0.0282843,0.1,0.0517157,|0.0282843,0,0.0517157,|0.0153073,0,0.0430448,|0.0153073,0.1,0.0430448,|0.0153073,0,0.0430448,|0,0,0.04,|0,0,0.08,|-0.0153073,0,0.116955,|-0.0282843,0,0.108284,|-0.0282843,0,0.108284,|-0.0369552,0,0.0953073,|0,0,0.08,|-0.0369552,0,0.0953073,|-0.04,0,0.08,|0,0,0.08,|-0.04,0,0.08,|-0.0369552,0,0.0646927,|0,0,0.08,|-0.0369552,0,0.0646927,|-0.0282843,0,0.0517157,|0,0,0.08,|-0.0282843,0,0.0517157,|-0.0153073,0,0.0430448,|0,0,0.08,|-0.0153073,0,0.0430448,|0,0,0.04,|0,0,0.08,|0,0,0.04,|0.0153073,0,0.0430448,|0,0,0.08,|0.0153073,0,0.0430448,|0.0282843,0,0.0517157,|0,0,0.08,|0.0282843,0,0.0517157,|0.0369552,0,0.0646927,|0,0,0.08,|0.0369552,0,0.0646927,|0.04,0,0.08,|0,0,0.08,|0.04,0,0.08,|0.0369552,0,0.0953073,|0,0,0.08,|0.0369552,0,0.0953073,|0.0282843,0,0.108284,|0,0,0.08,|0.0282843,0,0.108284,|0.0153073,0,0.116955,|0,0,0.08,|0.0153073,0,0.116955,|4.89859e-18,0,0.12,|0,0,0.08,|4.89859e-18,0,0.12,|-0.0153073,0,0.116955,|0,0,0.08,|";
    int arr[10] = {1,2};
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << PsClient::comQueryToServer << fromUsername  << str;
    out.device()->seek(0);
    _clients.at(0)->_sok->write(block);
}

void PsServer::doSendToAllServerMessage(QString message)
{
    
}

void PsServer::doSendServerMessageToUsers(QString message, const QStringList &users)
{
   
}

void PsServer::doSendMessageToUsers(QString message, const QStringList &users, QString fromUsername)
{
    
}



bool PsServer::isNameValid(QString name) const
{
   
    return 0;
}

bool PsServer::isNameUsed(QString name) const
{
   
    return false;
}

void PsServer::incomingConnection(int handle)
{
    //??????? ???????
    PsClient *client = new PsClient(handle, this, this);
    if (_widget != 0)
    {
        connect(client, SIGNAL(addUserToGui(QString)), _widget, SLOT(onAddUserToGui(QString)));
        connect(client, SIGNAL(removeUserFromGui(QString)), _widget, SLOT(onRemoveUserFromGui(QString)));
        connect(client, SIGNAL(messageToGui(QString,QString,QStringList)), _widget, SLOT(onMessageToGui(QString,QString,QStringList)));
    }
    connect(client, SIGNAL(removeUser(PsClient*)), this, SLOT(onRemoveUser(PsClient*)));
    _clients.append(client);
}

void PsServer::onRemoveUser(PsClient *client)
{
    
}

void PsServer::onMessageFromGui(QString message, const QStringList &users)
{
  
}

void PsServer::loadFile(QString data)
{
    char* nmfile = "D:\\ClientServerPar\\ParasolidServer\\tmp.x_t";
    CSession m_session;
    m_session.Start();
    QFile file("tmp.x_t");
    QTextStream out(&file);
    if(!file.open(QIODevice::WriteOnly))
    {
          return;
    }
    out<<data;
    file.close();

    PK_PART_t *parts;

     int n_parts = 0;
     parts = NULL;
           PK_MEMORY_free(parts);
           PK_ERROR_code_t err = PK_ERROR_no_errors;
           PK_PART_receive_o_t receive_opts;
           PK_PART_receive_o_m(receive_opts);
           receive_opts.receive_user_fields = PK_LOGICAL_true;
           receive_opts.transmit_format = PK_transmit_format_text_c;

           err = PK_PART_receive(nmfile, &receive_opts, &m_nparts, &m_parts);

    int n_partitions;
          PK_CURVE_t *curve;
          PK_POINT_t point;
          PK_GEOM_t *geom;
          PK_PARTITION_t  *pt;
          PK_SESSION_ask_partitions(&n_partitions, &pt);
          PK_BODY_t *bod;
          int n_bod;
          PK_PARTITION_ask_bodies(pt[0], &n_bod, &bod);
          if(n_bod == 0) return;
          PK_EDGE_t *edge;
          int n_edge;
          PK_BODY_ask_edges(*bod, &n_edge, &edge);
          PK_CLASS_t *class_curve;
          PK_VERTEX_t *vert;
          PK_INTERVAL_t *interval;
          PK_LOGICAL_t *l;
          PK_POINT_sf_t point_s;
          PK_POINT_sf_t point_sff[4];
          PK_POINT_sf_t point_sff2[2];
          PK_FACE_t *face;
          int n_face;
          //????????? ??????
          PK_BODY_ask_topology_o_t ot ;
          int n_topol;
          PK_TOPOL_t *topol;
          PK_CLASS_t *classtop;
          int a, *b, *c;
          PK_TOPOL_sense_t *sence;



          PK_BODY_ask_topology(*bod, &ot, &n_topol, &topol, &classtop, &a, &b, &c, &sence );
          //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

          PK_TOPOL_render_facet_o_t  m_facetOptions;
          PK_TOPOL_facet_mesh_o_m( m_facetOptions.control );
          PK_TOPOL_render_facet_go_o_m( m_facetOptions.go_option );
          m_facetOptions.go_option.go_normals = PK_facet_go_normals_no_c;
           m_facetOptions.control.is_surface_plane_tol = PK_LOGICAL_true;
           m_facetOptions.control.surface_plane_tol = 0.005 * 9.11 ;
           m_facetOptions.control.is_curve_chord_tol = PK_LOGICAL_true;
           m_facetOptions.control.curve_chord_tol = 0.001 * 9.11;
           m_facetOptions.go_option.go_edges = PK_facet_go_edges_yes_c;
           m_facetOptions.control.match =  PK_facet_match_geom_c;
           PK_ERROR_code_t err2 = PK_ERROR_no_errors;
           //err2 =  PK_TOPOL_render_facet(n_topol, topol, NULL, PK_ENTITY_null, &m_facetOptions);
           PK_ERROR_t error = PK_ERROR_no_errors;

       PK_TOPOL_facet_2_r_t refTables;
       PK_TOPOL_facet_2_o_t option;
       PK_TOPOL_facet_mesh_2_o_m (option.control);
       PK_TOPOL_facet_choice_2_o_m (option.choice);

       //Parasolid Default?
       option.control.match = PK_facet_match_topol_c;
      option.control.shape = PK_facet_shape_convex_c;
       option.control.inflect = PK_facet_inflect_split_near_c;
       option.control.quality = PK_facet_quality_improved_c;

       option.control.is_surface_plane_tol = PK_LOGICAL_false;
       option.control.is_surface_plane_ang = PK_LOGICAL_false;

       option.choice.facet_fin = PK_LOGICAL_true;
       option.choice.fin_fin = PK_LOGICAL_true;
       option.choice.fin_data = PK_LOGICAL_true;
       option.choice.data_point_idx = PK_LOGICAL_true;
       option.choice.point_vec = PK_LOGICAL_true;
       option.choice.facet_face = PK_LOGICAL_true;
       option.choice.fin_edge = PK_LOGICAL_true;
       option.choice.normal_vec = PK_LOGICAL_true;
       option.choice.data_normal_idx = PK_LOGICAL_true;
       error = PK_TOPOL_facet_2(1, m_parts, NULL, &option, &refTables);

       PK_TOPOL_fctab_facet_fin_t *facetFinTable = NULL;
       PK_TOPOL_fctab_fin_data_t *finDataTable = NULL;
       PK_TOPOL_fctab_data_point_t *dataPointTable = NULL;
       PK_TOPOL_fctab_data_normal_t *dataNormalTable = NULL;
       PK_TOPOL_fctab_point_vec_t *pointVecTable = NULL;
       PK_TOPOL_fctab_normal_vec_t *normalVecTable = NULL;
       PK_TOPOL_fctab_facet_face_t *facetFaceTable = NULL;
       PK_TOPOL_fctab_fin_edge_t *finEdgeTable = NULL;
       for (int i = 0; i < refTables.number_of_tables; i++)
       {
                       /// Assign the correct table to the facet table variables
            if (refTables.tables[i].fctab == PK_TOPOL_fctab_facet_fin_c)
            {
                           /// If this is the facet-fin table
                facetFinTable = refTables.tables[i].table.facet_fin;
            }
            else if (refTables.tables[i].fctab == PK_TOPOL_fctab_fin_data_c)
            {
                           /// If this is the fin-data table
                finDataTable = refTables.tables[i].table.fin_data;
            }
            else if (refTables.tables[i].fctab == PK_TOPOL_fctab_data_point_c)
            {
                           /// If this is the data-point table
                 dataPointTable = refTables.tables[i].table.data_point_idx;
            }
            else if (refTables.tables[i].fctab == PK_TOPOL_fctab_data_normal_c)
            {
                           /// If this is the data-normal table
                 dataNormalTable = refTables.tables[i].table.data_normal_idx;
            }
            else if (refTables.tables[i].fctab == PK_TOPOL_fctab_point_vec_c)
            {
                           /// If this is the point-vector table
                 pointVecTable = refTables.tables[i].table.point_vec;
            }
            else if (refTables.tables[i].fctab == PK_TOPOL_fctab_normal_vec_c)
            {
                           /// If this is the normal-vector table
                 normalVecTable = refTables.tables[i].table.normal_vec;
            }
            else if (refTables.tables[i].fctab == PK_TOPOL_fctab_facet_face_c)
            {
                           /// If this is the facet-face table
                 facetFaceTable = refTables.tables[i].table.facet_face;
            }
            else if (refTables.tables[i].fctab == PK_TOPOL_fctab_fin_edge_c)
            {
                           /// If this is the fin-edge table
                 finEdgeTable = refTables.tables[i].table.fin_edge;
            }
         }
       QList<PK_VECTOR_t> *vertexList = new QList<PK_VECTOR_t>();
       QList<PK_VECTOR_t> *normalList = new QList<PK_VECTOR_t>();
       QList<PK_FACE_t> *faceList = new QList<PK_FACE_t>();

	   QString dataCords;
        for (int i = 0; i < facetFinTable->length; i++)
        {
                       /// Get the fin ID
                       int finID = facetFinTable->data[i].fin;

                       // Get the index of the fin
                       int finIndex = finDataTable->data[finID];

                       /// Get the point of the fin
                       int point = dataPointTable->point[finIndex];

                       /// Get the vector that specifies the point in space
                      PK_VECTOR_t vertex = pointVecTable->vec[point];

                       /// Add the vertex to the vertices list
                       vertexList->push_back(vertex);
					   dataCords.push_back(","+QString::number(vertex.coord[0]));
					   dataCords.push_back(","+QString::number(vertex.coord[1]));
					   dataCords.push_back(","+QString::number(vertex.coord[2]));
                       /// Get the normal of the fin
                       int normalIndex = dataNormalTable->normal[finIndex];

                       /// Get the vector that specifies the normal
                       PK_VECTOR_t normal = normalVecTable->vec[normalIndex];

                       /// Add to the normals list
                       normalList->push_back(normal);

                       /// Get the facet id
                       /*int facetID = facetFinTable->data[i].facet;

                       /// Get the face tag
                       PK_FACE_t face = facetFaceTable->face[facetID];

                       /// Add to the face tag list
                       faceList->push_back(face);*/

          }
        PK_VECTOR_t vec_p;
        PK_POINT_t p_p;
        int count = 0;
        PK_POINT_sf_t point_sp[3];
		sendFileToClient(dataCords);

}

void  PsServer::sendFileToClient(QString data)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << PsClient::passFileToServer << data;
	qDebug()<<data;
    out.device()->seek(0);
    _clients.at(0)->_sok->write(block);
}
