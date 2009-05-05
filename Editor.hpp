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
		void objectSelected_(const QModelIndex &);
		void setArea_();
		void updateObject_();
		void setObject_();
		void newObject_();
		void newRigidBody_();
		void newCreature_();
		void deleteObject_();
		void setModel_(const QModelIndex &index);

	private:
		void updateObjectList_();
		Object* object_;
		Tile* tile_;
		Interface* interface_;
		bool isUpdating_;

		QPushButton* luaButton_;
		QComboBox* luaComboBox_;
		QListWidget* objectsListView_;
		QCheckBox* hideTemporyCheckBox_;
		QLineEdit* areaTagLineEdit_;
		QSpinBox* heightLineEdit_;
		QSpinBox* widthLineEdit_;
		QDirModel* modelsDirModel_;
		QListView* modelsListView_;

		QCheckBox* invisibleCheckBox_;
		QLineEdit* objTagLineEdit_;
		QDoubleSpinBox* xSpinbox_;
		QDoubleSpinBox* ySpinbox_;
		QDoubleSpinBox* zSpinbox_;
		QDoubleSpinBox* rxSpinbox_;
		QDoubleSpinBox* rySpinbox_;
		QDoubleSpinBox* rzSpinbox_;
		QDoubleSpinBox* raSpinbox_;
		QLineEdit* objOnUpdateLineEdit_;
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

Q_DECLARE_METATYPE( Object* )

#endif /* TX_EDITOR_HPP */
