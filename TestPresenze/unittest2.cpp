#include "stdafx.h"
#include "CppUnitTest.h"
#include "datetime.h"
#include "dipendente.h"
#include "repositorydipendente.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace date;

namespace TestDipendenteRepository
{
	TEST_CLASS(TestRepositoryDipendente)
	{
		TEST_METHOD(AggiungiDipendente)
		{
			RepositoryDipendente repo;
			Dipendente dip = repo.add("Gianni", "Barbagianni");

			Assert::IsTrue(dip.get_nome() == "Gianni");
		}
		

	};
}