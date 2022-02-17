#pragma once
#ifndef __TILE__
#define __TILE__

#include "NavigationObject.h"
#include "TileStatus.h"
#include "Label.h"
#include "NeighbourTile.h"
class Tile: public NavigationObject
{
public:
	Tile();


	~Tile();


	void draw() override;
	void update() override;
	void clean() override;


	Tile* getNeighbpourTile(NeighbourTile position);
	void setNeighbourTile(NeighbourTile position, Tile* tile);

	float getTIleCost() const;
	void setTileCost(float cost);
	TileStatus getTileStatus(TileStatus status);

	TileStatus getTileStatus() const;
	void setTileStatus(const TileStatus status);

	void addLabels();
	void setLabelsEnabled(bool state);

private:

	float m_cost;
	TileStatus m_status;

	Label* m_costLabel;
	Label* m_statusLabel;

	Tile* m_neighbours[NUM_OF_NEIGHBOUR_TILES];
};
#endif /* defined (__TILE__)  */