#include "Cartridge.h"

#include "common/Game.h"

#include <QFile>
#include <QString>

Cartridge::Cartridge(const uint8_t* rom, const QString& sramPath, QObject* parent)
	: QObject(parent)
	, m_sram(new QFile(sramPath, this))
	, m_romMap(rom)
{
	m_sram->open(QIODevice::ReadWrite);
	m_sramMap = m_sram->map(0, m_sram->size());
	m_game = Game::load(m_sramMap, m_romMap);
}

Cartridge::~Cartridge() {
	m_game = nullptr;
	m_sram->unmap(m_sramMap);
	m_romMap = nullptr;
	m_sramMap = nullptr;
}

Game* Cartridge::game() {
	return m_game.get();
}
