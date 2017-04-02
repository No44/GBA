#include "stdafx.h"
#include "CppUnitTest.h"

#include "MMU.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{

    TEST_CLASS(MMUTest)
    {
    public:

        using MMU = GBA::Memory::MMU;

        TEST_METHOD(TestReadWrite)
        {
            MMU mmu;

            mmu.write<_32>(0x44, 0xFF00FF00);
            auto actual = mmu.read<_32>(0x44);

            Assert::AreEqual(0xFF00FF00, actual);
        }

    };

}