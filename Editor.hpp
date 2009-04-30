#ifndef TX_EDITOR_HPP
#define TX_EDITOR_HPP

#include <QtGui>

#include "Object.hpp"
#include "Tile.hpp"
class Interface;

/**
 * A QTWindow for editing.
 */
class EditorWin : public QWidget {
	Q_OBJECT

	public:
		EditorWin();
		void setEditObject(Object* object);
		void setEditTile(Tile* tile);
		void setInterface(Interface* interface);

	public slots:
		virtual void luaExecute_();
		void updateWindow();

	private:
		void updateObjectList_();

		Object* object_;
		Tile* tile_;
		Interface* interface_;

		QPushButton* luaButton_;
		QComboBox* luaComboBox_;
		QListWidget* objectsListView_;
		QCheckBox* hideTemporyCheckBox_;
		QLineEdit* areaTagLineEdit_;
		QSpinBox* heightLineEdit_;
		QSpinBox* widthLineEdit_;
};

/**
 * An interface for map editing.
 */
class Editor {
	public:
		Editor();
		~Editor();
		void show();
		void hide();
		void processQtEvents();
		void setEditObject(Object* object);
		void setEditTile(Tile* tile);
		void setInterface(Interface* interface);
		void updateWindow();

	protected:
		QApplication *app_;
		EditorWin *window_;
		bool isHidden_;
};

#endif /* TX_EDITOR_HPP */
