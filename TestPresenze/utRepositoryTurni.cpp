#include "stdafx.h"
#include "CppUnitTest.h"
#include "repositorypresenze.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace date;

namespace TestRepositoryTurni
{
	TEST_CLASS(TestRepositoryPresenze)
	{
		TEST_METHOD(AggiungiPresenza)
		{
			RepositoryPresenze repo;
			Presenza p = repo.add(1, date::datetime(26, 4, 2016, 10, 0, 0), date::datetime(26, 4, 2016, 18, 0, 0), "cassa");
			Assert::IsTrue(p.get_id() > 0);
		}


	};
}