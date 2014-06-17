#ifndef PTXN_Q_GAME_REGISTRY_VIEW_H
#define PTXN_Q_GAME_REGISTRY_VIEW_H

#include <QListView>
#include <QWidget>

class GameRegistry;

class GameRegistryView : public QWidget {
Q_OBJECT
public:
	GameRegistryView(QWidget* parent = nullptr);

	void setRegistry(GameRegistry* registry);

private:
	QListView* m_listView;
	GameRegistry* m_registry;

private slots:
	void openSavegame(const QModelIndex&);
};

#endif
