#include "adopter.h"
#include "serializer.h"
#include "mousegestures.h"
#include "ui_mousegestures.h"
#include "pathcorrector.h"
#include "validpathcreator.h"
#include "GeometricForms.h"
#include "paintmanager.h"

//todo:: ���-�� ����� �������� ��������... ���� �� �� ����� �������
static const QString pathToFile = "../mouse_gestures.xml";
static const QString xmlDir = "../../../unreal/trunk/qrxml";

MouseGestures::MouseGestures(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MouseGestures)
{
    ui->setupUi(this);
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(loadFile()));
    connect(ui->twObjectPathTable, SIGNAL(currentItemChanged(QTableWidgetItem*,QTableWidgetItem*)), this, SLOT(drawGesture()));
    mPaintManager = new PaintManager(ui->gvGesture);
    Serializer serializer(pathToFile);
    this->mKeyObjectTable.add(serializer.deserialize());
    showTable();
}

void MouseGestures::changePath()
{
    int currentRow = ui->twObjectPathTable->currentRow();
    QString name = ui->twObjectPathTable->item(currentRow, objectColumn)->text();
    QString pathStr = ui->twObjectPathTable->item(currentRow, pathColumn)->text();
    QList<QPoint> path = Adopter::stringToPath(pathStr);
    if (!path.isEmpty())
        mKeyObjectTable.setPath(name, path);
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Invalid string. Path cannot be modified.");
        msgBox.exec();
        path = mKeyObjectTable.getPath(name);
        pathStr = Adopter::pathToString(path);
        ui->twObjectPathTable->item(currentRow, pathColumn)->setText(pathStr);
    }
    QString key = mKeyObjectTable.getKey(name);
    ui->twObjectPathTable->item(currentRow, keyColumn)->setText(key);
}

void MouseGestures::loadFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Xml"), xmlDir,
                                                    tr("Xml files (*.xml)"));
    Serializer serializer(fileName);
    EntityVector entities = serializer.parseXml();
    addEntities(entities);
    showTable();
}

void MouseGestures::showTable()
{
    this->disconnect(ui->twObjectPathTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(changePath()));
    for (int i = 0; i < this->mKeyObjectTable.size(); i ++)
    {
        KeyObjectItem object = this->mKeyObjectTable.at(i);
        int rowCount = ui->twObjectPathTable->rowCount();
        ui->twObjectPathTable->setRowCount(rowCount + 1);
        QTableWidgetItem *item = new QTableWidgetItem(object.object);
        item->setFlags(Qt::NoItemFlags);
        ui->twObjectPathTable->setItem(rowCount, objectColumn, item);
        QString text = Adopter::pathToString(object.correctPath);
        item = new QTableWidgetItem(text);
        ui->twObjectPathTable->setItem(rowCount, pathColumn, item);
        text = object.key;
        item = new QTableWidgetItem(text);
        item->setFlags(Qt::NoItemFlags);
        ui->twObjectPathTable->setItem(rowCount, keyColumn, item);
    }
    connect(ui->twObjectPathTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(changePath()));
}

void MouseGestures::addEntities(EntityVector const & entities)
{
    foreach (Entity entity, entities)
    {
        ValidPathCreator pathCreator;
        QList<QPoint> path = pathCreator.createPath(entity.components);
        mKeyObjectTable.add(entity.name, path);
    }
}

void MouseGestures::mouseMoveEvent(QMouseEvent * event)
{
    mMousePath.push_back(event->pos());
    this->update();
}

void MouseGestures::mouseReleaseEvent(QMouseEvent *event)
{
    mMousePath.push_back(event->pos());
    mCorrectPath = PathCorrector::correctPath(mMousePath);
    QString object = mKeyObjectTable.getObject(mCorrectPath);
    ui->teObject->setText(object);
    this->update();
}

void MouseGestures::mousePressEvent(QMouseEvent * event)
{
    mMousePath.clear();
    mCorrectPath.clear();
    mMousePath.push_back(event->pos());
    this->update();
}

void MouseGestures::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    PaintManager::drawPath(&painter, mMousePath);
    painter.setPen(Qt::red);
    PaintManager::drawPath(&painter, mCorrectPath);
}

void MouseGestures::drawGesture()
{
    int row = ui->twObjectPathTable->currentRow();
    QString pathStr = ui->twObjectPathTable->item(row, pathColumn)->text();
    mPaintManager->drawGesture(pathStr);
}

MouseGestures::~MouseGestures()
{
    Serializer serializer(pathToFile);
    serializer.serialize(this->mKeyObjectTable.getObjects());
    delete ui;
}