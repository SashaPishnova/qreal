#include "beginningOfLoopBlock.h"

using namespace qReal;
using namespace interpreters::robots::details::blocks;

BeginningOfLoopBlock::BeginningOfLoopBlock()
	: mIterations(0)
	, mLoopDone(true)
{
}

void BeginningOfLoopBlock::run()
{
	if (mLoopDone) {
		mLoopDone = false;
		additionalInit();
		emit loopBeginningRun(mLoopDone);
	}

	--mIterations;
	if (mIterations <= 0) {
		mLoopDone = true;
		emit loopBeginningRun(mLoopDone);
	}

	emit done(mNextBlock);
}

void BeginningOfLoopBlock::additionalInit()
{
	mIterations = evaluate("Iterations").toInt();
	if (mIterations <= 0) {
		error(tr("In the Beginning of Loop Block not a positive number of iterations is selected.Please, enter a positive number"));
	}
}
