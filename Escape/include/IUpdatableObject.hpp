#ifndef UPDATABLEOBJECT_HPP
#define UPDATABLEOBJECT_HPP

namespace esc
{
	class IUpdatableObject 
	{
		public: virtual void update(float) = 0;
	};
}
#endif
