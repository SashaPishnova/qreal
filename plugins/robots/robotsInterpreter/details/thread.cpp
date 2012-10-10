#include "thread.h"

using namespace qReal;
using namespace interpreters::robots;
using namespace interpreters::robots::details;

Thread::Thread(gui::MainWindowInterpretersInterface &interpretersInterface, BlocksTable &blocksTable
		, Id const &initialNode)
	: mInterpretersInterface(interpretersInterface)
	, mCurrentBlock(NULL)
	, mBlocksTable(blocksTable)
{
	mCurrentBlock = blocksTable.block(initialNode);
}

Thread::~Thread()
{
	if (mCurrentBlock) {
		mInterpretersInterface.dehighlight(mCurrentBlock->id());
	}
}

void Thread::interpret()
{
	nextBlock(mCurrentBlock);
}

void Thread::nextBlock(blocks::Block * const block)
{
	// This is a signal not from a current block of this thread.
	// Other thread shall process it, we will just ignore.
	if (sender() && sender() != mCurrentBlock) {
		return;
	}

	if (sender()) {
		sender()->disconnect(this);
	}

	mInterpretersInterface.dehighlight(mCurrentBlock->id());

	mCurrentBlock = block;
	if (!mCurrentBlock) {
		emit stopped();
		return;
	}

	mInterpretersInterface.highlight(mCurrentBlock->id(), false);
	connect(mCurrentBlock, SIGNAL(done(blocks::Block * const)), this, SLOT(nextBlock(blocks::Block * const)));
	connect(mCurrentBlock, SIGNAL(newThread(details::blocks::Block * const)), this, SIGNAL(newThread(details::blocks::Block*const)));
	connect(mCurrentBlock, SIGNAL(failure()), this, SLOT(failure()));
	connect(mCurrentBlock, SIGNAL(loopBeginningRun(bool const)), this, SLOT(loopBeginningRun(bool const)));
	connect(mCurrentBlock, SIGNAL(loopDone()), this, SLOT(loopDone()));
	connect(mCurrentBlock, SIGNAL(updateData()), this, SLOT(updateData()));
	mCurrentBlock->interpret();
}

void Thread::failure()
{
	emit stopped();
}

void Thread::loopBeginningRun(bool const lastRun)
{
	if (lastRun) {
		mLoopBeginnings.first() = qMakePair(mCurrentBlock, lastRun);
	} else {
		mLoopBeginnings.prepend(qMakePair(mCurrentBlock, lastRun));
	}
}

void Thread::loopDone()
{
	if (!mLoopBeginnings.isEmpty()) {
		mLoopBeginnings.removeFirst();
	}
}

void Thread::updateData()
{
	if (!mLoopBeginnings.isEmpty()) {
		mCurrentBlock->loopBeginning(mLoopBeginnings.first().first, mLoopBeginnings.first().second);
	}
}

void Thread::setLoopsDone()
{
	while (!mLoopBeginnings.isEmpty()) {
		blocks::Block * block = mLoopBeginnings.first().first;
		block->setLoopDone();
		mLoopBeginnings.removeFirst();
	}
}
