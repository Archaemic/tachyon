#include "GameRegistryView.h"

#include <QHBoxLayout>

GameRegistryView::GameRegistryView(QWidget* parent)
	: QWidget(parent)
	, m_listView(new QListView(this))
{
	QHBoxLayout* hbox = new QHBoxLayout;
	hbox->addWidget(m_listView);
	setLayout(hbox);
}
