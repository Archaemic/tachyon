#ifndef PTXN_Q_GAME_REGISTRY_VIEW_H
#define PTXN_Q_GAME_REGISTRY_VIEW_H

#include <QListView>
#include <QWidget>

class GameRegistryView : public QWidget {
Q_OBJECT
public:
	GameRegistryView(QWidget* parent = nullptr);

	QListView& listView() { return *m_listView; }
	const QListView& listView() const { return *m_listView; }

private:
	QListView* m_listView;
};

#endif
