#include "Tile.h"
#include <filesystem>
#include "Config.h"
#include "Util.h"
#include <sstream>
#include <iomanip>
#include  "Label.h"

Tile::Tile(): m_cost(0.0f)
{
	setWidth(Config::TILE_SIZE);
	setHeight(Config::TILE_SIZE);
}
Tile::~Tile()

	= default;



void Tile::draw()
{
	Util::DrawRect(getTransform()->position, getWidth(), getHeight());
}

void Tile::update()
{
}

void Tile::clean()
{
}

Tile* Tile::getNeighbpourTile(NeighbourTile position)
{
	return m_neighbours[position];
}

void Tile::setNeighbourTile(NeighbourTile position, Tile* tile)
{
	m_neighbours[position] = tile;
}

float Tile::getTIleCost() const
{
	return m_cost;
}

void Tile::setTileCost(const float cost)
{
	m_cost = cost;

	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << m_cost;
	const std::string cost_string = stream.str();

	m_costLabel->setText(cost_string);
}

TileStatus Tile::getTileStatus(const TileStatus status) 
{
	
	return m_status;
}

void Tile::setTileStatus(TileStatus status)
{
	
	m_status = status;

	switch (m_status)
	{
	case UNVISITED:

		m_statusLabel->setText("=");

		break;
	case OPEN:
		m_statusLabel->setText("O");
		break;
	case CLOSED:
		m_statusLabel->setText("C");
		break;
	case IMPASSABLE:
		m_statusLabel->setText("I");
		break;
	case GOAL:
		m_statusLabel->setText("G");
		break;
	case START:
		m_statusLabel->setText("S");
		break;

	}
}

void Tile::addLabels()
{
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);

	m_statusLabel = new Label("99.9", "Consolas", 12);
	m_costLabel->getTransform()->position = getTransform()->position + offset + glm::vec2(0.0f, 6.0f);
	getParent()->addChild(m_costLabel);
	m_costLabel->setEnabled(false);
}

void Tile::setLabelsEnabled(bool state)
{
	m_costLabel->setEnabled(state);
	m_statusLabel->setEnabled(state);
}