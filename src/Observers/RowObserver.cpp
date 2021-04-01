#include "RowObserver.hh"

RowObserver::RowObserver(PlayableArea *area,
                         std::list<AbstractEntity *> entities)
{
    this->_area = area;
    this->_entities = entities;
};

std::vector<BlockEntity *> GetAllBlocks(std::list<AbstractEntity *> entities)
{
    std::vector<BlockEntity *> blocks;
    for (const auto &entity : entities)
    {
        auto shape = dynamic_cast<ShapeEntity *>(entity);
        if (shape != nullptr)
        {
            if (!shape->isPreview())
            {
                std::list<BlockEntity *>::iterator listIter;
                std::list<BlockEntity *> blockList = shape->GetBlockList();
                for (listIter = blockList.begin(); listIter != blockList.end(); ++listIter)
                {
                    blocks.push_back(*listIter);
                }
            }
        }
    }

    return blocks;
}

void DeleteBlock(std::list<AbstractEntity *> entities, BlockEntity *block)
{
    for (const auto &entity : entities)
    {
        auto shape = dynamic_cast<ShapeEntity *>(entity);
        if (shape != nullptr)
        {
            if (!shape->isPreview())
            {
                shape->RemoveBlock(block);
            }
        }
    }
}

void DeleteBlocks(std::list<AbstractEntity *> entities, std::vector<BlockEntity *> blocks)
{
    std::vector<BlockEntity *>::iterator it;
    for (it = blocks.begin(); it != blocks.end(); it++)
    {
        DeleteBlock(entities, *it);
    }
}


void RowObserver::MakeShapesFall(double lowCoord) {
    std::list<AbstractEntity *>::iterator it;
    for (it = this->_entities.begin(); it != this->_entities.end(); it++)
    {
        auto shape = dynamic_cast<ShapeEntity *>(*it);
        if (shape != nullptr)
        {
            if (!shape->isPreview()) {
                for (auto block : shape->GetBlockList())
                {
                    sf::RectangleShape rect = block->GetBlock();
                    if (rect.getPosition().y < lowCoord) {
                        rect.setPosition(rect.getPosition().x, rect.getPosition().y + this->_area->GetGridSize());
                        block->SetBlock(rect);
                    }
                }
            }
        }
    }
}

void RowObserver::DeleteFullRow(std::vector<BlockEntity *> blocks)
{
    int currentRow = 1;
    int rowValue = -1;
    int maxBlocks = this->_area->GetMaxBlocks();
    int deletedRows = 0;
    std::vector<BlockEntity *> toDelete;
    std::vector<BlockEntity *>::iterator vecIt;

    for (vecIt = blocks.begin(); vecIt != blocks.end(); vecIt++)
    {
        sf::RectangleShape shape = (*vecIt)->GetBlock();
        int y = shape.getPosition().y;
        if (y > (rowValue - maxBlocks) && y < (rowValue + maxBlocks))
        {
            toDelete.push_back(*vecIt);
            currentRow++;
        }
        else
        {
            toDelete.clear();
            currentRow = 1;
            rowValue = y;
            toDelete.push_back(*vecIt);
        }

        if (currentRow >= ROW_SIZE)
        {
            DeleteBlocks(this->_entities, toDelete);
            MakeShapesFall(y);
            deletedRows++;
        }
    }

    this->_area->AddRowsScore(deletedRows);
}

void RowObserver::Notify(IObservable *observable)
{
    /* Removes row */
    (void)observable;
    std::list<AbstractEntity *> entities = this->_entities;
    if ((entities.size() * BLOCK_NUMBER_PER_SHAPE) >= ROW_SIZE)
    {
        std::vector<BlockEntity *> blocks = GetAllBlocks(entities);

        std::sort(blocks.begin(), blocks.end(), [](BlockEntity *a, BlockEntity *b) {
            sf::RectangleShape aBlock = a->GetBlock();
            sf::RectangleShape bBlock = b->GetBlock();

            return aBlock.getPosition().y < bBlock.getPosition().y;
        });

        DeleteFullRow(blocks);
    }
};