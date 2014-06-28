#ifndef PTXN_Q_GAME_REGISTRY_VIEW_H
#define PTXN_Q_GAME_REGISTRY_VIEW_H

#include <QWidget>

class GameRegistry;
class QTreeView;

class GameRegistryView : public QWidget {
Q_OBJECT
public:
	GameRegistryView(QWidget* parent = nullptr);

	void setRegistry(GameRegistry* registry);

private:
	QTreeView* m_listView;
	GameRegistry* m_registry;

private slots:
	void openSavegame(const QModelIndex&);
};

#endif
