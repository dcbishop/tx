#include "Editor.hpp"
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
	QPushButton* setSizeButton = new QPushButton(tr("Set Size"));
	areaLayout->addWidget(areaLabel);
	areaLayout->addWidget(areaTagLineEdit_);
	areaLayout->addWidget(heightLabel);
	areaLayout->addWidget(heightLineEdit_);
	areaLayout->addWidget(WidthLabel);
	areaLayout->addWidget(widthLineEdit_);
	areaLayout->addWidget(setSizeButton);

	// Object list
	objectsListView_ = new QListWidget();
	hideTemporyCheckBox_ = new QCheckBox(tr("Hide tempory"));
	hideTemporyCheckBox_->setCheckState(Qt::Checked);
	QVBoxLayout *objectsLayout = new QVBoxLayout();
	objectsLayout->addWidget(objectsListView_);
	objectsLayout->addWidget(hideTemporyCheckBox_);
	QObject::connect(hideTemporyCheckBox_, SIGNAL(clicked()), this, SLOT(updateWindow()));
	QObject::connect(objectsListView_, SIGNAL(clicked(const QModelIndex &)), this, SLOT(objectSelected_(const QModelIndex &)));


	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(luaLayout);
	mainLayout->addLayout(areaLayout);
	mainLayout->addLayout(objectsLayout);

	setLayout(mainLayout);
}

/*EditorWin::~EditorWin() {
}*/

void EditorWin::updateWindow() {
	updateObjectList_();

	Area* area = interface_->getArea();
	if(!area) {
		return;
	}
	areaTagLineEdit_->setText(tr(area->getTag().c_str()));
	widthLineEdit_->setValue(area->getWidth());
	heightLineEdit_->setValue(area->getHeight());
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
}

void EditorWin::luaExecute_() {
	DEBUG_M("Entering function...");
	this->updateWindow();

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
	this->updateWindow();
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
