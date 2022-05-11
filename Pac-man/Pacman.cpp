#include "Pacman.h"
using namespace std;

Pacman::Pacman(Tile* tile, Texture* texture)
{
	// Set all variables to default state
	currTile = tile;
	nextTile = NULL;

	if (currTile != NULL) {
		currTile->SetPacman(this);

		position.x = currTile->GetPosition().x * Width;
		position.y = currTile->GetPosition().y * Height;
	}
	else {
		position.x = 0;
		position.y = 0;
	}

	collider.w = Width;
	collider.h = Height;

	moveDir = LEFT;
	nextDir = LEFT;

	pacmanTexture = texture;
	isWon = false;
	isLost = false;
	score = 0;

}

Pacman::~Pacman()
{
	Free();
}


void Pacman::SetTile(Tile* newTile)
{
	if (currTile != NULL)
		currTile->SetPacman(NULL);

	currTile = newTile;

	if (currTile != NULL) {
		currTile->SetPacman(this);

		position.x = currTile->GetPosition().x * Tile::Width;
		position.y = currTile->GetPosition().y * Tile::Height;
	}
}

void Pacman::SetNextTile(Tile* newNextTile)
{
	nextTile = newNextTile;
}

void Pacman::HandleEvents(SDL_Event* event)
{
	
	if (event->type == SDL_KEYDOWN && event->key.repeat == 0) {
		switch (event->key.keysym.sym)
		{
			// Move up
		case SDLK_UP:
		case SDLK_w: nextDir = UP; break;

			// Move down
		case SDLK_DOWN:
		case SDLK_s: nextDir = DOWN; break;

			// Move left
		case SDLK_LEFT:
		case SDLK_a: nextDir = LEFT; break;

			// Move right
		case SDLK_RIGHT:
		case SDLK_d: nextDir = RIGHT; break;
		}
	}
}


bool Pacman::isMoveable(Direction direction)
{
	Tile* destTile = NULL;

	switch (direction)
	{
	case UP:
		destTile = tileGraph->GetTileAt(currTile->GetPosition().x, currTile->GetPosition().y - 1);
		break;
	case DOWN:
		destTile = tileGraph->GetTileAt(currTile->GetPosition().x, currTile->GetPosition().y + 1);
		break;
	case LEFT:
		destTile = tileGraph->GetTileAt(currTile->GetPosition().x - 1, currTile->GetPosition().y);
		break;
	case RIGHT:
		destTile = tileGraph->GetTileAt(currTile->GetPosition().x + 1, currTile->GetPosition().y);
		break;
	}


	if (destTile == NULL) {
		SetNextTile(NULL);
		return false;
	}

	// confronting wall
	if (destTile->GetWall() != NULL) {
		SetNextTile(NULL);
		return false;
	}

	SetNextTile(destTile);

	return true;
}

bool Pacman::CheckForCollision(const SDL_Rect& otherCollider)
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

bool Pacman::CheckForCollision(const SDL_Rect& collider, const SDL_Rect& otherCollider)
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

void Pacman::Update()
{
	if (currTile != NULL && currTile->GetPoint() != NULL) {
		SDL_Rect food = {
			position.x + Point::Margin,
			position.y + Point::Margin,
			Point::Width,
			Point::Height,
		};

		if (CheckForCollision(food, nextTile->GetPoint()->GetCollider())) {
			nextTile->GetPoint()->Delete();
			score += 50;
			Point* point = GameObject::tileGraph->GetPoint();
			if (point == NULL)
				isWon = true;
		}
	}

	if (!isWon) {
		// Change of tile/movement
		if (nextTile == currTile || nextTile == NULL) {
			if (nextDir != moveDir && isMoveable(nextDir))
				moveDir = nextDir;
			else
				isMoveable(moveDir);

		}
		else {
			switch (moveDir)
			{
			case UP:
				position.y = max(position.y - Velocity, nextTile->GetPosition().y * Tile::Height);
				break;
			case DOWN:
				position.y = min(position.y + Velocity, nextTile->GetPosition().y * Tile::Height);
				break;
			case LEFT:
				position.x = max(position.x - Velocity, nextTile->GetPosition().x * Tile::Width);
				break;
			case RIGHT:
				position.x = min(position.x + Velocity, nextTile->GetPosition().x * Tile::Width);
				break;
			}

			collider.x = position.x;
			collider.y = position.y;

			if ((moveDir == DOWN || moveDir == UP) && position.y == nextTile->GetPosition().y * Tile::Height)
				SetTile(nextTile);

			if ((moveDir == LEFT || moveDir == RIGHT) && position.x == nextTile->GetPosition().x * Tile::Width)
				SetTile(nextTile);
		}
	}
}

void Pacman::Render()
{
	pacmanTexture->Render(position.x, position.y);
}

void Pacman::Delete()
{
	// Calling the base function
	GameObject::Delete();

	currTile->SetPacman(NULL);
}



Direction Pacman::GetMoveDirection()
{
	return moveDir;
}

SDL_Rect Pacman::GetCollider()
{
	return collider;
}

SDL_Point Pacman::GetPosition()
{
	return position;
}

Tile* Pacman::GetTile()
{
	return currTile;
}

Tile* Pacman::GetNextTile()
{
	return nextTile;
}
