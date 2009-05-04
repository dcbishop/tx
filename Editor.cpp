#include "Editor.hpp"

#include <stdio.h>
#include <stdlib.h>

#include "Interface.hpp"
#include "console.h"

Editor::Editor() {
	DEBUG_M("Entering function...");
	LOG("Initilizing Qt editing interface...");
	int dummy = 0;
	char* dummy2 = NULL;
	app_ = new QApplication(dummy, &dummy2);
	window_ = new EditorWin();
	app_->processEvents();
	isHidden_ = true;

	DEBUG_H("Exiting function...");
}

Editor::~Editor() {
	// I assume QT cleans up after itself since trying to delete
	// anything segfaults

	//delete button_;
	//delete window_;
	//delete window2_;
	//delete app_;
}

/**
 * Makes the Qt editing windows appear.
 */
void Editor::show() {
	DEBUG_M("Entering function...");
	isHidden_ = false;
	window_->show();
}

/**
 * Makes the QT eidting windows disapear.
 */
void Editor::hide() {
	DEBUG_M("Entering function...");
	isHidden_ = true;
	window_->hide();
}

/**
 * Sets the object that the editor modifies.
 * @param object Pointer to the Object to modify.
 */
void Editor::setEditObject(Object* object) {
	DEBUG_M("Entering function...");
	window_->setEditObject(object);
}

/**
 * Sets the tile that the editor modifies.
 * @param tile Pointer to the Tile to modify.
 */
void Editor::setEditTile(Tile* tile) {
	DEBUG_M("Entering function...");
	window_->setEditTile(tile);
}

/**
 * Sets the interface the Editor is bound to.
 * @param The interface
 */
void Editor::setInterface(Interface* interface) {
	window_->setInterface(interface);
}

/**
 * The Qt event processor, makes buttons click, etc...
 */
void Editor::processQtEvents() {
	//DEBUG_V("Entering function...");
	if(isHidden_) {
		window_->hide();
	} else {
		app_->processEvents();
		//window_->updateObjectList();
	}
}

/**
 * Updates information in the editor window.
 */
void Editor::updateWindow() {
	if(!isHidden_) {
		window_->updateWindow();
	}
}

EditorWin::EditorWin() {
	interface_ = NULL;
	tile_ = NULL;
	object_ = NULL;

	resize(320, 340);
	//window_->show();
	setWindowTitle(QObject::tr("Tilexor Editor"));

	// Lua shell
	QHBoxLayout *luaLayout = new QHBoxLayout();
	QLabel *luaLabel = new QLabel(QObject::tr("Lua:"));
	luaLabel->setMaximumWidth(40);
	luaLayout->addWidget(luaLabel);

	luaComboBox_ = new QComboBox;
	luaComboBox_->setEditable(true);
	luaComboBox_->setMinimumWidth(200);
	luaComboBox_->addItem(tr("print('Hello World!')"));
	luaComboBox_->addItem(tr("player = gm:getObjectByTag('Player')"));
	luaComboBox_->addItem(tr("print('Clear area'); area = gm:getAreaByTag('TestArea'); area:fill(0, 0, area.width-1, area.height-1, 'data/models/floor.dae', false, 0.0)"));
	luaComboBox_->addItem(tr("print('Resize area test'); area = gm:getAreaByTag('TestArea'); area.width = area.width + 1"));
	luaComboBox_->addItem(tr("print('Big room'); area = gm:getAreaByTag('TestArea'); area:boxRoom(area.width*(1/4), area.height*(1/4), area.width*(3/4), area.height*(3/4))"));	
	luaLayout->addWidget(luaComboBox_);

	luaButton_ = new QPushButton(QObject::tr("Execute!"));
	luaButton_->setMaximumWidth(70);
	luaButton_->move(100, 100);
	luaButton_->show();
	QObject::connect(luaButton_, SIGNAL(clicked()), this, SLOT(luaExecute_()));
	QObject::connect(luaComboBox_->lineEdit(), SIGNAL(returnPressed()), this, SLOT(luaExecute_()));
	//QObject::connect(luaComboBox_, SIGNAL(activated(int)), this, SLOT(luaExecute_(int)));
	luaLayout->addWidget(luaButton_);

	// Area information
	QHBoxLayout *areaLayout = new QHBoxLayout();
	QLabel *areaLabel = new QLabel(QObject::tr("Area:"));
	QLabel *heightLabel = new QLabel(QObject::tr("Height:"));
	QLabel *WidthLabel = new QLabel(QObject::tr("Width:"));
	areaTagLineEdit_ = new QLineEdit();
	heightLineEdit_ = new QSpinBox();
	widthLineEdit_ = new QSpinBox();
	QPushButton* setSizeButton = new QPushButton(tr("Set Area"));
	areaLayout->addWidget(areaLabel);
	areaLayout->addWidget(areaTagLineEdit_);
	areaLayout->addWidget(heightLabel);
	areaLayout->addWidget(heightLineEdit_);
	areaLayout->addWidget(WidthLabel);
	areaLayout->addWidget(widthLineEdit_);
	areaLayout->addWidget(setSizeButton);
	QObject::connect(setSizeButton, SIGNAL(clicked()), this, SLOT(setArea_()));

	// Object list
	objectsListView_ = new QListWidget();
	hideTemporyCheckBox_ = new QCheckBox(tr("Hide tempory"));
	hideTemporyCheckBox_->setCheckState(Qt::Checked);
	QLabel *newLabel = new QLabel(QObject::tr("New:"));
	//QVBoxLayout *objectsLayout = new QVBoxLayout();
	QPushButton* newObjectButton = new QPushButton(tr("Object"));
	QPushButton* newRigidBodyButton = new QPushButton(tr("RigidBody"));
	QPushButton* newCreatureButton = new QPushButton(tr("Creature"));
	QObject::connect(newObjectButton, SIGNAL(clicked()), this, SLOT(newObject_()));
	QObject::connect(newRigidBodyButton, SIGNAL(clicked()), this, SLOT(newRigidBody_()));
	QObject::connect(newCreatureButton, SIGNAL(clicked()), this, SLOT(newCreature_()));

	QGridLayout* objectsLayout = new QGridLayout();
	objectsLayout->addWidget(objectsListView_,0,0,1,6);
	objectsLayout->addWidget(hideTemporyCheckBox_,1,0);
	objectsLayout->addWidget(newLabel, 1,1);
	objectsLayout->addWidget(newObjectButton, 1,2);
	objectsLayout->addWidget(newRigidBodyButton, 1,3);
	objectsLayout->addWidget(newCreatureButton, 1,4);

	//Object information
	QGridLayout* objectLayout = new QGridLayout();

	QLabel *objectTypeLabel = new QLabel(QObject::tr("Object"));
	QLabel *tagLabel = new QLabel(QObject::tr("Tag:"));
	QLabel *xLabel = new QLabel(QObject::tr("X:"));
	QLabel *yLabel = new QLabel(QObject::tr("Y:"));
	QLabel *zLabel = new QLabel(QObject::tr("Z:"));
	QLabel *rxLabel = new QLabel(QObject::tr("RX:"));
	QLabel *ryLabel = new QLabel(QObject::tr("RY:"));
	QLabel *rzLabel = new QLabel(QObject::tr("RZ:"));
	QLabel *raLabel = new QLabel(QObject::tr("RA:"));
	QLabel *onUpdateLabel = new QLabel(QObject::tr("Update Script:"));

	objTagLineEdit_ = new QLineEdit();
	xSpinbox_ = new QDoubleSpinBox();
	ySpinbox_ = new QDoubleSpinBox();
	zSpinbox_ = new QDoubleSpinBox();
	rxSpinbox_ = new QDoubleSpinBox();
	rySpinbox_ = new QDoubleSpinBox();
	rzSpinbox_ = new QDoubleSpinBox();
	raSpinbox_ = new QDoubleSpinBox();
	xSpinbox_->setRange(-9999.0, 9999.0);
	ySpinbox_->setRange(-9999.0, 9999.0);
	zSpinbox_->setRange(-9999.0, 9999.0);
	rxSpinbox_->setRange(-9999.0, 9999.0);
	rySpinbox_->setRange(-9999.0, 9999.0);
	rzSpinbox_->setRange(-9999.0, 9999.0);
	raSpinbox_->setRange(-9999.0, 9999.0);
	objOnUpdateLineEdit_ = new QLineEdit();

	objectLayout->addWidget(objectTypeLabel, 0, 0);
	objectLayout->addWidget(tagLabel, 1, 0);
	objectLayout->addWidget(objTagLineEdit_, 1, 1);
	objectLayout->addWidget(xLabel, 2, 0);
	objectLayout->addWidget(xSpinbox_, 2, 1);
	objectLayout->addWidget(yLabel, 3, 0);
	objectLayout->addWidget(ySpinbox_, 3, 1);
	objectLayout->addWidget(zLabel, 4, 0);
	objectLayout->addWidget(zSpinbox_, 4, 1);
	objectLayout->addWidget(rxLabel, 5, 0);
	objectLayout->addWidget(rxSpinbox_, 5, 1);
	objectLayout->addWidget(ryLabel, 6, 0);
	objectLayout->addWidget(rySpinbox_, 6, 1);
	objectLayout->addWidget(rzLabel, 7, 0);
	objectLayout->addWidget(rzSpinbox_, 7, 1);
	objectLayout->addWidget(raLabel, 8, 0);
	objectLayout->addWidget(raSpinbox_, 8, 1);
	objectLayout->addWidget(onUpdateLabel, 9, 0);
	objectLayout->addWidget(objOnUpdateLineEdit_, 9, 1);

	QObject::connect(hideTemporyCheckBox_, SIGNAL(clicked()), this, SLOT(updateWindow()));
	QObject::connect(objectsListView_, SIGNAL(clicked(const QModelIndex &)), this, SLOT(objectSelected_(const QModelIndex &)));

	QObject::connect(objTagLineEdit_, SIGNAL(textChanged(const QString &)), this, SLOT(setObject_()));
	QObject::connect(xSpinbox_, SIGNAL(valueChanged(double)), this, SLOT(setObject_()));
	QObject::connect(ySpinbox_, SIGNAL(valueChanged(double)), this, SLOT(setObject_()));
	QObject::connect(zSpinbox_, SIGNAL(valueChanged(double)), this, SLOT(setObject_()));
	QObject::connect(rxSpinbox_, SIGNAL(valueChanged(double)), this, SLOT(setObject_()));
	QObject::connect(rySpinbox_, SIGNAL(valueChanged(double)), this, SLOT(setObject_()));
	QObject::connect(rzSpinbox_, SIGNAL(valueChanged(double)), this, SLOT(setObject_()));
	QObject::connect(raSpinbox_, SIGNAL(valueChanged(double)), this, SLOT(setObject_()));
	QObject::connect(objOnUpdateLineEdit_, SIGNAL(textChanged(const QString &)), this, SLOT(setObject_()));

	isUpdating_ = false;
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(luaLayout);
	mainLayout->addLayout(areaLayout);
	mainLayout->addLayout(objectsLayout);
	//mainLayout->addWidget(objectTypeLabel);
	mainLayout->addLayout(objectLayout);

	setLayout(mainLayout);
}

/*EditorWin::~EditorWin() {
}*/

void EditorWin::setArea_() {
	DEBUG_M("Entering function...");
	Area* area = interface_->getArea();
	if(!area) {
		return;
	}

	int x = widthLineEdit_->value();
	int y = heightLineEdit_->value();
	area->setSize(x, y);

	string tag = areaTagLineEdit_->text().toStdString();
	if(area->getTag() != tag) {
		area->setTag(tag);
	}
}

void EditorWin::newObject_() {
	DEBUG_A("Entering function...");
	//Object* selected = interface_->getSelectedObject();
	//Object* object = selected.clone();

	/*if(isPlaced_ == false) {
		DELETE(selected);
	}*/
	static int objects = 0;
	//char* tag = "UntaggedObject";
	//snprintf(tag, 9, 
	string tag = "Object_";
	char num[6];
	snprintf(num, 6, "%0d", objects++);
	tag.append(num);

	VModel* model = new VModel("data/models/cube.dae");
	Object* object = new Object(tag, model);
	interface_->setSelectedObject(object);
	interface_->setEditModeObject();
	updateWindow();
}

void EditorWin::setObject_() {
	DEBUG_M("Entering function...");
	if(isUpdating_ == true) {
		return;
	}

	Object* object = interface_->getSelectedObject();
	if(!object) {
		return;
	}

	//LOG("%s", object->getTag());

	object->setTag(objTagLineEdit_->text().toStdString());
	object->setPos(xSpinbox_->value(), ySpinbox_->value(), zSpinbox_->value());
	object->setRotX(rxSpinbox_->value());
	object->setRotY(rySpinbox_->value());
	object->setRotZ(rzSpinbox_->value());
	object->setRotAngle(raSpinbox_->value());
	object->setScript(SCRIPT_ONUPDATE, objOnUpdateLineEdit_->text().toStdString());

	//object->setX(xSpinbox_->value());
	//object->setY(ySpinbox_->value());
	//object->setZ(zSpinbox_->value());
}

void EditorWin::updateWindow() {
	isUpdating_ = true;
	updateObjectList_();
	updateObject_();

	Area* area = interface_->getArea();
	if(!area) {
		isUpdating_ = false;
		return;
	}
	areaTagLineEdit_->setText(tr(area->getTag().c_str()));
	widthLineEdit_->setValue(area->getWidth());
	heightLineEdit_->setValue(area->getHeight());
	isUpdating_ = false;
}

/**
 * Updates the information about the selected object.
 */
void EditorWin::updateObject_() {
	Object* object = interface_->getSelectedObject();
	if(!object) {
		return;
	}

	objTagLineEdit_->setText(tr(object->getTag().c_str()));
	xSpinbox_->setValue(object->getX());
	ySpinbox_->setValue(object->getY());
	zSpinbox_->setValue(object->getZ());
	rxSpinbox_->setValue(object->getRotX());
	rySpinbox_->setValue(object->getRotY());
	rzSpinbox_->setValue(object->getRotZ());
	raSpinbox_->setValue(object->getRotAngle());
	objOnUpdateLineEdit_->setText(tr(object->getScript(SCRIPT_ONUPDATE).c_str()));
}

/**
 * Updates the list of Objects.
 */
void EditorWin::updateObjectList_() {
	Area* area = interface_->getArea();
	if(!area) {
		return;
	}

	objectsListView_->clear();
	for(ChildrenIterator iter = area->getFirstChild(); iter < area->getChildEnd(); iter++) {

		Object* object = dynamic_cast<Object*>(*iter);
		if(!object) {
			continue;
		}
		if(hideTemporyCheckBox_->checkState() && object->isTempory()) {
			continue;
		}
		//objectsListView_->addItem(tr(object->getTag().c_str()));
		QListWidgetItem* item = new QListWidgetItem(tr(object->getTag().c_str()), objectsListView_);
		//QPointer<void*> ptr = new QPointer(object);
		//QPointer<void> ptr = (void*)object;
		QVariant v;
		v.setValue(object);
		item->setData(Qt::UserRole, v);
		objectsListView_->addItem(item);

		if(object == interface_->getSelectedObject()) {
			objectsListView_->setCurrentItem(item);
		}
	}
}


void EditorWin::objectSelected_(const QModelIndex&) {
	DEBUG_A("Selected!");
	QListWidgetItem* current = objectsListView_->currentItem();
	//QVariant *v = current->data(Qt::UserRole);
	//Object* object = v->value<Object*>();
	Object* object = current->data(Qt::UserRole).value<Object*>();
	interface_->setSelectedObject(object);
	updateWindow();
}

void EditorWin::luaExecute_() {
	DEBUG_M("Entering function...");
	updateWindow();

	if(!interface_) {
		return;
	}

	GameManager* gm = interface_->getGameManager();
	if(!gm) {
		return;
	}

	Scripting& sc = gm->getScripting();
	if(!&sc) {
		return;
	}

	if(!luaComboBox_) {
		return;
	}

	if(luaComboBox_->currentText().length() <= 0) {
		return;
	}

	string str = luaComboBox_->currentText().toStdString();
	sc.doString(str);
	luaComboBox_->clearEditText();
	updateWindow();
}


/**
 * Sets the object that the editor modifies.
 * @param object Pointer to the Object to modify.
 */
void EditorWin::setEditObject(Object* object) {
	DEBUG_M("Entering function...");
	object_ = object;
	this->updateWindow();
}

/**
 * Sets the tile that the editor modifies.
 * @param tile Pointer to the Tile to modify.
 */
void EditorWin::setEditTile(Tile* tile) {
	DEBUG_M("Entering function...");
	tile_ = tile;
}

/**
 * Sets the interface the Editor is bound to.
 * @param The interface
 */
void EditorWin::setInterface(Interface* interface) {
	interface_ = interface;
	this->updateWindow();
}
