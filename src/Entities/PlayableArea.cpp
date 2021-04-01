#include "PlayableArea.hh"
#include "../env.hh"

sf::Vector2f GetRightSize(double x, double y)
{
    double xGridSize = (double)x / ROW_SIZE;
    double yGridSize = (double)y / COLUMN_SIZE;

    if (xGridSize != yGridSize)
    {
        double divider = 1.0;

        if (xGridSize < yGridSize)
        {
            divider = xGridSize / yGridSize;
            return sf::Vector2f(x, (y * divider));
        }
        else
        {
            divider = yGridSize / xGridSize;
            return sf::Vector2f((x * divider), y);
        }
    }

    return sf::Vector2f(x, y);
}

PlayableArea::PlayableArea(sf::RenderWindow *window)
{
    double xSize = window->getSize().x * LEFT_PLAYABLE_RATIO;
    double ySize = window->getSize().y * TOP_PLAYABLE_RATIO;
    sf::Vector2f sizes = GetRightSize(xSize, ySize);

    SetGridSize(sizes.x / ROW_SIZE);

    double xPos = (window->getSize().x - sizes.x) - GetGridSize();
    double yPos = window->getSize().y - sizes.y;

    // auto borderColor = sf::Color(255, 255, 255);
    sf::RectangleShape rect;
    rect.setFillColor(DARK_GREY);
    // rect.setOutlineThickness(2);
    // rect.setOutlineColor(borderColor);
    rect.setSize(sizes);
    rect.setPosition(xPos, yPos);

    SetArea(rect);
    this->_basePos = sf::Vector2f((GetArea().getSize().x / 2) + (4 * GetGridSize()), yPos); // TODO Setter
}

PlayableArea::~PlayableArea() {}

sf::RectangleShape PlayableArea::GetArea() const
{
    return this->_area;
}

sf::Vector2f PlayableArea::GetBasePos() const
{
    return this->_basePos;
}

void PlayableArea::SetArea(sf::RectangleShape area)
{
    this->_area = area;
}

int PlayableArea::GetGridSize() const
{
    return this->_gridSize;
}

void PlayableArea::SetGridSize(int gridSize)
{
    this->_gridSize = gridSize;
}

int PlayableArea::GetMaxBlocks() const
{
    sf::RectangleShape area = GetArea();
    return area.getSize().y / GetGridSize();
}

double PlayableArea::GetClosestSnap(double yCoord) const
{
    double ySize = GetArea().getSize().y + GetArea().getPosition().y;
    yCoord = -yCoord;

    double divider = (double)GetGridSize();
    double pastValue;
    double currentValue = divider;
    if (yCoord >= ySize)
        return -ySize;

    while (currentValue < ySize)
    {
        pastValue = currentValue;
        currentValue += divider;

        if (pastValue <= yCoord && currentValue >= yCoord)
        {
            if ((yCoord - pastValue) <= (currentValue - yCoord))
            {
                return -pastValue;
            }

            return -currentValue;
        }
    }

    return -yCoord;
}

int PlayableArea::GetScore() const {
    return this->_score;
};

void PlayableArea::SetScore(int score) {
    this->_score = score;
};

void PlayableArea::AddScore(int scoreToAdd) {
    this->_score += scoreToAdd;
};

void PlayableArea::AddRowsScore(int rowsDeleted) {
    switch (rowsDeleted) {
        case 1:
            AddScore(40);
            break;
        case 2:
            AddScore(100);
           break;
        case 3:
            AddScore(300);
            break;
        case 4:
            AddScore(1200);
            break;
    }
};
