#include "stdafx.h"
#include "CppUnitTest.h"
#include "datetime.h"
#include "dipendente.h"
#include "dipendenterepository.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace date;

namespace TestDipendenteRepository
{
	TEST_CLASS(TestRepositoryDipendente)
	{
		TEST_METHOD(AggiungiDipendente)
		{
			Dipendente dip("Gianni", "Barbagianni");
			DipendenteRepository repo;
			repo.add(dip);

			Assert::IsTrue(dip.get_id() == 18);
		}
		

	};
}