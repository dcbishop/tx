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
	}
}

EditorWin::EditorWin() {
	interface_ = NULL;
	tile_ = NULL;
	object_ = NULL;

	resize(320, 340);
	//window_->show();
	setWindowTitle(QObject::tr("Tilexor Editor"));

	QHBoxLayout *luaLayout = new QHBoxLayout;

	QLabel *luaLabel = new QLabel(QObject::tr("Lua:"));
	luaLabel->setMaximumWidth(40);
	luaLayout->addWidget(luaLabel);

	luaComboBox_ = new QComboBox;
	luaComboBox_->setEditable(true);
	luaComboBox_->setMinimumWidth(200);
	luaLayout->addWidget(luaComboBox_);

	luaButton_ = new QPushButton(QObject::tr("Execute!"));
	luaButton_->setMaximumWidth(70);
	luaButton_->move(100, 100);
	luaButton_->show();
	QObject::connect(luaButton_, SIGNAL(clicked()), this, SLOT(luaExecute_()));
	QObject::connect(luaComboBox_->lineEdit(), SIGNAL(returnPressed()), this, SLOT(luaExecute_()));
	//QObject::connect(luaComboBox_, SIGNAL(activated(int)), this, SLOT(luaExecute_(int)));
	luaLayout->addWidget(luaButton_);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(luaLayout);

	setLayout(mainLayout);
}

/*EditorWin::~EditorWin() {
}*/

void EditorWin::luaExecute_() {
	DEBUG_M("Entering function...");

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
}

/**
 * Sets the object that the editor modifies.
 * @param object Pointer to the Object to modify.
 */
void EditorWin::setEditObject(Object* object) {
	DEBUG_M("Entering function...");
	object_ = object;
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
}
