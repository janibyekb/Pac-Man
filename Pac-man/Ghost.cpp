#include "Ghost.h"
#include "Djikstra_Search.h"
#include <iostream>

Ghost::Ghost(Tile* tile, Texture* texture)
{
	// Set all variables to default state
	currTile = tile;
	nextTile = NULL;

	if (currTile != NULL) {
		currTile->SetGhost(this);
		nextTile = tileGraph->GetTileAt(currTile->GetPosition().x, currTile->GetPosition().y);

		position.x = currTile->GetPosition().x * Width;
		position.y = currTile->GetPosition().y * Height;
	}
	else {
		position.x = 0;
		position.y = 0;
	}

	collider.w = Width;
	collider.h = Height;

	moveDir = RIGHT;
	nextDir = RIGHT;

	ghostTexture = texture;
}

Ghost::~Ghost()
{
	Free();
}

void Ghost::Update()
{
	Pacman* pacman = tileGraph->GetPacman();

	if (pacman != NULL && !(pacman->isWon)) {

		if (currTile == nextTile) {
			// Djikstra algorithm
			Djikstra_Search searchTile(tileGraph);
			searchTile.SetAvoidFunction(Ghost::isNoWall);
			path = searchTile.CalculateRoute(currTile, pacman->GetTile());

			
			try {
				nextTile = path[1];
				//throw 1;
			}
			catch (std::exception &e) {
				std::cout << "exception: " << e.what() << std::endl;
			}


			if (position.x < nextTile->GetPosition().x * Tile::Width)
				moveDir = RIGHT;

			else if (position.x > nextTile->GetPosition().x* Tile::Width)
				moveDir = LEFT;

			else if (position.y > nextTile->GetPosition().y* Tile::Width)
				moveDir = UP;

			else if (position.y < nextTile->GetPosition().y * Tile::Width)
				moveDir = DOWN;

			for (auto tile : tileGraph->Get_Neighbours(currTile)) {
				if (tile->GetPacman() != NULL && CheckForCollision(tile->GetPacman()->GetCollider())) {
					tile->GetPacman()->Delete();
					//pacman->isLost = true;
				}
			}
		}

		//MOvement of ghost
		switch (moveDir)
		{
		case UP:
			position.y = std::max(position.y - Velocity, nextTile->GetPosition().y * Tile::Height);
			break;
		case DOWN:
			position.y = std::min(position.y + Velocity, nextTile->GetPosition().y * Tile::Height);
			break;
		case LEFT:
			position.x = std::max(position.x - Velocity, nextTile->GetPosition().x * Tile::Width);
			break;
		case RIGHT:
			position.x = std::min(position.x + Velocity, nextTile->GetPosition().x * Tile::Width);
			break;
		}

		// collider
		collider.x = position.x;
		collider.y = position.y;
		
		if ((moveDir == DOWN || moveDir == UP) && position.y == nextTile->GetPosition().y * Tile::Height)
			SetTile(nextTile);

		if ((moveDir == LEFT || moveDir == RIGHT) && position.x == nextTile->GetPosition().x * Tile::Width)
			SetTile(nextTile);
	}

}

void Ghost::Render()
{
	ghostTexture->Render(position.x, position.y);
}

void Ghost::SetTile(Tile* newTile)
{
	if (currTile != NULL)
		currTile->SetPacman(NULL);

	currTile = newTile;

	if (currTile != NULL) {
		currTile->SetGhost(this);

		position.x = currTile->GetPosition().x * Tile::Width;
		position.y = currTile->GetPosition().y * Tile::Height;
	}
}

void Ghost::SetNextTile(Tile* newNextTile)
{
	nextTile = newNextTile;
}

bool Ghost::CheckForCollision(const SDL_Rect& otherCollider)
{
	if (otherCollider.x > collider.x + collider.w) {
		return false;
	}

	if (otherCollider.y > collider.y + collider.h) {
		return false;
	}

	if (otherCollider.x + otherCollider.w < collider.x) {
		return false;
	}

	if (otherCollider.y + otherCollider.h < collider.y) {
		return false;
	}

	return true;
}

bool Ghost::CheckForCollision(const SDL_Rect& collider, const SDL_Rect& otherCollider)
{
	if (otherCollider.x > collider.x + collider.w) {
		return false;
	}

	if (otherCollider.y > collider.y + collider.h) {
		return false;
	}

	if (otherCollider.x + otherCollider.w < collider.x) {
		return false;
	}

	if (otherCollider.y + otherCollider.h < collider.y) {
		return false;
	}

	return true;
}


bool Ghost::isNoWall(Tile* tile)
{
	if (tile->GetWall() != NULL) return true;

	return false;
}

void Ghost::Delete()
{
	GameObject::Delete();

}


SDL_Rect Ghost::GetCollider()
{
	return collider;
}

SDL_Point Ghost::GetPosition()
{
	return position;
}

Tile* Ghost::GetTile()
{
	return currTile;
}

Tile* Ghost::GetNextTile()
{
	return nextTile;
}
