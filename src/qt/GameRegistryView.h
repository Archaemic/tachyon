#ifndef PTXN_Q_GAME_REGISTRY_VIEW_H
#define PTXN_Q_GAME_REGISTRY_VIEW_H

#include "ui_GameRegistryView.h"

#include <QWidget>

class GameRegistry;
class QTreeView;

class GameRegistryView : public QWidget {
Q_OBJECT
public:
	GameRegistryView(QWidget* parent = nullptr);

	void setRegistry(GameRegistry* registry);

private:
	Ui::GameRegistryView m_ui;

	GameRegistry* m_registry;

private slots:
	void openSavegame();
	void openSavegame(const QModelIndex&);
	void addFile();
	void addDirectory();
};

#endif
