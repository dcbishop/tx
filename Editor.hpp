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

	private:
		Object* object_;
		Tile* tile_;
		Interface* interface_;

		QPushButton* luaButton_;
		QLineEdit* luaLineEdit_;
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

	protected:
		QApplication *app_;
		EditorWin *window_;
};

#endif // TX_EDITOR_HPP
