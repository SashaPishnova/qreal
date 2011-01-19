#pragma once

#include <QtCore/QHash>

#include "../../../kernel/ids.h"
#include "../../../models/graphicalModelAssistApi.h"
#include "../../../models/logicalModelAssistApi.h"

namespace qReal {
namespace interpreters {
namespace robots {
namespace details {

namespace blocks {
class Block;
}

class BlocksTable
{
public:
	BlocksTable(models::GraphicalModelAssistApi const &graphicalModelApi
			, models::LogicalModelAssistApi const &logicalModelApi
	);
	~BlocksTable();
	blocks::Block *block(Id const &element);
	void clear();

private:
	QHash<Id, blocks::Block *> mBlocks;  // Has ownership

	models::GraphicalModelAssistApi const &mGraphicalModelApi;
	models::LogicalModelAssistApi const &mLogicalModelApi;
};

}
}
}
}
