#pragma once

namespace ge {
	class Handle
	{
	private:
		long id;
	public:
		Handle(long id)
			: id{ id }
		{}

		long getID() const { return id; }
	};
}
