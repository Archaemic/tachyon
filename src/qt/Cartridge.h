#ifndef PTXN_Q_CARTRIDGE_H
#define PTXN_Q_CARTRIDGE_H

#include <QObject>

class Game;
class QFile;
class QString;

class Cartridge : public QObject {
Q_OBJECT
public:
	Cartridge(const uint8_t* rom, const QString& sramPath, QObject* parent = nullptr);
	virtual ~Cartridge();

	Game* game();

private:
	QFile* m_sram;
	std::unique_ptr<Game> m_game;
	const uint8_t* m_romMap;
	uchar* m_sramMap;
};

#endif
