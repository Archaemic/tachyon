#include "Cartridge.h"

#include "common/Game.h"

#include <QFile>
#include <QString>

Cartridge::Cartridge(const QString& romPath, const QString& sramPath, QObject* parent)
	: QObject(parent)
	, m_rom(new QFile(romPath, this))
	, m_sram(new QFile(sramPath, this))
{
	m_rom->open(QIODevice::ReadOnly);
	m_sram->open(QIODevice::ReadWrite);
	m_romMap = m_rom->map(0, m_rom->size());
	m_sramMap = m_sram->map(0, m_sram->size());
	m_game = Game::load(m_sramMap, m_romMap);
}

Cartridge::~Cartridge() {
	m_game = nullptr;
	m_rom->unmap(m_romMap);
	m_sram->unmap(m_sramMap);
	m_romMap = nullptr;
	m_sramMap = nullptr;
}

Game* Cartridge::game() {
	return m_game.get();
}
