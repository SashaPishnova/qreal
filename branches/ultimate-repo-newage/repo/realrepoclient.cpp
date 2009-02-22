/** @file realrepoclient.cpp
 * 	@brief API для доступа к репозиторию
 * */
#include "realrepoclient.h"
//#define _LONG_DEBUG
#include "dbg.h"

#include <QDataStream>
#include <QByteArray>
#include <QStringList>

using namespace qRealTypes;

RealRepoClient::RealRepoClient( const QString &addr, const int port, QObject *parent ) : QObject(parent)
{
dbg;
	socket = new QTcpSocket(this);
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

	socket->abort();
	m_error = -1;
	socket->connectToHost(addr, port);
		if (!socket->waitForConnected(5*1000)) {
//		emit socket->error(socket->error(), socket->errorString());
		qDebug() << "cannot connect to the server" << endl;
			return;
		}
	m_error = socket->error();
}

RealRepoClient::~RealRepoClient()
{
dbg;
	socket->disconnectFromHost();
	if (socket->state() == QAbstractSocket::UnconnectedState ||  socket->waitForDisconnected(1000))
		qDebug("Disconnected!");
}

QString RealRepoClient::sendData( QString data )
{
dbg;
	if( socket->state() != QAbstractSocket::ConnectedState )
		return "";

	//QString data = QString("%1\t%2\t%3\t%4\t").arg(CMD_CREATE_ENTITY).arg(type).arg(id).arg(name);
//	qDebug() << "[CLIENT]: sending" << data;
	//int bytes =
	socket->write(data.toUtf8());
//	qDebug() << "written " << bytes << " bytes";
	//bool res =
	socket->waitForReadyRead();
//	qDebug() << "ready - " << res;
	QByteArray req = socket->readAll();
//	qDebug() << "[CLIENT]: recvd" << req;
	return extractData(QString::fromUtf8(req));
}

void RealRepoClient::displayError(QAbstractSocket::SocketError socketError)
{
dbg;
	switch (socketError) {
		case QAbstractSocket::RemoteHostClosedError:
			qDebug() << "QAbstractSocket::RemoteHostClosedError";
			break;
		case QAbstractSocket::ConnectionRefusedError:
			qDebug() << "ConnectionRefusedError";
			break;
		default:
			qDebug() << socket->errorString();
		break;
	}
	m_error = socketError;
}

QString RealRepoClient::extractData(QString const &resp)
{
	QString errorCode = resp.section('\t', 0, 0);
	bool errCodeCorrect = false;
	if (errorCode.toInt(&errCodeCorrect) != ERR_STATUS_OK || !errCodeCorrect)
	{
		throw errorCode;  // TODO: Throw something more appropriate.
	} else
	{
		return resp.section('\t', 1);
	}
}

QString RealRepoClient::getName( int id )
{
dbg;
	QString data = QString("%1\t%2\t").arg(CMD_GET_NAME).arg(id);
	return sendData(data);
}

int RealRepoClient::setName( int id, QString name )
{
dbg;
	QString data = QString("%1\t%2\t%3\t").arg(CMD_SET_NAME).arg(id).arg(name);
	return sendData(data).toInt();
}

void RealRepoClient::setPosition( int id, int parent, int x, int y)
{
dbg;
	QString data = QString("%1\t%2\t%3\t%4\t%5\t").arg(CMD_SET_POSITION).arg(id).arg(parent).arg(x).arg(y);
	QString resp = sendData(data);
//	qDebug() << "recvd" << resp;
}

void RealRepoClient::setDescription( int id, QString desc )
{
dbg;
	QString data = QString("%1\t%2\t%3\t").arg(CMD_SET_DESCRIPTION).arg(id).arg(desc);
	QString resp = sendData(data);
}

QString RealRepoClient::getDescription( int id )
{
dbg;
	QString data = QString("%1\t%2\t").arg(CMD_GET_DESCRIPTION).arg(id);
	QString resp = sendData(data);
	return resp;
}

int RealRepoClient::setPropValue( int id, QString name, QString value)
{
dbg;
	QString data = QString("%1\t%2\t%3\t%4\t").arg(CMD_SET_PROPERTY).arg(id).arg(name).arg(value);
	QString resp = sendData(data);
	return resp.toInt();
}

QString RealRepoClient::getPropValue( int id, QString name )
{
dbg;
	QString data = QString("%1\t%2\t%3\t").arg(CMD_GET_PROPERTY).arg(id).arg(name);
	QString resp = sendData(data);
	return resp;
}

int RealRepoClient::createObject(TypeIdType type, QString name)
{
dbg;
	qDebug() << "creating a new entity: " << type << name;
	QString data = QString("%1\t%2\t%3\t").arg(CMD_CREATE_ENTITY).arg(type).arg(name);
	QString resp = sendData(data);
	return resp.toInt();
}

int RealRepoClient::copyEntity(TypeIdType type, int id, int newParent, int oldParent, bool full)
{
dbg;
	QString data;
	if( !full )
		data = QString("%1\t%2\t%3\t%4\t%5\t").arg(CMD_COPY_ENTITY).arg(type).arg(id).arg(newParent).arg(oldParent);
	else
		data = QString("%1\t%2\t%3\t%4\t%5\t").arg(CMD_FULLCOPY_ENTITY).arg(type).arg(id).arg(newParent).arg(oldParent);
	QString resp = sendData(data);
	return resp.toInt();
}

int RealRepoClient::createObjectWithParent(TypeIdType type, QString name, int parent)
{
dbg;
	qDebug() << "creating a new entity: " << type << name << parent;
	QString data = QString("%1\t%2\t%3\t%4\t").arg(CMD_CREATE_ENTITY).arg(type).arg(name).arg(parent);
	QString resp = sendData(data);
	return resp.toInt();
//	qDebug() << "recvd" << resp;
}

int RealRepoClient::createLink(QString name)
{
	return createObject("krneDirRelationship", name);
}

int RealRepoClient::createLinkWithType(QString name, TypeIdType type)
{
	qDebug() << ">>>>type: "<< type << endl;
	return createObject(type, name);
}

int RealRepoClient::createLinkWithParent(TypeIdType type, QString name, int parent)
{
	return createObjectWithParent(type, name, parent);
}

void RealRepoClient::deleteObject(int id, int parent)
{
dbg;
	QString data = QString("%1\t%2\t%3\t").arg(CMD_DELETE_ENTITY).arg(id).arg(parent);
	QString resp = sendData(data);
}

void RealRepoClient::deleteObject( int id )
{
	QIntList parents = getParents(id);
	foreach (int parent, parents) {
		deleteObject(id, parent);
	}
}

void RealRepoClient::deleteLink(int id, int parent)
{
	deleteObject(id, parent);
}

void RealRepoClient::deleteLink(int id)
{
	deleteObject(id);
}

int RealRepoClient::getTypesCount()
{
dbg;
	return sendData(QString::number(CMD_GET_TYPES_COUNT)).toInt();
}

QList<TypeIdType> RealRepoClient::getAllTypes()
{
dbg;
	QString res = sendData(QString::number(CMD_GET_ALL_TYPES));
	QList<TypeIdType> list;
	foreach( QString str, res.split('\t') )
		list << str;
	list.removeLast(); // WTF???
	return list;
}

#if 0 // see header file.
TypeInfo RealRepoClient::getTypeInfo( int arg )
{
dbg;
	TypeInfo info;
	QString cmd = QString("%1\t%2").arg(CMD_GET_TYPE_INFO).arg(arg);
	QString resp = sendData(cmd);
	int id = resp.section("\t",0,0).toInt();

	if( id == INVALID_ID ){
		// handle error
		// return info;
	}
//	qDebug() << "recvd info " << resp;
	info.fromString(resp);
	return info;
}
#endif

int RealRepoClient::getLastError()
{
dbg;
	return m_error;
}

QString RealRepoClient::getObjectsByType( TypeIdType type )
{
	QString cmd = QString("%1\t%2").arg(CMD_GET_OBJECTS_BY_TYPE).arg(type);
	QString resp = sendData(cmd);
	return resp;
}

QList<int> RealRepoClient::getObjectsListByType( TypeIdType type )
{
	QString resp = getObjectsByType(type);

	QList<int> list;
	foreach( QString str, resp.split('\t') )
		list += str.toInt();
	if( resp == "\t" )
		list.clear();
	return list;
}

QIntList RealRepoClient::getLinks()
{
	return getObjectsListByType("krneDirRelationship");
}


QString RealRepoClient::getObjectData(int id )
{
	QString cmd = QString("%1\t%2").arg(CMD_GET_OBJECT_DATA).arg(id);
	QString resp = sendData(cmd);
	return resp;
}

QString RealRepoClient::getChildren( int id )
{
	QString cmd = QString("%1\t%2\t").arg(CMD_GET_CHILDREN).arg(id);
	QString resp = sendData(cmd);
	return resp;
}

QIntList RealRepoClient::getParents(int id)
{
	QString cmd = QString("%1\t%2\t").arg(CMD_GET_CONTAINERS).arg(id);
	QString resp = sendData(cmd);
	QIntList list;
	foreach (QString str, resp.split('\t', QString::SkipEmptyParts))
		list += str.toInt();
	return list;
}

QString RealRepoClient::getPosition( int id, int parent )
{
	QString cmd = QString("%1\t%2\t%3\t").arg(CMD_GET_POSITION).arg(id).arg(parent);
	QString resp = sendData(cmd);
	return resp;
}

int RealRepoClient::setConfiguration( int id, int parent, QString conf)
{
dbg;
	QString cmd = QString("%1\t%2\t%3\t%4\t").arg(CMD_SET_CONFIGURATION).arg(id).arg(parent).arg(conf);
	QString resp = sendData(cmd);
	return resp.toInt();
}

QString RealRepoClient::getConfiguration( int id, int parent)
{
dbg;
	QString cmd = QString("%1\t%2\t%3\t").arg(CMD_GET_CONFIGURATION).arg(id).arg(parent);
	QString resp = sendData(cmd);
	return resp;
}

QString RealRepoClient::getEntireObject( int id )
{
dbg;
	//QString cmd = QString("%1\t%2\t%3\t").arg(CMD_GET_ENTIRE_OBJECT).arg(type).arg(id);
	QString cmd = QString("%1\t%2\t").arg(CMD_GET_ENTIRE_OBJECT).arg(id);
	QString resp = sendData(cmd);
	return resp;
}

RealObject RealRepoClient::getObjectById( int id )
{
dbg;
	QString data = getEntireObject(id);
	RealObject obj;
	obj.setTypeId(data.section("\t",0,0));
	obj.setId(id);
	obj.setVisibility(true);
	obj.setName(data.section("\t",2,2));
	obj.setDescription(data.section("\t",3,3));

	int childCount = data.section("\t",4,4).toInt();
	int counter = 5;
	for( int i=0; i<childCount; i++){
		obj.addChildElement(data.section("\t",counter,counter).toInt());
		counter++;
	}

	int incLinksCount = data.section("\t",counter,counter).toInt();
	counter++;
	for( int i=0; i<incLinksCount; i++){
		obj.addIncomingLink(data.section("\t",counter,counter).toInt());
		counter++;
	}

	int outcLinksCount = data.section("\t",counter,counter).toInt();
	counter++;
	for( int i=0; i<outcLinksCount; i++){
		obj.addOutcomingLink(data.section("\t",counter,counter).toInt());
		counter++;
	}

	int propsCount = data.section("\t",counter,counter).toInt();
	counter++;
	for( int i=0; i<propsCount; i++ ){
		QString pair = data.section("\t",counter,counter);
		obj.setProperty(pair.section(";",0,0), pair.section(";",1,1));
		counter++;
	}
	obj.setRepoClient(this);
	return obj;
}

RealLink RealRepoClient::getLinkById( int id )
{
dbg;
	QString data = getEntireObject(id);
	RealLink link;
	link.setTypeId(data.section("\t",0,0));
	link.setId(data.section("\t",1,1).toInt());
	link.setName(data.section("\t",3,3));
	link.setDescription(data.section("\t",4,4));

	int fromId = data.section("\t",5,5).toInt();
	int counter = 6;
	link.setFromId(fromId);

	int toId = data.section("\t",counter,counter).toInt();
	counter++;
	link.setToId(toId);

	int propsCount = data.section("\t",counter,counter).toInt();
	counter++;
	for( int i=0; i<propsCount; i++ ){
		QString pair = data.section("\t",counter,counter);
		link.setProperty(pair.section(";",0,0), pair.section(";",1,1));
		counter++;
	}
	link.setRepoClient(this);
	return link;
}

QString RealRepoClient::getLinksByObject( int id, int direction )
{
dbg;
	QString cmd = QString("%1\t%2\t%3\t").arg(CMD_GET_LINKS_BY_OBJECT).arg(id).arg(direction);
	QString resp = sendData(cmd);
	return resp;
}

QString RealRepoClient::getObjectsByLink( int id )
{
dbg;
	QString cmd = QString("%1\t%2\t").arg(CMD_GET_OBJECTS_BY_LINK).arg(id);
	QString resp = sendData(cmd);
	return resp;
}

QIntList RealRepoClient::getTypesByMetaType( const MetaType arg )
{
dbg;
	QString cmd = QString("%1\t%2\t").arg(CMD_GET_TYPES_BY_METATYPE).arg(arg);
	QString resp = sendData(cmd);
	QIntList list;
	foreach( QString str, resp.split('\t') )
		if( str.toInt() != 0 )
			list += str.toInt();
	return list;
}


RealType RealRepoClient::getTypeById( const TypeIdType id )
{
dbg;
	QString cmd = QString("%1\t%2").arg(CMD_GET_TYPE_INFO).arg(id);
	QString data = sendData(cmd);
	RealType type;
	type.loadFromString(data);

	return type;
}

RealType RealRepoClient::getTypeByName( const QString name )
{
dbg;
	QString cmd = QString("%1\t%2").arg(CMD_GET_TYPE_BY_NAME).arg(name);
	QString data = sendData(cmd);
	RealType type;
	type.loadFromString(data);

	return type;
}

int RealRepoClient::getTypeIdByName( const QString name )
{
	return getTypeByName(name).getId();
}

void RealRepoClient::addLink( int obj_id, int link_id, int direction )
{
dbg;
	QString cmd = QString("%1\t%2\t%3\t%4\t").arg(CMD_ADD_LINK).arg(obj_id).arg(link_id).arg(direction);
	sendData(cmd);
}

void RealRepoClient::removeLink( int obj_id, int link_id, int direction )
{
dbg;
	QString cmd = QString("%1\t%2\t%3\t%4\t").arg(CMD_REMOVE_LINK).arg(obj_id).arg(link_id).arg(direction);
	sendData(cmd);
}

