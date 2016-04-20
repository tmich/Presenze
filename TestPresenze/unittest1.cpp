#include "stdafx.h"
#include "CppUnitTest.h"
#include "datetime.h"
#include "dipendente.h"
#include "pianificazione.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace date;

namespace TestPresenze
{		
	TEST_CLASS(UnitTestDipendente)
	{
	public:
		
		TEST_METHOD(TestCostruzione)
		{
			Dipendente dip("Tiziano", "Michelessi");
			Assert::AreEqual(dip.get_nome(), string("Tiziano"));
			Assert::AreEqual(dip.get_cognome(), string("Michelessi"));
		}

	};

	TEST_CLASS(UnitTestAssenza)
	{
	public:
		TEST_METHOD(TestCostruzione)
		{
			Assenza ass1("ferie estive");
			Assert::AreEqual(ass1.get_motivazione(), string("ferie estive"));	
		}

		TEST_METHOD(TestPianifica)
		{
			Dipendente mario("Mario", "Rossi");
			mario.set_id(18);
			Assenza ass1("permesso");
			ass1.pianifica(mario.get_id(), datetime(30, 5, 2016, 10, 0, 0), datetime(30, 5, 2016, 12, 0, 0));
			Assert::AreEqual(DipendenteId(18), ass1.get_id_dipendente());
		}

		TEST_METHOD(NonPuoiPianificareConFinePrecedenteInizio)
		{
			Dipendente mario("Gino", "Bianchi");
			mario.set_id(19);
			Assenza ass1("malattia");
			try
			{
				ass1.pianifica(mario.get_id(), datetime(30, 5, 2016), datetime(29, 5, 2016));
				Assert::Fail(L"non doveva arrivare qui...");
			}
			catch (const std::invalid_argument&)
			{
				//OK
			}
			catch (const std::exception&)
			{
				throw;
			}
		}
	};
}