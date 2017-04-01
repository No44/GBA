#ifndef _MMU_H_
#define _MMU_H_

#include <vector>

namespace GBA
{

    namespace Memory
    {

        class MMU
        {
        public:





        private:
            // Returns a pointer to physical memory corresponding to the input virtual address
            uint8_t* memAccess_(uint32_t virtualAddr);

            std::vector<uint8_t> memory_;
        };

    }

}


#endif
