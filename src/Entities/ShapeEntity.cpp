#include "ShapeEntity.hh"
#include "TimeManager.hh"
#include <math.h>

ShapeEntity::ShapeEntity(std::list<BlockEntity *> blockList, int level)
{
    this->_blockList = blockList;
    SetDirection(90);

    double speed = base_shape_speed + (level * speed_increase);
    SetSpeed(speed);
    this->_slowSpeed = speed;
    SetMoving(false);
}

int ShapeEntity::GetSize() const
{
    return this->_size;
}
void ShapeEntity::SetSize(int size)
{
    this->_size = size;
}

void ShapeEntity::Draw(sf::RenderWindow *window)
{
    std::list<BlockEntity *>::iterator it;
    for (it = this->_blockList.begin(); it != this->_blockList.end(); ++it)
    {
        (*it)->Draw(window);
    }
};

void ShapeEntity::Update()
{
    if (GetMoving())
        UpdatePosition();
};

void ShapeEntity::UpdatePosition()
{
    double seconds = TimeManager::GetInstance()->GetElapsedTime() / 100.0;
    TranslateY(((this->_speed * -1) / seconds));
}

void ShapeEntity::TranslateX(double x)
{
    if (GetMoving())
    {
        MoveX(x);
    }
}

void ShapeEntity::MoveX(double x)
{
    this->_x = this->_x + x;
    for (auto block : this->_blockList)
    {
        sf::RectangleShape rect = block->GetBlock();
        rect.setPosition(rect.getPosition().x - x, rect.getPosition().y);
        block->SetBlock(rect);
    }
}

void ShapeEntity::TranslateY(double y)
{
    if (GetMoving())
    {
        this->_y = this->_y + y;
        for (auto block : this->_blockList)
        {
            sf::RectangleShape rect = block->GetBlock();
            rect.setPosition(rect.getPosition().x, rect.getPosition().y - y);
            block->SetBlock(rect);
        }
    }
}

void ShapeEntity::SetX(double x)
{
    TranslateX(this->_x - x);
    this->_x = x;
}

void ShapeEntity::SetY(double y)
{
    TranslateY(this->_y - y);
    this->_y = y;
}

void ShapeEntity::SetPosition(sf::Vector2f pos)
{
    SetX(pos.x);
    SetY(pos.y);
}

std::list<BlockEntity *> ShapeEntity::GetBlockList() const
{
    return this->_blockList;
}

void ShapeEntity::RemoveBlock(BlockEntity *entity)
{
    this->_blockList.remove(entity);
}

void ShapeEntity::TurnBlocks(bool revert)
{
    for (auto block : this->_blockList)
    {
        block->Turn(this->_currentRotation, revert);
    }
}

void ShapeEntity::Turn()
{
    if (GetMoving())
    {
        this->_lastRotation = this->_currentRotation;
        if (this->_currentRotation == (BLOCK_NUMBER_PER_SHAPE - 1))
        {
            this->_currentRotation = 0;
        }
        else
        {
            this->_currentRotation += 1;
        }

        TurnBlocks(false);
    }
}

int GetPrevRotation(int current) {
    if (current == 0)
    {
        current = (BLOCK_NUMBER_PER_SHAPE - 1);
    }
    else
    {
        current -= 1;
    }

    return current;
}

void ShapeEntity::RevertTurn()
{
    if (GetMoving())
    {
        TurnBlocks(true);
        this->_currentRotation = GetPrevRotation(this->_currentRotation);
        this->_lastRotation = GetPrevRotation(this->_currentRotation);
    }
}

void ShapeEntity::SetPreview(bool isPreview)
{
    this->_isPreview = isPreview;
}

bool ShapeEntity::isPreview() const
{
    return this->_isPreview;
}

void ShapeEntity::NotifyAllObservers()
{
    std::list<IObserver *>::iterator it;
    for (it = this->_observers.begin(); it != this->_observers.end(); ++it)
    {
        (*it)->Notify(this);
    }
}

void ShapeEntity::AddObserver(IObserver *observer)
{
    this->_observers.push_front(observer);
};

void ShapeEntity::RemoveObserver(IObserver *observer)
{
    this->_observers.remove(observer);
};

void ShapeEntity::Freeze()
{
    SetMoving(false);
    NotifyAllObservers();
};

double ShapeEntity::GetSlowSpeed() const {
    return this->_slowSpeed;
}

void ShapeEntity::SetSlowSpeed(double speed) {
    this->_slowSpeed = speed;
}
