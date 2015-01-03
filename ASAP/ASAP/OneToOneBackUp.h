#pragma once
#include "DataBackUp.h"

namespace ASAP {
	ref class OneToOneBackUp : public DataBackUp
	{
		public:
			OneToOneBackUp(JobStruct^ job);
			void StartBackUp(void) override;

		private:
			String^ GetTagetLocation();
	};
}