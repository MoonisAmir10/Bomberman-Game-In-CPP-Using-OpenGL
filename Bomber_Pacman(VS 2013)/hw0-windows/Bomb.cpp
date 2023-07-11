#include "Bomb.h"

void Bomb::Draw(float sx, float sy, float radius)
{
	DrawCircle(sx, sy, radius, colors[getColor()]);
}

void Bomb::updateTimer()
{
	if (getStatus() == true)
	{
		m_time++;
	}
}

void Bomb::explode(Board& pb, float bm_xpos, float bm_ypos, bool& flag)
{
	if (getStatus() == true)
	{
		if (m_time == 4) //bomb will explode after 4 seconds
		{
			setStatus(false);

			setIsPlaced(false);

			m_time = 0;

			checkWall(pb);

			checkBombermanCollision(bm_xpos, bm_ypos, pb, flag);

			setXpos(0);
			setYpos(0);
		}
	}

}

void Bomb::setIsPlaced(bool isp)
{
	m_isPlaced = isp;
}

bool Bomb::getIsPlaced()
{
	return m_isPlaced;
}

bool Bomb::checkWall(Board& pb, int key)
{
	int checkX = (getXpos() + pb.GetCellSize() / 2) / pb.GetCellSize();
	int checkY = (getYpos() + pb.GetCellSize() / 2) / pb.GetCellSize();

	int temp_checkX = 0, temp_checkY = 0;

	//checking block upwards of bomb
	if (pb.GetInitBlockPosition(checkX, 12 - checkY) == R_BRICK || pb.GetInitBlockPosition(checkX, 12 - checkY) == G_BRICK)
	{
		if (pb.GetInitBlockPosition(checkX, 12 - checkY) == R_BRICK)
		{
			temp_checkX = checkX;
			temp_checkY = checkY + 1;

			checkCascadedWall(pb, temp_checkX, temp_checkY);
		}

		pb.SetInitBlockColor(checkX, 12 - checkY, NILL);
	}

	//checking block downwards of bomb
	if (pb.GetInitBlockPosition(checkX, 14 - checkY) == R_BRICK || pb.GetInitBlockPosition(checkX, 14 - checkY) == G_BRICK)
	{
		if (pb.GetInitBlockPosition(checkX, 14 - checkY) == R_BRICK)
		{
			temp_checkX = checkX;
			temp_checkY = checkY - 1;

			checkCascadedWall(pb, temp_checkX, temp_checkY);
		}

		pb.SetInitBlockColor(checkX, 14 - checkY, NILL);
	}

	//checking block right of bomb
	if (pb.GetInitBlockPosition(checkX + 1, 13 - checkY) == R_BRICK || pb.GetInitBlockPosition(checkX + 1, 13 - checkY) == G_BRICK)
	{
		if (pb.GetInitBlockPosition(checkX + 1, 13 - checkY) == R_BRICK)
		{
			temp_checkX = checkX + 1;
			temp_checkY = checkY;

			checkCascadedWall(pb, temp_checkX, temp_checkY);
		}

		pb.SetInitBlockColor(checkX + 1, 13 - checkY, NILL);
	}

	//checking block left of bomb
	if (pb.GetInitBlockPosition(checkX - 1, 13 - checkY) == R_BRICK || pb.GetInitBlockPosition(checkX - 1, 13 - checkY) == G_BRICK)
	{
		if (pb.GetInitBlockPosition(checkX - 1, 13 - checkY) == R_BRICK)
		{
			temp_checkX = checkX - 1;
			temp_checkY = checkY;

			checkCascadedWall(pb, temp_checkX, temp_checkY);
		}

		pb.SetInitBlockColor(checkX - 1, 13 - checkY, NILL);
	}

	return true;
}

void Bomb::checkCascadedWall(Board& pb, int temp_checkX, int temp_checkY)
{
	//checking block upwards of red block
	if (pb.GetInitBlockPosition(temp_checkX, 12 - temp_checkY) == R_BRICK || pb.GetInitBlockPosition(temp_checkX, 12 - temp_checkY) == G_BRICK)
	{
		pb.SetInitBlockColor(temp_checkX, 12 - temp_checkY, NILL);
	}

	//checking block downwards of red block
	if (pb.GetInitBlockPosition(temp_checkX, 14 - temp_checkY) == R_BRICK || pb.GetInitBlockPosition(temp_checkX, 14 - temp_checkY) == G_BRICK)
	{
		pb.SetInitBlockColor(temp_checkX, 14 - temp_checkY, NILL);
	}

	//checking block right of red block
	if (pb.GetInitBlockPosition(temp_checkX + 1, 13 - temp_checkY) == R_BRICK || pb.GetInitBlockPosition(temp_checkX + 1, 13 - temp_checkY) == G_BRICK)
	{
		pb.SetInitBlockColor(temp_checkX + 1, 13 - temp_checkY, NILL);
	}

	//checking block left of red block
	if (pb.GetInitBlockPosition(temp_checkX - 1, 13 - temp_checkY) == R_BRICK || pb.GetInitBlockPosition(temp_checkX - 1, 13 - temp_checkY) == G_BRICK)
	{
		pb.SetInitBlockColor(temp_checkX - 1, 13 - temp_checkY, NILL);
	}
}

void Bomb::checkBombermanCollision(float bm_xpos, float bm_ypos, Board& pb, bool& flag)
{
	//checking right and left of bomb
	if ((getXpos() + 1.5 * pb.GetCellSize() >= bm_xpos) && (bm_xpos >= getXpos() - 1.5*pb.GetCellSize()))
		if (bm_ypos <= getYpos() + 0.5*pb.GetCellSize() && (bm_ypos >= getYpos() - 0.5*pb.GetCellSize()))
	{
		cout << "Bomberman Killed Horizontally" << endl;

		flag = true;
	}

	//checking up and down of bomb
	else if ((getYpos() + 1.5 * pb.GetCellSize() >= bm_ypos) && (bm_ypos >= getYpos() - 1.5 * pb.GetCellSize()))
	{
			if (bm_xpos <= getXpos() + 0.5 * pb.GetCellSize() && (bm_xpos >= getXpos() - 0.5 * pb.GetCellSize()))
			{
				cout << "Bomberman Killed Vertically" << endl;

				flag = true;
			}
	}
}