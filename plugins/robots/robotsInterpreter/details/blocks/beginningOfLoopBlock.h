#include <QtCore/QObject>
#include <QtCore/QTimer>

#include "block.h"
#include "../robotParts/robotModel.h"

namespace qReal {
namespace interpreters {
namespace robots {
namespace details {
namespace blocks {

class BeginningOfLoopBlock : public Block
{
	Q_OBJECT

public:
	BeginningOfLoopBlock();
	virtual void run();
};
}
}
}
}
}
