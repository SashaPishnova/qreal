#include "endOfLoopBlock.h"

using namespace qReal;
using namespace interpreters::robots::details::blocks;

EndOfLoopBlock::EndOfLoopBlock()
{
}

void EndOfLoopBlock::run()
{
	emit done(mNextBlock);
}

bool EndOfLoopBlock::initNextBlocks()
{
	updateLoopData();

	if (!mLoopBeginning.first) {
		error(tr("No beginning of the loop found, please add this block to a diagram"));
		return false;
	}

	IdList const links = mGraphicalModelApi->graphicalRepoApi().outgoingLinks(id());

	if (links.count() > 1) {
		error(tr("Too many outgoing links"));
		return false;
	}

	if (links.count() == 0) {
		error(tr("No outgoing links, please connect this block to something or use Final Node to end program"));
		return false;
	}
\
	bool lastRun = mLoopBeginning.second;
	if (!lastRun) {
		mNextBlock = mLoopBeginning.first;
		return true;
	}

	if (links.count() == 1) {
		Id const targetBlockId = mGraphicalModelApi->graphicalRepoApi().otherEntityFromLink(links[0], id());
		if (targetBlockId == Id()) {
			error(tr("Outgoing link is not connected"));
			return false;
		}
		mNextBlock = mBlocksTable->block(targetBlockId);
		emit loopDone();
	}

	return true;
}

void EndOfLoopBlock::updateLoopData()
{
	emit updateData();
}

void EndOfLoopBlock::loopBeginning(Block * const block, const bool lastRun)
{
	mLoopBeginning.first = block;
	mLoopBeginning.second = lastRun;
}

