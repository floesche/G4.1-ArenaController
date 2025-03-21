//.$file${./ArenaControlle~::Region.cpp} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//
// Model: ArenaController.qm
// File:  ${./ArenaControlle~::Region.cpp}
//
// This code has been generated by QM 5.1.3 <www.state-machine.com/qm/>.
// DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
//
// This program is open source software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.
//
//.$endhead${./ArenaControlle~::Region.cpp} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#include "Region.hpp"


using namespace QP;

// helper function to provide the ID of this mine ............................
static inline uint8_t REGION_ID(AC::Region const * const me) {
    return static_cast<uint8_t>(me - &AC::Region::instances[0]);
}

//============================================================================
//.$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//. Check for the minimum required QP version
#if (QP_VERSION < 690U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpcpp version 6.9.0 or higher required
#endif
//.$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//.$define${Shared::getRegionInstance} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
namespace AC {

//.${Shared::getRegionInstance} ..............................................
QP::QHsm * getRegionInstance(std::uint8_t id) {
    //Q_REQUIRE(id < Q_DIM(Region::instances));
    return &Region::instances[id];
}

} // namespace AC
//.$enddef${Shared::getRegionInstance} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//============================================================================
// generate definition of the AO
//.$define${AOs::Region} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
namespace AC {

//.${AOs::Region} ............................................................
Region Region::instances[constants::region_count_per_frame_max];
//.${AOs::Region::SM} ........................................................
Q_STATE_DEF(Region, initial) {
    //.${AOs::Region::SM::initial}

    QS_FUN_DICTIONARY(&Region::state1);

    return tran(&state1);
}
//.${AOs::Region::SM::state1} ................................................
Q_STATE_DEF(Region, state1) {
    QP::QState status_;
    switch (e->sig) {
        default: {
            status_ = super(&top);
            break;
        }
    }
    return status_;
}

} // namespace AC
//.$enddef${AOs::Region} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
